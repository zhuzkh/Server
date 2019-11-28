#include "NetProxy.h"
#include "AsioSocket.h"
#include "MemoryPool.h"
#include "SystemConfig.h"
#include "Logger.h"
#include "PerfStatistics.h"

NetProxy::NetProxy(io_context& service) : m_service(service), m_acceptor(service)
{

}

bool NetProxy::Initlize()
{
	int32_t port = SystemConfig::GetInstance().GetConf().network.listen_port;
	if (!m_acceptor.Initilize("127.0.0.1", port))
	{
		LOG_INFO("acceptor initilize err {}", "lalala");
		return false;
	}
	m_acceptor.RegisterAcceptFunc(std::bind(&NetProxy::OnAccept, this, std::placeholders::_1, std::placeholders::_2));
	m_acceptor.AsyncAccept();
	LOG_INFO("acceptor start");

	if (!m_receive_queue.Init(MESSAGE_CIRULAR_QUEUE_LENGTH))
	{
		return false;
	}
	if (m_send_queue.Init(MESSAGE_CIRULAR_QUEUE_LENGTH))
	{
		return false;
	}
	return true;
}

void NetProxy::SendMsg()
{
	bool ret;
	size_t nCodeLength;
	for (int i = 0; i < MAX_HANDLE_MSG_COUNT_ONCE; i++)
	{
		nCodeLength = (size_t)MSG_MAX_LEN;
		ret = m_send_queue.Pop(m_send_temp_buffer, nCodeLength);
		if (!ret)
			break;

		if (nCodeLength <= 0)
			break;
		DoSendMsg();
	}
}

void NetProxy::DoSendMsg()
{
	MsgHeader header;
	memmove(&header, m_send_temp_buffer, MSG_HEADER_LEN);
	std::map<int32_t, std::shared_ptr<AsioSocket>>::iterator it = m_client_socket_map.find(header.player_id);
	if (it == m_client_socket_map.end())
	{
		return;
	}
	if (!it->second)
	{
		return;
	}
	it->second->AsyncWrite(m_send_temp_buffer + MSG_HEADER_LEN, header.length - MSG_HEADER_LEN);
}

void NetProxy::OnReceive(std::shared_ptr<AsioSocket> socket, system::error_code err, std::size_t bytes, MsgBufferBase* buffer)
{
	if (!socket)
	{
		return;
	}

	if (err)
	{
		LOG_ERROR(err.message());
		if (bytes == 0)
		{
			SocketClose(socket);
			//通知逻辑线程掉线
			//m_receive_queue.Append(buffer->p_data, bytes + MSG_HEADER_LEN);
			return;
		}
	}
	else
	{
		m_receive_queue.Append(buffer->p_data, bytes + MSG_HEADER_LEN);
		socket->AsyncReadHeader();
	}
}

void NetProxy::OnSend(std::shared_ptr<AsioSocket> socket, system::error_code err)
{
	if (!socket)
	{
		return;
	}
	if (err)
	{
		SocketClose(socket);
		//通知逻辑线程掉线
		//m_receive_queue.Append(buffer->p_data, bytes + MSG_HEADER_LEN);
	}
}
void NetProxy::OnAccept(system::error_code err, ip::tcp::socket& socket)
{
	int socket_id = MakeSocketId();
	std::shared_ptr<AsioSocket> asioSocket = std::make_shared<AsioSocket>(socket_id, std::move(socket));
	if (!asioSocket)
	{
		return;
	}
	asioSocket->REGISTER_READ_FUNC(&NetProxy::OnReceive, this);
	//asioSocket->RegisterReadFunc(std::bind(&NetProxy::OnReceive, &NetProxy::GetInstance(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
//   	asioSocket->RegisterWriteFunc(std::bind(&NetProxy::OnSend, &NetProxy::GetInstance(), std::placeholders::_1, std::placeholders::_2));

	m_client_socket_map[socket_id] = asioSocket;

	asioSocket->AsyncReadHeader();
}

void NetProxy::OnConnect(std::shared_ptr<AsioSocket> pSocket, system::error_code err)
{
	int socket_id = MakeSocketId();
	if (err)
	{
		LOG_ERROR(err.message());
		return;
	}
	if (!pSocket)
	{
		return;
	}
	m_server_socket_map[socket_id] = pSocket;
}

void NetProxy::SocketClose(std::shared_ptr<AsioSocket> socket)
{
	socket->Close();
	if (m_client_socket_map.find(socket->GetId()) != m_client_socket_map.end())
	{
		m_client_socket_map.erase(socket->GetId());
	}
}

int32_t NetProxy::MakeSocketId()
{
	static int32_t socket_id = 0;
	return ++socket_id;
}

MessageCirularQueue& NetProxy::GetSendQueue()
{
	return m_send_queue;
}

MessageCirularQueue& NetProxy::GetReceiveQueue()
{
	return m_receive_queue;
}

void NetProxy::Run()
{
	while (true)
	{
		Update();
#ifdef WIN32
		Sleep(1);
#else
		usleep(500);
#endif
	}
}

void NetProxy::Update()
{
	m_service.poll_one();
	SendMsg();
	PrintPerfStatistic();
}

void NetProxy::PrintPerfStatistic()
{
	static time_t last_time = time(0);
	time_t now_time = time(0);
	if (now_time - last_time >= 5)
	{
		LOG_INFO("receive bytes : {}", PerfStatistics::GetInstance().GetNetReceiveBytes());
		LOG_INFO("send bytes : {}", PerfStatistics::GetInstance().GetNetSendBytes());
		LOG_INFO("receive count : {}", PerfStatistics::GetInstance().GetNetReceiveCount());
		LOG_INFO("send count : {}", PerfStatistics::GetInstance().GetNetSendCount());

		PerfStatistics::GetInstance().Reset();
		last_time = now_time;
	}
}

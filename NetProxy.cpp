#include "NetProxy.h"
#include "AsioSocket.h"
bool NetProxy::Initlize()
{
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

void NetProxy::Update()
{
	while (true)
	{
		ReceiveMsg();
		SendMsg();
		Sleep(10);
	}
}

void NetProxy::OnProcessMsg()
{

}

void NetProxy::ReceiveMsg()
{
	bool ret;
	size_t nCodeLength;
	for (int i = 0; i < MAX_HANDL_MSG_COUNT_ONCE; i++)
	{
		nCodeLength = (size_t)MAX_MSG_LEN;
		ret = m_receive_queue.Pop(m_recive_temp_buf, nCodeLength);
		if (!ret)
			break;

		if (nCodeLength <= 0)
			break;

		OnProcessMsg();
	}
}

void NetProxy::SendMsg()
{
	bool ret;
	size_t nCodeLength;
	for (int i = 0; i < MAX_HANDL_MSG_COUNT_ONCE; i++)
	{
		nCodeLength = (size_t)MAX_MSG_LEN;
		ret = m_send_queue.Pop(m_send_temp_buf, nCodeLength);
		if (!ret)
			break;

		if (nCodeLength <= 0)
			break;

	}
}

void NetProxy::OnReceive(AsioSocket* socket, system::error_code err, std::size_t bytes, MemoryObj<MsgData>* buffer)
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
			socket->Close();
			if (m_client_socket_map.find(socket->GetId()) != m_client_socket_map.end())
			{
				m_client_socket_map.erase(socket->GetId());
			}
			delete socket;
			return;
		}
	}
	LOG_INFO("receive client echo : {}, buffer size {}", bytes, strlen(buffer->GetData<0>().body));
	buffer->Recycle();
	socket->AsyncReadHeader();
}

void NetProxy::OnSend(AsioSocket* socket, system::error_code err, std::size_t bytes)
{
	if (!socket)
	{
		return;
	}
}
void NetProxy::OnAccept(system::error_code err, ip::tcp::socket& socket)
{
	int socket_id = MakeSocketId();
	AsioSocket* asioSocket = new AsioSocket(socket_id, std::move(socket));
	if (!asioSocket)
	{
		return;
	}
	asioSocket->RegisterReadFunc(std::bind(&NetProxy::OnReceive, &NetProxy::GetInstance(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_client_socket_map[socket_id] = asioSocket;
	asioSocket->AsyncReadHeader();
}

void NetProxy::OnConnect(AsioSocket* pSocket, system::error_code err)
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

char* NetProxy::GetReceiveBuff()
{
	return m_recive_temp_buf;
}

char* NetProxy::GetSendBuff()
{
	return m_send_temp_buf;
}

int32_t NetProxy::MakeSocketId()
{
	static int32_t socket_id = 0;
	return ++socket_id;
}

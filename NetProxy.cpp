#include "NetProxy.h"
#include "AsioSocket.h"
#include "MemoryPool.h"
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
		Sleep(10);
	}
}

void NetProxy::OnProcessMsg()
{
	MsgHeader header;
	char body[256] = { 0 };
	memmove(&header, m_recive_temp_buffer, MSG_HEADER_LEN);
	memmove(body, m_recive_temp_buffer + MSG_HEADER_LEN, header.length - MSG_HEADER_LEN);
	
	m_send_queue.Append(m_recive_temp_buffer, header.length);
// 	LOG_INFO("receive : {}", body);
}

void NetProxy::ReceiveMsg()
{
	bool ret;
	size_t nCodeLength;
	for (int i = 0; i < MAX_HANDL_MSG_COUNT_ONCE; i++)
	{
		nCodeLength = (size_t)MSG_MAX_LEN;
		ret = m_receive_queue.Pop(m_recive_temp_buffer, nCodeLength);
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
	char body[256] = { 0 };
	memmove(&header, m_send_temp_buffer, MSG_HEADER_LEN);
	memmove(body, m_send_temp_buffer + MSG_HEADER_LEN, header.length - MSG_HEADER_LEN);
	std::map<int32_t, AsioSocket*>::iterator it = m_client_socket_map.find(header.player_id);
	if (it == m_client_socket_map.end())
	{
		return;
	}
	if (!it->second)
	{
		return;
	}
	it->second->AsyncWrite(body);
}

void NetProxy::OnReceive(AsioSocket* socket, system::error_code err, std::size_t bytes, MsgBufferBase* buffer)
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
			return;
		}
	}
	else
	{
		m_receive_queue.Append(buffer->p_data, bytes + MSG_HEADER_LEN);
		socket->AsyncReadHeader();
	}
}

void NetProxy::OnSend(AsioSocket* socket, system::error_code err)
{
	if (!socket)
	{
		return;
	}
	if (err)
	{
		SocketClose(socket);
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
//   	asioSocket->RegisterWriteFunc(std::bind(&NetProxy::OnSend, &NetProxy::GetInstance(), std::placeholders::_1, std::placeholders::_2));

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

void NetProxy::SocketClose(AsioSocket* socket)
{
	socket->Close();
	if (m_client_socket_map.find(socket->GetId()) != m_client_socket_map.end())
	{
		m_client_socket_map.erase(socket->GetId());
	}
	delete socket;
}

int32_t NetProxy::MakeSocketId()
{
	static int32_t socket_id = 0;
	return ++socket_id;
}

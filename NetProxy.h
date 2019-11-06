#pragma once
#include "Singleton.h"
#include "MessageCirularQueue.h"
#include "MsgDefing.h"
#include <iostream>
#include "boost/asio.hpp"
#include "MemoryPool.h"
#define MESSAGE_CIRULAR_QUEUE_LENGTH			0x5000000
#define MAX_HANDL_MSG_COUNT_ONCE				512
using namespace boost::asio;
using namespace boost;
class AsioSocket;
class NetProxy : public Singleton<NetProxy>
{
public:
	bool Initlize();
	void Update();
	void OnProcessMsg();
	void ReceiveMsg();
	//////////////////////////////////////////////////////////////////////////
	//网络线程调用
	void SendMsg();
	void DoSendMsg();
	void OnSend(std::shared_ptr<AsioSocket> socket, system::error_code err);

	void OnReceive(std::shared_ptr<AsioSocket> socket, system::error_code err, std::size_t bytes, MsgBufferBase* buffer);
	void OnAccept(system::error_code err, ip::tcp::socket& socket);
	void OnConnect(std::shared_ptr<AsioSocket> socket, system::error_code err);
	void SocketClose(std::shared_ptr<AsioSocket> socket);
	int32_t MakeSocketId();
	//////////////////////////////////////////////////////////////////////////
private:
	char m_send_temp_buffer[MSG_MAX_LEN];
	char m_recive_temp_buffer[MSG_MAX_LEN];

	MessageCirularQueue m_send_queue;
	MessageCirularQueue m_receive_queue;
	
	std::map<int32_t, std::shared_ptr<AsioSocket>> m_client_socket_map;
	std::map<int32_t, std::shared_ptr<AsioSocket>> m_server_socket_map;
};

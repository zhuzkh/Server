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
using namespace boost::system;
class AsioSocket;
class NetProxy : public Singleton<NetProxy>
{
public:
	bool Initlize();
	void Update();
	void OnProcessMsg();
	void ReceiveMsg();
	void SendMsg();
	void OnReceive(AsioSocket* socket, error_code err, std::size_t bytes, MSG_DATA* buffer);
	void OnSend(AsioSocket* socket, error_code err, std::size_t bytes);
	void OnAccept(error_code err, ip::tcp::socket& socket);
	void OnConnect(AsioSocket* socket, error_code err);
	char* GetReceiveBuff();
	char* GetSendBuff();

	int32_t MakeSocketId();
private:
	char m_send_temp_buf[MAX_MSG_LEN];
	char m_recive_temp_buf[MAX_MSG_LEN];

	MessageCirularQueue m_send_queue;
	MessageCirularQueue m_receive_queue;
	
	std::map<int32_t, AsioSocket*> m_client_socket_map;
	std::map<int32_t, AsioSocket*> m_server_socket_map;
};

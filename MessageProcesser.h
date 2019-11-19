#pragma once
#include "Singleton.h"
#include "MessageCirularQueue.h"
#include "MsgDefing.h"
#include <map>

class MessageProcessor : public Singleton<MessageProcessor>
{
public:
	MessageProcessor(MessageCirularQueue& send_queue, MessageCirularQueue& receive_queue);
	bool Initlize();
	void Update();
	void OnProcessMsg();
	void ReceiveMsg();

	void SendMsg2Client(int32_t player_id, char* buf, int32_t length);
public:
	void OnCSMsgTest(int32_t player_id, char* buf, int32_t length);
private:
	char m_send_temp_buffer[MSG_MAX_LEN];
	char m_recive_temp_buffer[MSG_MAX_LEN];

	MessageCirularQueue& m_send_queue;
	MessageCirularQueue& m_receive_queue;

	std::map<int32_t, std::function<void(int32_t, char*, int32_t)>> m_message_handler_map;
};

/*#define REGISTER_CS_MESSAGE(id, func) */
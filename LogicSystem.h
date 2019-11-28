#pragma once
#include "Singleton.h"
#include "MessageProcessor.h"

class LogicSystem : public Singleton<LogicSystem>
{
public:
	LogicSystem(MessageCirularQueue& send_queue, MessageCirularQueue& receive_queue);
	bool Initilize();
	void Run();
private:
	void Update();
private:
	MessageProcessor m_msg_processor;
};

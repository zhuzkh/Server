#include "LogicSystem.h"
#include <synchapi.h>

LogicSystem::LogicSystem(MessageCirularQueue& send_queue, MessageCirularQueue& receive_queue) : 
	m_msg_processor(send_queue, receive_queue)
{
	m_msg_processor.Initlize();
}

bool LogicSystem::Initilize()
{
	return true;
}

void LogicSystem::Run()
{
	while (true)
	{
		Update();
		Sleep(1);
	}
}

void LogicSystem::Update()
{
	m_msg_processor.Update();
}

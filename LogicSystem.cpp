#include "LogicSystem.h"
#include "TimeHelper.h"
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
#ifdef WIN32
		Sleep(1);
#else
		usleep(500);
#endif // WIN32
	}
}

void LogicSystem::Update()
{
	m_msg_processor.Update();
}
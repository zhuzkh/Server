#include "NetProxy.h"
#include "AsioAcceptor.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/async.h"
#include <chrono>
#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "MemoryPool.h"
#include "TimeHelper.h"
#include "signal.h"
#include <string>
#include "TimerManager.h"
#include "MemoryPoolManager.h"
#include <memory>
#include "StringHelper.h"
void Release()
{
	TimerManager::GetInstance().Release();
	MemoryPoolMgr::GetInstance().Release();
}

void ReceiveThread()
{

}

void SendThread()
{

}

void TimerCallBack(int i, int j)
{
	std::cout<<i<<std::endl;
}


template<typename ...Args>
std::function<void()> make_my_closure(std::function<void(Args...)> func)
{
	return [=]() mutable {
		func(Args...);
	};
}

int main(int argc, char* argv[])
{
	Logger::GetInstance().Initlize("logger", "..\\log\\test.log");
	NetProxy::GetInstance().Initlize();
	std::thread work_thread([]() { NetProxy::GetInstance().Update(); });
	io_context service;
	AsioAcceptor acceptor(service);

	REGISTER_NORMAL_TIMER(1, std::bind(&TimerCallBack, 1, 2));
	TimerManager::GetInstance().Tick(time(0));

	if (!acceptor.Initilize("127.0.0.1", 8888))
	{
		LOG_INFO("acceptor initilize err {}", "lalala");
	}
	else
	{
		acceptor.RegisterAcceptFunc(std::bind(&NetProxy::OnAccept, &NetProxy::GetInstance(), std::placeholders::_1, std::placeholders::_2));
		LOG_INFO("acceptor start");
		acceptor.AsyncAccept();
	}
	while (true)
	{
		service.poll_one();
		NetProxy::GetInstance().SendMsg();
		Sleep(1);
	}
	//service.run();
	
	Release();		
	::system("pause");
	return 1;
}
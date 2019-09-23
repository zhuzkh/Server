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
void Release()
{
	TimerManager::GetInstance().Release();
	MemoryPoolMgr::GetInstance().Release();
}
void Update()
{

}

int main(int argc, char* argv[])
{
	Logger::GetInstance().Initlize("logger", "..\\log\\test.log");
	NetProxy::GetInstance().Initlize();
	std::thread work_thread([]() { NetProxy::GetInstance().Update(); });
	io_context service;
	AsioAcceptor acceptor(service);
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
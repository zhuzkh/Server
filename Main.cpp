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
#include <map>
#include <unordered_map>
#include "MessageProcesser.h"
#include "PerfStatistics.h"
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

void PrintPerfStatistic()
{
	static time_t last_time = time(0);
	time_t now_time = time(0);
	if (now_time - last_time >= 5)
	{
		LOG_INFO("receive bytes : {}", PerfStatistics::GetInstance().GetNetReceiveBytes());
		LOG_INFO("send bytes : {}", PerfStatistics::GetInstance().GetNetSendBytes());
		LOG_INFO("receive count : {}", PerfStatistics::GetInstance().GetNetReceiveCount());
		LOG_INFO("send count : {}", PerfStatistics::GetInstance().GetNetSendCount());

		PerfStatistics::GetInstance().Reset();
		last_time = now_time;
	}
}

int main(int argc, char* argv[])
{
	Logger::GetInstance().Initlize("logger", "..\\log\\test.log");
 	
	NetProxy::GetInstance().Initlize();
	MessageProcessor msg_processor(NetProxy::GetInstance().GetSendQueue(), NetProxy::GetInstance().GetReceiveQueue());
	msg_processor.Initlize();
 	std::thread work_thread([&msg_processor]() { msg_processor.Update(); });
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
		time_t now_time = time(0);
 		service.poll_one();
 		NetProxy::GetInstance().SendMsg();

		PrintPerfStatistic();

 		Sleep(1);
 	}
 	//service.run();
 	
 	Release();		
 	::system("pause");
	return 1;
}
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
#include "MessageProcessor.h"
#include "PerfStatistics.h"
#include "SystemConfig.h"
#include "LogicSystem.h"
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
const std::string system_config_path = "../config/config.json";

void NetworkThreadRun(io_context& service, NetProxy& net_proxy)
{
	while (true)
	{
		service.poll_one();
		net_proxy.SendMsg();

		PrintPerfStatistic();

		Sleep(1);
	}
}

int main(int argc, char* argv[])
{
	SystemConfig::GetInstance().Initlize(system_config_path);
	Logger::GetInstance().Initlize("logger", SystemConfig::GetInstance().GetConf().logger.path);
 	
	io_context service;
	NetProxy net_proxy(service);
	net_proxy.Initlize();
	LogicSystem game_logic(net_proxy.GetSendQueue(), net_proxy.GetReceiveQueue());

	std::thread network_thread([&service, &net_proxy]() {NetworkThreadRun(service, net_proxy); });
	game_logic.Run();
 	//service.run();
 	
 	Release();		
 	::system("pause");
	return 1;
}
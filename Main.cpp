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

const std::string system_config_path = "../config/config.json";

void Release()
{
	TimerManager::GetInstance().Release();
	MemoryPoolMgr::GetInstance().Release();
}

int main(int argc, char* argv[])
{
	SystemConfig::GetInstance().Initlize(system_config_path);
	Logger::GetInstance().Initlize("logger", SystemConfig::GetInstance().GetConf().logger.path);
 	
	io_context service;
 	NetProxy* net_proxy = new NetProxy(service);
 	net_proxy->Initlize();
 	LogicSystem* game_logic = new LogicSystem(net_proxy->GetSendQueue(), net_proxy->GetReceiveQueue());

  	std::thread network_thread([&net_proxy]() {net_proxy->Run(); });
  	game_logic->Run();
 	//service.run();
 	
 	Release();	
 	delete net_proxy;
	delete game_logic;
 	::system("pause");
	return 1;
}
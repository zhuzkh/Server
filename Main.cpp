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
#include "SharedPtrMemoryPool.h"
#include <memory>
void Func(int a, std::string b)
{
	std::cout << a << '\t' << b << std::endl;
}

class Test : public OneWayListNode<Test>
{
public:
	Test()
	{
		m_test = 1000;
	}
	void Func(int a, int b)
	{
		LOG_DEBUG("time_stamp : {}; id : {}", a, b);
	}
	void Clear()
	{

	}
	int m_test;
};

void TestFunc(int32_t str, int32_t i)
{
	std::cout << str << "\t" << i << "\t" <<std::endl;
}

void AddTimer()
{
	Test test;
	for (size_t i = 1; i <= 10; ++i)
	{
		time_t time = TimeHelper::GetCurTime() + i;
		//TimerManager::GetInstance().RegisterNormalTimer<int>(i, time, std::bind(TestFunc, i, time));
		int id = REGISTER_NORMAL_TIMER(time, std::bind(TestFunc, i, time));
	}
	TimerManager::GetInstance().UnRegisterTimerBatch(0);
	for (size_t i = 11; i <= 20; ++i)
	{
		time_t time = TimeHelper::GetCurTime() + i;
		//TimerManager::GetInstance().RegisterNormalTimer<int>(i, time, std::bind(TestFunc, i, time));
		int id = REGISTER_NORMAL_TIMER(time, std::bind(TestFunc, i, time));
	}
}

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

	std::list<Test*> test_list;
	test_list.push_back(new Test());
	std::vector<Test*> vec;
	vec.push_back(new Test());
	MemoryPool<Test>::GetInstance().Resize(100000);
	Test* test_array[100000];
	TIME_DEBUG_START
	for (size_t i = 0; i != 100000; ++i)
	{
//		std::unique_ptr<Test> tmp = std::make_unique<Test>();
//		test_list.back();
//		Test* tmp = *test_list.begin();
//		std::shared_ptr<Test> tmp = std::make_shared<Test>();
//		std::shared_ptr<Test> tmp = GET_SHARED_PTR(Test);
		test_array[i] = GET_MEMORY_PTR(Test);
		//test_array[i] = new Test();
	}
	for (size_t i = 0; i != 100000; ++i)
	{
		RECYCLE_MEMORY_PTR(Test, test_array[i]);

//		delete test_array[i];
	}
	TIME_DEBUG_CUR
	MemoryPool<Test>::GetInstance().Release();
// 	MemoryObj<MsgData>* obj = MemoryPool<MsgData>::GetInstance().GetObj();
// 	obj->Recycle();
	//TIME_DEBUG_START
	//	AddTimer();
	//TIME_DEBUG_CUR
	//	while (true)
	//	{
	//		TimerManager::GetInstance().Tick(TimeHelper::GetCurTime());
	//	}

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
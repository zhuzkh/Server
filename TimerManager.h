#pragma once
#include "TimerWheel.h"
#include "TimeHelper.h"
#include "MemoryPool.h"
#include <set>
#include <unordered_map>

enum class eTimerType
{
	Unknow = 0,
	Normal,		//指定时间
	Cycle,		//一定时间间隔循环
};

//时间节点
class TimerNode : public ListNode<TimerNode>
{
public:
	TimerNode()
	{
		Clear();
	}
	void Init(int32_t id, time_t time, eTimerType type, uint32_t interval_time, time_t end_time, uint32_t cycle_count)
	{
		this->id = id;
		this->time_stamp = time;
		this->type = type;
		this->cycle_count = cycle_count;
		this->end_time_stamp = end_time;
		this->interval_time = interval_time;
	}
	void Clear()
	{
		id = 0;
		time_stamp = 0;
		cycle_count = 0;
		end_time_stamp = 0;
		interval_time = 0;
		type = eTimerType::Unknow;
	}
	virtual bool CallBack() = 0;
	virtual void Recycle() = 0;
	int32_t id;
	uint32_t cycle_count;
	uint32_t interval_time;
	time_t time_stamp;
	time_t end_time_stamp;
	eTimerType type;
};

class TimerNodeImpl : public TimerNode
{
public:
	bool CallBack()
	{
		return func();
	}
	void Recycle()
	{
		RECYCLE_MEMORY_PTR(TimerNodeImpl, this);
	}
	std::function<bool()> func;
};


/************************************************************************/
/* 定时器管理
/************************************************************************/
class TimerManager : public Singleton<TimerManager>
{
private:
	TimerManager();
	~TimerManager();
	friend Singleton<TimerManager>;
public:
	template <typename T>
	int32_t RegisterTimer(time_t time, T func)
	{
		TimerNodeImpl* node = GET_MEMORY_PTR(TimerNodeImpl);
		if (!node)
		{
			return 0;
		}
		node->func = [=] { return func(); };
		int32_t timer_id = ++m_max_id;
		node->Init(timer_id, time, eTimerType::Normal, 0, 0, 0);
		m_time_wheel.Push(node);
		return timer_id;
	}

	template <typename T>
	int32_t RegisterCycleTimer(time_t time, uint32_t interval_time, T func, time_t end_time = 0, uint32_t count = 0xffffffff)
	{
		TimerNodeImpl* node = GET_MEMORY_PTR(TimerNodeImpl);
		if (!node)
		{
			return 0;
		}
		node->func = [=] {func(); };
		int32_t timer_id = ++m_max_id;
		node->Init(timer_id, time, eTimerType::Cycle, interval_time, end_time, count);
		m_time_wheel.Push(node);
		return timer_id;
	}

	//删除计时器
	void UnRegisterTimer(int32_t timer_id);
	void Release();

	//tick
	void Tick(time_t now_time);
private:
	void recycle(TimerNode* node);

private:
	TimerWheel<TimerNode> m_time_wheel;
	int32_t m_max_id;
};

//根据时间戳定时，只调用一次
#define REGISTER_NORMAL_TIMER(time, func) TimerManager::GetInstance().RegisterTimer(time, func)
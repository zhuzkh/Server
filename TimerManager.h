#pragma once
#include "TimerWheel.h"
#include "TimeHelper.h"
#include "MemoryPool.h"
#include <set>
#include <unordered_map>

namespace eTimerType
{
	enum e
	{
		Unknow = 0,
		Normal,		//指定时间
		DayCircle,	//每一天
		WeekCircle,	//每一周
	};
}

//时间节点
class TimerNode : public ListNode<TimerNode>
{
public:
	void init(int64_t owner_id, int32_t id, time_t time, eTimerType::e type)
	{
		this->owner_id = owner_id;
		this->id = id;
		this->time_stamp = time;
		this->type = type;
	}
	void Clear()
	{
		id = 0;
		time_stamp = 0;
		type = eTimerType::Unknow;
	}
	virtual void CallBack() = 0;
	virtual void Recycle() = 0;
	int64_t owner_id;
	int32_t id;
	time_t time_stamp;
	eTimerType::e type;
};

class TimerNodeImpl : public TimerNode
{
public:
	void CallBack()
	{
		func();
	}
	void Recycle()
	{
		RECYCLE_MEMORY_PTR(TimerNodeImpl, this);
	}
	std::function<void()> func;
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
	int32_t RegisterTimer(int64_t owner_id, time_t time, std::function<void()> func)
	{
		TimerNodeImpl* node = GET_MEMORY_PTR(TimerNodeImpl);
		if (!node)
		{
			return 0;
		}
 		node->func = func;
		int32_t timer_id = ++m_max_id;
		node->init(owner_id, timer_id, time, eTimerType::Normal);
		m_time_wheel.Push(node);
		return timer_id;
	}

	//删除计时器
	void UnRegisterTimerBatch(int64_t owner_id);
	void UnRegisterTimer(int32_t timer_id);
	void Release();

	//tick
	void Tick(time_t now = 0);
private:
	void recycle(TimerNode* node);

private:
	TimerWheel<TimerNode> m_time_wheel;
	std::unordered_map<int64_t, std::set<int32_t>> m_timer_map;
	int32_t m_max_id;
};

//根据时间戳定时，只调用一次
#define REGISTER_NORMAL_TIMER(time, func) TimerManager::GetInstance().RegisterTimer(0, time, [=](){func();})
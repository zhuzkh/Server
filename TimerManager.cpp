#include "TimerManager.h"
#include "TimeHelper.h"

TimerManager::TimerManager() : m_max_id(0)
{
	m_time_wheel.Init(TimeHelper::GetCurTime());
}


TimerManager::~TimerManager()
{
}

void TimerManager::Release()
{
	std::unordered_map<int32_t, TimerNode*>& node_map = m_time_wheel.GetAllNode();
	for (auto& data : node_map)
	{
		UnRegisterTimer(data.first);
	}
	m_timer_map.clear();
}

void TimerManager::recycle(TimerNode* node)
{
	if (node)
	{
		node->Recycle();
	}
}

void TimerManager::UnRegisterTimer(int32_t timer_id)
{
	TimerNode* node = m_time_wheel.PopAndErase(timer_id);
	recycle(node);
}

void TimerManager::UnRegisterTimerBatch(int64_t owner_id)
{
	if (m_timer_map.find(owner_id) == m_timer_map.end())
	{
		return;
	}
	for (auto& data : m_timer_map[owner_id])
	{
		UnRegisterTimer(data);
	}
}

void TimerManager::Tick(time_t now)
{
	TimerNode* TmpNode = nullptr;
	TimerNode* node = m_time_wheel.PopAll(now);
	while (node)
	{
		node->CallBack();
		LOG_DEBUG("timer stamp : {}; id : {}", now, node->id);
		TmpNode = node->next;
		switch (node->type)
		{
		case eTimerType::DayCircle:
			node->time_stamp += TimeHelper::ONE_DAY_SECOND;
			m_time_wheel.Push(node);
			break;
		case eTimerType::WeekCircle:
			node->time_stamp += TimeHelper::ONE_WEEK_SECOND;
			m_time_wheel.Push(node);
			break;
		case eTimerType::Normal:
			recycle(node);
			break;
		default:
			break;
		}
		node = TmpNode;
	}
}


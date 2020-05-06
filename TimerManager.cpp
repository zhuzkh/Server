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
	while (!node_map.empty())
	{
		std::unordered_map<int32_t, TimerNode*>::iterator it = node_map.begin();
		if (it != node_map.end())
		{
			UnRegisterTimer(it->first);
		}
	}
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

void TimerManager::Tick(time_t now_time)
{
	TimerNode* TmpNode = nullptr;
	TimerNode* node = m_time_wheel.PopAll(now_time);
	while (node)
	{
		bool b_cycle = node->CallBack();
		TmpNode = node->next;
		switch (node->type)
		{
		case eTimerType::Normal:
			recycle(node);
			break;
		case eTimerType::Cycle:
			if (b_cycle)
			{
				node->cycle_count--;
				if (node->cycle_count == 0)
				{
					recycle(node);
					break;
				}
				node->time_stamp += node->interval_time;
				if (node->end_time_stamp != 0 && node->time_stamp > node->end_time_stamp)
				{
					recycle(node);
					break;
				}
				m_time_wheel.Push(node);
			}
			else
			{
				recycle(node);
			}
			break;
		default:
			break;
		}
		node = TmpNode;
	}
}


#pragma once
#include <map>
#include "Logger.h"
#include "TimeHelper.h"
using namespace std;

template<class T>
class ListNode
{
public:
	T* prev;
	T* next;
	void* wheel;

	ListNode()
	{
		prev = next = nullptr;
		wheel = nullptr;
	}

	virtual ~ListNode(){}
};

template<class T>
class WheelList
{
public:
	WheelList()
	{
		head = nullptr;
		m_count = 0;
	}
public:
	void Push(T* node)
	{
		node->wheel = this;
		if(!head)
		{
			head = node;
			node->prev = node;
			node->next = node;
		}
		else
		{
			head->prev->next = node;
			node->prev = head->prev;
			node->next = head;
			head->prev = node;
		}
		++m_count;
	}
	T* PopAll()
	{
		T* tmpHead = head;
		if(head)
		{
			head->prev->next = nullptr;
		}
		head = nullptr;
		m_count = 0;
		return tmpHead;
	}
	T* Pop()
	{
		T* tmpHead = head;
		if(head)
		{
			if(head == head->next)
			{
				head = nullptr;
			}
			else
			{
				head = head->next;
			}
			PopNode(tmpHead);
		}
		return tmpHead;
	}
	void Erase(T* obj)
	{
		if(head == obj)
		{
			if(head == head->next)
			{
				head = nullptr;
			}
			else
			{
				head = head->next;
			}
		}
		PopNode(obj);

	}
	bool HaveNode()
	{
		return head != nullptr;
	}
private:
	void PopNode(T* node)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		node->next = nullptr;
		node->prev = nullptr;
		--m_count;
	}
public:
	T* head;
	int32_t m_count;
};

//4 * 256； 可容纳uint32_t长度的时间戳
const int32_t WHEEL_CNT = 4;
const int32_t WHEEL_INDEX = WHEEL_CNT - 1;
const int32_t WHEEL_PER_CNT = 0x100;
#define WHEEL_TIMEVALUE(v, i) ((v >> (32 / WHEEL_CNT * i)) & (WHEEL_PER_CNT - 1))

template<class T>
class TimerWheel
{
public:
	TimerWheel()
	{
		m_cur_tick = 0;
		memset(m_wheel_cnt, 0, sizeof(m_wheel_cnt));
	}
	~TimerWheel()
	{
		memset(m_wheel_cnt, 0, sizeof(m_wheel_cnt));
		m_node_map.clear();
	}
	void Init(time_t v)
	{
		m_cur_tick = v - 1;
		for(int32_t i = WHEEL_INDEX; i >= 0; --i)
		{
			m_wheel_cnt[i] = WHEEL_TIMEVALUE(v, i);
		}
	}

	void Push(T* obj)
	{
// 		NodeMapItr_t it = m_node_map.find(obj->id); 
// 		if(it != m_node_map.end())
// 		{
// 			return;
// 		}
		WheelList<T>* pWheel = FindWheel(obj->time_stamp);
		pWheel->Push(obj);

		m_node_map[obj->id] = obj;
	}

	void PushAll(T* obj, int32_t wheel_index)
	{
		if (!obj)
		{
			return;
		}
		T* tmpNOde = obj;
		while(obj)
		{
			tmpNOde = obj->next;
			FindWheel(obj->time_stamp, wheel_index)->Push(obj);
			obj = tmpNOde;
		}
	}

	T* PopAll(time_t time)
	{
		if(time < m_cur_tick)
		{
			SetTick(time);
		}
		T *head = nullptr, *tmpHead = nullptr, *tail = nullptr;
		WheelList<T>* pTmpWheel = nullptr;
		head = m_wheel_before.PopAll();
		if(head)
		{
			tail = head->prev;
			tail->next = nullptr;
		}
		while(m_cur_tick < time)
		{
			pTmpWheel = FindWheel(m_cur_tick + 1);
			if(pTmpWheel->HaveNode())
			{
				tmpHead = pTmpWheel->PopAll();
				if(!head)
				{
					head = tmpHead;
				}
				if(tail)
				{
					tail->next = tmpHead;
				}
				tail = tmpHead->prev;
				tail->next = nullptr;
			}
		
			Tick();
		}
		tmpHead = head;
		while(tmpHead)
		{
			m_node_map.erase(tmpHead->id);
			tmpHead = tmpHead->next;
		}
		return head;
	}

	T* PopAndErase(int32_t id)
	{
		if (m_node_map.find(id) == m_node_map.end())
		{
			return nullptr;
		}
		T* tmpNode = m_node_map[id];
		((WheelList<T>*)tmpNode->wheel)->Erase(tmpNode);
		m_node_map.erase(id);
		return tmpNode;
	}

	std::unordered_map<int32_t, T*>& GetAllNode() 
	{
		return m_node_map;
	}

protected:
	void SetTick(time_t time)
	{
		T *head = nullptr, *tmpHead = nullptr, *tail = nullptr;
		head = m_wheel_before.PopAll();
		if(head)
		{
			tail = head->prev;
			tail->next = nullptr;
		}
		bool bContinue = false;
		for(int32_t i = WHEEL_INDEX; i > 0; --i)
		{
			if(m_wheel_cnt[i] != WHEEL_TIMEVALUE(time, i))
			{
				bContinue = true;
			}
			else if(!bContinue)
			{
				continue;
			}
			for(int32_t j = m_wheel_cnt[i]; j < WHEEL_PER_CNT; ++j)
			{
				if(m_wheel[i - 1][j].HaveNode())
				{
					tmpHead = m_wheel[i - 1][j].PopAll();

					if(!head)
					{
						head = tmpHead;
					}
					if(tail)
					{
						tail->next = tmpHead;
					}
					tail = tmpHead->prev;
					tail->next = nullptr;
				}
			}
		}
		
		Init(time);
		PushAll(head, WHEEL_INDEX);
	}

	WheelList<T>* FindWheel(time_t time, int32_t wheel_index = WHEEL_INDEX)
	{
		if(time < m_cur_tick)
		{
			return &m_wheel_before;
		}
		for(int32_t i = wheel_index; i >= 0; --i)
		{
			int32_t time_value = WHEEL_TIMEVALUE(time, i);
			if(time_value != m_wheel_cnt[i])
			{
				return &m_wheel[i][time_value];
			}
			else if(i == 0)
			{
				return &m_wheel[i][time_value];
			}
		}
		LOG_ERROR("can not find wheel; time stamp : {}", time);
		return nullptr;
	}

	void Tick()
	{
		++m_cur_tick;
		for(int32_t i = 0; i <= WHEEL_INDEX; ++i)
		{
			if(++m_wheel_cnt[i] >= WHEEL_PER_CNT)
			{
				m_wheel_cnt[i] = 0;
			}
			else
			{
				if(i > 0)
				{
					//往前一个wheel插入，无需遍历所有的wheel
					PushAll(m_wheel[i][m_wheel_cnt[i]].PopAll(), i - 1);
				}
				break;
			}
		}
	}
private:
	WheelList<T> m_wheel_before;
	WheelList<T> m_wheel[WHEEL_CNT][WHEEL_PER_CNT]; 
	int32_t m_wheel_cnt[WHEEL_CNT];
	time_t m_cur_tick;

	std::unordered_map<int32_t, T*> m_node_map;
};


template<class T>
class NewTimerWheel
{
private:
	static constexpr int32_t m_wheel_per_cnt = 60 * 1000;
	static constexpr int32_t m_precision = 1;

public:
	NewTimerWheel()
	{
		m_cur_index = 0;
		memset(m_wheel, 0, sizeof(m_wheel));
		m_node_map.clear();
	}
	~NewTimerWheel()
	{
		memset(m_wheel, 0, sizeof(m_wheel));
		m_node_map.clear();
	}
	void Init(int64_t init_time)
	{
		m_cur_index = 0;
		m_init_time = m_cur_time = init_time;
	}

	void Push(T* obj)
	{
		WheelList<T>* pWheel = FindWheel(obj->time_stamp);
		pWheel->Push(obj);

		m_node_map[obj->id] = obj;
	}

	T* PopAll(int64_t time)
	{
		if (time < m_cur_time)
		{
			return nullptr;
		}
		T* head = nullptr, * tmpHead = nullptr, * tail = nullptr;
		WheelList<T>* pTmpWheel;
		head = m_wheel_before.PopAll();
		if (head)
		{
			tail = head->prev;
			tail->next = nullptr;
		}
		while (m_cur_time <= time)
		{
			pTmpWheel = FindWheel(m_cur_time);
			if (pTmpWheel->HaveNode())
			{
				tmpHead = pTmpWheel->PopAll();
				if (!head)
				{
					head = tmpHead;
				}
				if (tail)
				{
					tail->next = tmpHead;
				}
				tail = tmpHead->prev;
				tail->next = nullptr;
			}

			Tick();
		}
		tmpHead = head;
		while (tmpHead)
		{
			m_node_map.erase(tmpHead->id);
			tmpHead = tmpHead->next;
		}
		return head;
	}

	T* PopAndErase(int32_t id)
	{
		if (m_node_map.find(id) == m_node_map.end())
		{
			return nullptr;
		}
		T* tmpNode = m_node_map[id];
		((WheelList<T>*)tmpNode->wheel)->Erase(tmpNode);
		m_node_map.erase(id);
		return tmpNode;
	}

	std::unordered_map<int32_t, T*>& GetAllNode()
	{
		return m_node_map;
	}

protected:
	WheelList<T>* FindWheel(int64_t time)
	{
		if (time < m_cur_time)
		{
			return &m_wheel_before;
		}
		else
		{
			int32_t index = GetIndex(time);
			return &m_wheel[index];
		}
	}

	void Tick()
	{
		++m_cur_index;
		++m_cur_time;
		if (m_cur_index >= m_wheel_per_cnt)
		{
			m_cur_index = 0;
		}
	}

	int32_t GetIndex(int64_t time)
	{
		int64_t time_interval = time - m_cur_time;
		int64_t cur_time_index = m_cur_index;
		int64_t cur_time = TimeHelper::GetCurMsTime();
		if (time >= cur_time)
		{
			time_interval = time - cur_time;
			cur_time_index = cur_time - m_init_time;
			cur_time_index %= m_wheel_per_cnt;
		}

		int64_t index = cur_time_index + time_interval;
		if (index >= m_wheel_per_cnt)
		{
			index = m_wheel_per_cnt - cur_time_index - 1;
		}
		if (index < 0 || index >= m_wheel_per_cnt)
		{
			LOG_ERROR("get index err; index [{}]", index);
			index = cur_time_index;
		}
		return (int32_t)index;
	}

private:
	WheelList<T> m_wheel_before;
	WheelList<T> m_wheel[m_wheel_per_cnt];
	int32_t m_cur_index;
	int64_t m_cur_time;
	int64_t m_init_time;

	std::unordered_map<int32_t, T*> m_node_map;
};
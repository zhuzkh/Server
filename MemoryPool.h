#pragma once
#include <list>
#include <tuple>
#include "Logger.h"
#include "Singleton.h"
#include <vector>
#include <queue>
const int32_t DEFAULT_POOL_SIZE = 100;

template <typename T>
class MemoryPool : public ThreadLocalSingleton<MemoryPool<T>>
{
private:
	friend ThreadLocalSingleton<MemoryPool>;
	MemoryPool() : m_max_size(0), m_header(nullptr), m_tail(nullptr)
	{
		for (; m_max_size < DEFAULT_POOL_SIZE; ++m_max_size)
		{
			CreateObj();
		}
	}

	~MemoryPool()
	{
		Release();
	}
public:
	T* GetObj()
	{
		if (m_header == nullptr)
		{
			ListNode* obj = new ListNode();
			if (!obj)
			{
				LOG_ERROR("create memory obj failed!");
				return nullptr;
			}
			++m_max_size;
			return reinterpret_cast<T*>(obj);
		}
		ListNode* obj = m_header;
		m_header = m_header->next_node;
		if (m_header == nullptr)
		{
			m_tail = nullptr;
		}
		obj->next_node = nullptr;
		return &(obj->data);
		//return reinterpret_cast<T*>(obj);
	}


	void Resize(uint32_t size)
	{
		if (m_max_size >= size)
		{
			return;
		}

		for (; m_max_size < size; ++m_max_size)
		{
			CreateObj();
		}
	}

	void Recycle(void* obj)
	{
		if (!obj)
		{
			return;
		}
		PushBack(obj);
	}

	void Release()
	{
		int32_t size = 0;
		while (m_header)
		{
			ListNode* tmp = m_header;
			m_header = m_header->next_node;
			delete tmp;
			++size;
		}
		m_tail = nullptr;
		if (size != m_max_size)
		{
			LOG_WARN("obj has not recycle completely! max size[{}],recycle size[{}]", m_max_size, size);
		}
		LOG_DEBUG("total malloc size : {}", m_max_size);
	}
private:
	class ListNode
	{
	public:
		ListNode() : next_node(nullptr)
		{}
		T data;
		ListNode* next_node;
	};

	void CreateObj()
	{
		ListNode* obj = new ListNode();
		if (!obj)
		{
			LOG_ERROR("create memory obj failed!");
			return;
		}
		PushBack(obj);
	}
	void PushBack(void* obj)
	{
		ListNode* node = reinterpret_cast<ListNode*>(obj);
		if (m_header == nullptr)
		{
			m_header = node;
			m_header->next_node = nullptr;
			m_tail = m_header;
		}
		else
		{
			node->next_node = nullptr;
			m_tail->next_node = node;
			m_tail = m_tail->next_node;
		}
	}

private:
	uint32_t	m_max_size;
	ListNode*	m_header;
	ListNode*	m_tail;
};


#define GET_MEMORY_PTR(T) MemoryPool<T>::GetInstance().GetObj();
#define RECYCLE_MEMORY_PTR(T, ptr) MemoryPool<T>::GetInstance().Recycle(ptr);
#define RELEASE_MEMORY_POOL(T) MemoryPool<T>::GetInstance().Release();

// class MemoryObjBase
// {
// public:
// 	MemoryObjBase()
// 	{
// 
// 	}
// 	virtual ~MemoryObjBase()
// 	{
// 
// 	}
// 	virtual void Recycle() = 0;
// };
// 
// template <typename ... Args>
// class MemoryObj : public MemoryObjBase
// {
// public:
// 	void Recycle()
// 	{
// 		m_func(this);
// 	}
// 	template <std::size_t size>
// 	auto& GetData()
// 	{
// 		return std::get<size>(m_param);
// 	}
// public:
// 	std::tuple<Args...> m_param;
// 	std::function<void(MemoryObj*)> m_func;
// };
// 
// template <typename ... Args>
// class MemoryPoolMultiParam : public Singleton<MemoryPoolMultiParam<Args...>>, public MemoryPoolBase
// {
// private:
// 	friend Singleton<MemoryPoolMultiParam>;
// 	MemoryPoolMultiParam() : m_max_size(0)
// 	{
// 		for (uint32_t i = 0; i != DEFAULT_POOL_SIZE; ++i)
// 		{
// 			addObj();
// 		}
// 	}
// 
// 	~MemoryPoolMultiParam()
// 	{
// 
// 	}
// public:
// 	MemoryObj<Args...>* GetObj()
// 	{
// 		if (m_object_list.empty())
// 		{
// 			MemoryObj<Args...>* obj = new MemoryObj<Args...>();
// 			if (!obj)
// 			{
// 				LOG_ERROR("create memory obj failed!");
// 				return nullptr;
// 			}
// 			++m_max_size;
// 			obj->m_func = std::bind(&MemoryPoolMultiParam<Args...>::Recycle, this, std::placeholders::_1);
// 			return obj;
// 		}
// 
// 		MemoryObj<Args...>* obj = m_object_list.back();
// 		m_object_list.pop_back();
// 		return obj;
// 	}
// 
// 	void Recycle(MemoryObj<Args...>* obj)
// 	{
// 		if (!obj)
// 		{
// 			return;
// 		}
// 		m_object_list.push_back(obj);
// 	}
// 
// 	void Resize(uint32_t size)
// 	{
// 		if (m_max_size <= size)
// 		{
// 			return;
// 		}
// 		
// 		for (uint32_t i = m_max_size; i <= size; ++i)
// 		{
// 			addObj();
// 		}
// 	}
// 
// 	void Release()
// 	{
// 		if (m_object_list.size() != m_max_size)
// 		{
// 			LOG_WARN("obj has not recycle completely! max size[{}],recycle size[{}]", m_max_size, m_object_list.size());
// 		}
// 		for (auto& data : m_object_list)
// 		{
// 			delete data;
// 			data = nullptr;
// 		}
// 		m_object_list.clear();
// 	}
// private:
// 	void addObj()
// 	{
// 		MemoryObj<Args...>* pObj = new MemoryObj<Args...>();
// 		if (!pObj)
// 		{
// 			LOG_ERROR("create memory obj failed!");
// 			return;
// 		}
// 		m_object_list.push_back(pObj);
// 		++m_max_size;
// 		pObj->m_func = std::bind(&MemoryPoolMultiParam<Args...>::Recycle, this, std::placeholders::_1);
// 	}
// private:
// 	std::list<MemoryObj<Args ...>*> m_object_list;
// 	uint32_t						m_max_size;
// };
// 
// 

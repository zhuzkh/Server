#pragma once
#include <list>
#include <tuple>
#include "Logger.h"
#include "Singleton.h"
#include <vector>
#include "MemoryPoolManager.h"

const int32_t DEFAULT_POOL_SIZE = 10000;

class MemoryPoolBase
{
public:
	MemoryPoolBase()
	{
		MemoryPoolMgr::GetInstance().AddPool(this);
	}
	virtual ~MemoryPoolBase()
	{

	}
};

class MemoryObjBase
{
public:
	MemoryObjBase()
	{

	}
	virtual ~MemoryObjBase()
	{

	}
};

template <typename ... Args>
class MemoryObj : public MemoryObjBase
{
public:
	void Clear()
	{

	}
public:
	std::tuple<Args...> m_param;
};

template <typename ... Args>
class MemoryPoolMultiParam : public Singleton<MemoryPoolMultiParam<Args...>>
{
private:
	friend Singleton<MemoryPoolMultiParam>;
	MemoryPoolMultiParam() : m_max_size(DEFAULT_POOL_SIZE)
	{
		for (uint32_t i = 0; i != m_max_size; ++i)
		{
			MemoryObj<Args...>* pObj = new MemoryObj<Args...>();
			if (!pObj)
			{
				LOG_ERROR("create memory obj failed!");
				break;
			}
			m_object_list.push_back(pObj);
		}
	}

	~MemoryPoolMultiParam()
	{
		for (auto& data : m_object_list)
		{
			delete data;
		}
		m_object_list.clear();
	}
public:
	MemoryObj<Args...>* GetObj()
	{
		if (m_object_list.empty())
		{
			MemoryObj<Args...>* obj = new MemoryObj<Args...>();
			if (!obj)
			{
				LOG_ERROR("create memory obj failed!");
				return nullptr;
			}
			++m_max_size;
			return obj;
		}

		MemoryObj<Args...>* obj = m_object_list.back();
		m_object_list.pop_back();
		obj->Clear();
		return obj;
	}

	void Recycle(MemoryObj<Args...>* obj)
	{
		if (!obj)
		{
			return;
		}
		m_object_list.push_back(obj);
	}
private:
	std::list<MemoryObj<Args ...>*> m_object_list;
	uint32_t						m_max_size;
};

 template <typename T>
 class MemoryPoolSingleParam : public Singleton<MemoryPoolSingleParam<T>>
 {
 private:
 	friend Singleton<MemoryPoolSingleParam>;
	MemoryPoolSingleParam() : m_max_size(DEFAULT_POOL_SIZE)
 	{
 		for (uint32_t i = 0; i != m_max_size; ++i)
 		{
 			T* pObj = new T();
 			if (!pObj)
 			{
 				LOG_ERROR("create memory obj failed!");
 				break;
 			}
 			m_object_list.push_back(pObj);
 		}
 	}

 	~MemoryPoolSingleParam()
 	{
 		for (auto& data : m_object_list)
 		{
 			delete data;
 		}
 		m_object_list.clear();
 	}
 public:
 	T* GetObj()
 	{
 		if (m_object_list.empty())
 		{
 			T* obj = new T();
 			if (!obj)
 			{
 				LOG_ERROR("create memory obj failed!");
 				return nullptr;
 			}
			++m_max_size;
 			return obj;
 		}
 
 		T* obj = m_object_list.back();
 		m_object_list.pop_back();
		obj->Clear();
 		return obj;
 	}
 
 	void Recycle(T* obj)
 	{
 		if (!obj)
 		{
 			return;
 		}
 		m_object_list.push_back(obj);
 	}

 private:
 	std::list<T*>					m_object_list;
 	uint32_t						m_max_size;
 };


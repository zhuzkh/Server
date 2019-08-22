#pragma once

#include <list>
#include <memory>
#include <functional>
#include "Singleton.h"
#include "MemoryPool.h"
template<typename T>
class SharedPtrMemoryPool : public Singleton<SharedPtrMemoryPool<T>>, public MemoryPoolBase 
{
public:
	SharedPtrMemoryPool(){};
	~SharedPtrMemoryPool(){};
public:
	std::shared_ptr<T> Get()
	{
		std::shared_ptr<T> p(create(), [this](T* pb)->void{this->DelMe(pb); });
		return p;
	}

	void DelMe(T* pb)
	{
		m_objMemoryPool.push_back(pb);
	}
	void Release()
	{
		m_objMemoryPool.clear();
	}
private:
	T* create()
	{
		T* pRet(nullptr);
		if (m_objMemoryPool.empty())
		{
			pRet = new T();
		}
		else
		{
			pRet = m_objMemoryPool.back();
			m_objMemoryPool.pop_back();
		}
		((T*)pRet)->Clear();
		return pRet;
	}
private:
	std::list<T*> m_objMemoryPool;
};

#define GET_SHARED_PTR(T) SharedPtrMemoryPool<T>::GetInstance().Get()
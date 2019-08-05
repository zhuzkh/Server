#pragma once
#include "MemoryPoolManager.h"
#include "MemoryPool.h"
MemoryPoolMgr::MemoryPoolMgr()
{

}
MemoryPoolMgr::~MemoryPoolMgr()
{
	for (auto& data : m_pool_vec)
	{
		delete data;
	}
	m_pool_vec.clear();
}
void MemoryPoolMgr::AddPool(MemoryPoolBase* pool_base)
{
	m_pool_vec.push_back(pool_base);
}



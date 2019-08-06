#pragma once
#include "MemoryPoolManager.h"
#include "MemoryPool.h"
MemoryPoolMgr::MemoryPoolMgr()
{
}
MemoryPoolMgr::~MemoryPoolMgr()
{
}

void MemoryPoolMgr::AddPool(MemoryPoolBase* pool_base)
{
	m_pool_vec.push_back(pool_base);
}

void MemoryPoolMgr::Release()
{
	for (auto& data : m_pool_vec)
	{
		if (data)
		{
			data->Release();
		}
	}
	m_pool_vec.clear();
}


#pragma once
#include "Logger.h"
#include "Singleton.h"
#include <vector>
#include <tuple>
class MemoryPoolBase;

class MemoryPoolMgr : public Singleton<MemoryPoolMgr>
{
private:
	MemoryPoolMgr();
	~MemoryPoolMgr();
	friend Singleton<MemoryPoolMgr>;
public:
	void AddPool(MemoryPoolBase* pool_base);
	void Release();
private:
	std::vector<MemoryPoolBase*> m_pool_vec;
};



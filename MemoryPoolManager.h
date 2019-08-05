#pragma once
#include "Logger.h"
#include "Singleton.h"
#include <vector>
class MemoryPoolBase;

class MemoryPoolMgr : public Singleton<MemoryPoolMgr>
{
private:
	MemoryPoolMgr();
	~MemoryPoolMgr();
	friend Singleton<MemoryPoolMgr>;
public:
	void AddPool(MemoryPoolBase* pool_base);
private:
	std::vector<MemoryPoolBase*> m_pool_vec;
};



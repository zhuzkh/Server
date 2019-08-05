#pragma once
#include "MsgInstanceMgr.h"

MsgInstMgr::MsgInstMgr()
{
	ClearData();
}

MsgInstMgr::~MsgInstMgr()
{
	ClearData();
}

void MsgInstMgr::ClearData()
{
	for (auto& data : m_pbMap)
	{
		if (data.second)
		{
			delete data.second;
		}
	}
	m_pbMap.clear();
}

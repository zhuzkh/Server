#include "ManagerModule.h"
#include "time.h"
#include <vector>
#include "Logger.h"
#include "netproxy.h"

ManagerModule::ManagerModule(std::string sModule) : ManagerModuleBase(sModule)
{
}

ManagerModule::~ManagerModule()
{
}


void ManagerModule::RegisterGSRefreshTime()
{
// 	const std::vector<RefreshEventBase*>* pRefreshTime = GetManagerModule(RefreshManager)->GetRefreshTimeByType(Enum_RT_ManagerModule, m_sModule);
// 	if (pRefreshTime == nullptr)
// 	{
// 		return;
// 	}
// 
// 	for (auto& pEventBase : *pRefreshTime)
// 	{
// 		for (const auto& timeCfg : pEventBase->vRefreshTime)
// 		{
// 			auto lEventId = REGISTER_HOURMIN_EVENT_P(Enum_TET_DAY, timeCfg.first, timeCfg.second, ManagerModule, OnHandleDailyReset, pEventBase);
// 			if (lEventId == INVALID_TIME_EVENT_ID)
// 			{
// 				GT_ERROR("Register DailyReset Error!");
// 				continue;
// 			}
// 			else
// 			{
// 				m_vEventId.push_back(lEventId);
// 			}
// 
// 		}
// 	}
}

void ManagerModule::UnRegisterTimeEvent()
{
// 	for (auto& lEventId : m_vEventId)
// 	{
// 		g_pTimeMgr->DelEvent(lEventId);
// 	}
}

void ManagerModule::OnHandleDailyReset(void* pParam, int nTime)
{
// 	//这里要先记录再刷新
// 	auto pEventBase = (RefreshEventBase*)pParam;
// 
// 	GetManagerModule(RefreshManager)->UpdateRecordTime(pEventBase->nId, nTime);
// 
// 	DailyReset(pParam);
}

void ManagerModule::OnHandleDailyReset(void* pParam)
{
	//这里要先记录再刷新
// 	auto pEventBase = (RefreshEventBase*)pParam;
// 
// 	GetManagerModule(RefreshManager)->UpdateRecordTime(pEventBase->nId, time(nullptr));
// 
// 	DailyReset(pParam);
}

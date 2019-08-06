#include "UserModule.h"
#include "netproxy.h"

UserModule::UserModule(std::string sModule) : UserModuleBase(sModule)
	,m_pGameClient(nullptr)
	,m_vTimeEventId()
	,m_bRun(false)
{
}

UserModule::~UserModule()
{
	m_pGameClient = nullptr;
}

void UserModule::RegisterDailyReset()
{
// 	const std::vector<RefreshEventBase*>* pRefreshTime = GetManagerModule(RefreshManager)->GetRefreshTimeByType(Enum_RT_UserModule, m_sModule);
// 	if(pRefreshTime == nullptr)
// 	{
// 		//GT_ERROR("Init Module RefreshTime Error ,ModuleType:%d",m_nModuleType);
// 		return;
// 	}
// 
// 	for (auto& pEventBase : *pRefreshTime)
// 	{
// 		if (!pEventBase->bDirRefresh)
// 		{
// 			//不添加定时器，玩家请求刷新
// 			continue;
// 		}
// 		for (const auto timeCfg : pEventBase->vRefreshTime)
// 		{
// 			auto lEventId = REGISTER_HOURMIN_EVENT_P(Enum_TET_DAY, timeCfg.first, timeCfg.second, UserModule, HandleDailyReset, pEventBase);
// 			if (lEventId == INVALID_TIME_EVENT_ID)
// 			{
// 				GT_ERROR("Register DailyReset Error!");
// 			}
// 			else
// 			{
// 				AddTimerEventId(lEventId);
// 			}
// 		}		
// 	}
}

void UserModule::UnRegisterTimer()
{
// 	auto it = m_vTimeEventId.begin();
// 	auto itEnd = m_vTimeEventId.end();
// 	for(;it!=itEnd;++it)
// 	{
// 		g_pTimeMgr->DelEvent(*it);
// 		//UNREGISTER_TIMER(*it);
// 	}
// 	m_vTimeEventId.clear();
}

void UserModule::CheckLastResetTime()
{
// 	time_t nNowTime = time(nullptr);
// 	struct tm tmNowTime;
// #ifdef WIN32_SYSTEM
// 	localtime_s(&tmNowTime, &nNowTime);
// #else
// 	localtime_r(&nNowTime, &tmNowTime);
// #endif
// 	const std::vector<RefreshEventBase*>* pRefreshTime = GetManagerModule(RefreshManager)->GetRefreshTimeByType(Enum_RT_UserModule, m_sModule);
// 	if (pRefreshTime == nullptr)
// 	{
// 		//GT_ERROR("Init Module RefreshTime Error ,ModuleType:%d", m_nModuleType);
// 		return;
// 	}
// 
// 	for (auto& pEventBase : *pRefreshTime)
// 	{
// 		auto it = pEventBase->vRefreshTime.begin();
// 		auto itEnd = pEventBase->vRefreshTime.end();
// 
// 		for (; it != itEnd; ++it)
// 		{
// 			if (!pEventBase->bDirRefresh)
// 			{
// 				continue;
// 			}
// 			tmNowTime.tm_hour  = it->first;
// 			tmNowTime.tm_min   = it->second;
// 			tmNowTime.tm_sec   = 0;
// 			tmNowTime.tm_isdst = -1;
// 
// 			int nRefreshTime = mktime(&tmNowTime);
// 
// 			int nLastRefreshTime = m_pGameClient->GetRefreshRecordTime(pEventBase->nId);
// 			if (nLastRefreshTime == 0)
// 			{
// 				HandleDailyReset(pEventBase, time(nullptr));
// 			}
// 			else
// 			{
// 				if (nNowTime - nLastRefreshTime >= 86400)
// 				{
// 					for (const auto& data : pEventBase->vRefreshTime)
// 					{
// 						OnDailyReset(pEventBase);
// 					}
// 					m_pGameClient->UpdateRecordTime(pEventBase->nId, time(nullptr));
// 				}
// 				else if ((nNowTime >= nRefreshTime) && nLastRefreshTime < nRefreshTime)
// 				{
// 					int nRecordTime = time(nullptr);
// 
// 					auto itTemp = it;
// 
// 					if (++itTemp != itEnd)
// 					{
// 						nRecordTime = nRefreshTime;
// 					}
// 					HandleDailyReset(pEventBase, nRecordTime);
// 				}
// 			}
// 		}
// 	}
}

void UserModule::HandleDailyReset(void* pParam, int nRecordTime)
{
// 	//这里要先记录再刷新
// 	auto pEventBase = (RefreshEventBase*)pParam;
// 
// 	m_pGameClient->UpdateRecordTime(pEventBase->nId, nRecordTime);
// 
// 	OnDailyReset(pParam);
}

void UserModule::HandleDailyReset(void* pParam)
{
// 	//这里要先记录再刷新
// 	auto pEventBase = (RefreshEventBase*)pParam;
// 
// 	m_pGameClient->UpdateRecordTime(pEventBase->nId, time(nullptr));
// 
// 	OnDailyReset(pParam);
}

void UserModule::AddTimerEventId(long long lEventId)
{
	m_vTimeEventId.push_back(lEventId);
}

//void UserModule::getNextRefreshTime(std::vector<std::pair<int,int>>& vRefreshTime)const
//{
	/*vRefreshTime.clear();
	auto vFreshTime = g_gameResource->GetRefreshTime((Enum_UserModule)m_nModuleType);
	auto it = vFreshTime.begin();
	auto itEnd = vFreshTime.end();
	for(;it!=itEnd;it++)
	{
		tm tmToday;
		time_t tTime = time(nullptr);
#ifdef WIN32_SYSTEM
		localtime_s(&tmToday, &tTime);
#else
		localtime_r(&tTime, &tmToday);
#endif
		tmToday.tm_hour = it->first;
		tmToday.tm_min = it->second;

		time_t tRefreshTime = mktime(&tmToday);
		if(tRefreshTime < tTime)
		{
			tRefreshTime += 86400;
		}
		vRefreshTime.push_back(tRefreshTime);
	}*/
//}

//void UserModule::UpdateRedDot(int nPointType, bool bStatus)
//{
//	if (!isDotTypeLegal(nPointType))
//	{
//		return;
//	}
//	m_mRedDotCollector[nPointType] = bStatus;
//}

//bool UserModule::isDotTypeLegal(int nDotType)
//{
//	if (nDotType < REDPOINT_BEGIN || nDotType >= REDPOINT_END)
//	{
//		return false;
//	}
//	return true;
//}



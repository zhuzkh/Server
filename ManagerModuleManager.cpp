#include "ManagerModuleManager.h"
#include "Logger.h"
#include "time.h"
#include "netproxy.h"

ManagerModuleManager::ManagerModuleManager()
{
	m_pAllMgrModule.clear();
	m_bStart = false;

	auto& dataMap = ManagerModuleBase::ClassNameMap();
	for (auto& data : dataMap)
	{
		m_pAllMgrModule[data.first] = (ManagerModule*)data.second();
	}
}

ManagerModuleManager::~ManagerModuleManager()
{
	for (auto& data : m_pAllMgrModule)
	{
		SAFE_DELETE(data.second);
	}
	m_pAllMgrModule.clear();
}

bool ManagerModuleManager::OnInitialize()
{
	for (auto& data : m_pAllMgrModule)
	{
		if (data.second == nullptr)
		{
			continue;
		}
		LOG_INFO("Init Manager Module! Name : %s", data.first.c_str());

		if (!data.second->Initialize())
		{
			LOG_ERROR("Init Manager Module Error! Name : %s", data.first.c_str());
			return false;
		}
	}
	m_bStart = true;
	return true;
}

bool ManagerModuleManager::OnUpdateXmlConfig()
{
	for (auto& data : m_pAllMgrModule)
	{
		if (data.second == nullptr)
		{
			continue;
		}
		LOG_INFO("Update Xml Config! Name : %s", data.first.c_str());

		if (!data.second->UpdateXmlConfig())
		{
			LOG_ERROR("Update Xml Config Error! Name : %s", data.first.c_str());
			return false;
		}
	}
	return true;
}

void ManagerModuleManager::OnClearData()
{
	for (auto& data : m_pAllMgrModule)
	{
		if (data.second == nullptr)
		{
			continue;
		}
		data.second->ClearData();
	}
}
void ManagerModuleManager::OnUpdate()
{
	if (!m_bStart)
	{
		return;
	}
	for (auto& data : m_pAllMgrModule)
	{
		if (data.second == nullptr)
		{
			continue;
		}
		data.second->Update();
	}
}

void ManagerModuleManager::MongoDBGetData()
{
	for (auto& data : m_pAllMgrModule)
	{
		if (data.second == nullptr)
		{
			continue;
		}
		data.second->MongoDBGetData();
	}
}

void ManagerModuleManager::OnInitAfterDataComplete()
{
	for (auto& data : m_pAllMgrModule)
	{
		if (data.second == nullptr)
		{
			continue;
		}
		data.second->InitAfterDataComplate();
	}
}

void ManagerModuleManager::OnDailyReset()
{
	for (auto& data : m_pAllMgrModule)
	{
		if (data.second == nullptr)
		{
			continue;
		}
		data.second->UnRegisterTimeEvent();
		data.second->RegisterGSRefreshTime();
	}
}

void ManagerModuleManager::CheckDailyReset()
{
	for (auto& data : m_pAllMgrModule)
	{
		if (data.second == nullptr)
		{
			continue;
		}
		checkRefreshTime(data.first);
	}
}

ManagerModule* ManagerModuleManager::GetModule(string sModule)
{
	if (m_pAllMgrModule.find(sModule) == m_pAllMgrModule.end())
	{
		return nullptr;
	}
	return m_pAllMgrModule[sModule];
}


void ManagerModuleManager::checkRefreshTime(std::string sModuleType)
{
// 	time_t nNowTime = time(nullptr);
// 	struct tm tmNowTime;
// #ifdef WIN32_SYSTEM
// 	localtime_s(&tmNowTime, &nNowTime);
// #else
// 	localtime_r(&nNowTime, &tmNowTime);
// #endif
// 	const std::vector<RefreshEventBase*>* pRefreshTime = GetManagerModule(RefreshManager)->GetRefreshTimeByType(Enum_RT_ManagerModule, sModuleType);
// 	if (pRefreshTime == nullptr)
// 	{
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
// 			tmNowTime.tm_hour = it->first;
// 			tmNowTime.tm_min = it->second;
// 			tmNowTime.tm_sec = 0;
// 			tmNowTime.tm_isdst = -1;
// 
// 			int nRefreshTimeCfg = mktime(&tmNowTime);
// 
// 			int nLastRefreshTime = GetManagerModule(RefreshManager)->GetMMRefreshRecordTime(pEventBase->nId);
// 			if (0 == nLastRefreshTime)
// 			{
// 				m_pAllMgrModule[sModuleType]->OnHandleDailyReset(pEventBase, time(nullptr));
// 			}
// 			else
// 			{
// 				if (nLastRefreshTime < nNowTime - 86400)
// 				{
// 					for (const auto& data : pEventBase->vRefreshTime)
// 					{
// 						m_pAllMgrModule[sModuleType]->DailyReset(pEventBase);
// 					}
// 					GetManagerModule(RefreshManager)->UpdateRecordTime(pEventBase->nId, time(nullptr));
// 				}
// 				else if (nNowTime >= nRefreshTimeCfg && nLastRefreshTime < nRefreshTimeCfg)
// 				{
// 					int nRecordTime = time(nullptr);
// 
// 					auto itTemp = it;
// 
// 					if (++itTemp != itEnd)
// 					{
// 						nRecordTime = nRefreshTimeCfg;
// 					}
// 					m_pAllMgrModule[sModuleType]->OnHandleDailyReset(pEventBase, nRecordTime);
// 				}
// 			}
// 		}
// 	}
}
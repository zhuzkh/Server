#pragma once
#include "ManagerModule.h"
#include <unordered_map>

class ManagerModuleManager
{
public:
	ManagerModuleManager();
	~ManagerModuleManager();
public:
	bool OnInitialize();
	bool OnUpdateXmlConfig();
	void OnClearData();
	void OnUpdate();	
	void MongoDBGetData();
	void OnInitAfterDataComplete();
	void OnDailyReset();
	void CheckDailyReset();
	ManagerModule* GetModule(std::string sModule);
private:
	void checkRefreshTime(std::string sModuleType);

private:
	std::unordered_map<std::string, ManagerModule*> m_pAllMgrModule;
	bool m_bStart;
};

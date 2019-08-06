#ifndef _MANAGER_MODULE_H_
#define _MANAGER_MODULE_H_

#include <vector>
#include "ManagerModuleBase.h"

class GameClient;
class ManagerModule : public ManagerModuleBase
{
public:
	ManagerModule(std::string sModule);
	virtual ~ManagerModule();
public:
	virtual bool UpdateXmlConfig() = 0;
	virtual bool Initialize() = 0;
	virtual void ClearData() = 0;
	virtual void MongoDBGetData() {};
	virtual void MongoDBSaveData() {};
	virtual void DailyReset(void*) {};
	virtual void InitAfterDataComplate() {};
	virtual void Update() {};
	virtual bool CheckRedDot(GameClient*) { return true; }

	void RegisterGSRefreshTime();
	void UnRegisterTimeEvent();
	void OnHandleDailyReset(void* pParam, int nTime);
	void OnHandleDailyReset(void* pParam);

private:
	std::vector<long long> m_vEventId;
};

#endif
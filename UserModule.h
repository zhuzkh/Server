#ifndef _USER_MODULE_H
#define _USER_MODULE_H

#include <vector>
//#include <string>
//#include <tuple>
#include "UserModuleBase.h"
//#include "DTimer.h"
//#include "CommDef.h"
//#include "RefreshManager.h"
//#include "dbstruct.h"


class GameClient;
class UserModule : public UserModuleBase
{
public:
	UserModule(std::string sModule);
	virtual ~UserModule();
	//static int GetModuleType() {};

public:
	inline GameClient* GetGameClient(){ return m_pGameClient; }
	inline void SetGameClient(GameClient* pGameClient){ m_pGameClient = pGameClient; }

	inline bool IsRun()const { return m_bRun; }
	inline void SetRun(bool bRun) { m_bRun = bRun; }

	inline bool IsInit()const { return m_bInit; }
	inline void SetInit(bool bInit) { m_bInit = bInit; }
public:
	virtual bool OnInitialize() = 0;
	virtual void OnDailyReset(void*) = 0;
	virtual void OnClearData() = 0;
	virtual bool MongoDBGetData() = 0;
	virtual void MongoDBSaveData() = 0;
	//virtual void CollectRedDot(std::vector<std::tuple<int, int>>& vRedDot) {};
	//virtual void CollectRedDotTimeStamp(std::vector<NetRedDot>& vRedDot) {};
public:
	void RegisterDailyReset();
	void UnRegisterTimer();
	void CheckLastResetTime();
	void AddTimerEventId(long long lEventId);
	void HandleDailyReset(void* pParam, int nRecordTime);
	void HandleDailyReset(void* pParam);

private:
	//void getNextRefreshTime(std::vector<std::pair<int,int>>& vRefreshTime)const;

private:
	std::vector<long long>				m_vTimeEventId; 
	GameClient*						    m_pGameClient;
	bool								m_bRun;
	bool								m_bInit;
};

#endif
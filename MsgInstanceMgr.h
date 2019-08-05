#pragma once
#include <map>
#include <string>
#include "google/protobuf/message.h"
#include "Singleton.h"

class MsgInstMgr : public Singleton<MsgInstMgr>
{
private:
	MsgInstMgr();
	~MsgInstMgr();
	friend Singleton<MsgInstMgr>;
public:
	void ClearData();

	template<typename T>
	T* GetMessage(std::string name)
	{
		if (m_pbMap.find(name) == m_pbMap.end())
		{
			T* pObj = new T();
			if (!pObj)
			{
				return NULL;
			}
			m_pbMap[name] = pObj;
		}
		return dynamic_cast<T*>(m_pbMap[name]);
	}
private:
	std::map<std::string, google::protobuf::MessageLite*> m_pbMap;
};

#define GetProtoBuf(T) PbManager::GetInstance()->GetMessage<T>(#T);

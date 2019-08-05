#pragma once
#include <map>
#include <string>
#include "google/protobuf/message.h"
using namespace pp2;

class PbManager
{
private:
	PbManager()
	{
		ClearData();
	}
	~PbManager()
	{
		ClearData();
	}
public:
	static PbManager* GetInstance()
	{
		static PbManager instance;
		return &instance;
	}

	void ClearData()
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

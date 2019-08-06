#pragma once
#include <stdlib.h>
#include <string>
#include <map>

class ManagerModuleBase
{
public:
	ManagerModuleBase(std::string sModule);
	virtual ~ManagerModuleBase();

public:
	typedef ManagerModuleBase* (*ClassGen)(); /* 声明函数指针*/
public:
	static std::map<std::string, ClassGen>& ClassNameMap()
	{
		static std::map<std::string, ClassGen> classNameMap;
		return classNameMap;
	}
public:
	static ManagerModuleBase* Create(std::string class_name)
	{
		auto iter = ClassNameMap().find(class_name);
		if (ClassNameMap().end() != iter)
		{
			return ((*iter).second)();
		}
		return nullptr;
	}
protected:
	static void Register(const std::string &class_name, ClassGen class_gen) /* 注册函数 */
	{
		ClassNameMap().insert(std::make_pair(class_name, class_gen));
	}

protected:
	std::string m_sModule;
};

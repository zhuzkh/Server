#pragma once
#include <string>
// #include "UserModuleDefine.h"
class UserModuleBase
{
public:
	UserModuleBase(std::string sModule);
	virtual ~UserModuleBase();

protected:
	std::string	m_sModule;

// 	H_FILE_USER_BASE(UserModuleBase)
};

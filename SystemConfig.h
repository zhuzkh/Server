#pragma once
#include "Singleton.h"
#include "nlohmann/json.hpp"
using namespace nlohmann;
using namespace std;

struct SystemConfigConfLogger
{
	string path;
};

struct SystemConfigConfNetwork
{
	string listen_address;
	int32_t listen_port;
};

struct SystemConfigConf 
{
	SystemConfigConfLogger logger;
	SystemConfigConfNetwork network;
};

void to_json(json& j, const SystemConfigConf& p);
void to_json(json& j, const SystemConfigConfLogger& p);
void to_json(json& j, const SystemConfigConfNetwork& p);

void from_json(const json& j, SystemConfigConfLogger& p);
void from_json(const json& j, SystemConfigConfNetwork& p);
void from_json(const json& j, SystemConfigConf& p); 

class SystemConfig : public Singleton<SystemConfig>
{
public:
	bool Initlize(const std::string& path);
	const SystemConfigConf& GetConf();
private:
	SystemConfigConf m_conf;
};

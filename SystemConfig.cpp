#include "SystemConfig.h"
#include <fstream>
bool SystemConfig::Initlize(const string& path)
{
	json config;
	config.clear();
	std::ifstream file(path);
	config = json::parse(file);
	m_conf = config.get<SystemConfigConf>();
	return true;
}

const SystemConfigConf& SystemConfig::GetConf()
{
	return m_conf;
}

void to_json(json& j, const SystemConfigConf& p)
{
	j = json{ {"logger", p.logger}, {"network", p.network} };
}

void to_json(json& j, const SystemConfigConfLogger& p)
{
	j = json{ {"path", p.path} };
}

void to_json(json& j, const SystemConfigConfNetwork& p)
{
	j = json{ {"listen_address", p.listen_address}, {"listen_port", p.listen_port} };
}

void from_json(const json& j, SystemConfigConf& p)
{
	j["logger"].get_to(p.logger);
	j["network"].get_to(p.network);
}

void from_json(const json& j, SystemConfigConfLogger& p)
{
	j["path"].get_to(p.path);
}

void from_json(const json& j, SystemConfigConfNetwork& p)
{
	j["listen_address"].get_to(p.listen_address);
	j["listen_port"].get_to(p.listen_port);

}

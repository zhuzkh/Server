#include "Logger.h"
#include <direct.h>
#include <spdlog\sinks\daily_file_sink.h>

 Logger::Logger() : m_logger(nullptr)
 {
 }
 
 Logger::~Logger()
 {
 }

bool Logger::Initlize(std::string logger_name, std::string logger_file_path)
{
	if (!makeDir(logger_file_path))
	{
		return false;
	}
	
	//m_logger = spdlog::synchronous_factory::create<spdlog::sinks::daily_file_sink_mt>(logger_name, logger_file_path, 0, 0, false);
	m_logger = spdlog::daily_logger_mt(logger_name, logger_file_path);
	if (!m_logger)
	{
		printf("create logger failed!");
		return false;
	}
	m_logger->flush_on(spdlog::level::err);
	spdlog::flush_every(std::chrono::seconds(1));
	m_logger->set_level(spdlog::level::trace);
	spdlog::set_level(spdlog::level::trace);
	m_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
	return true;
}

bool Logger::makeDir(std::string logger_file_path)
{
	std::string::size_type pos_1 = std::string::npos;
	std::string::size_type pos_2 = std::string::npos;
	std::string path;
	path.clear();
	do 
	{
		pos_1 = logger_file_path.find_first_of("/");
		pos_2 = logger_file_path.find_first_of('\\');
		if (pos_1 == logger_file_path.npos && pos_2 == logger_file_path.npos)
		{
			break;
		}
		else if (pos_2 == logger_file_path.npos || ((pos_1 != logger_file_path.npos && pos_2 != logger_file_path.npos) && (pos_1 < pos_2)))
		{
			path.append(logger_file_path.substr(0, pos_1 + 1));
			logger_file_path = logger_file_path.substr(pos_1 + 1);
		}
		else if (pos_1 == logger_file_path.npos || ((pos_1 != logger_file_path.npos && pos_2 != logger_file_path.npos) && (pos_2 < pos_1)))
		{
			path.append(logger_file_path.substr(0, pos_2 + 1));
			logger_file_path = logger_file_path.substr(pos_2 + 1);
		}
		else
		{
			printf("read logger path error! path : %s", logger_file_path.c_str());
			return false;
		}
		if (!path.empty())
		{
			if (_access(path.c_str(), 0) != 0)
			{
				if (_mkdir(path.c_str()) != 0)
				{
					printf("make logger dir error! path : %s", logger_file_path.c_str());
					return false;
				}
			}
		}

	} while (true);

	return true;
}

std::string Logger::Suffix(std::string msg, const char* file_name, const char* func_name, int line)
{
	std::string total_msg;
	return total_msg.append("[").append(file_name).append(":").append(std::to_string(line)).append("  ").append(func_name).append("()]  ").append(msg.c_str());
}


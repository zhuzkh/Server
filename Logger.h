#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "Singleton.h"
class Logger : public Singleton<Logger>
{
protected:
	Logger();
	~Logger();
	friend class Singleton<Logger>;
public:
	bool Initlize(std::string logger_name, std::string logger_file_path);

	template<typename... Args>
	void InfoLog(const char* file_name, const char* func_name, int line, std::string msg, const Args& ... args)
	{
		std::string fmt = Suffix(msg, file_name, func_name, line);
#ifdef WIN32
		spdlog::info(fmt, args...);
#endif
		if (m_logger)
		{
			m_logger->info(fmt, args...);
		}
	}

	template<typename... Args>
	void DebugLog(const char* file_name, const char* func_name, int line, std::string msg, const Args& ... args)
	{
		std::string fmt = Suffix(msg, file_name, func_name, line);
#ifdef WIN32
		spdlog::debug(fmt, args...);
#endif
		if (m_logger)
		{
			m_logger->debug(fmt, args...);
		}
	}


	template<typename... Args>
	void WarnLog(const char* file_name, const char* func_name, int line, std::string msg, const Args& ... args)
	{
		std::string fmt = Suffix(msg, file_name, func_name, line);
#ifdef WIN32
		spdlog::warn(fmt, args...);
#endif
		if (m_logger)
		{
			m_logger->warn(fmt, args...);
		}
	}


	template<typename... Args>
	void ErrorLog(const char* file_name, const char* func_name, int line, std::string msg, const Args& ... args)
	{
		std::string fmt = Suffix(msg, file_name, func_name, line);
#ifdef WIN32
		spdlog::error(fmt, args...);
#endif
		if (m_logger)
		{
			m_logger->error(fmt, args...);
		}
	}


	template<typename... Args>
	void CriticalLog(const char* file_name, const char* func_name, int line, std::string msg, const Args& ... args)
	{
		std::string fmt = Suffix(msg, file_name, func_name, line);
#ifdef WIN32
		spdlog::critical(fmt, args...);
#endif		
		if (m_logger)
		{
			m_logger->info(fmt, args...);
		}
	}

	template<typename... Args>
	void TraceLog(const char* file_name, const char* func_name, int line, std::string msg, const Args& ... args)
	{
		std::string fmt = Suffix(msg, file_name, func_name, line);
#ifdef WIN32
		spdlog::trace(fmt, args...);
#endif
		if (m_logger)
		{
			m_logger->trace(fmt, args...);
		}
	}
	bool makeDir(std::string logger_file_path);

	std::string Suffix(std::string msg, const char* file_name, const char* func_name, int line);

private:
	std::shared_ptr<spdlog::logger> m_logger;
};

#ifdef _WIN32
//strrchr:�����ַ���ָ���ַ��������濪ʼ�ĵ�һ�γ��ֵ�λ�ã�����ɹ������ظ��ַ��Լ�������ַ������ʧ�ܣ�����NULL
//strcgr:�����ַ���ָ���ַ����״γ��ֵ�λ��
#define __FILENAME__ (strrchr(__FILE__,'\\')?(strrchr(__FILE__,'\\')+1):__FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__,'/')?(strrchr(__FILE__,'/')+1):__FILE__)
#endif //_WIN32

//�ڴ��󼶱����־����׷���ļ������кţ�������
#define SUFFIX(msg) std::string(msg).append("  [").append(__FILENAME__).append(":").append(std::to_string(__LINE__)).append("  ").append(__FUNCTION__).append("()]").c_str()


#define LOG_ERROR(...) Logger::GetInstance().ErrorLog(__FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__);
#define LOG_INFO(...) Logger::GetInstance().InfoLog(__FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__);
#define LOG_DEBUG(...) Logger::GetInstance().DebugLog(__FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__);
#define LOG_WARN(...) Logger::GetInstance().WarnLog(__FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__);
#define LOG_CRITICAL(...) Logger::GetInstance().CriticalLog(__FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__);
#define LOG_TRACE(...) Logger::GetInstance().TraceLog(__FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__);

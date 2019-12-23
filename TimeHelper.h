#pragma once
#include <stdint.h>
#include <time.h>	
#include <chrono>
using namespace std::chrono;

class TimeHelper
{
public:
	static const int32_t ONE_DAY_SECOND = 86400;
	static const int32_t ONE_HOUR_SECOND = 3600;
	static const int32_t ONE_MINUTE_SECOND = 60;
	static const int32_t ONE_WEEK_SECOND = 7 * ONE_DAY_SECOND;
	
	static time_t GetCurTime();

	static int64_t GetCurMsTime();

	static void SetCurTime(time_t now_time);

	static inline void GetLocalTime(time_t now_time, tm& rtm);

	static time_t GetZeroClockTime(time_t now_time);

	static int32_t GetYearDay(time_t now_time);

	static time_t MakeTime(int y, int mn, int d, int h, int m, int s);

private:
	static time_t m_cur_time;
};

#define TIME_DEBUG_START\
	time_point<system_clock> begin_time = system_clock::now();\
	time_point<system_clock> end_time = begin_time;\
	milliseconds use_time;

#define TIME_DEBUG_CUR\
	end_time = system_clock::now();\
	use_time = duration_cast<milliseconds>(end_time - begin_time);\
 	LOG_INFO("cur use time : {}", use_time.count());
#include "TimeHelper.h"

time_t TimeHelper::m_cur_time = 0;

time_t TimeHelper::GetCurTime()
{
	return time(0);
	//return m_cur_time;
}

int64_t TimeHelper::GetCurMsTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void TimeHelper::SetCurTime(time_t now_time)
{
	m_cur_time = now_time;
}

struct tm TimeHelper::GetLocalTime(time_t now_time)
{
	struct tm rtm;
#ifdef WIN32
	localtime_s(&rtm, &now_time);
#else
	localtime_r(&now_time, &rtm);
#endif
	return rtm;
}

time_t TimeHelper::GetZeroClockTime(time_t now_time)
{
	struct tm tm_local = GetLocalTime(now_time);
	tm_local.tm_hour = 0;
	tm_local.tm_sec = 0;
	tm_local.tm_min = 0;
	return mktime(&tm_local);
}

int32_t TimeHelper::GetYearDay(time_t now_time)
{
	struct tm tm_local = GetLocalTime(now_time);
	return (tm_local.tm_year + 1900) * 1000 + tm_local.tm_yday;
}

time_t TimeHelper::MakeTime(int y, int mn, int d, int h, int m, int s)
{
	struct tm t = TimeHelper::GetLocalTime(GetCurTime());
	t.tm_year = y > 1900 ? y - 1900 : t.tm_year;
	t.tm_mon = mn > 0 ? mn - 1 : t.tm_mon;
	t.tm_mday = d < 1 ? t.tm_mday : d;
	t.tm_hour = h;
	t.tm_min = m;
	t.tm_sec = s;
	t.tm_isdst = -1;
	return mktime(&t);
}

bool TimeHelper::IsCurDay(time_t time)
{
	return IsTheSameDay(time, GetCurTime());
}

bool TimeHelper::IsTheSameDay(time_t time_1, time_t time_2)
{
	struct tm tm_1 = GetLocalTime(time_1);
	struct tm tm_2 = GetLocalTime(time_2);
	return (tm_1.tm_year == tm_2.tm_year && tm_1.tm_yday == tm_2.tm_yday);

}


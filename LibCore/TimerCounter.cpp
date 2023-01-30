#include "pch.h"
#include "TimerCounter.h"
#include <ctime>

TimerCounter::TimerCounter()
{
	QueryPerformanceFrequency(&frequnce_time_);
	Begin();
}


void TimerCounter::Begin()
{
	QueryPerformanceCounter(&begin_time_);
}


void TimerCounter::Reset()
{
	QueryPerformanceCounter(&begin_time_);
}

float TimerCounter::Usage()
{
	LARGE_INTEGER nEnd;
	QueryPerformanceCounter(&nEnd);
	return  static_cast<float>(1000 * (double(nEnd.QuadPart - begin_time_.QuadPart)
		/ frequnce_time_.QuadPart));
}

std::string TimerCounter::Date()
{
	time_t now = time(0);
	tm gmtm;
	localtime_s(&gmtm, &now);
	char time[MAX_PATH];
	sprintf_s(time, MAX_PATH, "%04d-%02d-%02d", gmtm.tm_year+ 1900, gmtm.tm_mon+1, gmtm.tm_mday);
	return std::string(time);
}


std::string TimerCounter::Time(bool include_tickcount)
{
	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	char time[MAX_PATH];
	if (include_tickcount)
	{
		sprintf_s(time, MAX_PATH, "%02d-%02d-%02d-%04d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	}
	else
	{
		sprintf_s(time, MAX_PATH, "%02d-%02d-%02d", st.wHour, st.wMinute, st.wSecond);
	}
	
	return std::string(time);
}


std::string TimerCounter::Current(bool include_tickcount)
{
	return Date() + std::string("_") + Time(include_tickcount);
}
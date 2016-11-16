#pragma once
#include <windows.h>
#include <iostream>

class Timer
{
	static Timer* timer_instance;
private:
	Timer()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		m_Frequency = 1.0 / frequency.QuadPart;
		QueryPerformanceCounter(&m_Start);
	}

	LARGE_INTEGER m_Start;
	double m_Frequency;
public:
	void reset()
	{
		QueryPerformanceCounter(&m_Start);

	}

	float elapsed()
	{
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);
		unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;
		return (float)(cycles*m_Frequency);
	}
	void print(const char* string)
	{
		std::cout << string << elapsed() <<"s"<< std::endl;
		
	}

	static Timer* instance()
	{
		if (!timer_instance)
			timer_instance = new Timer();
		return timer_instance;
	}
};


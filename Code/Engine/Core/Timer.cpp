#include "Timer.h"

void Timer::Reset()
{
	start = clock::now();
	previous = start;
}

double Timer::Tick()
{
	auto now = clock::now();
	std::chrono::duration<double> delta = now - previous;
	previous = now;
	return delta.count();
}

double Timer::TimeElapsed()
{
	auto now = clock::now();
	std::chrono::duration<double> elapsed = now - start;
	return elapsed.count();
}

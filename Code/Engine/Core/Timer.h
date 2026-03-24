#pragma once

#include <chrono>

class Timer
{
public:
	using clock = std::chrono::steady_clock;

	void Reset();

	double Tick();

	double TimeElapsed();

private:
	clock::time_point start{};
	clock::time_point previous{};
};
#pragma once

#include "Logger.h"
#include <string>
#include <source_location>

template<typename T>
bool CheckNotNull(const T* ptr, ::Logger& logger, const std::string& msg, const std::source_location& loc = std::source_location::current())
{
	if (ptr)
		return true;

	logger.Log(LogLevel::Error, msg, loc);
	return false;
}
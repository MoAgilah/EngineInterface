#pragma once

#include <Utilities/Logger.h>

namespace TestHelpers
{
	inline void ResetLoggerDefaultsForTests()
	{
		auto& logger = ::Logger::GetDefaultLogger();
		logger.Stop();

		::Logger::s_defaultLogPath.clear();
		::Logger::s_defaultLoggerInitialised = false;
	}
}
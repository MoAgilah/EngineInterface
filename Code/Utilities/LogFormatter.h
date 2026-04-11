#pragma once

#include "LogRecord.h"

#include <string>
#include <format>
#include <thread>
#include <functional>

namespace logger
{
	inline std::string FormatTimestamp(const std::chrono::system_clock::time_point& now)
	{
		return std::format("[ {:%Y-%m-%d %H:%M:%S} ]", now);
	}

	inline std::string FormatFilenameTimestamp(
		const std::chrono::system_clock::time_point& tp)
	{
		return std::format("{:%Y-%m-%d_%H-%M-%S}", tp);
	}

	inline std::string FormatFilenameTimestamp()
	{
		return FormatFilenameTimestamp(std::chrono::system_clock::now());
	}

	inline std::string FormatLogLevel(LogLevel lvl)
	{
		return std::format("[ {} ]", toString(lvl));
	}

	inline std::string FormatSourceLocation(const SourceInfo& si)
	{
		return std::format("{}({},{}): {}()", si.file, si.line, si.column, si.function);
	}

	inline std::string FormatThreadInfo(const ThreadInfo& ti)
	{
		const std::string& label =
			ti.optional_thread_label.empty()
			? "Thread"
			: ti.optional_thread_label;

		auto id = std::hash<std::thread::id>{}(ti.id);

		return std::format("[ {} ] id-{}", label, id);
	}

	inline std::string FormatSequenceID(uint64_t sid)
	{
		return std::format("[#{}]", sid);
	}

	inline bool ShouldShowSource(LogLevel level)
	{
		return level >= LogLevel::Warning;
	}

	inline std::string FormatRecord(const LogRecord& rec)
	{
		std::string out = std::format(
			"{} {} {} {}",
			FormatTimestamp(rec.timestamp),
			FormatLogLevel(rec.logLevel),
			FormatSequenceID(rec.sequenceId),
			FormatThreadInfo(rec.threadInfo));

		if (ShouldShowSource(rec.logLevel))
		{
			out += std::format(" {}", FormatSourceLocation(rec.sourceInfo));
		}

		out += std::format(": {}", rec.message);
		return out;
	}
}
#pragma once

#include "LogRecord.h"
#include <atomic>
#include <fstream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

class Logger
{
public:
	Logger() = default;
	~Logger();

	void Start(const std::string& filePath);
	void Stop();

	void Log(LogLevel logLevel, std::string message, const std::source_location& loc = std::source_location::current());

private:

	void ProcessQueue(std::stop_token stopToken);

	std::atomic<bool> m_running{ false };
	std::queue<LogRecord> m_logQueue;
	std::mutex m_queueMutex;
	std::condition_variable m_conVar;
	std::jthread m_workerThread;

	std::string m_logFilePath;
	std::ofstream m_logStream;
	std::atomic<uint64_t> m_nextSequenceId{ 0 };
};
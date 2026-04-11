#include "Logger.h"

#include "LogFormatter.h"

#include <thread>
#include <stop_token>

ThreadInfo GetThreadInfo()
{
	ThreadInfo ti;
	ti.id = std::this_thread::get_id();
	ti.optional_thread_label = "";
	return ti;
}

Logger::~Logger()
{
	Stop();
}

void Logger::Start(const std::string& filePath)
{
	if (m_running)
		return;

	m_logFilePath = filePath;

	m_logStream.open(m_logFilePath, std::ios::app);

	if (!m_logStream.is_open())
		return;

	m_running = true;

	m_workerThread = std::jthread([this](std::stop_token stopToken)
		{
			ProcessQueue(stopToken);
		});
}

void Logger::Stop()
{
	m_running = false;

	if (m_workerThread.joinable())
	{
		m_workerThread.request_stop();

		m_conVar.notify_one();

		m_workerThread.join();
	}

	if (m_logStream.is_open())
	{
		m_logStream.flush();

		m_logStream.close();
	}
}

void Logger::Log(LogLevel logLevel, std::string message, const std::source_location& loc)
{
	if (!m_running)
		return;

	LogRecord record = LogRecord(logLevel, std::move(message), loc);

	record.sequenceId = m_nextSequenceId.fetch_add(1);
	record.threadInfo = GetThreadInfo();

	std::unique_lock<std::mutex> lock(m_queueMutex);

	m_logQueue.push(std::move(record));

	lock.unlock();

	m_conVar.notify_one();
}

void Logger::ProcessQueue(std::stop_token stopToken)
{
	std::queue<LogRecord> localQueue;

	while (true)
	{
		std::unique_lock<std::mutex> lock(m_queueMutex);

		m_conVar.wait(lock, [&]() { return !m_logQueue.empty() || stopToken.stop_requested(); });

		if (m_logQueue.empty() && stopToken.stop_requested())
			break;

		localQueue = std::move(m_logQueue);

		lock.unlock();

		while (!localQueue.empty())
		{
			auto res = logger::FormatRecord(localQueue.front());

			m_logStream << res << "\n";

			if (!m_logStream)
			{
				m_running = false;
				break;
			}

			localQueue.pop();
		}

		m_logStream.flush();

		if (!m_logStream)
		{
			m_running = false;
			break;
		}
	}
}

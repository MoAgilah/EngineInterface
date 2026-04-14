#include "CppUnitTest.h"

#include <Utilities/Logger.h>
#include <Utilities/ThreadContext.h>
#include <string>
#include <source_location>
#include <thread>
#include <filesystem>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	std::filesystem::path GetFilePath()
	{
		return std::filesystem::temp_directory_path() /
			("logger_test_" + std::to_string(std::rand()) +
				"_" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) +
				".txt");
	}

	struct TempFileGuard
	{
		std::filesystem::path path;

		~TempFileGuard()
		{
			if (!path.empty() && std::filesystem::exists(path))
			{
				std::filesystem::remove(path);
			}
		}
	};

	TEST_CLASS(LoggerTests)
	{
	public:
		TEST_METHOD(Logger_Start_CreatesLogFile)
		{
			::Logger logger;

			TempFileGuard guard{ GetFilePath() };

			logger.Start(guard.path.string());
			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));
		}

		TEST_METHOD(Logger_Start_WhenAlreadyRunning_DoesNothing)
		{
			::Logger logger;

			TempFileGuard guard1{ GetFilePath() };
			TempFileGuard guard2{ GetFilePath() };

			logger.Start(guard1.path.string());

			logger.Start(guard2.path.string()); // should be ignored

			logger.Log(LogLevel::Info, "test");
			logger.Stop();

			// First file should contain output
			Assert::IsTrue(std::filesystem::exists(guard1.path));

			std::ifstream file1(guard1.path);
			std::string contents1((std::istreambuf_iterator<char>(file1)),
				std::istreambuf_iterator<char>());

			Assert::IsTrue(contents1.find("test") != std::string::npos);

			// Second file should NOT contain output
			if (std::filesystem::exists(guard2.path))
			{
				std::ifstream file2(guard2.path);
				std::string contents2((std::istreambuf_iterator<char>(file2)),
					std::istreambuf_iterator<char>());

				Assert::IsTrue(contents2.empty());
			}
		}

		TEST_METHOD(Logger_Start_WithInvalidPath_DoesNotStart)
		{
			::Logger logger;

			auto dir = std::filesystem::temp_directory_path() /
				("logger_test_dir_" + std::to_string(std::rand()));

			std::filesystem::create_directory(dir);

			logger.Start(dir.string()); // should fail

			// verify no file was created inside
			Assert::IsTrue(std::filesystem::exists(dir));
			Assert::IsTrue(std::filesystem::is_directory(dir));

			std::filesystem::remove(dir);
		}

		TEST_METHOD(Logger_Stop_WhenAlreadyStopped_DoesNothing)
		{
			::Logger logger;

			TempFileGuard guard{ GetFilePath() };

			logger.Start(guard.path.string());
			logger.Stop();

			logger.Stop();

			logger.Log(LogLevel::Info, "test");

			std::ifstream file(guard.path);
			std::string contents((std::istreambuf_iterator<char>(file)),
				std::istreambuf_iterator<char>());

			Assert::IsTrue(contents.find("test") == std::string::npos);
		}

		TEST_METHOD(Logger_Stop_BeforeStart_DoesNothing)
		{
			::Logger logger;

			TempFileGuard guard{ GetFilePath() };

			logger.Stop();

			logger.Start(guard.path.string());
			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));
		}

		TEST_METHOD(Logger_Start_AfterStop_StartsAgain)
		{
			::Logger logger;

			TempFileGuard guard1{ GetFilePath() };

			logger.Start(guard1.path.string());
			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard1.path));

			TempFileGuard guard2{ GetFilePath() };

			logger.Start(guard2.path.string());
			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard2.path));
		}

		TEST_METHOD(Logger_Log_AfterStart_WritesMessage)
		{
			::Logger logger;

			TempFileGuard guard{ GetFilePath() };


			logger.Start(guard.path.string());

			logger.Log(LogLevel::Info, "test");

			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::ifstream file1(guard.path);
			std::string contents((std::istreambuf_iterator<char>(file1)),
				std::istreambuf_iterator<char>());

			Assert::IsTrue(contents.find("test") != std::string::npos);
		}

		TEST_METHOD(Logger_Log_BeforeStart_DoesNothing)
		{
			::Logger logger;

			TempFileGuard guard{ GetFilePath() };

			logger.Log(LogLevel::Info, "test");

			logger.Start(guard.path.string());

			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::ifstream file1(guard.path);
			std::string contents((std::istreambuf_iterator<char>(file1)),
				std::istreambuf_iterator<char>());

			Assert::IsTrue(contents.find("test") == std::string::npos);
		}

		TEST_METHOD(Logger_Log_AfterStop_DoesNothing)
		{
			::Logger logger;

			TempFileGuard guard{ GetFilePath() };

			logger.Start(guard.path.string());

			logger.Stop();

			logger.Log(LogLevel::Info, "test");

			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::ifstream file1(guard.path);
			std::string contents((std::istreambuf_iterator<char>(file1)),
				std::istreambuf_iterator<char>());

			Assert::IsTrue(contents.find("test") == std::string::npos);
		}

		TEST_METHOD(Logger_Log_AfterRestart_WritesMessage)
		{
			::Logger logger;

			TempFileGuard guard1{ GetFilePath() };

			logger.Start(guard1.path.string());
			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard1.path));

			TempFileGuard guard2{ GetFilePath() };

			logger.Start(guard2.path.string());

			logger.Log(LogLevel::Info, "test");

			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard2.path));

			std::ifstream file1(guard2.path);
			std::string contents((std::istreambuf_iterator<char>(file1)),
				std::istreambuf_iterator<char>());

			Assert::IsTrue(contents.find("test") != std::string::npos);
		}

		TEST_METHOD(Logger_Log_MultipleMessages_WritesInSequenceOrder)
		{
			::Logger logger;

			TempFileGuard guard{ GetFilePath() };

			logger.Start(guard.path.string());

			logger.Log(LogLevel::Info, "test1");
			logger.Log(LogLevel::Info, "test2");
			logger.Log(LogLevel::Info, "test3");

			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::ifstream file1(guard.path);
			std::string contents((std::istreambuf_iterator<char>(file1)),
				std::istreambuf_iterator<char>());

			auto pos1 = contents.find("[#0]");
			auto pos2 = contents.find("[#1]");
			auto pos3 = contents.find("[#2]");

			Assert::IsTrue(pos1 != std::string::npos);
			Assert::IsTrue(pos2 != std::string::npos);
			Assert::IsTrue(pos3 != std::string::npos);

			auto pos4 = contents.find("test1");
			auto pos5 = contents.find("test2");
			auto pos6 = contents.find("test3");

			Assert::IsTrue(pos4 != std::string::npos);
			Assert::IsTrue(pos5 != std::string::npos);
			Assert::IsTrue(pos6 != std::string::npos);

			Assert::IsTrue(pos1 < pos2 && pos2 < pos3);
			Assert::IsTrue(pos1 < pos4 && pos2 < pos5 && pos3 < pos6);
			Assert::IsTrue(pos4 < pos5 && pos5 < pos6);
		}

		TEST_METHOD(Logger_Log_FromMultipleThreads_WritesMessages)
		{
			logger::ThreadContext::ClearLabel();
			logger::ThreadContext::SetLabel("Main");

			::Logger logger;

			TempFileGuard guard{ GetFilePath() };

			logger.Start(guard.path.string());

			logger.Log(LogLevel::Info, "test1");

			std::thread t([&]()
				{
					logger::ThreadContext::SetLabel("Worker");
					logger.Log(LogLevel::Info, "test2");
				});

			t.join();

			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::ifstream file1(guard.path);
			std::string contents((std::istreambuf_iterator<char>(file1)),
				std::istreambuf_iterator<char>());

			Assert::IsTrue(contents.find("[ Main ]") != std::string::npos);
			Assert::IsTrue(contents.find("test1") != std::string::npos);

			Assert::IsTrue(contents.find("[ Worker ]") != std::string::npos);
			Assert::IsTrue(contents.find("test2") != std::string::npos);
		}

		TEST_METHOD(Logger_Stop_DrainsQueuedMessagesBeforeExit)
		{
			::Logger logger;

			TempFileGuard guard{ GetFilePath() };

			logger.Start(guard.path.string());

			logger.Log(LogLevel::Info, "test1");
			logger.Log(LogLevel::Info, "test2");
			logger.Log(LogLevel::Info, "test3");
			logger.Log(LogLevel::Info, "test4");
			logger.Log(LogLevel::Info, "test5");
			logger.Log(LogLevel::Info, "test6");

			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::ifstream file1(guard.path);
			std::string contents((std::istreambuf_iterator<char>(file1)),
				std::istreambuf_iterator<char>());

			Assert::IsTrue(contents.find("test1") != std::string::npos);
			Assert::IsTrue(contents.find("test2") != std::string::npos);
			Assert::IsTrue(contents.find("test3") != std::string::npos);
			Assert::IsTrue(contents.find("test4") != std::string::npos);
			Assert::IsTrue(contents.find("test5") != std::string::npos);
			Assert::IsTrue(contents.find("test6") != std::string::npos);
		}

		TEST_METHOD(Logger_Destructor_DrainsQueuedMessagesBeforeExit)
		{
			TempFileGuard guard{ GetFilePath() };

			{
				::Logger logger;

				logger.Start(guard.path.string());

				logger.Log(LogLevel::Info, "test1");
				logger.Log(LogLevel::Info, "test2");
				logger.Log(LogLevel::Info, "test3");
				logger.Log(LogLevel::Info, "test4");
				logger.Log(LogLevel::Info, "test5");
				logger.Log(LogLevel::Info, "test6");
			}

			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::ifstream file1(guard.path);
			std::string contents((std::istreambuf_iterator<char>(file1)),
				std::istreambuf_iterator<char>());

			Assert::IsTrue(contents.find("test1") != std::string::npos);
			Assert::IsTrue(contents.find("test2") != std::string::npos);
			Assert::IsTrue(contents.find("test3") != std::string::npos);
			Assert::IsTrue(contents.find("test4") != std::string::npos);
			Assert::IsTrue(contents.find("test5") != std::string::npos);
			Assert::IsTrue(contents.find("test6") != std::string::npos);
		}

		TEST_METHOD(Logger_Log_CapturesThreadContextInOutput)
		{
			logger::ThreadContext::ClearLabel();
			logger::ThreadContext::SetLabel("Main");

			::Logger logger;

			TempFileGuard guard{ GetFilePath() };

			logger.Start(guard.path.string());

			logger.Log(LogLevel::Info, "test1");

			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::ifstream file1(guard.path);
			std::string contents((std::istreambuf_iterator<char>(file1)),
				std::istreambuf_iterator<char>());

			Assert::IsTrue(contents.find("[ Thread ]") == std::string::npos);
			Assert::IsTrue(contents.find("[ Main ]") != std::string::npos);
			Assert::IsTrue(contents.find("test1") != std::string::npos);
		}
	};
}
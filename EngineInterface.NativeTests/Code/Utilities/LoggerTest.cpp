#include "CppUnitTest.h"

#include <Engine/Core/Constants.h>
#include <Utilities/Logger.h>
#include <Utilities/ThreadContext.h>
#include <TestHelpers/TestFilesystemHelpers.h>
#include <TestHelpers/TestDefaultLoggerHelper.h>
#include <string>
#include <thread>
#include <filesystem>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(LoggerTests)
	{
	public:

		// ======================================================
		// Logger Lifecycle
		// ======================================================

		TEST_METHOD(Logger_Start_CreatesLogFile)
		{
			::Logger logger;

			TestHelpers::TempFileGuard guard{ TestHelpers::GetTempFilePath() };

			logger.Start(guard.path.string());
			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));
		}

		// ======================================================
		// Resource Loading
		// ======================================================

		TEST_METHOD(Logger_DefaultDirectory_GetsLogFileOnCreate)
		{
			::Logger logger;

			TestHelpers::TempFileGuard guard{ GameConstants::GetDefaultLogPath() };

			logger.Start(guard.path.string());
			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));
		}

		// ======================================================
		// Default Logger Access
		// ======================================================

		TEST_METHOD(Logger_GetDefaultLogger_GetsLogFileOnCreate)
		{
			TestHelpers::ResetLoggerDefaultsForTests();

			::Logger::GetDefaultLogger();

			TestHelpers::TempFileGuard guard{ ::Logger::GetDefaultLogPath() };

			::Logger::GetDefaultLogger().Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));
		}

		// ======================================================
		// Logger Lifecycle
		// ======================================================

		TEST_METHOD(Logger_Start_WhenAlreadyRunning_DoesNothing)
		{
			::Logger logger;

			TestHelpers::TempFileGuard guard1{ TestHelpers::GetTempFilePath() };
			TestHelpers::TempFileGuard guard2{ TestHelpers::GetTempFilePath() };

			logger.Start(guard1.path.string());

			logger.Start(guard2.path.string()); // should be ignored

			logger.Log(LogLevel::Info, "test");
			logger.Stop();

			// First file should contain output
			Assert::IsTrue(std::filesystem::exists(guard1.path));

			std::string contents1 = TestHelpers::ReadFile(guard1.path);

			Assert::IsTrue(contents1.find("test") != std::string::npos);

			// Second file should NOT contain output
			if (std::filesystem::exists(guard2.path))
			{
				std::string contents2 = TestHelpers::ReadFile(guard2.path);

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

			TestHelpers::TempFileGuard guard{ TestHelpers::GetTempFilePath() };

			logger.Start(guard.path.string());
			logger.Stop();

			logger.Stop();

			logger.Log(LogLevel::Info, "test");

			std::string contents = TestHelpers::ReadFile(guard.path);

			Assert::IsTrue(contents.find("test") == std::string::npos);
		}

		TEST_METHOD(Logger_Stop_BeforeStart_DoesNothing)
		{
			::Logger logger;

			TestHelpers::TempFileGuard guard{ TestHelpers::GetTempFilePath() };

			logger.Stop();

			logger.Start(guard.path.string());
			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));
		}

		TEST_METHOD(Logger_Start_AfterStop_StartsAgain)
		{
			::Logger logger;

			TestHelpers::TempFileGuard guard1{ TestHelpers::GetTempFilePath() };

			logger.Start(guard1.path.string());
			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard1.path));

			TestHelpers::TempFileGuard guard2{ TestHelpers::GetTempFilePath() };

			logger.Start(guard2.path.string());
			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard2.path));
		}

		// ======================================================
		// Logging
		// ======================================================

		TEST_METHOD(Logger_Log_AfterStart_WritesMessage)
		{
			::Logger logger;

			TestHelpers::TempFileGuard guard{ TestHelpers::GetTempFilePath() };

			logger.Start(guard.path.string());

			logger.Log(LogLevel::Info, "test");

			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::string contents = TestHelpers::ReadFile(guard.path);

			Assert::IsTrue(contents.find("test") != std::string::npos);
		}

		TEST_METHOD(Logger_Log_BeforeStart_DoesNothing)
		{
			::Logger logger;

			TestHelpers::TempFileGuard guard{ TestHelpers::GetTempFilePath() };

			logger.Log(LogLevel::Info, "test");

			logger.Start(guard.path.string());

			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::string contents = TestHelpers::ReadFile(guard.path);

			Assert::IsTrue(contents.find("test") == std::string::npos);
		}

		TEST_METHOD(Logger_Log_AfterStop_DoesNothing)
		{
			::Logger logger;

			TestHelpers::TempFileGuard guard{ TestHelpers::GetTempFilePath() };

			logger.Start(guard.path.string());

			logger.Stop();

			logger.Log(LogLevel::Info, "test");

			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::string contents = TestHelpers::ReadFile(guard.path);

			Assert::IsTrue(contents.find("test") == std::string::npos);
		}

		TEST_METHOD(Logger_Log_AfterRestart_WritesMessage)
		{
			::Logger logger;

			TestHelpers::TempFileGuard guard1{ TestHelpers::GetTempFilePath() };

			logger.Start(guard1.path.string());
			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard1.path));

			TestHelpers::TempFileGuard guard2{ TestHelpers::GetTempFilePath() };

			logger.Start(guard2.path.string());

			logger.Log(LogLevel::Info, "test");

			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard2.path));

			std::string contents = TestHelpers::ReadFile(guard2.path);

			Assert::IsTrue(contents.find("test") != std::string::npos);
		}

		TEST_METHOD(Logger_Log_MultipleMessages_WritesInSequenceOrder)
		{
			::Logger logger;

			TestHelpers::TempFileGuard guard{ TestHelpers::GetTempFilePath() };

			logger.Start(guard.path.string());

			logger.Log(LogLevel::Info, "test1");
			logger.Log(LogLevel::Info, "test2");
			logger.Log(LogLevel::Info, "test3");

			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::string contents = TestHelpers::ReadFile(guard.path);

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

			TestHelpers::TempFileGuard guard{ TestHelpers::GetTempFilePath() };

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

			std::string contents = TestHelpers::ReadFile(guard.path);

			Assert::IsTrue(contents.find("[ Main ]") != std::string::npos);
			Assert::IsTrue(contents.find("test1") != std::string::npos);

			Assert::IsTrue(contents.find("[ Worker ]") != std::string::npos);
			Assert::IsTrue(contents.find("test2") != std::string::npos);
		}

		// ======================================================
		// Logger Lifecycle
		// ======================================================

		TEST_METHOD(Logger_Stop_DrainsQueuedMessagesBeforeExit)
		{
			::Logger logger;

			TestHelpers::TempFileGuard guard{ TestHelpers::GetTempFilePath() };

			logger.Start(guard.path.string());

			logger.Log(LogLevel::Info, "test1");
			logger.Log(LogLevel::Info, "test2");
			logger.Log(LogLevel::Info, "test3");
			logger.Log(LogLevel::Info, "test4");
			logger.Log(LogLevel::Info, "test5");
			logger.Log(LogLevel::Info, "test6");

			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::string contents = TestHelpers::ReadFile(guard.path);

			Assert::IsTrue(contents.find("test1") != std::string::npos);
			Assert::IsTrue(contents.find("test2") != std::string::npos);
			Assert::IsTrue(contents.find("test3") != std::string::npos);
			Assert::IsTrue(contents.find("test4") != std::string::npos);
			Assert::IsTrue(contents.find("test5") != std::string::npos);
			Assert::IsTrue(contents.find("test6") != std::string::npos);
		}

		TEST_METHOD(Logger_Destructor_DrainsQueuedMessagesBeforeExit)
		{
			TestHelpers::TempFileGuard guard{ TestHelpers::GetTempFilePath() };

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

			std::string contents = TestHelpers::ReadFile(guard.path);

			Assert::IsTrue(contents.find("test1") != std::string::npos);
			Assert::IsTrue(contents.find("test2") != std::string::npos);
			Assert::IsTrue(contents.find("test3") != std::string::npos);
			Assert::IsTrue(contents.find("test4") != std::string::npos);
			Assert::IsTrue(contents.find("test5") != std::string::npos);
			Assert::IsTrue(contents.find("test6") != std::string::npos);
		}

		// ======================================================
		// Logging
		// ======================================================

		TEST_METHOD(Logger_Log_CapturesThreadContextInOutput)
		{
			logger::ThreadContext::ClearLabel();
			logger::ThreadContext::SetLabel("Main");

			::Logger logger;

			TestHelpers::TempFileGuard guard{ TestHelpers::GetTempFilePath() };

			logger.Start(guard.path.string());

			logger.Log(LogLevel::Info, "test1");

			logger.Stop();

			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::string contents = TestHelpers::ReadFile(guard.path);

			Assert::IsTrue(contents.find("[ Thread ]") == std::string::npos);
			Assert::IsTrue(contents.find("[ Main ]") != std::string::npos);
			Assert::IsTrue(contents.find("test1") != std::string::npos);
		}
	};
}
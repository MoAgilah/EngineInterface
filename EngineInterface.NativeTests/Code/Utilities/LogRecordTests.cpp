#include "CppUnitTest.h"

#include <Utilities/LogRecord.h>
#include <string>
#include <source_location>
#include <thread>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(LogRecordTests)
	{
	public:
		TEST_METHOD(LogLeveltoString_DebugReturnsDEBUG)
		{
			LogLevel lvl = LogLevel::Debug;

			Assert::AreEqual("DEBUG", toString(lvl));
		}

		TEST_METHOD(LogLeveltoString_InfoReturnsINFO)
		{
			LogLevel lvl = LogLevel::Info;

			Assert::AreEqual("INFO", toString(lvl));
		}

		TEST_METHOD(LogLeveltoString_WarningReturnsWARNING)
		{
			LogLevel lvl = LogLevel::Warning;

			Assert::AreEqual("WARNING", toString(lvl));
		}

		TEST_METHOD(LogLeveltoString_ErrorReturnsERROR)
		{
			LogLevel lvl = LogLevel::Error;

			Assert::AreEqual("ERROR", toString(lvl));
		}

		TEST_METHOD(LogLeveltoString_FatalReturnsFATAL)
		{
			LogLevel lvl = LogLevel::Fatal;

			Assert::AreEqual("FATAL", toString(lvl));
		}

		TEST_METHOD(LogLeveltoString_UnknownValueReturnsUNKNOWN)
		{
			LogLevel lvl = static_cast<LogLevel>(999);

			Assert::AreEqual("UNKNOWN", toString(lvl));
		}

		TEST_METHOD(SourceInfoConstructor_PopulatesFileLineColumnAndFunction)
		{
			std::source_location sl = std::source_location::current();

			SourceInfo si(sl);

			Assert::AreEqual(std::string(sl.file_name()), si.file);
			Assert::IsTrue(sl.line() == si.line);
			Assert::IsTrue(sl.column() == si.column);
			Assert::AreEqual(std::string(sl.function_name()), si.function);
		}

		TEST_METHOD(LogRecordConstructor_PopulatesTimestampLevelMessageAndSourceInfo)
		{
			LogLevel lvl(LogLevel::Debug);
			std::string msg("testing");
			std::source_location sl = std::source_location::current();

			auto before = std::chrono::system_clock::now();

			LogRecord rec(lvl, msg, sl);

			auto after = std::chrono::system_clock::now();

			Assert::IsTrue(rec.timestamp >= before);
			Assert::IsTrue(rec.timestamp <= after);
			Assert::IsTrue(rec.logLevel == lvl);
			Assert::AreEqual(msg, rec.message);
			Assert::AreEqual(std::string(sl.file_name()), rec.sourceInfo.file);
			Assert::IsTrue(sl.line() == rec.sourceInfo.line);
			Assert::IsTrue(sl.column() == rec.sourceInfo.column);
			Assert::AreEqual(std::string(sl.function_name()), rec.sourceInfo.function);
		}

		TEST_METHOD(LogRecordConstructor_DefaultsSequenceIdToZero)
		{
			LogRecord rec(LogLevel::Debug, "msg", std::source_location::current());

			Assert::IsTrue(0 == rec.sequenceId);
		}

		TEST_METHOD(LogRecordConstructor_DefaultInitialisesThreadInfo)
		{
			LogRecord rec(LogLevel::Debug, "msg", std::source_location::current());

			Assert::AreEqual(std::string(), rec.threadInfo.optional_thread_label);
			Assert::IsTrue(std::thread::id() == rec.threadInfo.id);
		}
	};
}
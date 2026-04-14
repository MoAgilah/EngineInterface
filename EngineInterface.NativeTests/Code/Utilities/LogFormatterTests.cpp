#include "CppUnitTest.h"

#include <Utilities/LogFormatter.h>
#include <Utilities/LogRecord.h>
#include <string>
#include <source_location>
#include <thread>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
    LogRecord CreateTestLogRecord()
    {
        LogRecord rec(LogLevel::Info, "Test message", std::source_location::current());

        // deterministic overrides
        rec.timestamp = std::chrono::system_clock::time_point{};
        rec.sequenceId = 42;

        rec.threadInfo.id = std::thread::id{};
        rec.threadInfo.optional_thread_label = "TestThread";

        // override source info
        rec.sourceInfo.file = "TestFile.cpp";
        rec.sourceInfo.line = 123;
        rec.sourceInfo.column = 45;
        rec.sourceInfo.function = "TestFunction";

        return rec;
    }

	TEST_CLASS(LogFormatterTests)
	{
	public:

        TEST_METHOD(FormatTimestamp)
        {
            std::string expected = "[ 1970-01-01 00:00:00.0000000 ]";

            auto timestamp = std::chrono::system_clock::time_point{};

            auto res = logger::FormatTimestamp(timestamp);

            Assert::AreEqual(expected, res);
        }

        TEST_METHOD(FormatFilenameTimestamp)
        {
            std::string expected = "1970-01-01_00-00-00.0000000";

            auto timestamp = std::chrono::system_clock::time_point{};

            auto res = logger::FormatFilenameTimestamp(timestamp);

            Assert::AreEqual(expected, res);
        }

        TEST_METHOD(FormatLogLevel)
        {
            std::string expected = "[ DEBUG ]";

            auto lvl = LogLevel::Debug;

            auto res = logger::FormatLogLevel(lvl);

            Assert::AreEqual(expected, res);
        }

        TEST_METHOD(FormatSourceLocation)
        {
            std::string expected = "TestFile.cpp(123,45): TestFunction()";

            SourceInfo si(std::source_location::current());

            // override source info
            si.file = "TestFile.cpp";
            si.line = 123;
            si.column = 45;
            si.function = "TestFunction";

            auto res = logger::FormatSourceLocation(si);

            Assert::AreEqual(expected, res);
        }

        TEST_METHOD(FormatThreadInfo)
        {
            ThreadInfo ti;
            ti.id = std::thread::id{};
            ti.optional_thread_label = "TestThread";

            auto expectedId = std::hash<std::thread::id>{}(ti.id);

            std::string expected = std::format("[ {} ] id-{}", "TestThread", expectedId);

            auto res = logger::FormatThreadInfo(ti);

            Assert::AreEqual(expected, res);
        }

        TEST_METHOD(FormatSequenceID)
        {
            std::string expected = "[#42]";

            uint64_t sid = 42;

            auto res = logger::FormatSequenceID(sid);

            Assert::AreEqual(expected, res);
        }

        TEST_METHOD(FormatRecordWhenShowSourceIsFalse)
        {
            auto rec = CreateTestLogRecord();

            std::string expected = std::format(
                "{} {} {} {}: {}",
                logger::FormatTimestamp(rec.timestamp),
                logger::FormatLogLevel(rec.logLevel),
                logger::FormatSequenceID(rec.sequenceId),
                logger::FormatThreadInfo(rec.threadInfo),
                rec.message
            );

            auto res = logger::FormatRecord(rec);

            Assert::AreEqual(expected, res);
        }

        TEST_METHOD(FormatRecordWhenShowSourceIsTrue)
        {
            auto rec = CreateTestLogRecord();
            rec.logLevel = LogLevel::Warning;

            std::string expected = std::format(
                "{} {} {} {} {}: {}",
                logger::FormatTimestamp(rec.timestamp),
                logger::FormatLogLevel(rec.logLevel),
                logger::FormatSequenceID(rec.sequenceId),
                logger::FormatThreadInfo(rec.threadInfo),
                logger::FormatSourceLocation(rec.sourceInfo),
                rec.message
            );

            auto res = logger::FormatRecord(rec);

            Assert::AreEqual(expected, res);
        }
	};
}
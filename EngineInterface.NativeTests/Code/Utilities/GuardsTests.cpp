#include "CppUnitTest.h"

#include <Utilities/Guards.h>
#include <Utilities/Logger.h>
#include <TestHelpers/TestFilesystemHelpers.h>
#include <TestHelpers/TestDefaultLoggerHelper.h>
#include <memory>
#include <string>
#include <filesystem>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(GuardsTests)
	{
	public:
		TEST_METHOD(CheckNotNull_WhenPtrIsNotNullDoesNotLog)
		{
			TestHelpers::ResetLoggerDefaultsForTests();

			std::unique_ptr<int> ptr = std::make_unique<int>(7);

			::Logger::GetDefaultLogger();

			TestHelpers::TempFileGuard guard{ ::Logger::GetDefaultLogPath() };

			std::string msg = "ptr is null";

			Assert::IsTrue(CheckNotNull(ptr.get(), msg));

			::Logger::GetDefaultLogger().Stop();

			// First file should contain output
			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::string contents = TestHelpers::ReadFile(guard.path);

			Assert::IsTrue(contents.find(msg) == std::string::npos);
		}

		TEST_METHOD(CheckNotNull_WhenPtrIsNullDoesLog)
		{
			TestHelpers::ResetLoggerDefaultsForTests();

			std::unique_ptr<int> ptr = nullptr;

			::Logger::GetDefaultLogger();

			TestHelpers::TempFileGuard guard{ ::Logger::GetDefaultLogPath() };

			std::string msg = "ptr is null";

			Assert::IsFalse(CheckNotNull(ptr.get(), msg));

			::Logger::GetDefaultLogger().Stop();

			// First file should contain output
			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::string contents = TestHelpers::ReadFile(guard.path);

			Assert::IsTrue(contents.find(msg) != std::string::npos);
		}
	};
}
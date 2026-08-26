#include "CppUnitTest.h"

#include <Utilities/Guards.h>
#include <Utilities/Logger.h>
#include <TestHelpers/TestDefaultLoggerHelper.h>
#include <TestHelpers/TestFilesystemHelpers.h>
#include <filesystem>
#include <memory>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(GuardsTests)
	{
	public:
		TEST_METHOD_CLEANUP(TestCleanup)
		{
			TestHelpers::CleanupDefaultLoggerForTests();
		}

		// ======================================================
		// Behaviour
		// ======================================================

		TEST_METHOD(CheckNotNull_WhenPtrIsNotNullDoesNotLog)
		{
			std::unique_ptr<int> ptr = std::make_unique<int>(7);

			::Logger::GetDefaultLogger();

			std::string msg = "ptr is null";

			Assert::IsTrue(CheckNotNull(ptr.get(), msg));

			::Logger::GetDefaultLogger().Stop();

			// First file should contain output
			Assert::IsTrue(std::filesystem::exists(::Logger::GetDefaultLogPath()));

			std::string contents = TestHelpers::ReadFile(::Logger::GetDefaultLogPath());

			Assert::IsTrue(contents.find(msg) == std::string::npos);
		}

		TEST_METHOD(CheckNotNull_WhenPtrIsNullDoesLog)
		{
			std::unique_ptr<int> ptr = nullptr;

			::Logger::GetDefaultLogger();

			std::string msg = "ptr is null";

			Assert::IsFalse(CheckNotNull(ptr.get(), msg));

			::Logger::GetDefaultLogger().Stop();

			// First file should contain output
			Assert::IsTrue(std::filesystem::exists(::Logger::GetDefaultLogPath()));

			std::string contents = TestHelpers::ReadFile(::Logger::GetDefaultLogPath());

			Assert::IsTrue(contents.find(msg) != std::string::npos);
		}
	};
}
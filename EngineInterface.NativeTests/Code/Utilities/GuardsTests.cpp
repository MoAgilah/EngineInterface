#include "CppUnitTest.h"

#include <Utilities/Guards.h>
#include <Utilities/Logger.h>
#include <TestHelpers/TestFilesystemHelpers.h>
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
			std::unique_ptr<int> ptr = std::make_unique<int>(7);

			::Logger logger;

			TestHelpers::TempFileGuard guard{ TestHelpers::GetTempFilePath() };

			logger.Start(guard.path.string());

			std::string msg = "ptr is null";

			Assert::IsTrue(CheckNotNull(ptr.get(), logger, msg));

			logger.Stop();

			// First file should contain output
			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::string contents = TestHelpers::ReadFile(guard.path);

			Assert::IsTrue(contents.find(msg) == std::string::npos);
		}

		TEST_METHOD(CheckNotNull_WhenPtrIsNullDoesLog)
		{
			std::unique_ptr<int> ptr = nullptr;

			::Logger logger;

			TestHelpers::TempFileGuard guard{ TestHelpers::GetTempFilePath() };

			logger.Start(guard.path.string());

			std::string msg = "ptr is null";

			Assert::IsFalse(CheckNotNull(ptr.get(), logger, msg));

			logger.Stop();

			// First file should contain output
			Assert::IsTrue(std::filesystem::exists(guard.path));

			std::string contents = TestHelpers::ReadFile(guard.path);

			Assert::IsTrue(contents.find(msg) != std::string::npos);
		}
	};
}
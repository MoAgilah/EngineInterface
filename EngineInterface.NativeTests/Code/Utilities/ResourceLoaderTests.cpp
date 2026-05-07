#include "CppUnitTest.h"

#include <Utilities/ResourceLoader.h>
#include <TestHelpers/TestFilesystemHelpers.h>
#include <Fakes/Resources/FakeLoadableResource.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(ResourceLoaderTests)
	{
	public:

		// ======================================================
		// Resource Loading
		// ======================================================

		TEST_METHOD(ResourceLoader_IsValidDirectory_ReturnsFalse_OnNonExistentPath)
		{
			auto path = std::filesystem::temp_directory_path() / "nonexistent_dir_test";

			std::filesystem::remove_all(path); // ensure it's gone

			Assert::IsFalse(ResourceUtils::IsValidDirectory(path));
		}

		TEST_METHOD(ResourceLoader_IsValidDirectory_ReturnsFalse_OnFilePath)
		{
			TestHelpers::TempDirGuard temp;

			auto filePath = temp.path / "test.txt";
			std::ofstream(filePath) << "test";

			Assert::IsFalse(ResourceUtils::IsValidDirectory(filePath));
		}

		TEST_METHOD(ResourceLoader_IsValidDirectory_ReturnsTrue_OnDirectoryPath)
		{
			TestHelpers::TempDirGuard temp;

			Assert::IsTrue(ResourceUtils::IsValidDirectory(temp.path));
		}

		// ======================================================
		// Clean Name Access
		// ======================================================

		TEST_METHOD(ResourceLoader_GetCleanName_RemovesExtension_OnValidFile)
		{
			TestHelpers::TempDirGuard temp;

			auto filePath = temp.path / "test.txt";
			std::ofstream(filePath) << "test";

			auto name = ResourceUtils::GetCleanName(filePath);

			Assert::AreEqual(std::string("test"), name);
		}

		TEST_METHOD(ResourceLoader_GetCleanName_ReturnsFilename_OnFileWithoutExtension)
		{
			TestHelpers::TempDirGuard temp;

			auto filePath = temp.path / "test";

			auto name = ResourceUtils::GetCleanName(filePath);

			Assert::AreEqual(std::string("test"), name);
		}

		// ======================================================
		// Resource Loading
		// ======================================================

		TEST_METHOD(ResourceLoader_LoadResources_FailsGracefully_OnInvalidPath)
		{
			auto path = std::filesystem::temp_directory_path() / "nonexistent_dir_test";

			std::filesystem::remove_all(path);

			ResourceLoader<FakeLoadableResource> loader;

			loader.LoadResources(path);

			Assert::AreEqual(size_t(0), loader.GetResourceCount());
		}

		TEST_METHOD(ResourceLoader_LoadResources_ReturnsNoResources_OnEmptyDirectory)
		{
			TestHelpers::TempDirGuard temp;

			ResourceLoader<FakeLoadableResource> loader;

			loader.LoadResources(temp.path);

			Assert::AreEqual(size_t(0), loader.GetResourceCount());
		}

		TEST_METHOD(ResourceLoader_LoadResources_LoadsAllFiles_OnValidDirectory)
		{
			TestHelpers::TempDirGuard temp;

			std::ofstream(temp.path / "one.txt") << "File one content";
			std::ofstream(temp.path / "two.txt") << "File two content";

			ResourceLoader<FakeLoadableResource> loader;

			loader.LoadResources(temp.path);

			Assert::AreEqual(size_t(2), loader.GetResourceCount());
			Assert::IsNotNull(loader.GetResource("one"));
			Assert::IsNotNull(loader.GetResource("two"));
		}

		TEST_METHOD(ResourceLoader_LoadResources_SkipsFiles_OnLoadFailure)
		{
			TestHelpers::TempDirGuard temp;

			std::ofstream(temp.path / "one.txt") << "File one content";
			std::ofstream(temp.path / "two.txt");

			ResourceLoader<FakeLoadableResource> loader;

			loader.LoadResources(temp.path);

			Assert::AreEqual(size_t(1), loader.GetResourceCount());
			Assert::IsNotNull(loader.GetResource("one"));
			Assert::IsNull(loader.GetResource("two"));
		}

		// ======================================================
		// Resource Access
		// ======================================================

		TEST_METHOD(ResourceLoader_GetResource_ReturnsNull_OnInvalidName)
		{
			TestHelpers::TempDirGuard temp;

			std::ofstream(temp.path / "one.txt") << "File one content";

			ResourceLoader<FakeLoadableResource> loader;
			loader.LoadResources(temp.path);

			Assert::IsNotNull(loader.GetResource("one"));
			Assert::IsNull(loader.GetResource("two"));
		}

		TEST_METHOD(ResourceLoader_GetResource_ReturnsValidResource_OnValidName)
		{
			TestHelpers::TempDirGuard temp;

			std::ofstream(temp.path / "one.txt") << "File one content";
			std::ofstream(temp.path / "two.txt") << "File two content";

			ResourceLoader<FakeLoadableResource> loader;

			loader.LoadResources(temp.path);

			Assert::IsNotNull(loader.GetResource("one"));
			Assert::IsNotNull(loader.GetResource("two"));
		}
	};
}
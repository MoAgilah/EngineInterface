#include "CppUnitTest.h"

#include <Utilities/MovementController.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(EnumUtilsTests)
	{
	public:
		TEST_METHOD(ToInt_EnumValue_ReturnsUnderlyingInt)
		{
			enum class TestMovement
			{
				Walk = 0,
				Run = 1
			};

			Assert::AreEqual(0, ToInt(TestMovement::Walk));
			Assert::AreEqual(1, ToInt(TestMovement::Run));
		}
	};
}
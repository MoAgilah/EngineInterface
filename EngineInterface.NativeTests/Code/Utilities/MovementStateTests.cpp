#include "CppUnitTest.h"

#include <Utilities/MovementController.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(MovementStateTests)
	{
	public:

		// ======================================================
		// Movement Values
		// ======================================================

		TEST_METHOD(MovementState_AddVelocity_StoresVelocity)
		{
			MovementState ms;

			ms.AddVelocity(0, 1.5f);

			Assert::AreEqual(1.5f, ms.GetVelocity(0), 0.001f);
		}

		TEST_METHOD(MovementState_AddVelocity_WithSameKeyWillNotOverride)
		{
			MovementState ms;

			ms.AddVelocity(0, 1.5f);
			ms.AddVelocity(0, 2.5f);

			Assert::AreEqual(1.5f, ms.GetVelocity(0), 0.001f);
		}

		TEST_METHOD(MovementState_AddAcceleration_StoresAcceleration)
		{
			MovementState ms;

			ms.AddAcceleration(0, 1.5f);

			Assert::AreEqual(1.5f, ms.GetAcceleration(0), 0.001f);
		}

		TEST_METHOD(MovementState_AddAcceleration_WithSameKeyWillNotOverride)
		{
			MovementState ms;

			ms.AddAcceleration(0, 1.5f);
			ms.AddAcceleration(0, 2.5f);

			Assert::AreEqual(1.5f, ms.GetAcceleration(0), 0.001f);
		}

		TEST_METHOD(MovementState_AddDeceleration_StoresDeceleration)
		{
			MovementState ms;

			ms.AddDeceleration(0, 1.5f);

			Assert::AreEqual(1.5f, ms.GetDeceleration(0), 0.001f);
		}

		TEST_METHOD(MovementState_AddDeceleration_WithSameKeyWillNotOverride)
		{
			MovementState ms;

			ms.AddDeceleration(0, 1.5f);
			ms.AddDeceleration(0, 2.5f);

			Assert::AreEqual(1.5f, ms.GetDeceleration(0), 0.001f);
		}

		TEST_METHOD(MovementState_GetVelocity_ReturnsStoredVelocity)
		{
			MovementState ms;

			ms.AddVelocity(0, 1.5f);
			ms.AddVelocity(1, 2.5f);

			Assert::AreEqual(1.5f, ms.GetVelocity(0), 0.001f);
			Assert::AreEqual(2.5f, ms.GetVelocity(1), 0.001f);
		}

		TEST_METHOD(MovementState_GetVelocity_ReturnsZeroWhenKeyNotFound)
		{
			MovementState ms;

			Assert::AreEqual(0.0f, ms.GetVelocity(0), 0.001f);
		}

		TEST_METHOD(MovementState_GetAcceleration_ReturnsStoredAcceleration)
		{
			MovementState ms;

			ms.AddAcceleration(0, 1.5f);
			ms.AddAcceleration(1, 2.5f);

			Assert::AreEqual(1.5f, ms.GetAcceleration(0), 0.001f);
			Assert::AreEqual(2.5f, ms.GetAcceleration(1), 0.001f);
		}

		TEST_METHOD(MovementState_GetAcceleration_ReturnsZeroWhenKeyNotFound)
		{
			MovementState ms;

			Assert::AreEqual(0.0f, ms.GetAcceleration(0), 0.001f);
		}

		TEST_METHOD(MovementState_GetDeceleration_ReturnsStoredDeceleration)
		{
			MovementState ms;

			ms.AddDeceleration(0, 1.5f);
			ms.AddDeceleration(1, 2.5f);

			Assert::AreEqual(1.5f, ms.GetDeceleration(0), 0.001f);
			Assert::AreEqual(2.5f, ms.GetDeceleration(1), 0.001f);
		}

		TEST_METHOD(MovementState_GetDeceleration_ReturnsZeroWhenKeyNotFound)
		{
			MovementState ms;

			Assert::AreEqual(0.0f, ms.GetDeceleration(0), 0.001f);
		}

		TEST_METHOD(MovementState_SetCurrentVelLimit_AssignsCurrentVelocity)
		{
			MovementState ms;

			ms.AddVelocity(0, 1.5f);
			ms.AddVelocity(1, 2.5f);

			ms.SetCurrentVelLimit(1);

			Assert::AreEqual(2.5f, ms.GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementState_GetCurrentVelLimit_ReturnsCurrentVelocity)
		{
			MovementState ms;

			ms.AddVelocity(0, 1.5f);
			ms.AddVelocity(1, 2.5f);

			ms.SetCurrentVelLimit(1);
			Assert::AreEqual(2.5f, ms.GetCurrentVelLimit(), 0.001f);

			ms.SetCurrentVelLimit(0);
			Assert::AreEqual(1.5f, ms.GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementState_GetCurrentVelLimit_ReturnsZeroWhenNotAssigned)
		{
			MovementState ms;

			Assert::AreEqual(0.0f, ms.GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementState_SetCurrentVelLimit_WithInvalidKeySetsZero)
		{
			MovementState ms;

			ms.SetCurrentVelLimit(99);

			Assert::AreEqual(0.0f, ms.GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementState_SetCurrentAccel_AssignsCurrentAcceleration)
		{
			MovementState ms;

			ms.AddAcceleration(0, 1.5f);
			ms.AddAcceleration(1, 2.5f);

			ms.SetCurrentAccel(1);

			Assert::AreEqual(2.5f, ms.GetCurrentAccel(), 0.001f);
		}

		TEST_METHOD(MovementState_GetCurrentAccel_ReturnsCurrentAcceleration)
		{
			MovementState ms;

			ms.AddAcceleration(0, 1.5f);
			ms.AddAcceleration(1, 2.5f);

			ms.SetCurrentAccel(1);
			Assert::AreEqual(2.5f, ms.GetCurrentAccel(), 0.001f);

			ms.SetCurrentAccel(0);
			Assert::AreEqual(1.5f, ms.GetCurrentAccel(), 0.001f);
		}

		TEST_METHOD(MovementState_GetCurrentAccel_ReturnsZeroWhenNotAssigned)
		{
			MovementState ms;

			Assert::AreEqual(0.0f, ms.GetCurrentAccel(), 0.001f);
		}

		TEST_METHOD(MovementState_SetCurrentAccel_WithInvalidKeySetsZero)
		{
			MovementState ms;

			ms.SetCurrentAccel(99);

			Assert::AreEqual(0.0f, ms.GetCurrentAccel(), 0.001f);
		}

		TEST_METHOD(MovementState_SetCurrentDecel_AssignsCurrentDeceleration)
		{
			MovementState ms;

			ms.AddDeceleration(0, 1.5f);
			ms.AddDeceleration(1, 2.5f);

			ms.SetCurrentDecel(1);

			Assert::AreEqual(2.5f, ms.GetCurrentDecel(), 0.001f);
		}

		TEST_METHOD(MovementState_GetCurrentDecel_ReturnsCurrentDeceleration)
		{
			MovementState ms;

			ms.AddDeceleration(0, 1.5f);
			ms.AddDeceleration(1, 2.5f);

			ms.SetCurrentDecel(1);
			Assert::AreEqual(2.5f, ms.GetCurrentDecel(), 0.001f);

			ms.SetCurrentDecel(0);
			Assert::AreEqual(1.5f, ms.GetCurrentDecel(), 0.001f);
		}

		TEST_METHOD(MovementState_GetCurrentDecel_ReturnsZeroWhenNotAssigned)
		{
			MovementState ms;

			Assert::AreEqual(0.0f, ms.GetCurrentDecel(), 0.001f);
		}

		TEST_METHOD(MovementState_SetCurrentDecel_WithInvalidKeySetsZero)
		{
			MovementState ms;

			ms.SetCurrentDecel(99);

			Assert::AreEqual(0.0f, ms.GetCurrentDecel(), 0.001f);
		}
	};
}
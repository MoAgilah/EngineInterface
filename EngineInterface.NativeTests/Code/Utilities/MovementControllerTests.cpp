#include "CppUnitTest.h"

#include <Utilities/MovementController.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(MovementControllerTests)
	{
	public:
		TEST_METHOD(MovementController_GetCurrentXState_ReturnsDefaultMovementXStateWhenNotAssigned)
		{
			MovementController mc;

			Assert::AreEqual(0.0f, mc.GetCurrentXState().GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementController_GetCurrentYState_ReturnsDefaultMovementYStateWhenNotAssigned)
		{
			MovementController mc;

			Assert::AreEqual(0.0f, mc.GetCurrentYState().GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementController_AddMovementXState_CanAddMovementXState)
		{
			MovementState msX;
			msX.AddVelocity(0, 1.5f);
			msX.SetCurrentVelLimit(0);

			MovementController mc;
			mc.AddMovementXState(0, msX);
			mc.ChangeMovementXState(0);

			Assert::AreEqual(1.5f, mc.GetCurrentXState().GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementController_AddMovementYState_CanAddMovementYState)
		{
			MovementState msY;
			msY.AddVelocity(0, 1.5f);
			msY.SetCurrentVelLimit(0);

			MovementController mc;
			mc.AddMovementYState(0, msY);
			mc.ChangeMovementYState(0);

			Assert::AreEqual(1.5f, mc.GetCurrentYState().GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementController_ChangeMovementXState_CanChangeMovementXState)
		{
			MovementState msX1;
			msX1.AddVelocity(0, 1.5f);
			msX1.SetCurrentVelLimit(0);

			MovementState msX2;
			msX2.AddVelocity(0, 2.5f);
			msX2.SetCurrentVelLimit(0);

			MovementController mc;
			mc.AddMovementXState(0, msX1);
			mc.AddMovementXState(1, msX2);
			mc.ChangeMovementXState(0);

			Assert::AreEqual(1.5f, mc.GetCurrentXState().GetCurrentVelLimit(), 0.001f);

			mc.ChangeMovementXState(1);

			Assert::AreEqual(2.5f, mc.GetCurrentXState().GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementController_ChangeMovementYState_CanChangeMovementYState)
		{
			MovementState msY1;
			msY1.AddVelocity(0, 1.5f);
			msY1.SetCurrentVelLimit(0);

			MovementState msY2;
			msY2.AddVelocity(0, 2.5f);
			msY2.SetCurrentVelLimit(0);

			MovementController mc;
			mc.AddMovementYState(0, msY1);
			mc.AddMovementYState(1, msY2);
			mc.ChangeMovementYState(0);

			Assert::AreEqual(1.5f, mc.GetCurrentYState().GetCurrentVelLimit(), 0.001f);

			mc.ChangeMovementYState(1);

			Assert::AreEqual(2.5f, mc.GetCurrentYState().GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementController_GetCurrentXState_ReturnsAssignedMovementXState)
		{
			MovementState msX;
			msX.AddVelocity(0, 1.5f);
			msX.SetCurrentVelLimit(0);

			MovementController mc;
			mc.AddMovementXState(0, msX);
			mc.ChangeMovementXState(0);

			Assert::AreEqual(1.5f, mc.GetCurrentXState().GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementController_GetCurrentYState_ReturnsAssignedMovementYState)
		{
			MovementState msY;
			msY.AddVelocity(0, 1.5f);
			msY.SetCurrentVelLimit(0);

			MovementController mc;
			mc.AddMovementYState(0, msY);
			mc.ChangeMovementYState(0);

			Assert::AreEqual(1.5f, mc.GetCurrentYState().GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentVelLimitForXState_UpdatesCurrentVelocity)
		{
			MovementState msX;
			msX.AddVelocity(0, 1.5f);
			msX.AddVelocity(1, 2.5f);

			MovementController mc;
			mc.AddMovementXState(0, msX);
			mc.ChangeMovementXState(0);

			mc.SetCurrentVelLimitForXState(1);

			Assert::AreEqual(2.5f, mc.GetCurrentXState().GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentVelLimitForYState_UpdatesCurrentVelocity)
		{
			MovementState msY;
			msY.AddVelocity(0, 1.5f);
			msY.AddVelocity(1, 2.5f);

			MovementController mc;
			mc.AddMovementYState(0, msY);
			mc.ChangeMovementYState(0);

			mc.SetCurrentVelLimitForYState(1);

			Assert::AreEqual(2.5f, mc.GetCurrentYState().GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentAccelForXState_UpdatesCurrentAcceleration)
		{
			MovementState msX;
			msX.AddAcceleration(0, 1.5f);
			msX.AddAcceleration(1, 2.5f);

			MovementController mc;
			mc.AddMovementXState(0, msX);
			mc.ChangeMovementXState(0);

			mc.SetCurrentAccelForXState(1);

			Assert::AreEqual(2.5f, mc.GetCurrentXState().GetCurrentAccel(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentAccelForYState_UpdatesCurrentAcceleration)
		{
			MovementState msY;
			msY.AddAcceleration(0, 1.5f);
			msY.AddAcceleration(1, 2.5f);

			MovementController mc;
			mc.AddMovementYState(0, msY);
			mc.ChangeMovementYState(0);

			mc.SetCurrentAccelForYState(1);

			Assert::AreEqual(2.5f, mc.GetCurrentYState().GetCurrentAccel(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentDecelForXState_UpdatesCurrentDeceleration)
		{
			MovementState msX;
			msX.AddDeceleration(0, 1.5f);
			msX.AddDeceleration(1, 2.5f);

			MovementController mc;
			mc.AddMovementXState(0, msX);
			mc.ChangeMovementXState(0);

			mc.SetCurrentDecelForXState(1);

			Assert::AreEqual(2.5f, mc.GetCurrentXState().GetCurrentDecel(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentDecelForYState_UpdatesCurrentDeceleration)
		{
			MovementState msY;
			msY.AddDeceleration(0, 1.5f);
			msY.AddDeceleration(1, 2.5f);

			MovementController mc;
			mc.AddMovementYState(0, msY);
			mc.ChangeMovementYState(0);

			mc.SetCurrentDecelForYState(1);

			Assert::AreEqual(2.5f, mc.GetCurrentYState().GetCurrentDecel(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentVelLimitForXState_WhenNoCurrentState_DoesNothing)
		{
			MovementController mc;

			mc.SetCurrentVelLimitForXState(0);

			Assert::AreEqual(0.0f, mc.GetCurrentXState().GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentVelLimitForYState_WhenNoCurrentState_DoesNothing)
		{
			MovementController mc;

			mc.SetCurrentVelLimitForYState(0);

			Assert::AreEqual(0.0f, mc.GetCurrentYState().GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentAccelForXState_WhenNoCurrentState_DoesNothing)
		{
			MovementController mc;

			mc.SetCurrentAccelForXState(0);

			Assert::AreEqual(0.0f, mc.GetCurrentXState().GetCurrentAccel(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentAccelForYState_WhenNoCurrentState_DoesNothing)
		{
			MovementController mc;

			mc.SetCurrentAccelForYState(0);

			Assert::AreEqual(0.0f, mc.GetCurrentYState().GetCurrentAccel(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentDecelForXState_WhenNoCurrentState_DoesNothing)
		{
			MovementController mc;

			mc.SetCurrentDecelForXState(0);

			Assert::AreEqual(0.0f, mc.GetCurrentXState().GetCurrentDecel(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentDecelForYState_WhenNoCurrentState_DoesNothing)
		{
			MovementController mc;

			mc.SetCurrentDecelForYState(0);

			Assert::AreEqual(0.0f, mc.GetCurrentYState().GetCurrentDecel(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentVelLimitForXState_WithInvalidKeySetsZero)
		{
			MovementState msX;
			msX.AddVelocity(0, 1.5f);

			MovementController mc;
			mc.AddMovementXState(0, msX);
			mc.ChangeMovementXState(0);

			mc.SetCurrentVelLimitForXState(99);

			Assert::AreEqual(0.0f, mc.GetCurrentXState().GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentVelLimitForYState_WithInvalidKeySetsZero)
		{
			MovementState msY;
			msY.AddVelocity(0, 1.5f);

			MovementController mc;
			mc.AddMovementYState(0, msY);
			mc.ChangeMovementYState(0);

			mc.SetCurrentVelLimitForYState(99);

			Assert::AreEqual(0.0f, mc.GetCurrentYState().GetCurrentVelLimit(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentAccelForXState_WithInvalidKeySetsZero)
		{
			MovementState msX;
			msX.AddAcceleration(0, 1.5f);

			MovementController mc;
			mc.AddMovementXState(0, msX);
			mc.ChangeMovementXState(0);

			mc.SetCurrentAccelForXState(99);

			Assert::AreEqual(0.0f, mc.GetCurrentXState().GetCurrentAccel(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentAccelForYState_WithInvalidKeySetsZero)
		{
			MovementState msY;
			msY.AddAcceleration(0, 1.5f);

			MovementController mc;
			mc.AddMovementYState(0, msY);
			mc.ChangeMovementYState(0);

			mc.SetCurrentAccelForYState(99);

			Assert::AreEqual(0.0f, mc.GetCurrentYState().GetCurrentAccel(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentDecelForXState_WithInvalidKeySetsZero)
		{
			MovementState msX;
			msX.AddDeceleration(0, 1.5f);

			MovementController mc;
			mc.AddMovementXState(0, msX);
			mc.ChangeMovementXState(0);

			mc.SetCurrentDecelForXState(99);

			Assert::AreEqual(0.0f, mc.GetCurrentXState().GetCurrentDecel(), 0.001f);
		}

		TEST_METHOD(MovementController_SetCurrentDecelForYState_WithInvalidKeySetsZero)
		{
			MovementState msY;
			msY.AddDeceleration(0, 1.5f);

			MovementController mc;
			mc.AddMovementYState(0, msY);
			mc.ChangeMovementYState(0);

			mc.SetCurrentDecelForYState(99);

			Assert::AreEqual(0.0f, mc.GetCurrentYState().GetCurrentDecel(), 0.001f);
		}
	};
}
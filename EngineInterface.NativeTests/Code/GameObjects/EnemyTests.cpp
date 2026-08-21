#include "CppUnitTest.h"

#include <Engine/Core/GameManager.h>
#include <Fakes/Collisions/FakeBoundingBox.h>
#include <Fakes/Drawables/FakeSprite.h>
#include <Fakes/Drawables/FakeShape.h>
#include <Fakes/Collisions/FakeCollisionManager.h>
#include <Fakes/GameObjects/TestableEnemy.h>
#include <Fakes/Renderer/FakeCamera.h>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameObjects
{
	TEST_CLASS(EnemyTests)
	{
	public:

		// ======================================================
		// Constructor
		// ======================================================

		TEST_METHOD(Enemy_Constructor_SetsLivesToMaxLives)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			int maxLives = 1;

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), maxLives);

			Assert::AreEqual(maxLives, enmy.GetNumLivesForTesting());
		}

		// ======================================================
		// Active State
		// ======================================================

		TEST_METHOD(Enemy_GetActive_WhenAliveAndBaseActive_ReturnsTrue)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			bool active = true;

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), active, true, Vector2f(16.f, 16.f), 1);

			Assert::IsTrue(enmy.GetActive());
		}

		TEST_METHOD(Enemy_GetActive_WhenDead_ReturnsFalse)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			bool active = true;

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), active, true, Vector2f(16.f, 16.f), 1);

			Assert::IsTrue(enmy.GetActive());

			enmy.DecrementLife();

			enmy.Update(0.25f);

			Assert::IsFalse(enmy.GetActive());
		}

		TEST_METHOD(Enemy_GetActive_WhenBaseInactive_ReturnsFalse)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			bool active = true;

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), active, true, Vector2f(16.f, 16.f), 1);

			Assert::IsTrue(enmy.GetActive());

			enmy.SetActive(false);

			Assert::IsFalse(enmy.GetActive());
		}

		// ======================================================
		// Lives
		// ======================================================

		TEST_METHOD(Enemy_HasLifes_WhenLivesRemain_ReturnsTrue)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::IsTrue(enmy.HasLifes());
		}

		TEST_METHOD(Enemy_DecrementLife_DecrementsLives)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::AreEqual(1, enmy.GetNumLivesForTesting());

			enmy.DecrementLife();

			Assert::AreEqual(0, enmy.GetNumLivesForTesting());
		}

		TEST_METHOD(Enemy_DecrementLife_WhenLivesRemain_DoesNotCallDie)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 2);

			Assert::AreEqual(2, enmy.GetNumLivesForTesting());

			enmy.DecrementLife();

			Assert::AreEqual(0, enmy.dieCount);
		}

		TEST_METHOD(Enemy_DecrementLife_WhenLivesReachZero_CallsDie)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::AreEqual(1, enmy.GetNumLivesForTesting());

			enmy.DecrementLife();

			Assert::AreEqual(1, enmy.dieCount);
		}

		TEST_METHOD(Enemy_DecrementLife_WhenAlreadyZero_DoesNotCallDieAgain)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::AreEqual(1, enmy.GetNumLivesForTesting());

			enmy.DecrementLife();

			Assert::AreEqual(1, enmy.dieCount);

			enmy.DecrementLife();

			Assert::AreEqual(1, enmy.dieCount);
		}

		TEST_METHOD(Enemy_HasLifes_WhenLivesReachZero_ReturnsFalse)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeSprite>("obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::AreEqual(1, enmy.GetNumLivesForTesting());

			enmy.DecrementLife();

			Assert::IsFalse(enmy.HasLifes());
		}

		// ======================================================
		// Alive State
		// ======================================================

		TEST_METHOD(Enemy_GetIsAlive_ReturnsDefaultTrue)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::IsTrue(enmy.GetIsAlive());
		}

		// ======================================================
		// Airbourne State
		// ======================================================

		TEST_METHOD(Enemy_GetAirbourne_ReturnsDefaultFalse)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::IsFalse(enmy.GetAirbourne());
		}

		TEST_METHOD(Enemy_SetAirbourne_UpdatesAirbourne)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::IsFalse(enmy.GetAirbourne());

			enmy.SetAirbourne(true);

			Assert::IsTrue(enmy.GetAirbourne());
		}

		// ======================================================
		// Invulnerability
		// ======================================================

		TEST_METHOD(Enemy_GetInvulnerable_ReturnsDefaultFalse)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::IsFalse(enmy.GetInvulnerabe());
		}

		TEST_METHOD(Enemy_SetInvulnerability_UpdatesInvulnerability)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::IsFalse(enmy.GetInvulnerabe());

			enmy.SetInvulnerability(true);

			Assert::IsTrue(enmy.GetInvulnerabe());
		}

		// ======================================================
		// Speed Access
		// ======================================================

		TEST_METHOD(Enemy_GetSpeedX_ReturnsDefault)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::AreEqual(0.f, enmy.GetSpeedX());
		}

		TEST_METHOD(Enemy_SetSpeedX_UpdatesSpeedX)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			enmy.SetSpeedX(1.f);

			Assert::AreEqual(1.f, enmy.GetSpeedX());
		}

		TEST_METHOD(Enemy_GetSpeedY_ReturnsDefault)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::AreEqual(0.f, enmy.GetSpeedY());
		}

		TEST_METHOD(Enemy_SetSpeedY_UpdatesSpeedY)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			enmy.SetSpeedY(1.f);

			Assert::AreEqual(1.f, enmy.GetSpeedY());
		}

		// ======================================================
		// Direction
		// ======================================================

		TEST_METHOD(Enemy_GetDirection_ReturnsDefault)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			bool dir = true;

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, dir, Vector2f(16.f, 16.f), 1);

			Assert::IsTrue(enmy.GetDirection());
		}

		TEST_METHOD(Enemy_SetDirection_UpdatesDirection)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			bool dir = true;

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, dir, Vector2f(16.f, 16.f), 1);

			enmy.SetDirection(false);

			Assert::IsFalse(enmy.GetDirection());
		}

		TEST_METHOD(Enemy_SetDirectionTrue_SetsPositiveXVelocity)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			bool dir = false;

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, dir, Vector2f(16.f, 16.f), 1);

			enmy.SetSpeedX(1.f);

			enmy.SetDirection(enmy.GetDirection());

			Assert::AreEqual(-1.f, enmy.GetXVelocity());

			enmy.SetDirection(true);

			Assert::AreEqual(1.f, enmy.GetXVelocity());
		}

		TEST_METHOD(Enemy_SetDirectionFalse_SetsNegativeXVelocity)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			bool dir = true;

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, dir, Vector2f(16.f, 16.f), 1);

			enmy.SetSpeedX(1.f);

			enmy.SetDirection(enmy.GetDirection());

			Assert::AreEqual(1.f, enmy.GetXVelocity());

			enmy.SetDirection(false);

			Assert::AreEqual(-1.f, enmy.GetXVelocity());
		}

		TEST_METHOD(Enemy_SetDirection_WithSprite_UpdatesSpriteDirection)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			bool dir = true;

			TestableEnemy enmy(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), true, dir, Vector2f(16.f, 16.f), 1);

			enmy.SetDirection(enmy.GetDirection());

			auto drw = enmy.GetDrawable();
			Assert::IsNotNull(drw);

			auto spr = dynamic_cast<FakeSprite*>(drw);
			Assert::IsNotNull(spr);

			Assert::IsTrue(spr->direction);

			enmy.SetDirection(false);

			Assert::IsFalse(spr->direction);
		}

		TEST_METHOD(Enemy_SetDirection_WithNonSpriteDrawable_DoesNotThrow)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			bool dir = true;

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, dir, Vector2f(16.f, 16.f), 1);

			enmy.SetDirection(false);
		}


		// ======================================================
		// Air Timer
		// ======================================================

		TEST_METHOD(Enemy_GetAirTimer_ReturnsTimer)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::IsNotNull(enmy.GetAirTimer());
		}

		TEST_METHOD(Enemy_SetAirTime_UpdatesAirTimer)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			auto airTimer = enmy.GetAirTimer();
			Assert::IsNotNull(airTimer);

			float airTime = 1.f;

			enmy.SetAirTime(airTime);

			Assert::AreEqual(airTime, airTimer->GetMaxTime());
			Assert::AreEqual(airTime, airTimer->GetCurrTime());
		}

		// ======================================================
		// Activation Timer
		// ======================================================

		TEST_METHOD(Enemy_SetTimeLeftActive_UpdatesActivationTimer)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			float actTime = 1.f;

			enmy.SetTimeLeftActive(actTime);

			auto actTimer = enmy.GetActivationTimerForTesting();
			Assert::IsNotNull(actTimer);

			Assert::AreEqual(actTime, actTimer->GetMaxTime());
			Assert::AreEqual(actTime, actTimer->GetCurrTime());
		}

		// ======================================================
		// Reset
		// ======================================================

		TEST_METHOD(Enemy_Reset_PerformsDynamicGameObjectReset)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			enmy.SetVelocity(Vector2f(1.f, 0.5f));

			enmy.SetOnGround(true);

			enmy.Reset();

			auto vel = enmy.GetVelocity();

			Assert::AreEqual(0.f, vel.x);
			Assert::AreEqual(0.f, vel.y);

			Assert::IsFalse(enmy.GetOnGround());
		}

		TEST_METHOD(Enemy_Reset_SetsAliveTrue)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			enmy.DecrementLife();

			enmy.Update(0.25f);

			Assert::IsFalse(enmy.GetIsAlive());

			enmy.Reset();

			Assert::IsTrue(enmy.GetIsAlive());
		}

		TEST_METHOD(Enemy_Reset_RestoresLivesToMaxLives)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			enmy.DecrementLife();

			Assert::AreEqual(0, enmy.GetNumLivesForTesting());

			enmy.Reset();

			Assert::AreEqual(enmy.GetMaxLivesForTesting(), enmy.GetNumLivesForTesting());
		}

		TEST_METHOD(Enemy_Reset_SetsResetAllowedFalse)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			enmy.SetResetAllowedForTesting(true);

			Assert::IsTrue(enmy.GetResetAllowedForTesting());

			enmy.Reset();

			Assert::IsFalse(enmy.GetResetAllowedForTesting());
		}

		TEST_METHOD(Enemy_Reset_SetsInvulnerableFalse)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			enmy.SetInvulnerability(true);

			Assert::IsTrue(enmy.GetInvulnerabe());

			enmy.Reset();

			Assert::IsFalse(enmy.GetInvulnerabe());
		}

		TEST_METHOD(Enemy_Reset_RestartsResetTimer)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			auto resTimer = enmy.GetResetTimerForTesting();
			Assert::IsNotNull(resTimer);

			resTimer->SetMaxTime(1.f);
			resTimer->RestartTimer();

			for (size_t i = 0; i < 3; i++)
			{
				resTimer->Update(0.25f);
			}

			Assert::AreEqual(0.25f, resTimer->GetCurrTime());

			enmy.Reset();

			Assert::AreEqual(resTimer->GetMaxTime(), resTimer->GetCurrTime());
		}

		TEST_METHOD(Enemy_Reset_RestartsActivationTimer)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			auto actTimer = enmy.GetActivationTimerForTesting();
			Assert::IsNotNull(actTimer);

			actTimer->SetMaxTime(1.f);
			actTimer->RestartTimer();

			for (size_t i = 0; i < 3; i++)
			{
				actTimer->Update(0.25f);
			}

			Assert::AreEqual(0.25f, actTimer->GetCurrTime());

			enmy.Reset();

			Assert::AreEqual(actTimer->GetMaxTime(), actTimer->GetCurrTime());
		}

		// ======================================================
		// Update - Active
		// ======================================================

		TEST_METHOD(Enemy_Update_WhenActive_CallsAnimate)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::AreEqual(0, enmy.animateCount);

			enmy.Update(0.25f);

			Assert::AreEqual(1, enmy.animateCount);
		}

		TEST_METHOD(Enemy_Update_WhenActive_PassesDeltaTimeToAnimate)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::AreEqual(0.f, enmy.lastAnimateDeltaTime);

			enmy.Update(0.25f);

			Assert::AreEqual(0.25f, enmy.lastAnimateDeltaTime);
		}

		TEST_METHOD(Enemy_Update_WhenActiveAndHasLives_DoesNotKillEnemy)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			enmy.Update(0.25f);

			Assert::IsTrue(enmy.HasLifes());
			Assert::IsTrue(enmy.GetActive());
		}

		TEST_METHOD(Enemy_Update_WhenActiveAndNoLives_UpdatesActivationTimer)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			enmy.SetTimeLeftActive(1.f);

			enmy.DecrementLife();

			enmy.Update(0.25f);

			auto actTimer = enmy.GetActivationTimerForTesting();
			Assert::IsNotNull(actTimer);

			Assert::AreEqual(0.75f, actTimer->GetCurrTime());
			Assert::IsTrue(enmy.GetIsAlive());
		}

		TEST_METHOD(Enemy_Update_WhenActivationTimerEnds_SetsAliveFalse)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::IsTrue(enmy.GetIsAlive());

			enmy.DecrementLife();

			enmy.Update(0.25f);

			auto actTimer = enmy.GetActivationTimerForTesting();
			Assert::IsNotNull(actTimer);

			Assert::IsTrue(actTimer->CheckEnd());
			Assert::IsFalse(enmy.GetIsAlive());
		}

		// ======================================================
		// Update - Inactive
		// ======================================================

		TEST_METHOD(Enemy_Update_WhenInactive_FirstEnablesReset)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			Assert::IsFalse(enmy.GetResetAllowedForTesting());

			enmy.SetActive(false);

			enmy.Update(0.25f);

			Assert::IsTrue(enmy.GetResetAllowedForTesting());
		}

		TEST_METHOD(Enemy_Update_WhenInactive_UpdatesResetTimer)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			auto resTimer = enmy.GetResetTimerForTesting();
			Assert::IsNotNull(resTimer);

			resTimer->SetMaxTime(1.f);

			enmy.SetActive(false);

			enmy.Update(0.25f);

			Assert::AreEqual(0.75f, resTimer->GetCurrTime());
		}

		TEST_METHOD(Enemy_Update_WhenResetTimerEnds_WithoutGameManager_DoesNothing)
		{
			std::shared_ptr<TestableEnemy> enmy = 0;

			{
				GameManager gm;
				gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

				enmy = std::make_shared<TestableEnemy>(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);
			}

			Assert::IsNotNull(enmy.get());

			auto resTimer = enmy->GetResetTimerForTesting();
			Assert::IsNotNull(resTimer);

			enmy->SetActive(false);

			enmy->Update(0.25f);

			Assert::IsTrue(enmy->GetResetAllowedForTesting());

			Assert::IsTrue(resTimer->CheckEnd());

			Assert::IsTrue(enmy->GetResetAllowedForTesting());
		}

		TEST_METHOD(Enemy_Update_WhenResetTimerEnds_WithoutCamera_DoesNothing)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			auto resTimer = enmy.GetResetTimerForTesting();
			Assert::IsNotNull(resTimer);

			enmy.SetActive(false);

			enmy.Update(0.25f);

			Assert::IsTrue(enmy.GetResetAllowedForTesting());

			Assert::IsTrue(resTimer->CheckEnd());

			Assert::IsTrue(enmy.GetResetAllowedForTesting());
		}

		TEST_METHOD(Enemy_Update_WhenResetTimerEndsAndCameraBoundsTrue_CallsReset)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			auto cam = std::make_shared<FakeCamera>();
			cam->checkVerticalBounds = true;

			gm.SetCamera(cam);

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			auto resTimer = enmy.GetResetTimerForTesting();
			Assert::IsNotNull(resTimer);

			enmy.SetActive(false);

			resTimer->SetMaxTime(0.5f);

			enmy.Update(0.25f);

			Assert::IsTrue(enmy.GetResetAllowedForTesting());

			enmy.Update(0.25f);

			Assert::IsFalse(enmy.GetResetAllowedForTesting());
		}

		TEST_METHOD(Enemy_Update_WhenResetTimerEndsAndCameraBoundsFalse_DoesNotReset)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			auto cam = std::make_shared<FakeCamera>();
			cam->checkVerticalBounds = false;

			gm.SetCamera(cam);

			TestableEnemy enmy(std::make_shared<FakeBox>(), std::make_shared<FakeBoundingBox>(), true, true, Vector2f(16.f, 16.f), 1);

			auto resTimer = enmy.GetResetTimerForTesting();
			Assert::IsNotNull(resTimer);

			enmy.SetActive(false);

			resTimer->SetMaxTime(0.5f);

			enmy.Update(0.25f);

			Assert::IsTrue(enmy.GetResetAllowedForTesting());

			enmy.Update(0.25f);

			Assert::IsTrue(enmy.GetResetAllowedForTesting());
		}
	};
}
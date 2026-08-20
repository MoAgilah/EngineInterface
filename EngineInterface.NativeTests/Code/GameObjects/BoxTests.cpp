#include "CppUnitTest.h"

#include <Engine/Core/GameManager.h>
#include <Fakes/Collisions/FakeBoundingBox.h>
#include <Fakes/Drawables/FakeSprite.h>
#include <Fakes/Drawables/FakeShape.h>
#include <Fakes/Collisions/FakeCollisionManager.h>
#include <GameObjects/Box.h>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameObjects
{
	TEST_CLASS(BoxTests)
	{
	public:
		// ======================================================
		// Constructor / Initialisation
		// ======================================================

		TEST_METHOD(Box_Constructor_SetsInitialActiveTrue)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			Assert::IsTrue(box.GetInitialActive());
		}

		TEST_METHOD(Box_Constructor_SetsActiveTrue)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			Assert::IsTrue(box.GetActive());
		}

		TEST_METHOD(Box_Constructor_SetsInitialDirectionTrue)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			Assert::IsTrue(box.GetInitialDirection());
		}

		TEST_METHOD(Box_Constructor_SetsDirectionTrue)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			Assert::IsTrue(box.GetDirection());
		}

		TEST_METHOD(Box_Constructor_SetsInitialPosition)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			auto pos = box.GetInitialPosition();

			Assert::AreEqual(16.f, pos.x);
			Assert::AreEqual(16.f, pos.y);
		}

		TEST_METHOD(Box_Constructor_SetsPosition)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			auto pos = box.GetPosition();

			Assert::AreEqual(16.f, pos.x);
			Assert::AreEqual(16.f, pos.y);
		}

		TEST_METHOD(Box_Constructor_UpdatesVolumePosition)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			auto vol = box.GetVolume();
			Assert::IsNotNull(vol);

			auto pos = vol->GetPosition();

			Assert::AreEqual(16.f, pos.x);
			Assert::AreEqual(16.f, pos.y);
		}


		// ======================================================
		// Hit State
		// ======================================================

		TEST_METHOD(Box_GetCanHit_ReturnsDefaultTrue)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			Assert::IsTrue(box.GetCanHit());
		}

		TEST_METHOD(Box_SetCanHit_UpdatesCanHit)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			box.SetCanHit(false);

			Assert::IsFalse(box.GetCanHit());
		}

		TEST_METHOD(Box_GetJustHit_ReturnsDefaultFalse)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			Assert::IsFalse(box.GetJustHit());
		}

		TEST_METHOD(Box_SetJustHit_UpdatesJustHit)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			box.SetJustHit(true);

			Assert::IsTrue(box.GetJustHit());
		}

		TEST_METHOD(Box_WasJustHit_WhenCanHit_SetsJustHitTrue)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			Assert::IsFalse(box.GetJustHit());
			Assert::IsTrue(box.GetCanHit());

			box.WasJustHit();

			Assert::IsTrue(box.GetJustHit());
		}

		TEST_METHOD(Box_WasJustHit_WhenCannotHit_DoesNotSetJustHit)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			Assert::IsFalse(box.GetJustHit());

			box.SetCanHit(false);

			box.WasJustHit();

			Assert::IsFalse(box.GetJustHit());
		}

		// ======================================================
		// Reset
		// ======================================================

		TEST_METHOD(Box_Reset_SetsCanHitTrue)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			box.SetCanHit(false);

			box.Reset();

			Assert::IsTrue(box.GetCanHit());
		}

		TEST_METHOD(Box_Reset_SetsJustHitFalse)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			box.SetJustHit(true);

			box.Reset();

			Assert::IsFalse(box.GetJustHit());
		}

		TEST_METHOD(Box_Reset_PerformsGameObjectReset)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Box box(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			box.SetActive(false);
			box.SetDirection(false);
			box.SetPosition(Vector2f(32.f, 32.f));

			box.Reset();

			Assert::IsTrue(box.GetActive());
			Assert::IsTrue(box.GetDirection());

			auto pos = box.GetPosition();

			Assert::AreEqual(16.f, pos.x);
			Assert::AreEqual(16.f, pos.y);
		}
	};
}
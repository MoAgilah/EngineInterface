#include "CppUnitTest.h"

#include <Engine/Core/GameManager.h>
#include <Engine/Collisions/BoundingBox.h>
#include <Fakes/Collisions/FakeBoundingBox.h>
#include <Fakes/Drawables/FakeSprite.h>
#include <Fakes/Renderer/FakeCamera.h>
#include <Fakes/Renderer/FakeRenderer.h>
#include <Fakes/Drawables/FakeShape.h>
#include <Fakes/Collisions/FakeCollisionManager.h>
#include <Fakes/GameObjects/TestableGameObject.h>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameObjects
{
	TEST_CLASS(GameObjectTests)
	{
	public:

		// ======================================================
		// GameObject Constructor
		// ======================================================

		TEST_METHOD(GameObject_DefaultConstructor_DoesNotThrow)
		{
			TestableGameObject go;
		}

		TEST_METHOD(GameObject_DefaultConstructor_IncrementsObjectID)
		{
			TestableGameObject::s_objectNum = 0;

			TestableGameObject go1;
			TestableGameObject go2;

			Assert::AreEqual(0, go1.GetObjectNum());
			Assert::AreEqual(1, go2.GetObjectNum());
		}

		TEST_METHOD(GameObject_Constructor_WithNullDrawable_Throws)
		{
			Assert::ExpectException<std::invalid_argument>([]
				{
					TestableGameObject go(nullptr, nullptr);
				});
		}

		TEST_METHOD(GameObject_Constructor_WithNullVolume_Throws)
		{
			Assert::ExpectException<std::invalid_argument>([]
				{
					TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), nullptr);
				});
		}

		TEST_METHOD(GameObject_Constructor_WithoutGameManager_Throws)
		{
			Assert::ExpectException<std::runtime_error>([]
				{
					TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());
				});
		}

		TEST_METHOD(GameObject_Constructor_WithoutCollisionManager_Throws)
		{
			GameManager gm;

			Assert::ExpectException<std::runtime_error>([]
				{
					TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());
				});
		}


		TEST_METHOD(GameObject_Constructor_IncrementsObjectID)
		{
			TestableGameObject::s_objectNum = 0;

			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go1(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());
			TestableGameObject go2(std::make_shared<FakeSprite>("Obj2"), std::make_shared<FakeBoundingBox>());

			Assert::AreEqual(0, go1.GetObjectNum());
			Assert::AreEqual(1, go2.GetObjectNum());
		}

		TEST_METHOD(GameObject_Constructor_AppliesGameScale)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());

			auto scale = go.GetScale();

			Assert::AreEqual(GameConstants::Scale.x, scale.x);
			Assert::AreEqual(GameConstants::Scale.y, scale.y);
		}

		TEST_METHOD(GameObject_Constructor_AddsObjectToCollisionManager)
		{
			GameManager gm;
			auto colMgr = std::make_shared<FakeCollisionManager>(nullptr);
			gm.SetCollisionManager(colMgr);

			Assert::IsTrue(colMgr->GetCollidables().empty());

			TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());

			Assert::IsFalse(colMgr->GetCollidables().empty());
			Assert::AreEqual(
				std::size_t(1),
				colMgr->GetCollidables().size()
			);
		}

		// ======================================================
		// GameObject Destructor
		// ======================================================

		TEST_METHOD(GameObject_Destructor_RemovesObjectFromCollisionManager)
		{
			GameManager gm;
			auto colMgr = std::make_shared<FakeCollisionManager>(nullptr);
			gm.SetCollisionManager(colMgr);

			Assert::IsTrue(colMgr->GetCollidables().empty());

			{
				TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());

				Assert::AreEqual(
					std::size_t(1),
					colMgr->GetCollidables().size()
				);
			}

			Assert::AreEqual(
				std::size_t(0),
				colMgr->GetCollidables().size()
			);
		}

		// ======================================================
		// GameObject Render
		// ======================================================

		TEST_METHOD(GameObject_Render_WithNullRenderer_DoesNothing)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());

			go.Render(nullptr);

			auto spr = dynamic_cast<FakeSprite*>(go.GetDrawable());

			Assert::IsNotNull(spr);

			Assert::AreEqual(0, spr->renderCount);
		}

		TEST_METHOD(GameObject_Render_WithNullDrawable_DoesNothing)
		{
			TestableGameObject go;

			FakeRenderer fr;

			go.Render(&fr);
		}

		TEST_METHOD(GameObject_Render_CallsDrawableRender)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));
			gm.SetRenderer(std::make_shared<FakeRenderer>());

			auto spr = std::make_shared<FakeSprite>("Obj1");

			TestableGameObject go(spr, std::make_shared<FakeBoundingBox>());

			Assert::AreEqual(0, spr->renderCount);

			go.Render(gm.GetRenderer());

			Assert::AreEqual(1, spr->renderCount);
		}

#ifdef _DEBUG
		TEST_METHOD(GameObject_Render_WithNullVolume_DoesNotThrow)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));
			gm.SetRenderer(std::make_shared<FakeRenderer>());

			TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());

			go.SetVolumeForTesting(nullptr);

			go.Render(gm.GetRenderer());
		}

		TEST_METHOD(GameObject_Render_CallsVolumeRender)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));
			gm.SetRenderer(std::make_shared<FakeRenderer>());

			auto box = std::make_shared<FakeBoundingBox>();

			TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), box);

			auto* fakeBox = box->GetShape();

			Assert::IsNotNull(fakeBox);

			Assert::AreEqual(0, fakeBox->renderCount);

			go.Render(gm.GetRenderer());

			Assert::AreEqual(1, fakeBox->renderCount);
		}
#endif

		// ======================================================
		// GameObject Static Intersection
		// ======================================================

		TEST_METHOD(GameObject_IntersectsStatic_WithNullObject_ReturnsFalse)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());

			Assert::IsFalse(go.Intersects(nullptr));
		}

		TEST_METHOD(GameObject_IntersectsStatic_WithNullVolume_ReturnsFalse)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go1(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());
			TestableGameObject go2(std::make_shared<FakeSprite>("Obj2"), std::make_shared<FakeBoundingBox>());

			go1.SetVolumeForTesting(nullptr);

			Assert::IsFalse(go1.Intersects(&go2));
		}

		TEST_METHOD(GameObject_IntersectsStatic_WithNullObjectVolume_ReturnsFalse)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go1(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());
			TestableGameObject go2(std::make_shared<FakeSprite>("Obj2"), std::make_shared<FakeBoundingBox>());

			go2.SetVolumeForTesting(nullptr);

			Assert::IsFalse(go1.Intersects(&go2));
		}

		TEST_METHOD(GameObject_IntersectsStatic_CallsVolumeIntersects)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			auto box = std::make_shared<FakeBoundingBox>();

			TestableGameObject go1(std::make_shared<FakeSprite>("Obj1"), box);
			TestableGameObject go2(std::make_shared<FakeSprite>("Obj2"), std::make_shared<FakeBoundingBox>());

			Assert::IsTrue(go1.Intersects(&go2));

			Assert::IsTrue(box->intersectsCalled);
		}

		TEST_METHOD(GameObject_IntersectsStatic_ReturnsVolumeResult)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go1(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			TestableGameObject go2(
				std::make_shared<FakeSprite>("Obj2"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			Assert::IsTrue(go1.Intersects(&go2));
		}

		// ======================================================
		// GameObject Dynamic Intersection
		// ======================================================

		TEST_METHOD(GameObject_IntersectsDynamic_WithNullObject_ReturnsFalse)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());

			float tFirst, tLast = 0;

			Assert::IsFalse(go.Intersects(nullptr, tFirst, tLast));
		}

		TEST_METHOD(GameObject_IntersectsDynamic_WithNullVolume_ReturnsFalse)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());
			TestableDynamicGameObject dgo(std::make_shared<FakeSprite>("Obj2"), std::make_shared<FakeBoundingBox>());

			go.SetVolumeForTesting(nullptr);

			float tFirst, tLast = 0;

			Assert::IsFalse(go.Intersects(&dgo, tFirst, tLast));
		}

		TEST_METHOD(GameObject_IntersectsDynamic_WithNullObjectVolume_ReturnsFalse)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());
			TestableDynamicGameObject dgo(std::make_shared<FakeSprite>("Obj2"), std::make_shared<FakeBoundingBox>());

			dgo.SetVolumeForTesting(nullptr);

			float tFirst, tLast = 0;

			Assert::IsFalse(go.Intersects(&dgo, tFirst, tLast));
		}

		TEST_METHOD(GameObject_IntersectsDynamic_CallsVolumeIntersectsMoving)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			auto box = std::make_shared<FakeBoundingBox>();

			TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), box);
			TestableDynamicGameObject dgo(std::make_shared<FakeSprite>("Obj2"), std::make_shared<FakeBoundingBox>());

			float tFirst, tLast = 0;

			Assert::IsTrue(go.Intersects(&dgo, tFirst, tLast));

			Assert::IsTrue(box->intersectsMovingCalled);
		}

		TEST_METHOD(GameObject_IntersectsDynamic_PassesZeroTesterVelocity)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			auto box = std::make_shared<FakeBoundingBox>();

			TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), box);
			TestableDynamicGameObject dgo(std::make_shared<FakeSprite>("Obj2"), std::make_shared<FakeBoundingBox>());

			float tFirst, tLast = 0;

			Assert::IsTrue(go.Intersects(&dgo, tFirst, tLast));

			Assert::AreEqual(0.f, box->testerVel.x);
			Assert::AreEqual(0.f, box->testerVel.y);
		}

		TEST_METHOD(GameObject_IntersectsDynamic_PassesObjectVelocity)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			auto box = std::make_shared<FakeBoundingBox>();

			TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), box);
			TestableDynamicGameObject dgo(std::make_shared<FakeSprite>("Obj2"), std::make_shared<FakeBoundingBox>());

			dgo.SetVelocity(Vector2f(16.f, 32.f));

			float tFirst, tLast = 0;

			Assert::IsTrue(go.Intersects(&dgo, tFirst, tLast));

			Assert::AreEqual(16.f, box->testeeVel.x);
			Assert::AreEqual(32.f, box->testeeVel.y);
		}

		TEST_METHOD(GameObject_IntersectsDynamic_ReturnsVolumeResult)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			TestableDynamicGameObject dgo(
				std::make_shared<FakeSprite>("Obj2"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(40.0f, 16.0f)
			);

			dgo.SetVelocity(Vector2f(-24.0f, 0.0f));

			float tFirst, tLast = 0;

			Assert::IsTrue(go.Intersects(&dgo, tFirst, tLast));
		}

		// ======================================================
		// GameObject Reset
		// ======================================================

		TEST_METHOD(GameObject_Reset_RestoresInitialActiveState)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			Assert::IsFalse(go.GetActive());

			go.SetActive(true);

			Assert::IsTrue(go.GetActive());

			go.Reset();

			Assert::IsFalse(go.GetActive());
		}

		TEST_METHOD(GameObject_Reset_RestoresInitialDirection)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			Assert::IsTrue(go.GetDirection());

			go.SetDirection(false);

			Assert::IsFalse(go.GetDirection());

			go.Reset();

			Assert::IsTrue(go.GetDirection());
		}

		TEST_METHOD(GameObject_Reset_WithNullDrawable_DoesNotThrow)
		{
			TestableGameObject go;

			go.Reset();
		}

		TEST_METHOD(GameObject_Reset_RestoresInitialPosition)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			auto pos = go.GetPosition();

			Assert::AreEqual(16.f, pos.x);
			Assert::AreEqual(16.f, pos.y);

			go.SetPosition(Vector2f(8.f, 32.f));

			Assert::AreEqual(8.f, go.GetPosition().x);
			Assert::AreEqual(32.f, go.GetPosition().y);

			go.Reset();

			Assert::AreEqual(pos.x, go.GetPosition().x);
			Assert::AreEqual(pos.y, go.GetPosition().y);
		}

		TEST_METHOD(GameObject_Reset_WithNullVolume_DoesNotThrow)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.SetVolumeForTesting(nullptr);

			go.Reset();
		}

		TEST_METHOD(GameObject_Reset_UpdatesVolumeToResetPosition)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.SetPosition(Vector2f(32.f, 48.f));

			go.Reset();

			auto* vol = go.GetVolume();
			Assert::IsNotNull(vol);

			auto pos = vol->GetPosition();

			Assert::AreEqual(16.f, pos.x);
			Assert::AreEqual(16.f, pos.y);
		}

		// ======================================================
		// GameObject Drawable Access
		// ======================================================

		TEST_METHOD(GameObject_GetDrawable_WhenNull_ReturnsNull)
		{
			TestableGameObject go;

			Assert::IsNull(go.GetDrawable());
		}

		TEST_METHOD(GameObject_GetDrawable_ReturnsDrawable)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());

			Assert::IsNotNull(go.GetDrawable());
		}

		// ======================================================
		// GameObject Volume Access
		// ======================================================

		TEST_METHOD(GameObject_GetVolume_WhenNull_ReturnsNull)
		{
			TestableGameObject go;

			Assert::IsNull(go.GetVolume());
		}

		TEST_METHOD(GameObject_GetVolume_ReturnsVolume)
		{
			GameManager gm;
			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());

			Assert::IsNotNull(go.GetVolume());
		}

		// ======================================================
		// GameObject Position Access
		// ======================================================

		TEST_METHOD(GameObject_GetPosition_WithNullDrawable_ReturnsDefault)
		{
			TestableGameObject go;

			auto pos = go.GetPosition();

			Assert::AreEqual(0.f, pos.x);
			Assert::AreEqual(0.f, pos.y);
		}

		TEST_METHOD(GameObject_GetPosition_ReturnsDrawablePosition)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.f, 32.f)
			);

			auto pos = go.GetPosition();

			Assert::AreEqual(16.f, pos.x);
			Assert::AreEqual(32.f, pos.y);
		}

		TEST_METHOD(GameObject_SetPosition_WithNullDrawable_DoesNothing)
		{
			TestableGameObject go;

			go.SetPosition(16.f, 32.f);

			auto pos = go.GetPosition();

			Assert::AreEqual(0.f, pos.x);
			Assert::AreEqual(0.f, pos.y);
		}

		TEST_METHOD(GameObject_SetPosition_UpdatesDrawablePosition)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.f, 32.f)
			);

			go.SetPosition(Vector2f(32.f, 16.f));

			auto pos = go.GetPosition();

			Assert::AreEqual(32.f, pos.x);
			Assert::AreEqual(16.f, pos.y);
		}

		TEST_METHOD(GameObject_SetPositionXY_UpdatesDrawablePosition)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.f, 32.f)
			);

			go.SetPosition(32.f, 16.f);

			auto pos = go.GetPosition();

			Assert::AreEqual(32.f, pos.x);
			Assert::AreEqual(16.f, pos.y);
		}

		// ======================================================
		// GameObject Origin Access
		// ======================================================

		TEST_METHOD(GameObject_GetOrigin_WithNullDrawable_ReturnsDefault)
		{
			TestableGameObject go;

			auto ori = go.GetOrigin();

			Assert::AreEqual(0.f, ori.x);
			Assert::AreEqual(0.f, ori.y);
		}

		TEST_METHOD(GameObject_GetOrigin_ReturnsDrawableOrigin)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.f, 32.f)
			);

			auto ori = go.GetOrigin();

			Assert::AreEqual(8.f, ori.x);
			Assert::AreEqual(8.f, ori.y);
		}

		// ======================================================
		// GameObject Scale Access
		// ======================================================

		TEST_METHOD(GameObject_GetScale_WithNullDrawable_ReturnsDefault)
		{
			TestableGameObject go;

			auto scl = go.GetScale();

			Assert::AreEqual(0.f, scl.x);
			Assert::AreEqual(0.f, scl.y);
		}

		TEST_METHOD(GameObject_GetScale_ReturnsDrawableScale)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.f, 32.f)
			);

			auto scl = go.GetScale();

			Assert::AreEqual(GameConstants::Scale.x, scl.x);
			Assert::AreEqual(GameConstants::Scale.y, scl.y);
		}

		TEST_METHOD(GameObject_SetScale_WithNullDrawable_DoesNothing)
		{
			TestableGameObject go;

			auto scl = go.GetScale();

			go.SetScale(Vector2f(2.f, 2.f));

			Assert::AreEqual(0.f, scl.x);
			Assert::AreEqual(0.f, scl.y);
		}

		TEST_METHOD(GameObject_SetScale_WithNullVolume_DoesNothing)
		{
			GameManager gm;

			gm.SetCollisionManager(
				std::make_shared<FakeCollisionManager>(nullptr)
			);

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(
					Vector2f(16.0f, 16.0f)
				),
				false,
				true,
				Vector2f(16.f, 32.f)
			);

			go.SetVolumeForTesting(nullptr);

			auto* drawable = go.GetDrawable();

			Assert::IsNotNull(drawable);
			Assert::IsNull(go.GetVolume());

			auto scl = drawable->GetScale();

			Assert::AreEqual(GameConstants::Scale.x, scl.x);
			Assert::AreEqual(GameConstants::Scale.y, scl.y);

			go.SetScale(Vector2f(2.f, 2.f));

			scl = drawable->GetScale();

			Assert::AreEqual(GameConstants::Scale.x, scl.x);
			Assert::AreEqual(GameConstants::Scale.y, scl.y);

			scl = go.GetScale();

			Assert::AreEqual(GameConstants::Scale.x, scl.x);
			Assert::AreEqual(GameConstants::Scale.y, scl.y);
		}

		TEST_METHOD(GameObject_SetScale_UpdatesDrawableScale)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.f, 32.f)
			);

			go.SetScale(Vector2f(2.f, 2.f));

			auto scl = go.GetScale();

			Assert::AreEqual(2.f, scl.x);
			Assert::AreEqual(2.f, scl.y);
		}

		TEST_METHOD(GameObject_SetScale_UpdatesVolumeScale)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.f, 32.f)
			);

			go.SetScale(Vector2f(2.f, 2.f));

			auto vol = go.GetVolume();

			Assert::IsNotNull(vol);

			auto scl = vol->GetScale();

			Assert::AreEqual(2.f, scl.x);
			Assert::AreEqual(2.f, scl.y);
		}

		// ======================================================
		// GameObject Restitution Access
		// ======================================================

		TEST_METHOD(GameObject_GetRestitution_ReturnsDefault)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.f, 32.f)
			);

			Assert::AreEqual(1.f, go.GetRestitution());
		}

		TEST_METHOD(GameObject_SetRestitution_UpdatesRestitution)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.f, 32.f)
			);

			go.SetRestitution(0.5f);

			Assert::AreEqual(0.5f, go.GetRestitution());
		}

		// ======================================================
		// GameObject Initial Direction Access
		// ======================================================

		TEST_METHOD(GameObject_GetInitialDirection_ReturnsSpawnDirection)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			bool dir = true;

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				dir,
				Vector2f(16.f, 32.f)
			);

			Assert::AreEqual(dir, go.GetInitialDirection());
		}

		TEST_METHOD(GameObject_SetInitialDirection_UpdatesSpawnDirection)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			bool dir = true;

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				dir,
				Vector2f(16.f, 32.f)
			);

			go.SetInitialDirection(false);

			Assert::AreEqual(false, go.GetInitialDirection());
		}

		// ======================================================
		// GameObject Initial Position Access
		// ======================================================

		TEST_METHOD(GameObject_GetInitialPosition_ReturnsSpawnPosition)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Vector2f pos = Vector2f(16.f, 32.f);

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				pos
			);

			auto retPos = go.GetInitialPosition();

			Assert::AreEqual(pos.x, retPos.x);
			Assert::AreEqual(pos.y, retPos.y);
		}

		TEST_METHOD(GameObject_SetInitialPosition_UpdatesSpawnPosition)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			Vector2f pos = Vector2f(16.f, 32.f);

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				pos
			);

			go.SetInitialPosition(Vector2f(32.f, 16.f));

			auto retPos = go.GetInitialPosition();

			Assert::AreEqual(32.f, retPos.x);
			Assert::AreEqual(16.f, retPos.y);
		}

		// ======================================================
		// GameObject Initial Active Access
		// ======================================================

		TEST_METHOD(GameObject_GetInitialActive_ReturnsSpawnActiveState)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			bool act = false;

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				act,
				true,
				Vector2f(16.f, 32.f)
			);

			Assert::AreEqual(act, go.GetInitialActive());
		}

		TEST_METHOD(GameObject_SetInitialActive_UpdatesSpawnActiveState)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			bool act = false;

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				act,
				true,
				Vector2f(16.f, 32.f)
			);

			go.SetInitialActive(true);

			Assert::AreEqual(true, go.GetInitialActive());
		}

		// ======================================================
		// DynamicGameObject Constructor
		// ======================================================

		TEST_METHOD(DynamicGameObject_DefaultConstructor_DoesNotThrow)
		{
			TestableDynamicGameObject dgo;
		}

		TEST_METHOD(DynamicGameObject_Constructor_DoesNotThrow)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject dgo(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.f, 32.f)
			);
		}

		// ======================================================
		// DynamicGameObject Object Type
		// ======================================================

		TEST_METHOD(DynamicGameObject_IsDynamicObject_ReturnsTrue)
		{
			TestableDynamicGameObject dgo;

			Assert::AreEqual(true, dgo.IsDynamicObject());
		}

		// ======================================================
		// DynamicGameObject Static Intersection
		// ======================================================

		TEST_METHOD(DynamicGameObject_IntersectsStatic_WithNullObject_ReturnsFalse)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject dgo(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());

			Assert::IsFalse(dgo.Intersects(nullptr));
		}

		TEST_METHOD(DynamicGameObject_IntersectsStatic_WithNullVolume_ReturnsFalse)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject dgo(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());
			TestableGameObject go(std::make_shared<FakeSprite>("Obj2"), std::make_shared<FakeBoundingBox>());

			dgo.SetVolumeForTesting(nullptr);

			Assert::IsFalse(dgo.Intersects(&go));
		}

		TEST_METHOD(DynamicGameObject_IntersectsStatic_WithNullObjectVolume_ReturnsFalse)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject dgo(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());
			TestableGameObject go(std::make_shared<FakeSprite>("Obj2"), std::make_shared<FakeBoundingBox>());

			go.SetVolumeForTesting(nullptr);

			Assert::IsFalse(dgo.Intersects(&go));
		}

		TEST_METHOD(DynamicGameObject_IntersectsStatic_PassesSelfAsDynamicObject)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			auto box1 = std::make_shared<FakeBoundingBox>();
			auto box2 = std::make_shared<FakeBoundingBox>();

			TestableDynamicGameObject dgo(std::make_shared<FakeSprite>("Obj1"), box1);
			TestableGameObject go(std::make_shared<FakeSprite>("Obj2"), box2);

			Assert::IsTrue(dgo.Intersects(&go));

			Assert::IsFalse(box1->intersectsCalled);
			Assert::IsFalse(box1->intersectsMovingCalled);
			Assert::IsFalse(box2->intersectsCalled);
			Assert::IsTrue(box2->intersectsMovingCalled);
		}

		TEST_METHOD(DynamicGameObject_IntersectsStatic_ReturnsObjectResult)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject dgo(
				std::make_shared<FakeSprite>("Obj2"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(40.0f, 16.0f)
			);

			dgo.SetVelocity(Vector2f(-24.0f, 0.0f));

			TestableGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			Assert::IsTrue(dgo.Intersects(&go));
		}

		// ======================================================
		// DynamicGameObject Dynamic Intersection
		// ======================================================

		TEST_METHOD(DynamicGameObject_IntersectsDynamic_WithNullObject_ReturnsFalse)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject dgo(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());

			float tFirst, tLast = 0;

			Assert::IsFalse(dgo.Intersects(nullptr, tFirst, tLast));
		}

		TEST_METHOD(DynamicGameObject_IntersectsDynamic_WithNullVolume_ReturnsFalse)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject dgo1(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());
			TestableDynamicGameObject dgo2(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());

			dgo1.SetVolumeForTesting(nullptr);

			float tFirst, tLast = 0;

			Assert::IsFalse(dgo1.Intersects(&dgo2, tFirst, tLast));
		}

		TEST_METHOD(DynamicGameObject_IntersectsDynamic_WithNullObjectVolume_ReturnsFalse)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject dgo1(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());
			TestableDynamicGameObject dgo2(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>());

			dgo2.SetVolumeForTesting(nullptr);

			float tFirst, tLast = 0;

			Assert::IsFalse(dgo1.Intersects(&dgo2, tFirst, tLast));
		}

		TEST_METHOD(DynamicGameObject_IntersectsDynamic_CallsVolumeIntersectsMoving)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			auto box = std::make_shared<FakeBoundingBox>();

			TestableDynamicGameObject dgo1(std::make_shared<FakeSprite>("Obj1"), box);
			TestableDynamicGameObject dgo2(std::make_shared<FakeSprite>("Obj2"), std::make_shared<FakeBoundingBox>());

			float tFirst, tLast = 0;

			Assert::IsTrue(dgo1.Intersects(&dgo2, tFirst, tLast));

			Assert::IsTrue(box->intersectsMovingCalled);
		}

		TEST_METHOD(DynamicGameObject_IntersectsDynamic_PassesOwnVelocity)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			auto box = std::make_shared<FakeBoundingBox>();

			TestableDynamicGameObject dgo1(std::make_shared<FakeSprite>("Obj1"), box);
			TestableDynamicGameObject dgo2(std::make_shared<FakeSprite>("Obj2"), std::make_shared<FakeBoundingBox>());

			float tFirst, tLast = 0;

			dgo1.SetVelocity(Vector2f(16.f, 32.f));

			Assert::IsTrue(dgo1.Intersects(&dgo2, tFirst, tLast));

			Assert::AreEqual(16.f, box->testerVel.x);
			Assert::AreEqual(32.f, box->testerVel.y);
		}

		TEST_METHOD(DynamicGameObject_IntersectsDynamic_PassesObjectVelocity)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			auto box = std::make_shared<FakeBoundingBox>();

			TestableDynamicGameObject dgo1(std::make_shared<FakeSprite>("Obj1"), box);
			TestableDynamicGameObject dgo2(std::make_shared<FakeSprite>("Obj2"), std::make_shared<FakeBoundingBox>());

			float tFirst, tLast = 0;

			dgo2.SetVelocity(Vector2f(32.f, 16.f));

			Assert::IsTrue(dgo1.Intersects(&dgo2, tFirst, tLast));

			Assert::AreEqual(32.f, box->testeeVel.x);
			Assert::AreEqual(16.f, box->testeeVel.y);
		}

		TEST_METHOD(DynamicGameObject_IntersectsDynamic_ReturnsVolumeResult)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject dgo1(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			TestableDynamicGameObject dgo2(
				std::make_shared<FakeSprite>("Obj2"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(40.0f, 16.0f)
			);

			dgo1.SetVelocity(Vector2f(12.f, 0.0f));
			dgo2.SetVelocity(Vector2f(-12.0f, 0.0f));

			float tFirst, tLast = 0;

			Assert::IsTrue(dgo1.Intersects(&dgo2, tFirst, tLast));
		}

		// ======================================================
		// DynamicGameObject Reset
		// ======================================================

		TEST_METHOD(DynamicGameObject_Reset_PerformsGameObjectReset)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			auto pos = go.GetPosition();

			Assert::IsFalse(go.GetActive());
			Assert::IsTrue(go.GetDirection());
			Assert::AreEqual(16.f, pos.x);
			Assert::AreEqual(16.f, pos.y);

			go.SetActive(true);
			go.SetDirection(false);
			go.SetPosition(Vector2f(32.f, 32.f));

			pos = go.GetPosition();

			Assert::IsTrue(go.GetActive());
			Assert::IsFalse(go.GetDirection());
			Assert::AreEqual(32.f, pos.x);
			Assert::AreEqual(32.f, pos.y);

			go.Reset();

			pos = go.GetPosition();

			Assert::IsFalse(go.GetActive());
			Assert::IsTrue(go.GetDirection());
			Assert::AreEqual(16.f, pos.x);
			Assert::AreEqual(16.f, pos.y);
		}

		TEST_METHOD(DynamicGameObject_Reset_SetsVelocityToZero)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.SetVelocity(Vector2f(16.f, 16.f));

			auto vel = go.GetVelocity();

			Assert::AreEqual(16.f, vel.x);
			Assert::AreEqual(16.f, vel.y);

			go.Reset();

			vel = go.GetVelocity();

			Assert::AreEqual(0.f, vel.x);
			Assert::AreEqual(0.f, vel.y);
		}

		TEST_METHOD(DynamicGameObject_Reset_SetsOnGroundFalse)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.SetOnGround(true);

			Assert::IsTrue(go.GetOnGround());

			go.Reset();

			Assert::IsFalse(go.GetOnGround());
		}

		// ======================================================
		// DynamicGameObject Move
		// ======================================================

		TEST_METHOD(DynamicGameObject_Move_WithNullDrawableAndVolume_DoesNothing)
		{
			TestableDynamicGameObject go;

			go.Move(Vector2f(16.f, 16.f));

			auto pos = go.GetPosition();

			Assert::AreEqual(0.f, pos.x);
			Assert::AreEqual(0.f, pos.y);
		}

		TEST_METHOD(DynamicGameObject_Move_WithNullVolume_DoesNothing)
		{
			GameManager gm;

			gm.SetCollisionManager(
				std::make_shared<FakeCollisionManager>(nullptr)
			);

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(
					Vector2f(16.0f, 16.0f)
				),
				false,
				true,
				Vector2f(16.f, 16.f)
			);

			go.SetVolumeForTesting(nullptr);

			auto initialPos = go.GetPosition();
			auto initialPrevPos = go.GetPrevPosition();

			Assert::AreEqual(16.f, initialPos.x);
			Assert::AreEqual(16.f, initialPos.y);

			go.Move(Vector2f(16.f, 8.f));

			auto pos = go.GetPosition();
			auto prevPos = go.GetPrevPosition();

			Assert::AreEqual(initialPos.x, pos.x);
			Assert::AreEqual(initialPos.y, pos.y);

			Assert::AreEqual(initialPrevPos.x, prevPos.x);
			Assert::AreEqual(initialPrevPos.y, prevPos.y);
		}

		TEST_METHOD(DynamicGameObject_Move_SetsPreviousPosition)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.Move(Vector2f(16.f, 8.f));

			auto prevPos = go.GetPrevPosition();

			Assert::AreEqual(16.f, prevPos.x);
			Assert::AreEqual(16.f, prevPos.y);
		}

		TEST_METHOD(DynamicGameObject_Move_OffsetsDrawablePosition)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.Move(Vector2f(16.f, 8.f));

			auto pos = go.GetPosition();

			Assert::AreEqual(32.f, pos.x);
			Assert::AreEqual(24.f, pos.y);
		}

		TEST_METHOD(DynamicGameObject_Move_UpdatesVolumePosition)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.Move(Vector2f(16.f, 8.f));

			auto vol = go.GetVolume();

			Assert::IsNotNull(vol);

			auto pos = vol->GetPosition();

			Assert::AreEqual(32.f, pos.x);
			Assert::AreEqual(24.f, pos.y);
		}

		TEST_METHOD(DynamicGameObject_MoveXY_MovesBySuppliedValues)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.Move(16.f, 8.f);

			auto pos = go.GetPosition();

			Assert::AreEqual(32.f, pos.x);
			Assert::AreEqual(24.f, pos.y);

			auto vol = go.GetVolume();

			Assert::IsNotNull(vol);

			pos = vol->GetPosition();

			Assert::AreEqual(32.f, pos.x);
			Assert::AreEqual(24.f, pos.y);
		}

		// ======================================================
		// DynamicGameObject Previous Position Access
		// ======================================================

		TEST_METHOD(DynamicGameObject_GetPreviousPosition_ReturnsDefault)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			auto prevPos = go.GetPrevPosition();

			Assert::AreEqual(0.f, prevPos.x);
			Assert::AreEqual(0.f, prevPos.y);
		}

		TEST_METHOD(DynamicGameObject_SetPreviousPosition_UpdatesPreviousPosition)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.SetPrevPosition(Vector2f(16.f, 32.f));

			auto prevPos = go.GetPrevPosition();

			Assert::AreEqual(16.f, prevPos.x);
			Assert::AreEqual(32.f, prevPos.y);
		}

		TEST_METHOD(DynamicGameObject_SetPreviousPositionXY_UpdatesPreviousPosition)
		{
			GameManager gm;

			gm.SetCollisionManager(
				std::make_shared<FakeCollisionManager>(nullptr)
			);

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(
					Vector2f(16.0f, 16.0f)
				),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.SetPrevPosition(32.f, 48.f);

			auto prevPos = go.GetPrevPosition();

			Assert::AreEqual(32.f, prevPos.x);
			Assert::AreEqual(48.f, prevPos.y);
		}

		// ======================================================
		// DynamicGameObject X Velocity Access
		// ======================================================

		TEST_METHOD(DynamicGameObject_GetXVelocity_ReturnsDefault)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			Assert::AreEqual(0.f, go.GetXVelocity());
		}

		TEST_METHOD(DynamicGameObject_SetXVelocity_UpdatesXVelocity)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.SetXVelocity(16.f);

			Assert::AreEqual(16.f, go.GetXVelocity());
		}

		TEST_METHOD(DynamicGameObject_IncrementXVelocity_IncrementsXVelocity)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.SetXVelocity(16.f);

			go.IncrementXVelocity(1.f);

			Assert::AreEqual(17.f, go.GetXVelocity());
		}

		TEST_METHOD(DynamicGameObject_DecrementXVelocity_DecrementsXVelocity)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.SetXVelocity(16.f);

			go.DecrementXVelocity(1.f);

			Assert::AreEqual(15.f, go.GetXVelocity());
		}

		// ======================================================
		// DynamicGameObject Y Velocity Access
		// ======================================================

		TEST_METHOD(DynamicGameObject_GetYVelocity_ReturnsDefault)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			Assert::AreEqual(0.f, go.GetYVelocity());
		}

		TEST_METHOD(DynamicGameObject_SetYVelocity_UpdatesYVelocity)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.SetYVelocity(16.f);


			Assert::AreEqual(16.f, go.GetYVelocity());
		}

		TEST_METHOD(DynamicGameObject_IncrementYVelocity_IncrementsYVelocity)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.SetYVelocity(16.f);

			go.IncrementYVelocity(1.f);

			Assert::AreEqual(17.f, go.GetYVelocity());
		}

		TEST_METHOD(DynamicGameObject_DecrementYVelocity_DecrementsYVelocity)
		{
			GameManager gm;

			gm.SetCollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicGameObject go(
				std::make_shared<FakeSprite>("Obj1"),
				std::make_shared<BoundingBox<FakeBox>>(Vector2f(16.0f, 16.0f)),
				false,
				true,
				Vector2f(16.0f, 16.0f)
			);

			go.SetYVelocity(16.f);

			go.DecrementYVelocity(1.f);

			Assert::AreEqual(15.f, go.GetYVelocity());
		}

		// ======================================================
		// IDynamicGameObject State Logic
		// ======================================================

		TEST_METHOD(IDynamicGameObject_SetOnSlopeTrue_SetsOnGroundTrue)
		{
			TestableDynamicGameObject go;

			go.SetOnSlope(true);

			Assert::IsTrue(go.GetOnSlope());
			Assert::IsTrue(go.GetOnGround());
		}

		TEST_METHOD(IDynamicGameObject_SetShouldSlideLeftTrue_ClearsShouldSlideRight)
		{
			TestableDynamicGameObject go;

			go.SetShouldSlideRight(true);

			Assert::IsTrue(go.GetShouldSlideRight());

			go.SetShouldSlideLeft(true);

			Assert::IsTrue(go.GetShouldSlideLeft());
			Assert::IsFalse(go.GetShouldSlideRight());
		}

		TEST_METHOD(IDynamicGameObject_SetShouldSlideRightTrue_ClearsShouldSlideLeft)
		{
			TestableDynamicGameObject go;

			go.SetShouldSlideLeft(true);

			Assert::IsTrue(go.GetShouldSlideLeft());

			go.SetShouldSlideRight(true);

			Assert::IsTrue(go.GetShouldSlideRight());
			Assert::IsFalse(go.GetShouldSlideLeft());
		}

		TEST_METHOD(IDynamicGameObject_SetSlideLeftTrue_ClearsSlideRight)
		{
			TestableDynamicGameObject go;

			go.SetSlideRight(true);

			Assert::IsTrue(go.GetSlideRight());

			go.SetSlideLeft(true);

			Assert::IsTrue(go.GetSlideLeft());
			Assert::IsFalse(go.GetSlideRight());
		}

		TEST_METHOD(IDynamicGameObject_SetSlideRightTrue_ClearsSlideLeft)
		{
			TestableDynamicGameObject go;

			go.SetSlideLeft(true);

			Assert::IsTrue(go.GetSlideLeft());

			go.SetSlideRight(true);

			Assert::IsTrue(go.GetSlideRight());
			Assert::IsFalse(go.GetSlideLeft());
		}

		TEST_METHOD(IDynamicGameObject_GetFacingDirection_WithZeroVelocity_ReturnsDown)
		{
			TestableDynamicGameObject go;

			auto vel = go.GetVelocity();

			Assert::AreEqual(0.f, vel.x);
			Assert::AreEqual(0.f, vel.y);

			Assert::AreEqual(
				static_cast<int>(Direction::DDIR),
				static_cast<int>(go.GetFacingDirection())
			);
		}

		TEST_METHOD(IDynamicGameObject_GetFacingDirection_WithPositiveX_ReturnsRight)
		{
			TestableDynamicGameObject go;

			go.SetXVelocity(1.f);

			auto vel = go.GetVelocity();

			Assert::AreEqual(1.f, vel.x);
			Assert::AreEqual(0.f, vel.y);

			Assert::AreEqual(
				static_cast<int>(Direction::RDIR),
				static_cast<int>(go.GetFacingDirection())
			);
		}

		TEST_METHOD(IDynamicGameObject_GetFacingDirection_WithNegativeX_ReturnsLeft)
		{
			TestableDynamicGameObject go;

			go.SetXVelocity(-1.f);

			auto vel = go.GetVelocity();

			Assert::AreEqual(-1.f, vel.x);
			Assert::AreEqual(0.f, vel.y);

			Assert::AreEqual(
				static_cast<int>(Direction::LDIR),
				static_cast<int>(go.GetFacingDirection())
			);

		}

		TEST_METHOD(IDynamicGameObject_GetFacingDirection_WithPositiveY_ReturnsDown)
		{
			TestableDynamicGameObject go;

			go.SetYVelocity(1.f);

			auto vel = go.GetVelocity();

			Assert::AreEqual(0.f, vel.x);
			Assert::AreEqual(1.f, vel.y);

			Assert::AreEqual(
				static_cast<int>(Direction::DDIR),
				static_cast<int>(go.GetFacingDirection())
			);
		}

		TEST_METHOD(IDynamicGameObject_GetFacingDirection_WithNegativeY_ReturnsUp)
		{
			TestableDynamicGameObject go;

			go.SetYVelocity(-1.f);

			auto vel = go.GetVelocity();

			Assert::AreEqual(0.f, vel.x);
			Assert::AreEqual(-1.f, vel.y);

			Assert::AreEqual(
				static_cast<int>(Direction::UDIR),
				static_cast<int>(go.GetFacingDirection())
			);
		}

		TEST_METHOD(IDynamicGameObject_GetFacingDirection_WhenHorizontalVelocityDominates_UsesHorizontal)
		{
			TestableDynamicGameObject go;

			go.SetVelocity(Vector2f(-2.f, 1.f));

			Assert::AreEqual(
				static_cast<int>(Direction::LDIR),
				static_cast<int>(go.GetFacingDirection())
			);
		}

		TEST_METHOD(IDynamicGameObject_GetFacingDirection_WhenVerticalVelocityDominates_UsesVertical)
		{
			TestableDynamicGameObject go;

			go.SetVelocity(Vector2f(1.f, -2.f));

			Assert::AreEqual(
				static_cast<int>(Direction::UDIR),
				static_cast<int>(go.GetFacingDirection())
			);
		}
	};
}
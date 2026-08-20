#include "CppUnitTest.h"

#include <Engine/Core/GameManager.h>
#include <Fakes/Collisions/FakeBoundingBox.h>
#include <Fakes/Drawables/FakeSprite.h>
#include <Fakes/Drawables/FakeShape.h>
#include <Fakes/Collisions/FakeCollisionManager.h>
#include <Fakes/GameObjects/TestableCollectables.h>
#include <Fakes/GameObjects/TestableGameObject.h>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameObjects
{
	TEST_CLASS(CollectableTests)
	{
	public:

		// ======================================================
		// StaticCollectable Constructor
		// ======================================================

		TEST_METHOD(StaticCollectable_Constructor_SetsInitialActiveTrue)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableStaticCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			Assert::IsTrue(col.GetInitialActive());
		}

		TEST_METHOD(StaticCollectable_Constructor_SetsActiveTrue)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableStaticCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			Assert::IsTrue(col.GetActive());
		}

		TEST_METHOD(StaticCollectable_Constructor_SetsInitialDirectionTrue)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableStaticCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			Assert::IsTrue(col.GetInitialDirection());
		}

		TEST_METHOD(StaticCollectable_Constructor_SetsDirectionTrue)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableStaticCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			Assert::IsTrue(col.GetDirection());
		}

		TEST_METHOD(StaticCollectable_Constructor_SetsInitialPosition)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableStaticCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			auto pos = col.GetInitialPosition();

			Assert::AreEqual(16.f, pos.x);
			Assert::AreEqual(16.f, pos.y);
		}

		TEST_METHOD(StaticCollectable_Constructor_SetsPosition)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableStaticCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			auto pos = col.GetPosition();

			Assert::AreEqual(16.f, pos.x);
			Assert::AreEqual(16.f, pos.y);
		}

		TEST_METHOD(StaticCollectable_Constructor_UpdatesVolumePosition)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableStaticCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			auto vol = col.GetVolume();
			Assert::IsNotNull(vol);

			auto pos = vol->GetPosition();

			Assert::AreEqual(16.f, pos.x);
			Assert::AreEqual(16.f, pos.y);
		}

		// ======================================================
		// StaticCollectable InitCollectable
		// ======================================================
		TEST_METHOD(ICollectable_InitCollectable_WithNullObject_DoesNothing)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableStaticCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			col.SetObjectAsNull();

			col.InitCollectableForTesting(Vector2f(16.f, 16.f));
		}

		TEST_METHOD(ICollectable_InitCollectable_WithNullVolume_DoesNotThrow)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableStaticCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			col.SetVolumeAsNull();

			col.InitCollectableForTesting(Vector2f(16.f, 16.f));
		}

		// ======================================================
		// StaticCollectable Active State
		// ======================================================

		TEST_METHOD(StaticCollectable_GetActive_WhenNotCollectedAndBaseActive_ReturnsTrue)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableStaticCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			Assert::IsFalse(col.GetCollected());
			Assert::IsTrue(col.GetActive());
		}

		TEST_METHOD(StaticCollectable_GetActive_WhenCollected_ReturnsFalse)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableStaticCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			col.SetCollected();

			Assert::IsFalse(col.GetActive());
		}

		TEST_METHOD(StaticCollectable_GetActive_WhenBaseInactive_ReturnsFalse)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableStaticCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			col.SetActive(false);

			Assert::IsFalse(col.GetCollected());
			Assert::IsFalse(col.GetActive());
		}

		// ======================================================
		// StaticCollectable Collect
		// ======================================================

		TEST_METHOD(StaticCollectable_Collect_SetsCollectedTrue)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableStaticCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			TestableGameObject go;

			col.Collect(&go);

			Assert::IsTrue(col.GetCollected());
		}

		TEST_METHOD(StaticCollectable_Collect_ReceivesCollectingObject)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableStaticCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			TestableGameObject go;

			col.Collect(&go);

			Assert::IsNotNull(col.collectedObject);
		}

		// ======================================================
		// DynamicCollectable Constructor / Integration
		// ======================================================

		TEST_METHOD(DynamicCollectable_Constructor_DoesNotThrow)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));
		}

		TEST_METHOD(DynamicCollectable_Constructor_InitialisesPosition)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			auto pos = col.GetPosition();

			Assert::AreEqual(16.f, pos.x);
			Assert::AreEqual(16.f, pos.y);
		}

		TEST_METHOD(DynamicCollectable_Constructor_UpdatesVolumePosition)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			auto vol = col.GetVolume();
			Assert::IsNotNull(vol);

			auto pos = vol->GetPosition();

			Assert::AreEqual(16.f, pos.x);
			Assert::AreEqual(16.f, pos.y);
		}

		// ======================================================
		// DynamicCollectable Active State
		// ======================================================

		TEST_METHOD(DynamicCollectable_GetActive_WhenNotCollectedAndBaseActive_ReturnsTrue)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			Assert::IsFalse(col.GetCollected());
			Assert::IsTrue(col.GetActive());
		}

		TEST_METHOD(DynamicCollectable_GetActive_WhenCollected_ReturnsFalse)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			col.SetCollected();

			Assert::IsFalse(col.GetActive());
		}

		TEST_METHOD(DynamicCollectable_GetActive_WhenBaseInactive_ReturnsFalse)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			col.SetActive(false);

			Assert::IsFalse(col.GetCollected());
			Assert::IsFalse(col.GetActive());
		}

		// ======================================================
		// DynamicCollectable Collect
		// ======================================================

		TEST_METHOD(DynamicCollectable_Collect_SetsCollectedTrue)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			TestableGameObject go;

			col.Collect(&go);

			Assert::IsTrue(col.GetCollected());
		}

		TEST_METHOD(DynamicCollectable_Collect_ReceivesCollectingObject)
		{
			GameManager gm;
			gm.SetICollisionManager(std::make_shared<FakeCollisionManager>(nullptr));

			TestableDynamicCollectable col(std::make_shared<FakeSprite>("Obj1"), std::make_shared<FakeBoundingBox>(), Vector2f(16.f, 16.f));

			TestableGameObject go;

			col.Collect(&go);

			Assert::IsNotNull(col.collectedObject);
		}
	};
}
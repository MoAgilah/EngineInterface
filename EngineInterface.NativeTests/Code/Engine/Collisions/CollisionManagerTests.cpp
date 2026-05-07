#include "CppUnitTest.h"

#include <Engine/Interface/Collisions/ICollisionManager.h>
#include <Engine/Interface/Collisions/ITile.h>
#include <Engine/Collisions/BoundingBox.h>
#include <Fakes/Collisions/FakeCollisionManager.h>
#include <Fakes/Collisions/FakeGrid.h>
#include <Fakes/Collisions/FakeTile.h>
#include <Fakes/Drawables/FakeShape.h>
#include <Fakes/Drawables/FakeSprite.h>
#include <Fakes/GameObjects/FakeGameObject.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Collisions
    {
        TEST_CLASS(CollisionManagerTests)
        {
        public:

            // ======================================================
            // Constructor
            // ======================================================

            TEST_METHOD(CollisionManager_Constructor_AssignsGrid)
            {
                auto grid = std::make_shared<FakeGrid>(2, 10);

                FakeCollisionManager cm(grid);

                auto result = cm.GetGrid();

                Assert::AreEqual(size_t{ 20 }, result.size());
            }

            // ======================================================
            // Add / Store
            // ======================================================

            TEST_METHOD(CollisionManager_AddCollidable_DoesNothingIfNull)
            {
                FakeCollisionManager cm(nullptr);

                cm.AddCollidable(nullptr);

                auto result = cm.GetCollidables();

                Assert::AreEqual(size_t{ 0 }, result.size());
            }

            TEST_METHOD(CollisionManager_AddsCollidable)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject go(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&go);

                auto result = cm.GetCollidables();

                Assert::AreEqual(size_t{ 1 }, result.size());
            }

            // ======================================================
            // Last Added Access
            // ======================================================

            TEST_METHOD(CollisionManager_GetLastAdded_ReturnsNull)
            {
                FakeCollisionManager cm(nullptr);

                Assert::IsNull(cm.GetLastAdded());
            }

            TEST_METHOD(CollisionManager_GetLastAdded_ReturnsLastAdded)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject go(
                    std::make_shared<FakeSprite>("obj1"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&go);

                Assert::IsTrue(&go == cm.GetLastAdded());
            }

            TEST_METHOD(CollisionManager_GetLastAdded_AfterRemoveLastAdded_ReturnsPreviousOrNull)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject go1(std::make_shared<FakeSprite>("obj1"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&go1);

                FakeGameObject go2(std::make_shared<FakeSprite>("obj2"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&go2);

                auto result = cm.GetCollidables();

                Assert::AreEqual(size_t{ 2 }, result.size());

                cm.RemoveLastAdded();

                Assert::IsTrue(&go1 == cm.GetLastAdded());

                cm.RemoveLastAdded();

                Assert::IsNull(cm.GetLastAdded());
            }

            // ======================================================
            // Remove
            // ======================================================

            TEST_METHOD(CollisionManager_RemoveCollidable_DoesNothingIfEmpty)
            {
                FakeCollisionManager cm(nullptr);

                cm.RemoveCollidable(nullptr);

                auto result = cm.GetCollidables();

                Assert::AreEqual(size_t{ 0 }, result.size());
            }

            TEST_METHOD(CollisionManager_RemoveCollidable_IfNotEmpty)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject go(std::make_shared<FakeSprite>("obj1"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&go);

                auto result = cm.GetCollidables();

                Assert::AreEqual(size_t{ 1 }, result.size());

                cm.RemoveCollidable(&go);

                result = cm.GetCollidables();

                Assert::AreEqual(size_t{ 0 }, result.size());
            }

            TEST_METHOD(CollisionManager_RemoveCollidable_RemovesSpecificObject)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject go1(std::make_shared<FakeSprite>("obj1"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&go1);

                FakeGameObject go2(std::make_shared<FakeSprite>("obj2"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&go2);

                auto result = cm.GetCollidables();

                Assert::AreEqual(size_t{ 2 }, result.size());

                cm.RemoveCollidable(&go1);

                result = cm.GetCollidables();

                Assert::AreEqual(size_t{ 1 }, result.size());

                Assert::IsTrue(&go2 == result[0]);
            }

            TEST_METHOD(CollisionManager_RemoveCollidable_WhenObjectNotFound_DoesNothing)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject go(
                    std::make_shared<FakeSprite>("obj1"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );


                FakeGameObject go2(
                    std::make_shared<FakeSprite>("obj2"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&go2);

                auto before = cm.GetCollidables();

                cm.RemoveCollidable(&go);

                auto after = cm.GetCollidables();

                Assert::AreEqual(before.size(), after.size());
                Assert::IsTrue(&go2 == after[0]);
            }

            TEST_METHOD(CollisionManager_RemoveLastAdded_DoesNothingIfEmpty)
            {
                FakeCollisionManager cm(nullptr);

                cm.RemoveLastAdded();

                Assert::AreEqual(size_t{ 0 }, cm.GetCollidables().size());
                Assert::IsNull(cm.GetLastAdded());
            }

            TEST_METHOD(CollisionManager_RemoveLastAdded_IfNotEmpty)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject go(
                    std::make_shared<FakeSprite>("obj1"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&go);

                Assert::AreEqual(size_t{ 1 }, cm.GetCollidables().size());

                cm.RemoveLastAdded();

                Assert::AreEqual(size_t{ 0 }, cm.GetCollidables().size());
            }

            // ======================================================
            // Tile Access
            // ======================================================

            TEST_METHOD(CollisionManager_GetTile_IfEmptyReturnsNull)
            {
                FakeCollisionManager cm(nullptr);

                Assert::IsNull(cm.GetTile(0, 0));
            }

            TEST_METHOD(CollisionManager_GetTile_IfOutOfBoundsReturnsNull)
            {
                auto grid = std::make_shared<FakeGrid>(2, 10);

                FakeCollisionManager cm(grid);

                Assert::IsNull(cm.GetTile(2, 10));
            }

            TEST_METHOD(CollisionManager_GetTile_ReturnsValidTile)
            {
                auto grid = std::make_shared<FakeGrid>(2, 10);

                FakeCollisionManager cm(grid);

                Assert::IsNotNull(cm.GetTile(0, 0));
            }

            // ======================================================
            // Grid Access
            // ======================================================

            TEST_METHOD(CollisionManager_GetGrid_ReturnsEmptyContainerIfEmpty)
            {
                FakeCollisionManager cm(nullptr);

                Assert::IsTrue(cm.GetGrid().empty());
            }

            TEST_METHOD(CollisionManager_GetGrid_ReturnsContainerOfValidTiles)
            {
                auto grid = std::make_shared<FakeGrid>(2, 10);

                FakeCollisionManager cm(grid);

                for (auto* tile : cm.GetGrid())
                    Assert::IsNotNull(tile);
            }

            // ======================================================
            // Collidables Access
            // ======================================================

            TEST_METHOD(CollisionManager_GetCollidables_ReturnsEmptyContainerIfEmpty)
            {
                FakeCollisionManager cm(nullptr);

                Assert::IsTrue(cm.GetCollidables().empty());
            }

            TEST_METHOD(CollisionManager_GetCollidables_ReturnsContainerOfValidCollidables)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject go1(std::make_shared<FakeSprite>("obj1"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&go1);

                FakeGameObject go2(std::make_shared<FakeSprite>("obj2"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&go2);

                for (auto* obj : cm.GetCollidables())
                    Assert::IsNotNull(obj);
            }

            // ======================================================
            // Intersects / Collision
            // ======================================================

            TEST_METHOD(CollisionManager_GetCollisionDirection_WhenSeparationXPositive_ReturnsRDIR)
            {
                auto dir = ICollisionManager::GetCollisionDirection({ 5.f, 1.f }, {}, {});

                Assert::AreEqual(static_cast<int>(Direction::RDIR), static_cast<int>(dir));
            }

            TEST_METHOD(CollisionManager_GetCollisionDirection_WhenSeparationXNegative_ReturnsLDIR)
            {
                auto dir = ICollisionManager::GetCollisionDirection({ -5.f, 1.f }, {}, {});

                Assert::AreEqual(static_cast<int>(Direction::LDIR), static_cast<int>(dir));
            }

            TEST_METHOD(CollisionManager_GetCollisionDirection_WhenSeparationYPositive_ReturnsUDIR)
            {
                auto dir = ICollisionManager::GetCollisionDirection({ 1.f, 5.f }, {}, {});

                Assert::AreEqual(static_cast<int>(Direction::UDIR), static_cast<int>(dir));
            }

            TEST_METHOD(CollisionManager_GetCollisionDirection_WhenSeparationYNegative_ReturnsDDIR)
            {
                auto dir = ICollisionManager::GetCollisionDirection({ 1.f, -5.f }, {}, {});

                Assert::AreEqual(static_cast<int>(Direction::DDIR), static_cast<int>(dir));
            }

            TEST_METHOD(CollisionManager_GetCollisionDirection_WhenSeparationTiedUsesRelativeVelocityX)
            {
                auto dir = ICollisionManager::GetCollisionDirection(
                    { 1.f, 1.f },
                    { 4.f, 0.f },
                    { 1.f, 0.f }
                );

                Assert::AreEqual(static_cast<int>(Direction::RDIR), static_cast<int>(dir));
            }

            TEST_METHOD(CollisionManager_GetCollisionDirection_WhenSeparationTiedUsesRelativeVelocityY)
            {
                auto dir = ICollisionManager::GetCollisionDirection(
                    { 1.f, 1.f },
                    { 0.f, -4.f },
                    { 0.f, 1.f }
                );

                Assert::AreEqual(static_cast<int>(Direction::DDIR), static_cast<int>(dir));
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_WhenObjectIsNull_DoesNothing)
            {
                FakeCollisionManager cm(nullptr);

                cm.ProcessCollisions(nullptr);

                Assert::AreEqual(0, cm.objectToObjectCalls);
                Assert::AreEqual(0, cm.dynamicToObjectCalls);
                Assert::AreEqual(0, cm.dynamicToDynamicCalls);
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_WhenManagerIsEmpty_DoesNothing)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.ProcessCollisions(&obj);

                Assert::AreEqual(0, cm.objectToObjectCalls);
                Assert::AreEqual(0, cm.dynamicToObjectCalls);
                Assert::AreEqual(0, cm.dynamicToDynamicCalls);
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_SkipsSameObject)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&obj);

                cm.ProcessCollisions(&obj);

                Assert::AreEqual(0, cm.objectToObjectCalls);
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_SkipsInactiveObject)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                FakeGameObject other(
                    std::make_shared<FakeSprite>("other"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                other.SetActive(false);

                cm.AddCollidable(&obj);
                cm.AddCollidable(&other);

                cm.ProcessCollisions(&obj);

                Assert::AreEqual(0, cm.objectToObjectCalls);
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_ObjVsObjCollides)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                FakeGameObject other(
                    std::make_shared<FakeSprite>("other"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                obj.SetsIntersects(true);
                obj.SetActive(true);
                other.SetsIntersects(true);
                other.SetActive(true);

                cm.AddCollidable(&obj);
                cm.AddCollidable(&other);

                cm.ProcessCollisions(&obj);

                Assert::AreEqual(1, cm.objectToObjectCalls);
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_ObjVsObjDoesNothingWhenNoIntersection)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                FakeGameObject other(
                    std::make_shared<FakeSprite>("other"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                obj.SetsIntersects(false);
                obj.SetActive(true);
                other.SetsIntersects(false);
                other.SetActive(true);

                cm.AddCollidable(&obj);
                cm.AddCollidable(&other);

                cm.ProcessCollisions(&obj);

                Assert::AreEqual(0, cm.objectToObjectCalls);
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_WithMultipleCollidables_OnlyProcessesActiveIntersectingObjects)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject testObj(
                    std::make_shared<FakeSprite>("otherObj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                testObj.SetsIntersects(true);
                testObj.SetActive(true);

                FakeGameObject obj1(
                    std::make_shared<FakeSprite>("obj1"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                obj1.SetsIntersects(true);
                obj1.SetActive(false);

                FakeGameObject obj2(
                    std::make_shared<FakeSprite>("obj2"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                obj2.SetsIntersects(true);
                obj2.SetActive(true);

                DynamicFakeGameObject dynObj1(
                    std::make_shared<FakeSprite>("dynObj1"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                dynObj1.SetsIntersects(true);
                dynObj1.SetActive(true);

                DynamicFakeGameObject dynObj2(
                    std::make_shared<FakeSprite>("dynObj2"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                dynObj2.SetsIntersects(true);
                dynObj2.SetActive(false);

                cm.AddCollidable(&testObj);
                cm.AddCollidable(&obj1);
                cm.AddCollidable(&obj2);
                cm.AddCollidable(&dynObj1);
                cm.AddCollidable(&dynObj2);

                cm.ProcessCollisions(&testObj);

                Assert::AreEqual(1, cm.objectToObjectCalls);
                Assert::AreEqual(1, cm.dynamicToObjectCalls);
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_ObjVsMultipleObjects_CallsResolutionForEachCollision)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject testObj(
                    std::make_shared<FakeSprite>("testObj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                FakeGameObject obj1(
                    std::make_shared<FakeSprite>("obj1"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                FakeGameObject obj2(
                    std::make_shared<FakeSprite>("obj2"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                testObj.SetsIntersects(true);
                testObj.SetActive(true);
                obj1.SetsIntersects(true);
                obj1.SetActive(true);
                obj2.SetsIntersects(true);
                obj2.SetActive(true);

                cm.AddCollidable(&testObj);
                cm.AddCollidable(&obj1);
                cm.AddCollidable(&obj2);

                cm.ProcessCollisions(&testObj);

                Assert::AreEqual(2, cm.objectToObjectCalls);
                Assert::AreEqual(0, cm.dynamicToObjectCalls);
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_DynamicVsMixedObjects_RoutesEachCollisionCorrectly)
            {
                FakeCollisionManager cm(nullptr);

                DynamicFakeGameObject testObj(
                    std::make_shared<FakeSprite>("otherObj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                testObj.SetsIntersects(true);
                testObj.SetActive(true);

                FakeGameObject obj1(
                    std::make_shared<FakeSprite>("obj1"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                obj1.SetsIntersects(true);
                obj1.SetActive(true);

                FakeGameObject obj2(
                    std::make_shared<FakeSprite>("obj2"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                obj2.SetsIntersects(true);
                obj2.SetActive(true);

                DynamicFakeGameObject dynObj1(
                    std::make_shared<FakeSprite>("dynObj1"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                dynObj1.SetsIntersects(true);
                dynObj1.SetActive(true);

                DynamicFakeGameObject dynObj2(
                    std::make_shared<FakeSprite>("dynObj2"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                dynObj2.SetsIntersects(true);
                dynObj2.SetActive(true);

                cm.AddCollidable(&testObj);
                cm.AddCollidable(&obj1);
                cm.AddCollidable(&obj2);
                cm.AddCollidable(&dynObj1);
                cm.AddCollidable(&dynObj2);

                cm.ProcessCollisions(&testObj);

                Assert::AreEqual(2, cm.dynamicToObjectCalls);
                Assert::AreEqual(2, cm.dynamicToDynamicCalls);
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_DynamicVsObjCollides)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                DynamicFakeGameObject dynObj(
                    std::make_shared<FakeSprite>("dynObj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                obj.SetsIntersects(true);
                obj.SetActive(true);
                dynObj.SetsIntersects(true);
                dynObj.SetActive(true);

                cm.AddCollidable(&obj);
                cm.AddCollidable(&dynObj);

                cm.ProcessCollisions(&dynObj);

                Assert::AreEqual(1, cm.dynamicToObjectCalls);
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_DynamicVsObjDoesNothingWhenNoIntersection)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                DynamicFakeGameObject dynObj(
                    std::make_shared<FakeSprite>("dynObj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                obj.SetsIntersects(false);
                obj.SetActive(true);
                dynObj.SetsIntersects(false);
                dynObj.SetActive(true);

                cm.AddCollidable(&obj);
                cm.AddCollidable(&dynObj);

                cm.ProcessCollisions(&dynObj);

                Assert::AreEqual(0, cm.dynamicToObjectCalls);
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_StaticVsDynamicRoutesToDynamicVsObj)
            {
                FakeCollisionManager cm(nullptr);

                FakeGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                DynamicFakeGameObject dynObj(
                    std::make_shared<FakeSprite>("dynObj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                obj.SetsIntersects(true);
                obj.SetActive(true);
                dynObj.SetsIntersects(true);
                dynObj.SetActive(true);

                cm.AddCollidable(&obj);
                cm.AddCollidable(&dynObj);

                cm.ProcessCollisions(&obj);

                Assert::AreEqual(1, cm.dynamicToObjectCalls);
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_DynamicVsDynamicCollides)
            {
                FakeCollisionManager cm(nullptr);

                DynamicFakeGameObject dynObj(
                    std::make_shared<FakeSprite>("dynObj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                DynamicFakeGameObject other(
                    std::make_shared<FakeSprite>("other"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                dynObj.SetsIntersects(true);
                dynObj.SetActive(true);
                other.SetsIntersects(true);
                other.SetActive(true);

                cm.AddCollidable(&dynObj);
                cm.AddCollidable(&other);

                cm.ProcessCollisions(&dynObj);

                Assert::AreEqual(1, cm.dynamicToDynamicCalls);
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_DynamicVsDynamicDoesNothingWhenNoIntersection)
            {
                FakeCollisionManager cm(nullptr);

                DynamicFakeGameObject dynObj(
                    std::make_shared<FakeSprite>("dynObj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                DynamicFakeGameObject other(
                    std::make_shared<FakeSprite>("other"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                dynObj.SetsIntersects(false);
                dynObj.SetActive(true);
                other.SetsIntersects(false);
                other.SetActive(true);

                cm.AddCollidable(&dynObj);
                cm.AddCollidable(&other);

                cm.ProcessCollisions(&dynObj);

                Assert::AreEqual(0, cm.dynamicToDynamicCalls);
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_WithGridDoesNothingIfNothingCanCollideWithTiles)
            {
                auto grid = std::make_shared<FakeGrid>(2, 10);

                FakeCollisionManager cm(grid);

                DynamicFakeGameObject dynObj(
                    std::make_shared<FakeSprite>("dynObj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&dynObj);

                cm.ProcessCollisions(&dynObj);

                for (auto* tile : cm.GetGrid())
                {
                    auto* fakeTile = static_cast<FakeTile*>(tile);
                    Assert::IsFalse(fakeTile->resolveCollisionCalled);
                }
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_WithGridDoesNothingIfObjIsNull)
            {
                auto grid = std::make_shared<FakeGrid>(2, 10);

                FakeCollisionManager cm(grid);

                cm.ProcessCollisions(nullptr);

                for (auto* tile : cm.GetGrid())
                {
                    auto* fakeTile = static_cast<FakeTile*>(tile);
                    Assert::IsFalse(fakeTile->resolveCollisionCalled);
                }
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_WithGridAndCollidesWithTiles)
            {
                ICollisionManager::s_canCollideWithTile = { typeid(DynamicFakeGameObject) };

                auto grid = std::make_shared<FakeGrid>(2, 10);

                for (auto& tile : grid->GetGrid())
                {
                    tile->SetType(static_cast<int>(Types::GRND));
                }

                FakeCollisionManager cm(grid);

                for (auto* tile : cm.GetGrid())
                {
                    auto* fakeTile = static_cast<FakeTile*>(tile);
                    fakeTile->SetActive(true);
                    fakeTile->SetIntersects(true);
                }

                DynamicFakeGameObject dynObj(
                    std::make_shared<FakeSprite>("dynObj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                dynObj.SetActive(true);
                dynObj.SetsIntersects(true);

                cm.AddCollidable(&dynObj);

                cm.ProcessCollisions(&dynObj);

                for (auto* tile : cm.GetGrid())
                {
                    auto* fakeTile = static_cast<FakeTile*>(tile);
                    Assert::IsTrue(fakeTile->resolveCollisionCalled);
                }

                ICollisionManager::s_canCollideWithTile.clear();
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_WithGridAndEmptyTile_DoesNotResolveTile)
            {
                auto grid = std::make_shared<FakeGrid>(2, 10);

                for (auto& tile : grid->GetGrid())
                {
                    tile->SetType(static_cast<int>(Types::EMPTY));
                }

                FakeCollisionManager cm(grid);

                DynamicFakeGameObject dynObj(
                    std::make_shared<FakeSprite>("dynObj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&dynObj);

                cm.ProcessCollisions(&dynObj);

                for (auto* tile : cm.GetGrid())
                {
                    auto* fakeTile = static_cast<FakeTile*>(tile);

                    Assert::IsTrue(Types::EMPTY == fakeTile->GetType());
                    Assert::IsFalse(fakeTile->resolveCollisionCalled);
                }
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_WithGridAndTileDoesNotIntersect_DoesNotResolveTile)
            {
                ICollisionManager::s_canCollideWithTile = { typeid(DynamicFakeGameObject) };

                auto grid = std::make_shared<FakeGrid>(2, 10);

                for (auto& tile : grid->GetGrid())
                {
                    tile->SetType(static_cast<int>(Types::GRND));
                }

                FakeCollisionManager cm(grid);

                for (auto* tile : cm.GetGrid())
                {
                    auto* fakeTile = static_cast<FakeTile*>(tile);
                    fakeTile->SetActive(true);
                    fakeTile->SetIntersects(false);
                }

                DynamicFakeGameObject dynObj(
                    std::make_shared<FakeSprite>("dynObj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&dynObj);

                cm.ProcessCollisions(&dynObj);

                for (auto* tile : cm.GetGrid())
                {
                    auto* fakeTile = static_cast<FakeTile*>(tile);
                    Assert::IsFalse(fakeTile->resolveCollisionCalled);
                }

                ICollisionManager::s_canCollideWithTile.clear();
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_WithGridAndMultipleTiles_OnlyResolvesIntersectingTiles)
            {
                ICollisionManager::s_canCollideWithTile = { typeid(DynamicFakeGameObject) };

                auto grid = std::make_shared<FakeGrid>(2, 10);

                for (auto& tile : grid->GetGrid())
                {
                    tile->SetType(static_cast<int>(Types::GRND));
                }

                FakeCollisionManager cm(grid);

                auto tiles = cm.GetGrid();

                for (size_t i = 0; i < tiles.size(); ++i)
                {
                    auto* fakeTile = static_cast<FakeTile*>(tiles[i]);
                    fakeTile->SetActive(true);
                    fakeTile->SetIntersects(i % 2 == 0); // every other tile intersects
                }

                DynamicFakeGameObject dynObj(
                    std::make_shared<FakeSprite>("dynObj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&dynObj);

                cm.ProcessCollisions(&dynObj);

                tiles = cm.GetGrid();

                for (size_t i = 0; i < tiles.size(); ++i)
                {
                    auto* fakeTile = static_cast<FakeTile*>(tiles[i]);

                    if (i % 2 == 0)
                        Assert::IsTrue(fakeTile->resolveCollisionCalled);
                    else
                        Assert::IsFalse(fakeTile->resolveCollisionCalled);
                }

                ICollisionManager::s_canCollideWithTile.clear();
            }

            TEST_METHOD(CollisionManager_ProcessCollisions_WithGrid_ForwardsTFirstAndTLastToTileResolution)
            {
                ICollisionManager::s_canCollideWithTile = { typeid(DynamicFakeGameObject) };

                auto grid = std::make_shared<FakeGrid>(2, 10);

                for (auto& tile : grid->GetGrid())
                {
                    tile->SetType(static_cast<int>(Types::GRND));
                }

                FakeCollisionManager cm(grid);

                auto tiles = cm.GetGrid();

                // only one tile intersects
                auto* testTile = static_cast<FakeTile*>(tiles[0]);
                testTile->SetActive(true);
                testTile->SetIntersects(true);

                for (size_t i = 1; i < tiles.size(); ++i)
                {
                    auto* fakeTile = static_cast<FakeTile*>(tiles[i]);
                    fakeTile->SetActive(true);
                    fakeTile->SetIntersects(false);
                }

                DynamicFakeGameObject dynObj(
                    std::make_shared<FakeSprite>("dynObj"),
                    std::make_shared<BoundingBox<FakeBox>>()
                );

                cm.AddCollidable(&dynObj);

                cm.ProcessCollisions(&dynObj);

                Assert::IsTrue(testTile->resolveCollisionCalled);
                Assert::AreEqual(0.1f, testTile->resolvedTFirst);
                Assert::AreEqual(0.9f, testTile->resolvedTLast);

                ICollisionManager::s_canCollideWithTile.clear();
            }


            TEST_METHOD(CollisionManager_CanCollideWithTile_WhenTypeRegistered_ReturnsTrue)
            {
                ICollisionManager::s_canCollideWithTile = { typeid(DynamicFakeGameObject) };

                FakeCollisionManager cm(nullptr);

                Assert::IsTrue(cm.CanCollideWithTile(typeid(DynamicFakeGameObject)));

                ICollisionManager::s_canCollideWithTile.clear();
            }

            TEST_METHOD(CollisionManager_CanCollideWithTile_WhenTypeNotRegistered_ReturnsFalse)
            {
                ICollisionManager::s_canCollideWithTile = { typeid(DynamicFakeGameObject) };

                FakeCollisionManager cm(nullptr);

                Assert::IsFalse(cm.CanCollideWithTile(typeid(FakeGameObject)));

                ICollisionManager::s_canCollideWithTile.clear();
            }
        };
    }
}
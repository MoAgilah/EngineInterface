#include "CppUnitTest.h"

#include <Fakes/Drawables/FakeSprite.h>
#include <Fakes/Collisions/TestableTile.h>
#include <Fakes/Collisions/FakeBoundingBox.h>
#include <Fakes/GameObjects/FakeGameObject.h>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Collisions
    {
        TEST_CLASS(TileTests)
        {
        public:
            // ======================================================
            // Constructor
            // ======================================================

            TEST_METHOD(Tile_Constructor_WithValidBoundingBox_DoesNotThrow)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(), nullptr);
            }

            TEST_METHOD(Tile_Constructor_ThrowsWithoutValidBoundingBox)
            {
                Assert::ExpectException<std::invalid_argument>([]
                    {
                        TestableTile tile(0, 0, nullptr, nullptr);
                    });
            }

            TEST_METHOD(Tile_Constructor_SetsBoundingBox)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(), nullptr);

                Assert::IsNotNull(tile.GetBoundingBox());
            }

            TEST_METHOD(Tile_Constructor_SetsColNum)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(), nullptr);

                Assert::AreEqual(0, tile.GetColNum());
            }

            TEST_METHOD(Tile_Constructor_SetsRowNum)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(), nullptr);

                Assert::AreEqual(0, tile.GetRowNum());
            }

            TEST_METHOD(Tile_Constructor_SetsID)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(), nullptr);

                Assert::AreEqual(std::string_view("0,0"), tile.GetID());
            }

            TEST_METHOD(Tile_Constructor_SetsSlope)
            {
                auto triangle = std::make_shared<FakeTriangle>(
                    std::array<Vector2f, 3>
                {
                    Vector2f(0, 0),
                    Vector2f(1, 1),
                    Vector2f(1, 0)
                },
                    Vector2f(0, 0)
                );

                TestableTile tile(
                    0,
                    0,
                    std::make_shared<FakeBoundingBox>(),
                    triangle
                );

                Line2f slope = tile.GetSlope(0, 1);

                Assert::AreEqual(0.f, slope.start.x);
                Assert::AreEqual(0.f, slope.start.y);

                Assert::AreEqual(1.f, slope.end.x);
                Assert::AreEqual(1.f, slope.end.y);
            }

            TEST_METHOD(Tile_Constructor_SetsDefaultTypeToEmpty)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(), nullptr);

                Assert::IsTrue(TileTypes::EMPTY == tile.GetType());
            }

            TEST_METHOD(Tile_Constructor_SetsDefaultActiveToFalse)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(), nullptr);

                Assert::IsFalse(tile.GetActive());
            }

            TEST_METHOD(Tile_Constructor_WithNegativeCoordinates_Throws)
            {
                Assert::ExpectException<std::invalid_argument>([]
                    {
                        TestableTile tile(-1, -1, std::make_shared<FakeBoundingBox>(), nullptr);
                    });
            }

            // ======================================================
            // Position / Origin
            // ======================================================

            TEST_METHOD(Tile_GetPosition_ReturnsBoundingBoxPosition)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16, 16), Vector2f(16,16)), nullptr);

                auto* aabb = tile.GetBoundingBox();

                Assert::IsNotNull(aabb);

                auto boxPos = aabb->GetPosition();

                Assert::AreEqual(16.f, boxPos.x);
                Assert::AreEqual(16.f, boxPos.y);

                auto tilePos = tile.GetPosition();

                Assert::AreEqual(boxPos.x, tilePos.x);
                Assert::AreEqual(boxPos.y, tilePos.y);
            }

            TEST_METHOD(Tile_GetOrigin_ReturnsBoundingBoxOrigin)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16, 16), Vector2f(16, 16)), nullptr);

                auto* aabb = tile.GetBoundingBox();

                Assert::IsNotNull(aabb);

                auto boxOri = aabb->GetOrigin();

                Assert::AreEqual(8.f, boxOri.x);
                Assert::AreEqual(8.f, boxOri.y);

                auto tileOri = tile.GetOrigin();

                Assert::AreEqual(boxOri.x, tileOri.x);
                Assert::AreEqual(boxOri.y, tileOri.y);
            }

            TEST_METHOD(Tile_SetPosition_UpdatesBoundingBox)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16, 16), Vector2f(16, 16)), nullptr);

                tile.SetPosition(Vector2f(32.f, 32.f));

                auto* aabb = tile.GetBoundingBox();

                Assert::IsNotNull(aabb);

                auto boxPos = aabb->GetPosition();

                Assert::AreEqual(32.f, boxPos.x);
                Assert::AreEqual(32.f, boxPos.y);

                auto tilePos = tile.GetPosition();

                Assert::AreEqual(boxPos.x, tilePos.x);
                Assert::AreEqual(boxPos.y, tilePos.y);
            }

            TEST_METHOD(Tile_SetOrigin_UpdatesBoundingBox)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16, 16), Vector2f(16, 16)), nullptr);

                tile.SetOrigin(Vector2f(0.f, 0.f));

                auto* aabb = tile.GetBoundingBox();

                Assert::IsNotNull(aabb);

                auto boxOri = aabb->GetOrigin();

                Assert::AreEqual(0.f, boxOri.x);
                Assert::AreEqual(0.f, boxOri.y);

                auto tileOri = tile.GetOrigin();

                Assert::AreEqual(boxOri.x, tileOri.x);
                Assert::AreEqual(boxOri.y, tileOri.y);
            }

            // ======================================================
            // Bounding Box Access
            // ======================================================

            TEST_METHOD(Tile_GetTileWidth_ReturnsBoundingBoxWidth)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16, 16), Vector2f(16, 16)), nullptr);

                Assert::AreEqual(16.f, tile.GetTileWidth());
            }

            TEST_METHOD(Tile_GetTileHeight_ReturnsBoundingBoxHeight)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16, 16), Vector2f(16, 16)), nullptr);

                Assert::AreEqual(16.f, tile.GetTileHeight());
            }

            // ======================================================
            // Type / Active State
            // ======================================================

            TEST_METHOD(Tile_SetType_UpdatesType)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(), nullptr);

                tile.SetType(static_cast<int>(TileTypes::GRND));

                Assert::IsTrue(TileTypes::GRND == tile.GetType());
            }

            TEST_METHOD(Tile_SetActive_UpdatesActiveState)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(), nullptr);

                tile.SetActive(true);

                Assert::IsTrue(tile.GetActive());
            }

            // ======================================================
            // Slope
            // ======================================================

            TEST_METHOD(Tile_GetSlope_WithNullSlope_ReturnsDefaultLine)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(), nullptr);

                auto line = tile.GetSlope(0, 0);

                Assert::AreEqual(0.f, line.start.x);
                Assert::AreEqual(0.f, line.start.y);
                Assert::AreEqual(0.f, line.end.x);
                Assert::AreEqual(0.f, line.end.y);
            }

            TEST_METHOD(Tile_SetSlope_AddsSlope)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(), nullptr);

                auto triangle = std::make_shared<FakeTriangle>(
                    std::array<Vector2f, 3>
                {
                    Vector2f(0, 0),
                        Vector2f(1, 1),
                        Vector2f(1, 0)
                },
                    Vector2f(0, 0)
                );

                tile.SetSlope(triangle);

                Line2f slope = tile.GetSlope(0, 1);

                Assert::AreEqual(0.f, slope.start.x);
                Assert::AreEqual(0.f, slope.start.y);

                Assert::AreEqual(1.f, slope.end.x);
                Assert::AreEqual(1.f, slope.end.y);
            }

            TEST_METHOD(Tile_SetSlope_OverridesSlope)
            {
                auto original = std::make_shared<FakeTriangle>(
                    std::array<Vector2f, 3>
                {
                    Vector2f(0, 0),
                        Vector2f(1, 1),
                        Vector2f(1, 0)
                },
                    Vector2f(0, 0)
                );

                TestableTile tile(
                    0,
                    0,
                    std::make_shared<FakeBoundingBox>(),
                    original
                );

                auto other = std::make_shared<FakeTriangle>(
                    std::array<Vector2f, 3>
                {
                    Vector2f(0, 0),
                        Vector2f(2, 2),
                        Vector2f(2, 0)
                },
                    Vector2f(0, 0)
                );

                tile.SetSlope(other);

                Line2f slope = tile.GetSlope(0, 1);

                Assert::AreEqual(0.f, slope.start.x);
                Assert::AreEqual(0.f, slope.start.y);

                Assert::AreEqual(2.f, slope.end.x);
                Assert::AreEqual(2.f, slope.end.y);
            }

            TEST_METHOD(Tile_SetSlope_WithNullSlope_DoesNotReplaceExistingSlope)
            {
                auto triangle = std::make_shared<FakeTriangle>(
                    std::array<Vector2f, 3>
                {
                    Vector2f(0, 0),
                        Vector2f(1, 1),
                        Vector2f(1, 0)
                },
                    Vector2f(0, 0)
                );

                TestableTile tile(
                    0,
                    0,
                    std::make_shared<FakeBoundingBox>(),
                    triangle
                );

                tile.SetSlope(nullptr);

                Line2f slope = tile.GetSlope(0, 1);

                Assert::AreEqual(0.f, slope.start.x);
                Assert::AreEqual(0.f, slope.start.y);

                Assert::AreEqual(1.f, slope.end.x);
                Assert::AreEqual(1.f, slope.end.y);
            }

            // ======================================================
            // Intersects / Tile-Level Guard Behaviour
            // ======================================================

            TEST_METHOD(Tile_Intersects_WithNullObject_ReturnsFalse)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16, 16), Vector2f(16, 16)), nullptr);

                float tFirst = 0.f;
                float tLast = 0.f;

                auto res = tile.Intersects(nullptr, tFirst, tLast);

                Assert::IsFalse(res);
            }

            TEST_METHOD(Tile_Intersects_WithValidObject_ReturnsBoundingBoxResult)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16, 16), Vector2f(16, 16)), nullptr);

                FakeDynamicGameObject fdgo(std::make_shared<FakeSprite>("Test1"), std::make_shared<FakeBoundingBox>(Vector2f(16, 16), Vector2f(16, 16)));

                float tFirst = 0.f;
                float tLast = 0.f;

                auto res = tile.Intersects(static_cast<IDynamicGameObject*>(&fdgo), tFirst, tLast);

                Assert::IsTrue(res);
            }

            // ======================================================
            // Separation Vector / Tile-Level Guard Behaviour
            // ======================================================

            TEST_METHOD(Tile_GetSeparationVector_WithNullObject_ReturnsZeroVector)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16, 16), Vector2f(16, 16)), nullptr);

                auto sepVec = tile.Test_GetSeparationVector(static_cast<IDynamicGameObject*>(nullptr));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(0.f, sepVec.y);
            }

            TEST_METHOD(Tile_GetSeparationVector_WithValidObject_ReturnsBoundingBoxResult)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16, 16), Vector2f(16, 16)), nullptr);

                FakeDynamicGameObject fdgo(std::make_shared<FakeSprite>("Test1"), std::make_shared<FakeBoundingBox>(Vector2f(16, 16), Vector2f(16, 16)));

                auto sepVec = tile.Test_GetSeparationVector(static_cast<IDynamicGameObject*>(&fdgo));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(16.01f, sepVec.y);
            }

            // ======================================================
            // Shared Collision Resolution Helpers
            // ======================================================

            TEST_METHOD(Tile_ResolveObjectToBoxTop_SnapsObjectToTileTop)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16.f, 16.f), Vector2f(16.f, 16.f)), nullptr);

                FakeDynamicGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>(Vector2f(8.f, 8.f), Vector2f(16.f, 10.f))
                );

                obj.SetVelocity(Vector2f(0.f, 10.f));

                tile.Test_ResolveObjectToBoxTop(&obj, 1.0f, 1.0f);

                // Tile top = 8
                // Object half height = 4
                // Expected object center y = 4
                Assert::AreEqual(4.f, obj.GetPosition().y);
            }

            TEST_METHOD(Tile_ResolveObjectToBoxTop_ClearsDownwardVelocity)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16.f, 16.f), Vector2f(16.f, 16.f)), nullptr);

                FakeDynamicGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>(Vector2f(8.f, 8.f), Vector2f(16.f, 10.f))
                );

                obj.SetVelocity(Vector2f(0.f, 10.f));

                tile.Test_ResolveObjectToBoxTop(&obj, 1.0f, 1.0f);

                Assert::AreEqual(0.f, obj.GetVelocity().y);
            }

            TEST_METHOD(Tile_ResolveObjectToBoxTop_DoesNotClearUpwardVelocity)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16.f, 16.f), Vector2f(16.f, 16.f)), nullptr);

                auto objBox = std::make_shared<BoundingBox<FakeBox>>(
                    Vector2f(8.f, 8.f),
                    Vector2f(16.f, 10.f)
                );

                FakeDynamicGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>(Vector2f(8.f, 8.f), Vector2f(16.f, 10.f))
                );

                obj.SetVelocity(Vector2f(10.f, 10.f));

                tile.Test_ResolveObjectToBoxTop(&obj, 1.0f, 1.0f);

                Assert::AreEqual(10.f, obj.GetVelocity().x);
            }

            TEST_METHOD(Tile_ResolveObjectToBoxTop_SetsOnGroundTrue)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16.f, 16.f), Vector2f(16.f, 16.f)), nullptr);

                FakeDynamicGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>(Vector2f(8.f, 8.f), Vector2f(16.f, 10.f))
                );

                obj.SetVelocity(Vector2f(10.f, 10.f));

                tile.Test_ResolveObjectToBoxTop(&obj, 1.0f, 1.0f);

                Assert::IsTrue(obj.GetOnGround());
            }

            TEST_METHOD(Tile_ResolveObjectToBoxTop_SetsOnSlopeFalse)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16.f, 16.f), Vector2f(16.f, 16.f)), nullptr);

                FakeDynamicGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>(Vector2f(8.f, 8.f), Vector2f(16.f, 10.f))
                );

                obj.SetOnSlope(true);
                obj.SetVelocity(Vector2f(0.f, 10.f));

                tile.Test_ResolveObjectToBoxTop(&obj, 1.0f, 1.0f);

                Assert::IsFalse(obj.GetOnSlope());
            }

            TEST_METHOD(Tile_ResolveObjectToBoxBottom_SnapsObjectToTileBottom)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16.f, 16.f), Vector2f(16.f, 16.f)), nullptr);

                auto objBox = std::make_shared<BoundingBox<FakeBox>>(
                    Vector2f(8.f, 8.f),
                    Vector2f(16.f, 22.f)
                );

                FakeDynamicGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>(Vector2f(8.f, 8.f), Vector2f(16.f, 22.f))
                );

                obj.SetVelocity(Vector2f(0.f, -10.f));

                tile.Test_ResolveObjectToBoxBottom(&obj, 1.0f, 1.0f);

                // Tile bottom = 24
                // Object half height = 4
                // Expected object centre y = 28
                Assert::AreEqual(28.f, obj.GetPosition().y);
            }

            TEST_METHOD(Tile_ResolveObjectToBoxBottom_ClearsUpwardVelocity)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16.f, 16.f), Vector2f(16.f, 16.f)), nullptr);

                FakeDynamicGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>(Vector2f(8.f, 8.f), Vector2f(16.f, 22.f))
                );

                obj.SetVelocity(Vector2f(0.f, -10.f));

                tile.Test_ResolveObjectToBoxBottom(&obj, 1.0f, 1.0f);

                Assert::AreEqual(0.f, obj.GetVelocity().y);
            }

            TEST_METHOD(Tile_ResolveObjectToBoxBottom_DoesNotClearDownwardVelocity)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16.f, 16.f), Vector2f(16.f, 16.f)), nullptr);

                FakeDynamicGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>(Vector2f(8.f, 8.f), Vector2f(16.f, 22.f))
                );

                obj.SetVelocity(Vector2f(0.f, 10.f));

                tile.Test_ResolveObjectToBoxBottom(&obj, 1.0f, 1.0f);

                Assert::AreEqual(10.f, obj.GetVelocity().y);
            }

            TEST_METHOD(Tile_ResolveObjectToBoxHorizontally_SnapsObjectToTileSide)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16.f, 16.f), Vector2f(16.f, 16.f)), nullptr);

                FakeDynamicGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>(Vector2f(8.f, 8.f), Vector2f(10.f, 16.f))
                );

                obj.SetVelocity(Vector2f(10.f, 0.f));

                tile.Test_ResolveObjectToBoxHorizontally(&obj, 1.0f, 1.0f);

                // Tile left = 8
                // Object half width = 4
                // Expected object centre x = 4
                Assert::AreEqual(4.f, obj.GetPosition().x);
            }

            TEST_METHOD(Tile_ResolveObjectToBoxHorizontally_ClearsHorizontalVelocity)
            {
                TestableTile tile(0, 0, std::make_shared<FakeBoundingBox>(Vector2f(16.f, 16.f), Vector2f(16.f, 16.f)), nullptr);

                FakeDynamicGameObject obj(
                    std::make_shared<FakeSprite>("obj"),
                    std::make_shared<BoundingBox<FakeBox>>(Vector2f(8.f, 8.f), Vector2f(10.f, 16.f))
                );

                obj.SetVelocity(Vector2f(10.f, 0.f));

                tile.Test_ResolveObjectToBoxHorizontally(&obj, 1.0f, 1.0f);

                Assert::AreEqual(0.f, obj.GetVelocity().x);
            }
        };
    }
}

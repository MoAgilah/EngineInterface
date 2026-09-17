#include "CppUnitTest.h"


#include <Fakes/Collisions/FakeGrid.h>
#include <Fakes/Collisions/FakeTile.h>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Collisions
    {
        TEST_CLASS(GridTests)
        {
        public:

            TEST_METHOD_CLEANUP(TestCleanup)
            {
                GameConstants::DRender = false;
            }

            // ============================================================================
            // IGridTests
            // ============================================================================

            // ----------------------------------------------------------------------------
            // Constructor
            // ----------------------------------------------------------------------------

            TEST_METHOD(IGrid_Constructor_ThrowsWhenRowsAreNegative)
            {
                Assert::ExpectException<std::invalid_argument>([]
                    {
                        FakeGrid grid(-1, 4);
                    });
            }

            TEST_METHOD(IGrid_Constructor_ThrowsWhenColumnsAreNegative)
            {
                Assert::ExpectException<std::invalid_argument>([]
                    {
                        FakeGrid grid(2, -1);
                    });
            }

            TEST_METHOD(IGrid_Constructor_ThrowsWhenBothDimensionsAreZero)
            {
                Assert::ExpectException<std::invalid_argument>([]
                    {
                        FakeGrid grid(0, 0);
                    });
            }

            TEST_METHOD(IGrid_Constructor_ThrowsWhenZeroRows)
            {
                Assert::ExpectException<std::invalid_argument>([]
                    {
                        FakeGrid grid(0, 4);
                    });
            }

            TEST_METHOD(IGrid_Constructor_ThrowsWhenZeroColumns)
            {
                Assert::ExpectException<std::invalid_argument>([]
                    {
                        FakeGrid grid(2, 0);
                    });
            }

            TEST_METHOD(IGrid_Constructor_AcceptsPositiveDimensions)
            {
                FakeGrid grid(2, 4);
            }

            // ----------------------------------------------------------------------------
            // Render
            // ----------------------------------------------------------------------------

            TEST_METHOD(IGrid_Render_ReturnsEarlyIfGameConstantsDRenderIsFalse)
            {
                GameConstants::DRender = false;

                FakeGrid grid(2, 4);

                grid.SetTileActive(3, true);
                grid.SetTileActive(7, true);

                grid.Render(nullptr);

                for(const auto& tile : grid.GetGrid())
                {
                    Assert::IsNotNull(tile.get());

                    auto ft = dynamic_cast<FakeTile*>(tile.get());

                    Assert::IsNotNull(ft);

                    Assert::IsFalse(ft->renderCalled);
                }
            }

            TEST_METHOD(IGrid_Render_SkipsNullTiles)
            {
                GameConstants::DRender = true;

                FakeGrid grid(2, 4);

                grid.SetTileNull(2);
                grid.SetTileActive(3, true);
                grid.SetTileNull(5);
                grid.SetTileActive(7, true);

                grid.Render(nullptr);

                const auto& tiles = grid.GetGrid();

                for (size_t i = 0; i < tiles.size(); i++)
                {
                    if (i == 2 || i == 5)
                    {
                        Assert::IsNull(tiles[i].get());
                    }
                    else
                    {
                        Assert::IsNotNull(tiles[i].get());

                        auto ft = dynamic_cast<FakeTile*>(tiles[i].get());

                        Assert::IsNotNull(ft);

                        Assert::AreEqual(i == 3 || i == 7, ft->renderCalled);
                    }
                }
            }

            TEST_METHOD(IGrid_Render_DoesNotRenderInactiveTiles)
            {
                GameConstants::DRender = true;

                FakeGrid grid(2, 4);

                grid.SetTileActive(3, true);
                grid.SetTileActive(7, true);

                grid.Render(nullptr);

                for (const auto& tile : grid.GetGrid())
                {
                    Assert::IsNotNull(tile.get());

                    if (tile->GetActive())
                        continue;

                    auto ft = dynamic_cast<FakeTile*>(tile.get());

                    Assert::IsNotNull(ft);

                    Assert::IsFalse(ft->renderCalled);
                }
            }

            TEST_METHOD(IGrid_Render_RendersActiveTiles)
            {
                GameConstants::DRender = true;

                FakeGrid grid(2, 4);

                grid.SetTileActive(3, true);
                grid.SetTileActive(7, true);

                grid.Render(nullptr);

                for (const auto& tile : grid.GetGrid())
                {
                    Assert::IsNotNull(tile.get());

                    if (!tile->GetActive())
                        continue;

                    auto ft = dynamic_cast<FakeTile*>(tile.get());

                    Assert::IsNotNull(ft);

                    Assert::IsTrue(ft->renderCalled);
                }
            }

            // ----------------------------------------------------------------------------
            // GetTile
            // ----------------------------------------------------------------------------

            TEST_METHOD(IGrid_GetTile_ReturnsTileIfValidXY)
            {
                FakeGrid grid(2, 4);

                Assert::IsNotNull(grid.GetTile(0, 1));
            }

            TEST_METHOD(IGrid_GetTile_ReturnsNullIfInvalidXY)
            {
                FakeGrid grid(2, 4);

                Assert::IsNull(grid.GetTile(2, 4));
            }

            // ----------------------------------------------------------------------------
            // GetGrid
            // ----------------------------------------------------------------------------

            TEST_METHOD(IGrid_GetGrid_ReturnsTiles)
            {
                FakeGrid grid(2, 4);

                for (const auto& tile : grid.GetGrid())
                {
                    Assert::IsNotNull(tile.get());
                }
            }


            // ----------------------------------------------------------------------------
            // LoadTileTypes
            // ----------------------------------------------------------------------------

            TEST_METHOD(IGrid_LoadTileTypes_ThrowsIfFilePathDoesNotExist)
            {
                FakeGrid grid(2, 4);

                Assert::ExpectException<std::runtime_error>([&]
                    {
                        grid.LoadTileTypes("Resources/TileTypes.txt");
                    });

            }

            TEST_METHOD(IGrid_LoadTileTypes_ThrowsIfFileFailsToOpen)
            {
                FakeGrid grid(2, 4);

                Assert::IsTrue(std::filesystem::exists("Resources"));

                Assert::ExpectException<std::runtime_error>([&]
                    {
                        grid.LoadTileTypes("Resources");
                    });
            }

            TEST_METHOD(IGrid_LoadTileTypes_ThrowsIfTileCountMismatchesGridSize)
            {
                FakeGrid grid(2, 3);

                Assert::IsTrue(
                    std::filesystem::exists("Resources/TileTypes_Test.txt")
                );

                Assert::ExpectException<std::runtime_error>([&]
                    {
                        grid.LoadTileTypes("Resources/TileTypes_Test.txt");
                    });
            }

            TEST_METHOD(IGrid_LoadTileTypes_SetsTileTypes)
            {
                FakeGrid grid(2, 4);

                grid.LoadTileTypes("Resources/TileTypes_Test.txt");

                const auto& tiles = grid.GetGrid();

                for (std::size_t i = 0; i < tiles.size(); i++)
                {
                    Assert::IsNotNull(tiles[i].get());

                    Assert::AreEqual(static_cast<int>(i),
                        static_cast<int>(tiles[i]->GetType()));
                }
            }

            // ----------------------------------------------------------------------------
            // ArrangeTilePositions
            // ----------------------------------------------------------------------------

            TEST_METHOD(IGrid_ArrangeTilePositions_ThrowsIfFirstTileIsNull)
            {
                FakeGrid grid(2, 4);

                grid.SetTileNull(0);

                Assert::ExpectException<std::runtime_error>([&]
                    {
                        grid.ArrangeTilePositions();
                    });
            }

            TEST_METHOD(IGrid_ArrangeTilePositions_ThrowsIfSubsequentTileIsNull)
            {
                FakeGrid grid(2, 4);

                grid.SetTileNull(3);

                Assert::ExpectException<std::runtime_error>([&]
                    {
                        grid.ArrangeTilePositions();
                    });
            }

            TEST_METHOD(IGrid_ArrangeTilePositions_SetsTilePositions)
            {
                FakeGrid grid(2, 4);

                grid.ArrangeTilePositions();

                const auto& tiles = grid.GetGrid();

                for (std::size_t i = 0; i < tiles.size(); ++i)
                {
                    Assert::IsNotNull(tiles[i].get());

                    const std::size_t row = i / 4;
                    const std::size_t col = i % 4;

                    const float expectedX = 8.f + col * 16.f;
                    const float expectedY = 8.f + row * 16.f;

                    const auto pos = tiles[i]->GetPosition();

                    Assert::AreEqual(expectedX, pos.x);
                    Assert::AreEqual(expectedY, pos.y);
                }
            }

            TEST_METHOD(IGrid_ArrangeTilePositions_UpdatesBoundingBoxPositions)
            {
                FakeGrid grid(2, 4);

                grid.ArrangeTilePositions();

                for (const auto& tile : grid.GetGrid())
                {
                    Assert::IsNotNull(tile.get());

                    const auto tilePos = tile->GetPosition();
                    const auto boxPos = tile->GetBoundingBox()->GetPosition();

                    Assert::AreEqual(tilePos.x, boxPos.x);
                    Assert::AreEqual(tilePos.y, boxPos.y);
                }
            }


            // ============================================================================
            // FakeGridTests
            // ============================================================================

            // ----------------------------------------------------------------------------
            // Initialization — lightweight constructor
            // ----------------------------------------------------------------------------

            TEST_METHOD(FakeGrid_Init_CreatesExpectedNumberOfTiles)
            {
                int rows = 2;
                int cols = 4;

                FakeGrid grid(rows, cols);

                Assert::AreEqual(rows * cols, static_cast<int>(grid.GetGrid().size()));
            }

            TEST_METHOD(FakeGrid_Init_CreatesFakeTiles)
            {
                FakeGrid grid(2, 4);

                for (const auto& tile : grid.GetGrid())
                {
                    Assert::IsNotNull(tile.get());

                    auto* fakeTile = dynamic_cast<FakeTile*>(tile.get());

                    Assert::IsNotNull(fakeTile);
                }
            }

            // ----------------------------------------------------------------------------
            // Initialization — full constructor
            // ----------------------------------------------------------------------------

            TEST_METHOD(FakeGrid_Init_LoadsTileTypesFromFile)
            {
                FakeGrid grid(2, 4, "Resources/TileTypes_Test.txt");

                const auto& tiles = grid.GetGrid();

                for (std::size_t i = 0; i < tiles.size(); i++)
                {
                    Assert::IsNotNull(tiles[i].get());

                    Assert::AreEqual(static_cast<int>(i),
                        static_cast<int>(tiles[i]->GetType()));
                }
            }

            TEST_METHOD(FakeGrid_Init_ArrangesTilePositions)
            {
                FakeGrid grid(2, 4, "Resources/TileTypes_Test.txt");

                const auto& tiles = grid.GetGrid();

                for (std::size_t i = 0; i < tiles.size(); ++i)
                {
                    Assert::IsNotNull(tiles[i].get());

                    const std::size_t row = i / 4;
                    const std::size_t col = i % 4;

                    const float expectedX = 8.f + col * 16.f;
                    const float expectedY = 8.f + row * 16.f;

                    const auto pos = tiles[i]->GetPosition();

                    Assert::AreEqual(expectedX, pos.x);
                    Assert::AreEqual(expectedY, pos.y);
                }
            }
        };
    }
}
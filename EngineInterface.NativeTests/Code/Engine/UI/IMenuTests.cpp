#include "CppUnitTest.h"

#include <Engine/Core/GameManager.h>
#include <Engine/UI/MenuItem.h>
#include <Engine/Interface/UI/IMenu.h>
#include <Fakes/Drawables/FakeShape.h>
#include <Fakes/Drawables/FakeSprite.h>
#include <Fakes/Drawables/FakeText.h>
#include <Fakes/Renderer/FakeRenderer.h>
#include <Fakes/UI/TestableMenu.h>
#include <TestHelpers/TestDefaultLoggerHelper.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace UI
    {
        TEST_CLASS(MenuItemTests)
        {
        public:
            TEST_METHOD_CLEANUP(TestCleanup)
            {
                TestHelpers::CleanupDefaultLoggerForTests();
            }

            // ======================================================
            // MenuPositionData
            // ======================================================

            TEST_METHOD(MenuPositionData_Constructor_CenteredModeSetsCenterPoint)
            {
                Vector2f vec(16.f, 16.f);

                MenuPositionData mpd(MenuPositionMode::Centered, vec);

                Assert::AreEqual(static_cast<int>(MenuPositionMode::Centered), static_cast<int>(mpd.m_positionMode));

                auto centerPoint = mpd.m_centerPoint;

                Assert::IsTrue(centerPoint.has_value());

                Assert::AreEqual(vec.x, (*centerPoint).x);
                Assert::AreEqual(vec.y, (*centerPoint).y);
            }

            TEST_METHOD(MenuPositionData_Constructor_CenteredModeLeavesAnchorBoundsUnset)
            {
                Vector2f vec(16.f, 16.f);

                MenuPositionData mpd(MenuPositionMode::Centered, vec);

                Assert::AreEqual(static_cast<int>(MenuPositionMode::Centered), static_cast<int>(mpd.m_positionMode));

                Assert::IsFalse(mpd.m_anchorBounds.has_value());
            }

            TEST_METHOD(MenuPositionData_Constructor_AnchoredModeSetsAnchorBounds)
            {
                Vector2f vec(16.f, 16.f);

                MenuPositionData mpd(MenuPositionMode::Anchored, vec);

                Assert::AreEqual(static_cast<int>(MenuPositionMode::Anchored), static_cast<int>(mpd.m_positionMode));

                auto anchorBounds = mpd.m_anchorBounds;

                Assert::IsTrue(anchorBounds.has_value());

                Assert::AreEqual(vec.x, (*anchorBounds).x);
                Assert::AreEqual(vec.y, (*anchorBounds).y);
            }

            TEST_METHOD(MenuPositionData_Constructor_AnchoredModeLeavesCenterPointUnset)
            {
                Vector2f vec(16.f, 16.f);

                MenuPositionData mpd(MenuPositionMode::Anchored, vec);

                Assert::AreEqual(static_cast<int>(MenuPositionMode::Anchored), static_cast<int>(mpd.m_positionMode));

                Assert::IsFalse(mpd.m_centerPoint.has_value());
            }

            // ======================================================
            // Constructor
            // ======================================================

            TEST_METHOD(IMenu_Constructor_ThrowsIfDimensionsXIsNotGreaterThanZero)
            {
                Assert::ExpectException<std::runtime_error>([&]
                    {
                        TestableMenu menu(
                            Vector2f(600.f, 400.f),
                            2.f,
                            Vector2u(0u, 4u),
                            MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ));
                    });
            }

            TEST_METHOD(IMenu_Constructor_ThrowsIfDimensionsYIsNotGreaterThanZero)
            {
                Assert::ExpectException<std::runtime_error>([&]
                    {
                        TestableMenu menu(
                            Vector2f(600.f, 400.f),
                            2.f,
                            Vector2u(3u, 0u),
                            MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ));
                    });
            }

            TEST_METHOD(IMenu_Constructor_DoesNotThrowIfDimensionsAreValid)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));
            }

            // ======================================================
            // Geometry
            // ======================================================

            TEST_METHOD(IMenu_CalculateCellSize_DividesMenuSpaceByDimensions)
            {
                Vector2f menuSize(600.f, 400.f);

                TestableMenu menu(
                    menuSize,
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                auto cellSize = menu.CalculateCellSizeForTesting(menuSize);

                Assert::AreEqual(200.f, cellSize.x);
                Assert::AreEqual(100.f, cellSize.y);
            }

            TEST_METHOD(IMenu_CalculateMenuTopLeft_SubtractsOriginFromMenuPosition)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                auto topLeft = menu.CalculateMenuTopLeftForTesting(Vector2f(500, 350), Vector2f(300, 200));

                Assert::AreEqual(200.f, topLeft.x);
                Assert::AreEqual(150.f, topLeft.y);
            }

            TEST_METHOD(IMenu_CalculateCellPosition_ReturnsCorrectPositionForRowAndColumn)
            {
                Vector2f menuSize(600.f, 400.f);

                TestableMenu menu(
                    menuSize,
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.CalculateMenuTopLeftForTesting(Vector2f(500, 350), Vector2f(300, 200));
                menu.CalculateCellSizeForTesting(menuSize);

                auto cellPos = menu.CalculateCellPositionForTesting(1, 2);

                Assert::AreEqual(700.f, cellPos.x);
                Assert::AreEqual(300.f, cellPos.y);
            }

            TEST_METHOD(IMenu_CalculateCellPosition_ReturnsCorrectPositionForFirstCell)
            {
                Vector2f menuSize(600.f, 400.f);

                TestableMenu menu(
                    menuSize,
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.CalculateMenuTopLeftForTesting(Vector2f(500, 350), Vector2f(300, 200));
                menu.CalculateCellSizeForTesting(menuSize);

                auto cellPos = menu.CalculateCellPositionForTesting(0, 0);

                Assert::AreEqual(300.f, cellPos.x);
                Assert::AreEqual(200.f, cellPos.y);
            }

            TEST_METHOD(IMenu_CalculateCellPosition_ReturnsCorrectPositionForLastCell)
            {
                Vector2f menuSize(600.f, 400.f);

                TestableMenu menu(
                    menuSize,
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.CalculateMenuTopLeftForTesting(Vector2f(500, 350), Vector2f(300, 200));
                menu.CalculateCellSizeForTesting(menuSize);

                auto cellPos = menu.CalculateCellPositionForTesting(3, 2);

                Assert::AreEqual(700.f, cellPos.x);
                Assert::AreEqual(500.f, cellPos.y);
            }

            // ======================================================
            // BuildMenuSpace
            // ======================================================

            TEST_METHOD(IMenu_BuildMenuSpace_ThrowsIfMenuSpaceIsNull)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.SetMenuSpaceToNullForTesting();

                Assert::ExpectException<std::runtime_error>([&]
                    {
                        menu.BuildTestMenuSpace();
                    });
            }

            TEST_METHOD(IMenu_BuildMenuSpace_SetsMenuSpaceOriginToCenter)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestMenuSpace();

                auto menuSpace = menu.GetMenuSpace();
                Assert::IsNotNull(menuSpace);

                auto origin = menuSpace->GetOrigin();

                Assert::AreEqual(300.f, origin.x);
                Assert::AreEqual(200.f, origin.y);
            }

            TEST_METHOD(IMenu_BuildMenuSpace_AssignsMenuSpacePositionInCenteredMode)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestMenuSpace();

                auto menuSpace = menu.GetMenuSpace();
                Assert::IsNotNull(menuSpace);

                auto pos = menuSpace->GetPosition();

                Assert::AreEqual(500.f, pos.x);
                Assert::AreEqual(350.f, pos.y);

            }

            TEST_METHOD(IMenu_BuildMenuSpace_AssignsMenuSpacePositionInAnchoredMode)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Anchored,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestMenuSpace();

                auto menuSpace = menu.GetMenuSpace();
                Assert::IsNotNull(menuSpace);

                auto pos = menuSpace->GetPosition();

                Assert::AreEqual(250.f, pos.x);
                Assert::AreEqual(175.f, pos.y);
            }

            // ======================================================
            // BuildCells
            // ======================================================

            TEST_METHOD(ThrowsIfFactoryReturnsNullptr)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                Assert::ExpectException<std::runtime_error>([&]()
                    {
                        menu.BuildTestCellsWithFactory(
                            [](const Vector2f&, float) -> std::shared_ptr<MenuItem>
                            {
                                return nullptr;
                            }
                        );
                    });
            }

            TEST_METHOD(IMenu_BuildCells_PassesCorrectConfigurationToFactory)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                Assert::AreEqual(12, menu.factoryCallCount);
                Assert::AreEqual(2.f, menu.receivedOutlineThickness);

                auto cellSize = menu.receivedCellSize;

                Assert::AreEqual(200.f, cellSize.x);
                Assert::AreEqual(100.f, cellSize.y);
            }

            TEST_METHOD(IMenu_BuildCells_CreatesExpectedNumberOfCells)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                Assert::AreEqual(size_t(12), menu.GetNumberOfCells());
            }

            TEST_METHOD(IMenu_BuildCells_CreatesCellsWithCorrectGeometry)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                auto cell = menu.GetCell({ 1, 2 });
                Assert::IsNotNull(cell);

                auto cellPos = cell->GetPosition();

                Assert::AreEqual(700.f, cellPos.x);
                Assert::AreEqual(300.f, cellPos.y);

                auto cellSize = cell->GetSize();

                Assert::AreEqual(200.f, cellSize.x);
                Assert::AreEqual(100.f, cellSize.y);

                auto cellOri = cell->GetOrigin();

                Assert::AreEqual(cellSize.x * 0.5f, cellOri.x);
                Assert::AreEqual(cellSize.y * 0.5f, cellOri.y);
            }

            TEST_METHOD(IMenu_BuildCells_ReplacesExistingCellsOnRebuild)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                auto originalCell = menu.GetSharedCellForTesting(0);
                Assert::IsNotNull(originalCell.get());

                menu.BuildTestCells();

                Assert::AreEqual(size_t(12), menu.GetNumberOfCells());
                Assert::IsTrue(originalCell.get() != menu.GetCell({ 0, 0 }));
            }

            // ======================================================
            // Cell Indexing
            // ======================================================

            TEST_METHOD(IMenu_CalculateCellIndex_ReturnsIndexForRowColPair)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                auto first = menu.CalculateCellIndexForTesting(0, 0);
                Assert::AreEqual(size_t(0), first);


                auto rand = menu.CalculateCellIndexForTesting(1, 2);
                Assert::AreEqual(size_t(5), rand);

                auto last = menu.CalculateCellIndexForTesting(3, 2);
                Assert::AreEqual(size_t(11), last);
            }

            TEST_METHOD(IMenu_GetCellByIndex_OutOfBoundsReturnsNull)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                Assert::IsNull(menu.GetCellByIndex(12));
            }

            TEST_METHOD(IMenu_GetCellByIndex_ValidIndexReturnsCell)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                Assert::IsNotNull(menu.GetCellByIndex(5));
            }


            TEST_METHOD(IMenu_GetCell_ReturnsNullIfRowIsNegative)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                Assert::IsNull(menu.GetCell({-1, 2}));
            }

            TEST_METHOD(IMenu_GetCell_ReturnsNullIfColIsNegative)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                Assert::IsNull(menu.GetCell({ 1, -2 }));
            }

            TEST_METHOD(IMenu_GetCell_ReturnsNullIfCoordinatesAreOutOfBounds)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                Assert::IsNull(menu.GetCell({ 3, 3 }));
            }

            TEST_METHOD(IMenu_GetCell_ValidCoordinatesReturnsCell)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                Assert::IsNotNull(menu.GetCell({ 1, 2 }));
            }

            TEST_METHOD(IMenu_SetActiveCells_ThrowsIfDuplicateSlotNumber)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(2);

                Assert::ExpectException<std::runtime_error>([&]()
                    {
                        menu.SetActiveCells();
                    });
            }

            TEST_METHOD(IMenu_SetActiveCells_ThrowsIfSlotNumbersNotSequential)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(3);

                Assert::ExpectException<std::runtime_error>([&]()
                    {
                        menu.SetActiveCells();
                    });
            }

            TEST_METHOD(IMenu_SetActiveCells_AssignsActiveCells)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                auto activeCells = menu.GetActiveCellsForTesting();

                Assert::AreEqual(size_t(3), activeCells.size());
            }

            TEST_METHOD(IMenu_SetActiveCells_NoAssignedSlotsProducesEmptyActiveCells)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.SetActiveCells();

                auto activeCells = menu.GetActiveCellsForTesting();

                Assert::IsTrue(activeCells.empty());
            }

            TEST_METHOD(IMenu_GetCellBySlotNumber_ReturnsNullIfActiveCellsIsEmpty)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.SetActiveCells();

                Assert::IsNull(menu.GetCellBySlotNumber(0));
            }

            TEST_METHOD(IMenu_GetCellBySlotNumber_ReturnsNullIfActiveCellsDoesNotContainSlotNumber)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                Assert::IsNull(menu.GetCellBySlotNumber(3));
            }

            TEST_METHOD(IMenu_GetCellBySlotNumber_ValidSlotNumberReturnsCell)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                Assert::IsNotNull(menu.GetCellBySlotNumber(2));
            }

            // ======================================================
            // Cursor
            // ======================================================

            TEST_METHOD(IMenu_GetCursor_ReturnsNullIfCursorsEmpty)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                Assert::IsNull(menu.GetCursor(0));
            }

            TEST_METHOD(IMenu_GetCursor_ReturnsNullIfIndexIsOutOfRange)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                MenuNav nav(KeyCode::Up, KeyCode::Down);

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), nav);

                Assert::IsNull(menu.GetCursor(1));
            }

            TEST_METHOD(IMenu_AddCursor_ReturnsNullIfSpriteIsInvalid)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                MenuNav nav(KeyCode::Up, KeyCode::Down);

                auto cursor = menu.AddCursor(nullptr, nav);

                Assert::IsNull(cursor);
            }

            TEST_METHOD(IMenu_AddCursor_ReturnsCursor)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                MenuNav nav(KeyCode::Up, KeyCode::Down);

                auto cursor = menu.AddCursor(std::make_shared<FakeSprite>("spr"), nav);

                Assert::IsNotNull(cursor);
            }

            TEST_METHOD(IMenu_AddCursor_SetsCursor)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                MenuNav nav(KeyCode::Up, KeyCode::Down);

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), nav);

                auto cursor = menu.GetCursor(0);

                Assert::IsNotNull(cursor);
            }

            // ======================================================
            // SetActiveTextElement
            // ======================================================

            TEST_METHOD(IMenu_SetActiveTextElement_WithNoPassiveColour_DoesNotUpdateText)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                Colour overrideColour = Colour::Red;

                menu.AddTestTextCell(0, 2, "Txt2", Colour::Black, overrideColour);
                menu.AddTestTextCell(5, 0, "Txt0", Colour::Black, overrideColour);
                menu.AddTestTextCell(8, 1, "Txt1", Colour::Black, overrideColour);

                menu.SetActiveCells();

                menu.SetActiveTextElementForTesting();

                auto activeCells = menu.GetActiveCellsForTesting();
                for (auto cellIdx : activeCells)
                {
                    auto cell = menu.GetCellByIndex(cellIdx);
                    Assert::IsNotNull(cell);

                    auto textEle = cell->GetTextElement();
                    Assert::IsNotNull(textEle);

                    auto currColour = textEle->GetOutlineColour();

                    Assert::AreEqual(overrideColour.r, currColour.r);
                    Assert::AreEqual(overrideColour.g, currColour.g);
                    Assert::AreEqual(overrideColour.b, currColour.b);
                    Assert::AreEqual(overrideColour.a, currColour.a);
                }
            }

            TEST_METHOD(IMenu_SetActiveTextElement_WithPassiveColour_SetsSelectedTextDefaultColour)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.SetPassiveColour(Colour::White);

                Colour overrideColour = Colour::Red;

                menu.AddTestTextCell(0, 2, "Txt2", Colour::Black, overrideColour);
                menu.AddTestTextCell(5, 0, "Txt0", Colour::Black, overrideColour);
                menu.AddTestTextCell(8, 1, "Txt1", Colour::Black, overrideColour);

                menu.SetActiveCells();

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0,1,2 });

                menu.SetActiveTextElementForTesting();

                auto cell = menu.GetCellBySlotNumber(menuNav->GetCurrCursorPos());
                Assert::IsNotNull(cell);

                auto textEle = cell->GetTextElement();
                Assert::IsNotNull(textEle);

                auto currColour = textEle->GetOutlineColour();

                Assert::AreEqual(overrideColour.r, currColour.r);
                Assert::AreEqual(overrideColour.g, currColour.g);
                Assert::AreEqual(overrideColour.b, currColour.b);
                Assert::AreEqual(overrideColour.a, currColour.a);
            }

            TEST_METHOD(IMenu_SetActiveTextElement_WithPassiveColour_SetsUnselectedTextPassiveColour)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                Colour passiveColour = Colour::White;

                menu.SetPassiveColour(passiveColour);

                Colour overrideColour = Colour::Red;

                menu.AddTestTextCell(0, 2, "Txt2", Colour::Black, overrideColour);
                menu.AddTestTextCell(5, 0, "Txt0", Colour::Black, overrideColour);
                menu.AddTestTextCell(8, 1, "Txt1", Colour::Black, overrideColour);

                menu.SetActiveCells();

                menu.SetActiveTextElementForTesting();

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                auto currPos = menuNav->GetCurrCursorPos();

                for (size_t i = 0; i < 3; i++)
                {
                    if (static_cast<int>(i) == currPos)
                        continue;

                    auto cell = menu.GetCellBySlotNumber(i);
                    Assert::IsNotNull(cell);

                    auto textEle = cell->GetTextElement();
                    Assert::IsNotNull(textEle);

                    auto currColour = textEle->GetOutlineColour();

                    Assert::AreEqual(passiveColour.r, currColour.r);
                    Assert::AreEqual(passiveColour.g, currColour.g);
                    Assert::AreEqual(passiveColour.b, currColour.b);
                    Assert::AreEqual(passiveColour.a, currColour.a);
                }
            }

            // ======================================================
            // Update
            // ======================================================

            TEST_METHOD(IMenu_Update_WithNoCursorSetsActiveTextElement)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                Colour passiveColour = Colour::White;

                menu.SetPassiveColour(passiveColour);

                Colour overrideColour = Colour::Red;

                menu.AddTestTextCell(0, 2, "Txt2", Colour::Black, overrideColour);
                menu.AddTestTextCell(5, 0, "Txt0", Colour::Black, overrideColour);
                menu.AddTestTextCell(8, 1, "Txt1", Colour::Black, overrideColour);

                menu.SetActiveCells();

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0,1,2 });

                auto currPos = menuNav->GetCurrCursorPos();

                menu.Update(0.6f);

                for (size_t i = 0; i < 3; i++)
                {
                    Colour expectedColour;

                    if (static_cast<int>(i) == currPos)
                        expectedColour = overrideColour;
                    else
                        expectedColour = passiveColour;

                    auto cell = menu.GetCellBySlotNumber(i);
                    Assert::IsNotNull(cell);

                    auto textEle = cell->GetTextElement();
                    Assert::IsNotNull(textEle);

                    auto currColour = textEle->GetOutlineColour();

                    Assert::AreEqual(expectedColour.r, currColour.r);
                    Assert::AreEqual(expectedColour.g, currColour.g);
                    Assert::AreEqual(expectedColour.b, currColour.b);
                    Assert::AreEqual(expectedColour.a, currColour.a);
                }
            }

            TEST_METHOD(IMenu_Update_WithNoCursorAndNavigationUnchanged_DoesNotSetActiveTextElement)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                Colour passiveColour = Colour::White;

                menu.SetPassiveColour(passiveColour);

                Colour overrideColour = Colour::Red;

                menu.AddTestTextCell(0, 2, "Txt2", Colour::Black, overrideColour);
                menu.AddTestTextCell(5, 0, "Txt0", Colour::Black, overrideColour);
                menu.AddTestTextCell(8, 1, "Txt1", Colour::Black, overrideColour);

                menu.SetActiveCells();

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0,1,2 });

                auto currPos = menuNav->GetCurrCursorPos();

                menu.Update(0.6f);

                menu.Update(0.6f);

                for (size_t i = 0; i < 3; i++)
                {
                    Colour expectedColour;

                    if (static_cast<int>(i) == currPos)
                        expectedColour = overrideColour;
                    else
                        expectedColour = passiveColour;

                    auto cell = menu.GetCellBySlotNumber(i);
                    Assert::IsNotNull(cell);

                    auto textEle = cell->GetTextElement();
                    Assert::IsNotNull(textEle);

                    auto currColour = textEle->GetOutlineColour();

                    Assert::AreEqual(expectedColour.r, currColour.r);
                    Assert::AreEqual(expectedColour.g, currColour.g);
                    Assert::AreEqual(expectedColour.b, currColour.b);
                    Assert::AreEqual(expectedColour.a, currColour.a);
                }
            }


            TEST_METHOD(IMenu_Update_WithNoCursorUpdatesActiveMenuCells)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.AddTestTextCell(0, 2, "Txt2", Colour::Black, Colour::Red);
                menu.AddTestTextCell(5, 0, "Txt0", Colour::Black, Colour::Red);
                menu.AddTestTextCell(8, 1, "Txt1", Colour::Black, Colour::Red);

                menu.SetActiveCells();

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0,1,2 });

                menu.Update(0.6f);

                for (size_t i = 0; i < 3; i++)
                {
                    auto cell = menu.GetCellBySlotNumber(i);
                    Assert::IsNotNull(cell);

                    auto textEle = static_cast<FakeText*>(cell->GetTextElement());
                    Assert::IsNotNull(textEle);

                    Assert::AreEqual(1, textEle->updateCount);
                    Assert::AreEqual(0.6f, textEle->lastDeltaTime);
                }
            }

            TEST_METHOD(IMenu_Update_WithCursorPositionsCursorWhenNavigationChanges)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0,1,2 });

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), *menuNav);

                menu.Update(0.6f);

                auto cursor = menu.GetCursor(0);

                auto cursorSpr = static_cast<FakeSprite*>(cursor->GetSprite());
                Assert::IsNotNull(cursorSpr);

                auto cursorSprPos = cursorSpr->GetPosition();

                auto cell = menu.GetCellBySlotNumber(menuNav->GetCurrCursorPos());
                Assert::IsNotNull(cell);

                auto cellPos = cell->GetPosition();

                Assert::AreEqual(cellPos.x, cursorSprPos.x);
                Assert::AreEqual(cellPos.y, cursorSprPos.y);
            }

            TEST_METHOD(IMenu_Update_WithCursorDoesNotRepositionWhenNavigationUnchanged)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0,1,2 });

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), *menuNav);

                menu.Update(0.6f);

                menu.Update(0.6f);

                auto cursor = menu.GetCursor(0);

                auto cursorSpr = static_cast<FakeSprite*>(cursor->GetSprite());
                Assert::IsNotNull(cursorSpr);

                Assert::AreEqual(2, cursorSpr->updateCount);
                Assert::AreEqual(0.6f, cursorSpr->lastDeltaTime);

                auto cursorSprPos = cursorSpr->GetPosition();

                auto cell = menu.GetCellBySlotNumber(menuNav->GetCurrCursorPos());
                Assert::IsNotNull(cell);

                auto cellPos = cell->GetPosition();

                Assert::AreEqual(cellPos.x, cursorSprPos.x);
                Assert::AreEqual(cellPos.y, cursorSprPos.y);
            }

            TEST_METHOD(IMenu_Update_WithCursorUpdatesActiveMenuCells)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0,1,2 });

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), *menuNav);

                menu.Update(0.6f);

                auto cursor = menu.GetCursor(0);

                auto cursorSpr = static_cast<FakeSprite*>(cursor->GetSprite());
                Assert::IsNotNull(cursorSpr);

                Assert::AreEqual(1, cursorSpr->updateCount);
                Assert::AreEqual(0.6f, cursorSpr->lastDeltaTime);
            }

            TEST_METHOD(IMenu_Update_WithInvalidActiveCellIndex_SkipsCellUpdate)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.AddTestTextCell(0, 2, "Txt2", Colour::Black, Colour::Red);
                menu.AddTestTextCell(5, 0, "Txt0", Colour::Black, Colour::Red);
                menu.AddTestTextCell(8, 1, "Txt1", Colour::Black, Colour::Red);

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0,1,2 });

                menu.Update(0.6f);

                std::vector<int> range({0,5,8});

                for (size_t i = 0; i < 3; i++)
                {
                    auto cell = menu.GetCellByIndex(range[i]);
                    Assert::IsNotNull(cell);

                    auto textEle = static_cast<FakeText*>(cell->GetTextElement());
                    Assert::IsNotNull(textEle);

                    Assert::AreEqual(0, textEle->updateCount);
                    Assert::AreEqual(0.0f, textEle->lastDeltaTime);
                }
            }

            // ======================================================
            // Render
            // ======================================================

            TEST_METHOD(IMenu_Render_WithNullRenderer_DoesNotRender)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.AddTestTextCell(0, 2, "Txt2", Colour::Black, Colour::Red);
                menu.AddTestTextCell(5, 0, "Txt0", Colour::Black, Colour::Red);
                menu.AddTestTextCell(8, 1, "Txt1", Colour::Black, Colour::Red);

                menu.SetActiveCells();

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0,1,2 });

                menu.Render(nullptr);

                for (size_t i = 0; i < 3; i++)
                {
                    auto cell = menu.GetCellBySlotNumber(i);
                    Assert::IsNotNull(cell);

                    auto textEle = static_cast<FakeText*>(cell->GetTextElement());
                    Assert::IsNotNull(textEle);

                    Assert::AreEqual(0, textEle->renderCount);
                }
            }

#if defined _DEBUG

            TEST_METHOD(IMenu_Render_InDebugBuild_RendersMenuSpace)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestMenuSpace();

                FakeRenderer renderer;

                menu.Render(&renderer);

                auto menuSpace = static_cast<FakeBox*>(menu.GetMenuSpace());
                Assert::IsNotNull(menuSpace);

                Assert::AreEqual(1,menuSpace->renderCount);
            }

#endif

            TEST_METHOD(IMenu_Render_WithCells_RendersAllCells)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.AddTestTextCell(0, 2, "Txt2", Colour::Black, Colour::Red);
                menu.AddTestTextCell(5, 0, "Txt0", Colour::Black, Colour::Red);
                menu.AddTestTextCell(8, 1, "Txt1", Colour::Black, Colour::Red);

                menu.SetActiveCells();

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0,1,2 });

                FakeRenderer renderer;

                menu.Render(&renderer);

                for (size_t i = 0; i < 3; i++)
                {
                    auto cell = menu.GetCellBySlotNumber(i);
                    Assert::IsNotNull(cell);

                    auto textEle = static_cast<FakeText*>(cell->GetTextElement());
                    Assert::IsNotNull(textEle);

                    Assert::AreEqual(1, textEle->renderCount);
                }
            }

            TEST_METHOD(IMenu_Render_WithCursors_RendersAllCursors)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                MenuNav nav(KeyCode::Up, KeyCode::Down);

                menu.AddCursor(std::make_shared<FakeSprite>("spr1"), nav);
                menu.AddCursor(std::make_shared<FakeSprite>("spr2"), nav);
                menu.AddCursor(std::make_shared<FakeSprite>("spr3"), nav);

                FakeRenderer renderer;

                menu.Render(&renderer);

                for (size_t i = 0; i < 3; i++)
                {
                    auto cursor = menu.GetCursor(i);
                    Assert::IsNotNull(cursor);

                    auto spr = static_cast<FakeSprite*>(cursor->GetSprite());
                    Assert::IsNotNull(spr);

                    Assert::AreEqual(1, spr->renderCount);
                }
            }

            TEST_METHOD(IMenu_Render_WithCellsAndCursors_RendersBoth)
            {
                TestableMenu menu(
                    Vector2f(600.f, 400.f),
                    2.f,
                    Vector2u(3u, 4u),
                    MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ));

                menu.BuildTestCells();

                menu.AddTestTextCell(0, 2, "Txt2", Colour::Black, Colour::Red);
                menu.AddTestTextCell(5, 0, "Txt0", Colour::Black, Colour::Red);
                menu.AddTestTextCell(8, 1, "Txt1", Colour::Black, Colour::Red);

                menu.SetActiveCells();

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0,1,2 });

                MenuNav nav(KeyCode::Up, KeyCode::Down);

                menu.AddCursor(std::make_shared<FakeSprite>("spr1"), nav);
                menu.AddCursor(std::make_shared<FakeSprite>("spr2"), nav);
                menu.AddCursor(std::make_shared<FakeSprite>("spr3"), nav);

                FakeRenderer renderer;

                menu.Render(&renderer);

                for (size_t i = 0; i < 3; i++)
                {
                    auto cell = menu.GetCellBySlotNumber(i);
                    Assert::IsNotNull(cell);

                    auto textEle = static_cast<FakeText*>(cell->GetTextElement());
                    Assert::IsNotNull(textEle);

                    Assert::AreEqual(1, textEle->renderCount);
                }

                for (size_t i = 0; i < 3; i++)
                {
                    auto cursor = menu.GetCursor(i);
                    Assert::IsNotNull(cursor);

                    auto spr = static_cast<FakeSprite*>(cursor->GetSprite());
                    Assert::IsNotNull(spr);

                    Assert::AreEqual(1, spr->renderCount);
                }
            }
        };
    }
}
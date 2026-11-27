#include "CppUnitTest.h"

#include <Engine/Core/GameManager.h>
#include <Engine/UI/MenuItem.h>
#include <Engine/Interface/UI/IMenu.h>
#include <Engine/Interface/Scene/ITransforms.h>
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
        TEST_CLASS(IMenuTests)
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
                        TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(0u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            )}, Vector2f(600.f, 400.f));
                    });
            }

            TEST_METHOD(IMenu_Constructor_ThrowsIfDimensionsYIsNotGreaterThanZero)
            {
                Assert::ExpectException<std::runtime_error>([&]
                    {
                        TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 0u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));
                    });
            }

            TEST_METHOD(IMenu_Constructor_DoesNotThrowIfDimensionsAreValid)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));
            }

            // ======================================================
            // Geometry
            // ======================================================

            TEST_METHOD(IMenu_CalculateCellSize_DividesMenuSpaceByDimensions)
            {
                Vector2f menuSize(600.f, 400.f);

                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, menuSize);

                auto cellSize = menu.CalculateCellSizeForTesting(menuSize);

                Assert::AreEqual(200.f, cellSize.x);
                Assert::AreEqual(100.f, cellSize.y);
            }

            TEST_METHOD(IMenu_CalculateMenuTopLeft_SubtractsOriginFromMenuPosition)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                auto topLeft = menu.CalculateMenuTopLeftForTesting(Vector2f(500, 350), Vector2f(300, 200));

                Assert::AreEqual(200.f, topLeft.x);
                Assert::AreEqual(150.f, topLeft.y);
            }

            TEST_METHOD(IMenu_CalculateCellPosition_ReturnsCorrectPositionForRowAndColumn)
            {
                Vector2f menuSize(600.f, 400.f);

                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, menuSize);

                menu.CalculateMenuTopLeftForTesting(Vector2f(500, 350), Vector2f(300, 200));
                menu.CalculateCellSizeForTesting(menuSize);

                auto cellPos = menu.CalculateCellPositionForTesting(1, 2);

                Assert::AreEqual(700.f, cellPos.x);
                Assert::AreEqual(300.f, cellPos.y);
            }

            TEST_METHOD(IMenu_CalculateCellPosition_ReturnsCorrectPositionForFirstCell)
            {
                Vector2f menuSize(600.f, 400.f);

                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, menuSize);

                menu.CalculateMenuTopLeftForTesting(Vector2f(500, 350), Vector2f(300, 200));
                menu.CalculateCellSizeForTesting(menuSize);

                auto cellPos = menu.CalculateCellPositionForTesting(0, 0);

                Assert::AreEqual(300.f, cellPos.x);
                Assert::AreEqual(200.f, cellPos.y);
            }

            TEST_METHOD(IMenu_CalculateCellPosition_ReturnsCorrectPositionForLastCell)
            {
                Vector2f menuSize(600.f, 400.f);

                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, menuSize);

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
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.SetMenuSpaceToNullForTesting();

                Assert::ExpectException<std::runtime_error>([&]
                    {
                        menu.BuildTestMenuSpace();
                    });
            }

            TEST_METHOD(IMenu_BuildMenuSpace_SetsMenuSpaceOriginToCenter)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestMenuSpace();

                auto menuSpace = menu.GetMenuSpace();
                Assert::IsNotNull(menuSpace);

                auto origin = menuSpace->GetOrigin();

                Assert::AreEqual(300.f, origin.x);
                Assert::AreEqual(200.f, origin.y);
            }

            TEST_METHOD(IMenu_BuildMenuSpace_AssignsMenuSpacePositionInCenteredMode)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestMenuSpace();

                auto menuSpace = menu.GetMenuSpace();
                Assert::IsNotNull(menuSpace);

                auto pos = menuSpace->GetPosition();

                Assert::AreEqual(500.f, pos.x);
                Assert::AreEqual(350.f, pos.y);

            }

            TEST_METHOD(IMenu_BuildMenuSpace_AssignsMenuSpacePositionInAnchoredMode)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Anchored,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

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
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

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
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                Assert::AreEqual(12, menu.factoryCallCount);
                Assert::AreEqual(2.f, menu.receivedOutlineThickness);

                auto cellSize = menu.receivedCellSize;

                Assert::AreEqual(200.f, cellSize.x);
                Assert::AreEqual(100.f, cellSize.y);
            }

            TEST_METHOD(IMenu_BuildCells_CreatesExpectedNumberOfCells)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                Assert::AreEqual(size_t(12), menu.GetNumberOfCells());
            }

            TEST_METHOD(IMenu_BuildCells_CreatesCellsWithCorrectGeometry)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

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
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                auto originalCell = menu.GetSharedCellForTesting(0);
                Assert::IsNotNull(originalCell.get());

                menu.BuildTestCells();

                Assert::AreEqual(size_t(12), menu.GetNumberOfCells());
                Assert::IsTrue(originalCell.get() != menu.GetCell({ 0, 0 }));
            }

            // ======================================================
            // Configuring Cells
            // ======================================================

            TEST_METHOD(IMenu_ConfigureCell_WithNoCells_DoesNotThrow)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.ConfigureCell(0, 0, {});

                auto cell = menu.GetCell({ 0, 0 });

                Assert::IsNull(cell);
            }

            TEST_METHOD(IMenu_ConfigureCell_WithInvalidCoordinates_DoesNotThrow)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.ConfigureCell(4, 0, {});

                auto cell = menu.GetCell({ 4, 0 });

                Assert::IsNull(cell);
            }

            TEST_METHOD(IMenu_ConfigureCell_AssignsSlotNumber)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.ConfigureCell(0, 0, {.slotNumber = 0});

                auto cell = menu.GetCell({ 0, 0 });

                Assert::IsNotNull(cell);

                Assert::AreEqual(0, cell->GetMenuSlotNumber());
            }

            TEST_METHOD(IMenu_ConfigureCell_WithNoElements_AssignsNeitherElement)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.ConfigureCell(0, 0, { .slotNumber = 0 });

                auto cell = menu.GetCell({ 0, 0 });

                Assert::IsNotNull(cell);

                Assert::IsNull(cell->GetSprite());

                Assert::IsNull(cell->GetText());
            }

            TEST_METHOD(IMenu_ConfigureCell_WithTextOnly_AssignsTextElement)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                menu.ConfigureCell(0, 0, { .slotNumber = 0, .text = text });

                auto cell = menu.GetCell({ 0, 0 });

                Assert::IsNotNull(cell);

                Assert::IsNull(cell->GetSprite());

                auto retText = cell->GetText();
                Assert::IsNotNull(retText);

                Assert::IsTrue(text.get() == retText);
            }

            TEST_METHOD(IMenu_ConfigureCell_WithSpriteOnly_AssignsSpriteElement)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                auto spr = std::make_shared<FakeSprite>("Spr");

                menu.ConfigureCell(0, 0, { .slotNumber = 0, .sprite = spr });

                auto cell = menu.GetCell({ 0, 0 });

                Assert::IsNotNull(cell);

                Assert::IsNull(cell->GetText());

                auto retSpr = cell->GetSprite();
                Assert::IsNotNull(retSpr);

                Assert::IsTrue(spr.get() == retSpr);
            }

            TEST_METHOD(IMenu_ConfigureCell_WithTextAndSprite_AssignsBothElements)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                auto spr = std::make_shared<FakeSprite>("Spr");
                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                menu.ConfigureCell(0, 0, { .slotNumber = 0, .text = text, .sprite = spr, });

                auto cell = menu.GetCell({ 0, 0 });

                Assert::IsNotNull(cell);

                auto retText = cell->GetText();
                Assert::IsNotNull(retText);

                Assert::IsTrue(text.get() == retText);

                auto retSpr = cell->GetSprite();
                Assert::IsNotNull(retSpr);

                Assert::IsTrue(spr.get() == retSpr);
            }

            TEST_METHOD(IMenu_ConfigureCell_WithoutTextStyles_UsesDefaultTextStyles)
            {
                NavigationStyles textStyles;
                textStyles.defaultStyle.colour = Colour::Yellow;
                textStyles.selectedStyle.colour = Colour::Green;

                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ),
                    .defaultTextStyles = textStyles,
                    }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                menu.ConfigureCell(0, 0, { .slotNumber = 0, .text = text });

                auto cell = menu.GetCell({ 0, 0 });

                Assert::IsNotNull(cell);

                auto retText = cell->GetText();
                Assert::IsNotNull(retText);

                Assert::IsTrue(text.get() == retText);

                auto expColour = *textStyles.defaultStyle.colour;
                auto actColour = retText->GetFillColour();

                Assert::AreEqual(expColour.r, actColour.r);
                Assert::AreEqual(expColour.g, actColour.g);
                Assert::AreEqual(expColour.b, actColour.b);
                Assert::AreEqual(expColour.a, actColour.a);
            }

            TEST_METHOD(IMenu_ConfigureCell_WithoutSpriteStyles_UsesDefaultSpriteStyles)
            {
                NavigationStyles spriteStyles;
                spriteStyles.defaultStyle.colour = Colour::Green;
                spriteStyles.selectedStyle.colour = Colour::Yellow;

                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ),
                    .defaultSpriteStyles = spriteStyles }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                auto spr = std::make_shared<FakeSprite>("Spr");

                menu.ConfigureCell(0, 0, { .slotNumber = 0, .sprite = spr, });

                auto cell = menu.GetCell({ 0, 0 });

                Assert::IsNotNull(cell);

                auto retSpr = cell->GetSprite();
                Assert::IsNotNull(retSpr);

                Assert::IsTrue(spr.get() == retSpr);

                auto expColour = *spriteStyles.defaultStyle.colour;
                auto actColour = retSpr->GetColour();

                Assert::AreEqual(expColour.r, actColour.r);
                Assert::AreEqual(expColour.g, actColour.g);
                Assert::AreEqual(expColour.b, actColour.b);
                Assert::AreEqual(expColour.a, actColour.a);
            }

            TEST_METHOD(IMenu_ConfigureCell_WithTextStyles_OverridesDefaultTextStyles)
            {
                NavigationStyles textStyles;
                textStyles.defaultStyle.colour = Colour::Yellow;
                textStyles.selectedStyle.colour = Colour::Green;

                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ),
                    .defaultTextStyles = textStyles,
                    }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                NavigationStyles customStyles;
                customStyles.defaultStyle.colour = Colour::Magenta;
                customStyles.selectedStyle.colour = Colour::Cyan;

                menu.ConfigureCell(0, 0, { .slotNumber = 0, .text = text, .textStyles = customStyles });

                auto cell = menu.GetCell({ 0, 0 });

                Assert::IsNotNull(cell);

                auto retTxt = cell->GetText();
                Assert::IsNotNull(retTxt);

                Assert::IsTrue(text.get() == retTxt);

                auto expColour = *customStyles.defaultStyle.colour;
                auto actColour = retTxt->GetFillColour();

                Assert::AreEqual(expColour.r, actColour.r);
                Assert::AreEqual(expColour.g, actColour.g);
                Assert::AreEqual(expColour.b, actColour.b);
                Assert::AreEqual(expColour.a, actColour.a);
            }

            TEST_METHOD(IMenu_ConfigureCell_WithSpriteStyles_OverridesDefaultSpriteStyles)
            {
                NavigationStyles spriteStyles;
                spriteStyles.defaultStyle.colour = Colour::Yellow;
                spriteStyles.selectedStyle.colour = Colour::Green;

                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ),
                    .defaultSpriteStyles = spriteStyles,
                    }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                auto spr = std::make_shared<FakeSprite>("Spr");

                NavigationStyles customStyles;
                customStyles.defaultStyle.colour = Colour::Magenta;
                customStyles.selectedStyle.colour = Colour::Cyan;

                menu.ConfigureCell(0, 0, { .slotNumber = 0, .sprite = spr, .spriteStyles = customStyles });

                auto cell = menu.GetCell({ 0, 0 });

                Assert::IsNotNull(cell);

                auto retSpr = cell->GetSprite();
                Assert::IsNotNull(retSpr);

                Assert::IsTrue(spr.get() == retSpr);

                auto expColour = *customStyles.defaultStyle.colour;
                auto actColour = retSpr->GetColour();

                Assert::AreEqual(expColour.r, actColour.r);
                Assert::AreEqual(expColour.g, actColour.g);
                Assert::AreEqual(expColour.b, actColour.b);
                Assert::AreEqual(expColour.a, actColour.a);
            }

            // ======================================================
            // Cell Indexing
            // ======================================================

            TEST_METHOD(IMenu_CalculateCellIndex_ReturnsIndexForRowColPair)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                auto first = menu.CalculateCellIndexForTesting(0, 0);
                Assert::AreEqual(size_t(0), first);

                auto rand = menu.CalculateCellIndexForTesting(1, 2);
                Assert::AreEqual(size_t(5), rand);

                auto last = menu.CalculateCellIndexForTesting(3, 2);
                Assert::AreEqual(size_t(11), last);
            }

            TEST_METHOD(IMenu_GetCellByIndex_OutOfBoundsReturnsNull)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                Assert::IsNull(menu.GetCellByIndex(12));
            }

            TEST_METHOD(IMenu_GetCellByIndex_ValidIndexReturnsCell)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                Assert::IsNotNull(menu.GetCellByIndex(5));
            }

            TEST_METHOD(IMenu_GetCell_ReturnsNullIfRowIsNegative)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                Assert::IsNull(menu.GetCell({-1, 2}));
            }

            TEST_METHOD(IMenu_GetCell_ReturnsNullIfColIsNegative)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                Assert::IsNull(menu.GetCell({ 1, -2 }));
            }

            TEST_METHOD(IMenu_GetCell_ReturnsNullIfCoordinatesAreOutOfBounds)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                Assert::IsNull(menu.GetCell({ 3, 3 }));
            }

            TEST_METHOD(IMenu_GetCell_ValidCoordinatesReturnsCell)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                Assert::IsNotNull(menu.GetCell({ 1, 2 }));
            }

            TEST_METHOD(IMenu_SetActiveCells_ThrowsIfDuplicateSlotNumber)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

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
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

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
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

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
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.SetActiveCells();

                auto activeCells = menu.GetActiveCellsForTesting();

                Assert::IsTrue(activeCells.empty());
            }

            TEST_METHOD(IMenu_GetCellBySlotNumber_ReturnsNullIfActiveCellsIsEmpty)
            {
                TestableMenu menu({
                             .outlineThickness = 2.f,
                             .dimensions = Vector2u(3u, 4u),
                             .positionData = MenuPositionData(
                                 MenuPositionMode::Centered,
                                 Vector2f(500, 350)
                             ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.SetActiveCells();

                Assert::IsNull(menu.GetCellBySlotNumber(0));
            }

            TEST_METHOD(IMenu_GetCellBySlotNumber_ReturnsNullIfActiveCellsDoesNotContainSlotNumber)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                Assert::IsNull(menu.GetCellBySlotNumber(3));
            }

            TEST_METHOD(IMenu_GetCellBySlotNumber_ValidSlotNumberReturnsCell)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

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
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                Assert::IsNull(menu.GetCursor(0));
            }

            TEST_METHOD(IMenu_GetCursor_ReturnsNullIfIndexIsOutOfRange)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                MenuNav nav(KeyCode::Up, KeyCode::Down);

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), nav);

                Assert::IsNull(menu.GetCursor(1));
            }

            TEST_METHOD(IMenu_AddCursor_ReturnsNullIfSpriteIsInvalid)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                MenuNav nav(KeyCode::Up, KeyCode::Down);

                auto cursor = menu.AddCursor(nullptr, nav);

                Assert::IsNull(cursor);
            }

            TEST_METHOD(IMenu_AddCursor_ReturnsCursor)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                MenuNav nav(KeyCode::Up, KeyCode::Down);

                auto cursor = menu.AddCursor(std::make_shared<FakeSprite>("spr"), nav);

                Assert::IsNotNull(cursor);
            }

            TEST_METHOD(IMenu_AddCursor_SetsCursor)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                MenuNav nav(KeyCode::Up, KeyCode::Down);

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), nav);

                auto cursor = menu.GetCursor(0);

                Assert::IsNotNull(cursor);
            }

            // ======================================================
            // Update
            // ======================================================

            TEST_METHOD(IMenu_Update_WithNoCursor_UpdatesAllMenuCells)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.AddTestTextCell(0, 0, 2, Colour::White, "Txt2", {});
                menu.AddTestTextCell(1, 2, 0, Colour::White, "Txt0", {});
                menu.AddTestTextCell(2, 2, 1, Colour::White, "Txt1", {});
                menu.AddTestTextCell(3, 0, -1, Colour::White, "Txt3", {});

                menu.SetActiveCells();

                auto* menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0, 1, 2 });

                menu.Update(0.6f);

                std::vector<size_t> cellIndices = { 0, 5, 8, 9 };

                for (size_t index : cellIndices)
                {
                    auto* cell = menu.GetCellByIndex(index);
                    Assert::IsNotNull(cell);

                    auto* text = static_cast<FakeText*>(cell->GetText());
                    Assert::IsNotNull(text);

                    Assert::AreEqual(1, text->updateCount);
                    Assert::AreEqual(0.6f, text->lastDeltaTime);
                }
            }

            TEST_METHOD(IMenu_Update_WithCursor_UpdatesAllMenuCells)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.AddTestTextCell(0, 0, 2, Colour::White, "Txt2", {});
                menu.AddTestTextCell(1, 2, 0, Colour::White, "Txt0", {});
                menu.AddTestTextCell(2, 2, 1, Colour::White, "Txt1", {});
                menu.AddTestTextCell(3, 0, -1, Colour::White, "Txt3", {});

                menu.SetActiveCells();

                auto* menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0, 1, 2 });

                auto* cursor = menu.AddCursor(
                    std::make_shared<FakeSprite>("spr"), *menuNav);

                Assert::IsNotNull(cursor);

                menu.Update(0.6f);

                std::vector<size_t> cellIndices = { 0, 5, 8, 9 };

                for (size_t index : cellIndices)
                {
                    auto* cell = menu.GetCellByIndex(index);
                    Assert::IsNotNull(cell);

                    auto* text = static_cast<FakeText*>(cell->GetText());
                    Assert::IsNotNull(text);

                    Assert::AreEqual(1, text->updateCount);
                    Assert::AreEqual(0.6f, text->lastDeltaTime);
                }
            }

            TEST_METHOD(IMenu_Update_WithCursorPositionsCursorWhenNavigationChanges)
            {
                TestableMenu menu({
                             .outlineThickness = 2.f,
                             .dimensions = Vector2u(3u, 4u),
                             .positionData = MenuPositionData(
                                 MenuPositionMode::Centered,
                                 Vector2f(500, 350)
                             ) }, Vector2f(600.f, 400.f));

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
                Assert::IsNotNull(cursor);

                auto* transform = dynamic_cast<ITransforms*>(cursor->GetSprite());
                Assert::IsNotNull(transform);

                auto cursorPos = transform->GetPosition();

                Assert::AreEqual(700.f, cursorPos.x);
                Assert::AreEqual(300.f, cursorPos.y);
            }

            TEST_METHOD(IMenu_Update_WithCursorDoesNotRepositionWhenNavigationUnchanged)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

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
                Assert::AreEqual(1, cursorSpr->setPositionCount);
            }

            // ======================================================
            // Navigation selection
            // ======================================================

            TEST_METHOD(IMenu_Update_WithNoCursor_SelectsInitialCell)
            {
                TestableMenu menu({
                    .outlineThickness = 2.f,
                    .dimensions = Vector2u(3u, 4u),
                    .positionData = MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                auto* menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0, 1, 2 });

                Assert::AreEqual(0, menuNav->GetCurrCursorPos());

                auto* cell0 = menu.GetCellBySlotNumber(0);
                auto* cell1 = menu.GetCellBySlotNumber(1);
                auto* cell2 = menu.GetCellBySlotNumber(2);

                Assert::IsNotNull(cell0);
                Assert::IsNotNull(cell1);
                Assert::IsNotNull(cell2);

                Assert::IsFalse(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());

                menu.Update(0.6f);

                Assert::IsTrue(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());
            }

            TEST_METHOD(IMenu_Update_WithNoCursorAndNavigationChanged_UpdatesSelectedCells)
            {
                TestableMenu menu({
                    .outlineThickness = 2.f,
                    .dimensions = Vector2u(3u, 4u),
                    .positionData = MenuPositionData(
                        MenuPositionMode::Centered,
                        Vector2f(500, 350)
                    ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                auto* menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0, 1, 2 });

                Assert::AreEqual(0, menuNav->GetCurrCursorPos());

                auto* cell0 = menu.GetCellBySlotNumber(0);
                auto* cell1 = menu.GetCellBySlotNumber(1);
                auto* cell2 = menu.GetCellBySlotNumber(2);

                Assert::IsNotNull(cell0);
                Assert::IsNotNull(cell1);
                Assert::IsNotNull(cell2);

                menu.Update(0.6f);

                menuNav->SetPrevCursorPos(0);
                menuNav->SetCurrCursorPos(1);

                Assert::AreEqual(1, menuNav->GetCurrCursorPos());

                menu.Update(0.6f);

                Assert::IsFalse(cell0->GetSelected());
                Assert::IsTrue(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());
            }

            TEST_METHOD(IMenu_Update_WithCursor_SelectsInitialCell)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0,1,2 });

                Assert::AreEqual(0, menuNav->GetCurrCursorPos());

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), *menuNav);

                auto* cell0 = menu.GetCellBySlotNumber(0);
                auto* cell1 = menu.GetCellBySlotNumber(1);
                auto* cell2 = menu.GetCellBySlotNumber(2);

                Assert::IsNotNull(cell0);
                Assert::IsNotNull(cell1);
                Assert::IsNotNull(cell2);

                Assert::IsFalse(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());

                menu.Update(0.6f);

                Assert::IsTrue(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());
            }

            TEST_METHOD(IMenu_Update_WithCursorAndNavigationChanged_UpdatesSelectedCells)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0,1,2 });

                Assert::AreEqual(0, menuNav->GetCurrCursorPos());

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), *menuNav);

                auto* cell0 = menu.GetCellBySlotNumber(0);
                auto* cell1 = menu.GetCellBySlotNumber(1);
                auto* cell2 = menu.GetCellBySlotNumber(2);

                Assert::IsNotNull(cell0);
                Assert::IsNotNull(cell1);
                Assert::IsNotNull(cell2);

                menu.Update(0.6f);

                menuNav->SetCurrCursorPos(1);
                menuNav->SetPrevCursorPos(0);

                auto cursor = menu.GetCursor(0);
                Assert::IsNotNull(cursor);

                cursor->GetMenuNav().SetCurrCursorPos(1);
                cursor->GetMenuNav().SetPrevCursorPos(0);

                Assert::AreEqual(1, cursor->GetMenuNav().GetCurrCursorPos());

                menu.Update(0.6f);

                Assert::IsFalse(cell0->GetSelected());
                Assert::IsTrue(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());
            }

            TEST_METHOD(IMenu_Update_WithUnchangedNavigation_PreservesSelection)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                auto* menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0, 1, 2 });

                Assert::AreEqual(0, menuNav->GetCurrCursorPos());

                auto* cell0 = menu.GetCellBySlotNumber(0);
                auto* cell1 = menu.GetCellBySlotNumber(1);
                auto* cell2 = menu.GetCellBySlotNumber(2);

                Assert::IsNotNull(cell0);
                Assert::IsNotNull(cell1);
                Assert::IsNotNull(cell2);

                menu.Update(0.6f);

                Assert::IsTrue(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());

                Assert::IsFalse(menuNav->HasMoved());

                menu.Update(0.6f);

                Assert::IsTrue(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());
            }

            TEST_METHOD(IMenu_Update_WithInvalidInitialNavigationPosition_DoesNotSelectCell)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                auto* menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                Assert::AreEqual(MenuNav::s_InvalidPos, menuNav->GetCurrCursorPos());

                auto* cell0 = menu.GetCellBySlotNumber(0);
                auto* cell1 = menu.GetCellBySlotNumber(1);
                auto* cell2 = menu.GetCellBySlotNumber(2);

                Assert::IsNotNull(cell0);
                Assert::IsNotNull(cell1);
                Assert::IsNotNull(cell2);

                Assert::IsFalse(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());

                menu.Update(0.6f);

                Assert::IsFalse(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());
            }

            TEST_METHOD(IMenu_Update_WithRejectedNavigationChange_PreservesPreviousSelection)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                auto* menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0, 1, 2 });

                Assert::AreEqual(0, menuNav->GetCurrCursorPos());

                auto* cell0 = menu.GetCellBySlotNumber(0);
                auto* cell1 = menu.GetCellBySlotNumber(1);
                auto* cell2 = menu.GetCellBySlotNumber(2);

                Assert::IsNotNull(cell0);
                Assert::IsNotNull(cell1);
                Assert::IsNotNull(cell2);

                menu.Update(0.6f);

                menuNav->SetCurrCursorPos(MenuNav::s_InvalidPos);

                Assert::AreEqual(0, menuNav->GetCurrCursorPos());

                menu.Update(0.6f);

                Assert::IsTrue(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());
            }

            /*TEST_METHOD(IMenu_Update_WithInvalidNavigationChange_PreservesPreviousSelection)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                auto* menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0, 1, 2, 3 });

                Assert::AreEqual(0, menuNav->GetCurrCursorPos());

                auto* cell0 = menu.GetCellBySlotNumber(0);
                auto* cell1 = menu.GetCellBySlotNumber(1);
                auto* cell2 = menu.GetCellBySlotNumber(2);

                Assert::IsNotNull(cell0);
                Assert::IsNotNull(cell1);
                Assert::IsNotNull(cell2);

                menu.Update(0.6f);

                menuNav->SetCurrCursorPos(3);

                Assert::AreEqual(0, menuNav->GetCurrCursorPos());

                menu.Update(0.6f);

                Assert::IsTrue(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());
            }*/

            // ======================================================
            // Multiple cursor selection
            // ======================================================

            TEST_METHOD(IMenu_Update_WithMultipleCursors_SelectsAllOccupiedCells)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                MenuNav cursor1MenuNav(KeyCode::Up, KeyCode::Down);
                cursor1MenuNav.SetCursorRange({ 0,1,2 });

                Assert::AreEqual(0, cursor1MenuNav.GetCurrCursorPos());

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), cursor1MenuNav);

                MenuNav cursor2MenuNav(KeyCode::Up, KeyCode::Down);
                cursor2MenuNav.SetCursorRange({ 0,1,2 });

                cursor2MenuNav.SetCurrCursorPos(2);

                Assert::AreEqual(2, cursor2MenuNav.GetCurrCursorPos());

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), cursor2MenuNav);

                auto* cell0 = menu.GetCellBySlotNumber(0);
                auto* cell1 = menu.GetCellBySlotNumber(1);
                auto* cell2 = menu.GetCellBySlotNumber(2);

                Assert::IsNotNull(cell0);
                Assert::IsNotNull(cell1);
                Assert::IsNotNull(cell2);

                Assert::IsFalse(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());

                menu.Update(0.6f);

                Assert::IsTrue(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsTrue(cell2->GetSelected());
            }

            TEST_METHOD(IMenu_Update_WithMultipleCursorsOnSameCell_KeepsCellSelected)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                MenuNav cursor1MenuNav(KeyCode::Up, KeyCode::Down);
                cursor1MenuNav.SetCursorRange({ 0,1,2 });

                Assert::AreEqual(0, cursor1MenuNav.GetCurrCursorPos());

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), cursor1MenuNav);

                MenuNav cursor2MenuNav(KeyCode::Up, KeyCode::Down);
                cursor2MenuNav.SetCursorRange({ 0,1,2 });

                Assert::AreEqual(0, cursor2MenuNav.GetCurrCursorPos());

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), cursor2MenuNav);

                auto* cell0 = menu.GetCellBySlotNumber(0);
                auto* cell1 = menu.GetCellBySlotNumber(1);
                auto* cell2 = menu.GetCellBySlotNumber(2);

                Assert::IsNotNull(cell0);
                Assert::IsNotNull(cell1);
                Assert::IsNotNull(cell2);

                Assert::IsFalse(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());

                menu.Update(0.6f);

                Assert::IsTrue(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());
            }

            TEST_METHOD(IMenu_Update_WithOneCursorLeavingSharedCell_KeepsCellSelected)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                MenuNav cursor1MenuNav(KeyCode::Up, KeyCode::Down);
                cursor1MenuNav.SetCursorRange({ 0,1,2 });

                Assert::AreEqual(0, cursor1MenuNav.GetCurrCursorPos());

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), cursor1MenuNav);

                MenuNav cursor2MenuNav(KeyCode::Up, KeyCode::Down);
                cursor2MenuNav.SetCursorRange({ 0,1,2 });

                Assert::AreEqual(0, cursor2MenuNav.GetCurrCursorPos());

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), cursor2MenuNav);

                auto* cell0 = menu.GetCellBySlotNumber(0);
                auto* cell1 = menu.GetCellBySlotNumber(1);
                auto* cell2 = menu.GetCellBySlotNumber(2);

                Assert::IsNotNull(cell0);
                Assert::IsNotNull(cell1);
                Assert::IsNotNull(cell2);

                menu.Update(0.6f);

                Assert::IsTrue(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());

                auto cursor2 = menu.GetCursor(1);
                Assert::IsNotNull(cursor2);

                cursor2->GetMenuNav().SetCurrCursorPos(2);

                menu.Update(0.6f);

                Assert::IsTrue(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsTrue(cell2->GetSelected());
            }

            TEST_METHOD(IMenu_Update_WithLastCursorLeavingSharedCell_DeselectsCell)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                MenuNav cursor1MenuNav(KeyCode::Up, KeyCode::Down);
                cursor1MenuNav.SetCursorRange({ 0,1,2 });

                Assert::AreEqual(0, cursor1MenuNav.GetCurrCursorPos());

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), cursor1MenuNav);

                MenuNav cursor2MenuNav(KeyCode::Up, KeyCode::Down);
                cursor2MenuNav.SetCursorRange({ 0,1,2 });

                Assert::AreEqual(0, cursor2MenuNav.GetCurrCursorPos());

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), cursor2MenuNav);

                auto* cell0 = menu.GetCellBySlotNumber(0);
                auto* cell1 = menu.GetCellBySlotNumber(1);
                auto* cell2 = menu.GetCellBySlotNumber(2);

                Assert::IsNotNull(cell0);
                Assert::IsNotNull(cell1);
                Assert::IsNotNull(cell2);

                menu.Update(0.6f);

                Assert::IsTrue(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsFalse(cell2->GetSelected());

                auto cursor1 = menu.GetCursor(0);
                Assert::IsNotNull(cursor1);

                cursor1->GetMenuNav().SetCurrCursorPos(1);

                auto cursor2 = menu.GetCursor(1);
                Assert::IsNotNull(cursor2);

                cursor2->GetMenuNav().SetCurrCursorPos(2);

                menu.Update(0.6f);

                Assert::IsFalse(cell0->GetSelected());
                Assert::IsTrue(cell1->GetSelected());
                Assert::IsTrue(cell2->GetSelected());
            }

            TEST_METHOD(IMenu_Update_WithCursorsSwappingCells_PreservesSelection)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.GetCellByIndex(0)->SetMenuSlotNumber(2);
                menu.GetCellByIndex(5)->SetMenuSlotNumber(0);
                menu.GetCellByIndex(8)->SetMenuSlotNumber(1);

                menu.SetActiveCells();

                MenuNav cursor1MenuNav(KeyCode::Up, KeyCode::Down);
                cursor1MenuNav.SetCursorRange({ 0,1,2 });

                Assert::AreEqual(0, cursor1MenuNav.GetCurrCursorPos());

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), cursor1MenuNav);

                MenuNav cursor2MenuNav(KeyCode::Up, KeyCode::Down);
                cursor2MenuNav.SetCursorRange({ 0,1,2 });

                cursor2MenuNav.SetCurrCursorPos(2);

                Assert::AreEqual(2, cursor2MenuNav.GetCurrCursorPos());

                menu.AddCursor(std::make_shared<FakeSprite>("spr"), cursor2MenuNav);

                auto* cell0 = menu.GetCellBySlotNumber(0);
                auto* cell1 = menu.GetCellBySlotNumber(1);
                auto* cell2 = menu.GetCellBySlotNumber(2);

                Assert::IsNotNull(cell0);
                Assert::IsNotNull(cell1);
                Assert::IsNotNull(cell2);

                menu.Update(0.6f);

                Assert::IsTrue(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsTrue(cell2->GetSelected());

                auto cursor1 = menu.GetCursor(0);
                Assert::IsNotNull(cursor1);

                cursor1->GetMenuNav().SetCurrCursorPos(2);

                auto cursor2 = menu.GetCursor(1);
                Assert::IsNotNull(cursor2);

                cursor2->GetMenuNav().SetCurrCursorPos(0);

                menu.Update(0.6f);

                Assert::IsTrue(cell0->GetSelected());
                Assert::IsFalse(cell1->GetSelected());
                Assert::IsTrue(cell2->GetSelected());
            }

            // ======================================================
            // Render
            // ======================================================

            TEST_METHOD(IMenu_Render_WithNullRenderer_DoesNotRender)
            {
                TestableMenu menu({
                             .outlineThickness = 2.f,
                             .dimensions = Vector2u(3u, 4u),
                             .positionData = MenuPositionData(
                                 MenuPositionMode::Centered,
                                 Vector2f(500, 350)
                             ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.AddTestTextCell(0, 0, 2, Colour::Black, "Txt2", {});
                menu.AddTestTextCell(1, 2, 0, Colour::Black, "Txt0", {});
                menu.AddTestTextCell(2, 2, 1, Colour::Black, "Txt1", {});

                menu.SetActiveCells();

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0,1,2 });

                menu.Render(nullptr);

                for (size_t i = 0; i < 3; i++)
                {
                    auto cell = menu.GetCellBySlotNumber((int)i);
                    Assert::IsNotNull(cell);

                    auto textEle = static_cast<FakeText*>(cell->GetText());
                    Assert::IsNotNull(textEle);

                    Assert::AreEqual(0, textEle->renderCount);
                }
            }

#if defined _DEBUG

            TEST_METHOD(IMenu_Render_InDebugBuild_RendersMenuSpace)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

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
                TestableMenu menu({
                             .outlineThickness = 2.f,
                             .dimensions = Vector2u(3u, 4u),
                             .positionData = MenuPositionData(
                                 MenuPositionMode::Centered,
                                 Vector2f(500, 350)
                             ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.AddTestTextCell(0, 0, 2, Colour::Black, "Txt2", {});
                menu.AddTestTextCell(1, 2, 0, Colour::Black, "Txt0", {});
                menu.AddTestTextCell(2, 2, 1, Colour::Black, "Txt1", {});

                menu.SetActiveCells();

                auto menuNav = menu.GetMenuNav();
                Assert::IsNotNull(menuNav);

                menuNav->SetCursorRange({ 0,1,2 });

                FakeRenderer renderer;

                menu.Render(&renderer);

                for (size_t i = 0; i < 3; i++)
                {
                    auto cell = menu.GetCellBySlotNumber((int)i);
                    Assert::IsNotNull(cell);

                    auto textEle = static_cast<FakeText*>(cell->GetText());
                    Assert::IsNotNull(textEle);

                    Assert::AreEqual(1, textEle->renderCount);
                }
            }

            TEST_METHOD(IMenu_Render_WithCursors_RendersAllCursors)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                MenuNav nav(KeyCode::Up, KeyCode::Down);

                menu.AddCursor(std::make_shared<FakeSprite>("spr1"), nav);
                menu.AddCursor(std::make_shared<FakeSprite>("spr2"), nav);
                menu.AddCursor(std::make_shared<FakeSprite>("spr3"), nav);

                FakeRenderer renderer;

                menu.Render(&renderer);

                for (size_t i = 0; i < 3; i++)
                {
                    auto cursor = menu.GetCursor((int)i);
                    Assert::IsNotNull(cursor);

                    auto spr = static_cast<FakeSprite*>(cursor->GetSprite());
                    Assert::IsNotNull(spr);

                    Assert::AreEqual(1, spr->renderCount);
                }
            }

            TEST_METHOD(IMenu_Render_WithCellsAndCursors_RendersBoth)
            {
                TestableMenu menu({
                            .outlineThickness = 2.f,
                            .dimensions = Vector2u(3u, 4u),
                            .positionData = MenuPositionData(
                                MenuPositionMode::Centered,
                                Vector2f(500, 350)
                            ) }, Vector2f(600.f, 400.f));

                menu.BuildTestCells();

                menu.AddTestTextCell(0, 0, 2, Colour::Black, "Txt2", {});
                menu.AddTestTextCell(1, 2, 0, Colour::Black, "Txt0", {});
                menu.AddTestTextCell(2, 2, 1, Colour::Black, "Txt1", {});

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
                    auto cell = menu.GetCellBySlotNumber((int)i);
                    Assert::IsNotNull(cell);

                    auto textEle = static_cast<FakeText*>(cell->GetText());
                    Assert::IsNotNull(textEle);

                    Assert::AreEqual(1, textEle->renderCount);
                }

                for (size_t i = 0; i < 3; i++)
                {
                    auto cursor = menu.GetCursor((int)i);
                    Assert::IsNotNull(cursor);

                    auto spr = static_cast<FakeSprite*>(cursor->GetSprite());
                    Assert::IsNotNull(spr);

                    Assert::AreEqual(1, spr->renderCount);
                }
            }
        };
    }
}
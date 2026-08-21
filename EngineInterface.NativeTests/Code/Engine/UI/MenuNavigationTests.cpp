#include "CppUnitTest.h"

#include <Engine/Core/GameManager.h>
#include <Fakes/Input/FakeKeyConverter.h>
#include <Fakes/Input/TestableInputManager.h>
#include <Fakes/UI/TestableMenuNav.h>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Scene
    {
        TEST_CLASS(MenuNavigationTests)
        {
        public:
            // ======================================================
            // Constructor
            // ======================================================
            TEST_METHOD(MenuNav_Constructor_SetsNavigationKeys)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                Assert::AreEqual(
                    static_cast<int>(KeyCode::Left),
                    static_cast<int>(menuNav.GetAscKeyForTesting())
                );

                Assert::AreEqual(
                    static_cast<int>(KeyCode::Right),
                    static_cast<int>(menuNav.GetDesKeyForTesting())
                );
            }

            TEST_METHOD(MenuNav_Constructor_DefaultCurrentCursorPosition_IsInvalid)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                Assert::AreEqual(-1, menuNav.GetCurrCursorPos());
            }

            TEST_METHOD(MenuNav_Constructor_DefaultPreviousCursorPosition_IsInvalid)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                Assert::AreEqual(-1, menuNav.GetPrevCurrCursorPosForTesting());
            }

            TEST_METHOD(MenuNav_Constructor_DefaultHasMoved_ReturnsFalse)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                Assert::IsFalse(menuNav.HasMoved());
            }

            // ======================================================
            // ChangeNavKeys
            // ======================================================

            TEST_METHOD(MenuNav_ChangeNavKeys_UpdatesAscendingKey)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                Assert::AreEqual(
                    static_cast<int>(KeyCode::Left),
                    static_cast<int>(menuNav.GetAscKeyForTesting())
                );

                menuNav.ChangeNavKeys(KeyCode::Right, KeyCode::Left);

                Assert::AreEqual(
                    static_cast<int>(KeyCode::Right),
                    static_cast<int>(menuNav.GetAscKeyForTesting())
                );
            }

            TEST_METHOD(MenuNav_ChangeNavKeys_UpdatesDescendingKey)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                Assert::AreEqual(
                    static_cast<int>(KeyCode::Right),
                    static_cast<int>(menuNav.GetDesKeyForTesting())
                );

                menuNav.ChangeNavKeys(KeyCode::Right, KeyCode::Left);

                Assert::AreEqual(
                    static_cast<int>(KeyCode::Left),
                    static_cast<int>(menuNav.GetDesKeyForTesting())
                );
            }

            // ======================================================
            // SetCursorRange
            // ======================================================

            TEST_METHOD(MenuNav_SetCursorRange_WithEmptyRange_SetsCurrentToInvalid)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                Assert::AreEqual(MenuNav::s_InvalidPos, menuNav.GetCurrCursorPos());
            }

            TEST_METHOD(MenuNav_SetCursorRange_WithEmptyRange_SetsPreviousToInvalid)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                Assert::AreEqual(MenuNav::s_InvalidPos, menuNav.GetPrevCurrCursorPosForTesting());
            }

            TEST_METHOD(MenuNav_SetCursorRange_WithEmptyRange_HasMovedReturnsFalse)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                Assert::IsFalse(menuNav.HasMoved());
            }

            TEST_METHOD(MenuNav_SetCursorRange_WithValidRange_SetsCurrentToFirstPosition)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());
            }

            TEST_METHOD(MenuNav_SetCursorRange_WithValidRange_SetsPreviousToFirstPosition)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                Assert::AreEqual(menuNav.GetCurrCursorPos(), menuNav.GetPrevCurrCursorPosForTesting());
            }

            TEST_METHOD(MenuNav_SetCursorRange_WithValidRange_HasMovedReturnsFalse)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                Assert::IsFalse(menuNav.HasMoved());
            }

            TEST_METHOD(MenuNav_SetCursorRange_ReplacingRange_ResetsCurrentToNewFirstPosition)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());

                rng[0] = 3;
                rng[1] = 4;
                rng[2] = 5;

                menuNav.SetCursorRange(rng);

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());
            }

            TEST_METHOD(MenuNav_SetCursorRange_ReplacingRange_ResetsPreviousToNewFirstPosition)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                Assert::AreEqual(rng[0], menuNav.GetPrevCurrCursorPosForTesting());

                rng[0] = 3;
                rng[1] = 4;
                rng[2] = 5;

                menuNav.SetCursorRange(rng);

                Assert::AreEqual(rng[0], menuNav.GetPrevCurrCursorPosForTesting());
            }

            // ======================================================
            // SetCurrCursorPos
            // ======================================================

            TEST_METHOD(MenuNav_SetCurrCursorPos_WithEmptyRange_DoesNothing)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                Assert::AreEqual(MenuNav::s_InvalidPos, menuNav.GetCurrCursorPos());
            }

            TEST_METHOD(MenuNav_SetCurrCursorPos_WhenWithinRange_UpdatesCurrentPosition)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                Assert::AreEqual(rng[0], menuNav.GetPrevCurrCursorPosForTesting());
            }

            TEST_METHOD(MenuNav_SetCurrCursorPos_WhenBelowRange_DoesNotUpdatePosition)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());

                menuNav.SetCurrCursorPos(-1);

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());
            }

            TEST_METHOD(MenuNav_SetCurrCursorPos_WhenAboveRange_DoesNotUpdatePosition)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());

                menuNav.SetCurrCursorPos(3);

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());
            }

            TEST_METHOD(MenuNav_SetCurrCursorPos_ToLowerBoundary_UpdatesPosition)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                menuNav.SetCurrCursorPos(1);

                Assert::AreEqual(rng[1], menuNav.GetCurrCursorPos());

                menuNav.SetCurrCursorPos(0);

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());
            }

            TEST_METHOD(MenuNav_SetCurrCursorPos_ToUpperBoundary_UpdatesPosition)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());

                menuNav.SetCurrCursorPos(1);

                Assert::AreEqual(rng[1], menuNav.GetCurrCursorPos());
            }

            // ======================================================
            // Navigation Dependencies
            // ======================================================

            TEST_METHOD(MenuNav_HandleNavigation_WithoutGameManager_DoesNothing)
            {
                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());

                menuNav.HandleNavigation();

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());
            }

            TEST_METHOD(MenuNav_HandleNavigation_WithoutInputManager_DoesNothing)
            {
                GameManager gm;

                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());

                menuNav.HandleNavigation();

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());
            }

            // ======================================================
            // Navigation From Initial Position
            // ======================================================

            TEST_METHOD(MenuNav_HandleNavigation_AfterSettingRange_StartsAtFirstPosition)
            {
                GameManager gm;

                gm.SetInputManager(std::make_shared<TestableInputManager>(std::make_shared<FakeKeyConverter>()));

                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                menuNav.HandleNavigation();

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());
            }

            TEST_METHOD(MenuNav_HandleNavigation_WhenAscendingPressed_MovesFromFirstToNextPosition)
            {
                GameManager gm;

                auto inpMgr = std::make_shared<TestableInputManager>(std::make_shared<FakeKeyConverter>());

                gm.SetInputManager(inpMgr);

                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                menuNav.SetCurrCursorPos(1);

                inpMgr->SetKeyPressedForTesting(KeyCode::Left);

                menuNav.HandleNavigation();

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());
            }

            TEST_METHOD(MenuNav_HandleNavigation_WhenDescendingPressed_MovesFromFirstToNextPosition)
            {
                GameManager gm;

                auto inpMgr = std::make_shared<TestableInputManager>(std::make_shared<FakeKeyConverter>());

                gm.SetInputManager(inpMgr);

                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                inpMgr->SetKeyPressedForTesting(KeyCode::Right);

                menuNav.HandleNavigation();

                Assert::AreEqual(rng[1], menuNav.GetCurrCursorPos());
            }

            TEST_METHOD(MenuNav_HandleNavigation_WhenAscendingPressedAtFirstPosition_DoesNotMove)
            {
                GameManager gm;

                auto inpMgr = std::make_shared<TestableInputManager>(std::make_shared<FakeKeyConverter>());

                gm.SetInputManager(inpMgr);

                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                inpMgr->SetKeyPressedForTesting(KeyCode::Left);

                menuNav.HandleNavigation();

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());
            }

            TEST_METHOD(MenuNav_HandleNavigation_WhenAtLastPositionAndDescendingPressed_DoesNotMove)
            {
                GameManager gm;

                auto inpMgr = std::make_shared<TestableInputManager>(std::make_shared<FakeKeyConverter>());

                gm.SetInputManager(inpMgr);

                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                menuNav.SetCurrCursorPos(2);

                Assert::AreEqual(rng[2], menuNav.GetCurrCursorPos());

                inpMgr->SetKeyPressedForTesting(KeyCode::Right);

                menuNav.HandleNavigation();

                Assert::AreEqual(rng[2], menuNav.GetCurrCursorPos());
            }

            // ======================================================
            // Previous Position / Movement State
            // ======================================================

            TEST_METHOD(MenuNav_SetPrevCursorPos_UpdatesPreviousPosition)
            {
                GameManager gm;

                auto inpMgr = std::make_shared<TestableInputManager>(std::make_shared<FakeKeyConverter>());

                gm.SetInputManager(inpMgr);

                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());

                menuNav.SetPrevCursorPos(1);

                Assert::AreEqual(rng[1], menuNav.GetPrevCurrCursorPosForTesting());
            }

            TEST_METHOD(MenuNav_HasMoved_WhenCurrentEqualsPrevious_ReturnsFalse)
            {
                GameManager gm;

                auto inpMgr = std::make_shared<TestableInputManager>(std::make_shared<FakeKeyConverter>());

                gm.SetInputManager(inpMgr);

                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                Assert::IsFalse(menuNav.HasMoved());
            }

            TEST_METHOD(MenuNav_HasMoved_WhenCurrentDiffersFromPrevious_ReturnsTrue)
            {
                GameManager gm;

                auto inpMgr = std::make_shared<TestableInputManager>(std::make_shared<FakeKeyConverter>());

                gm.SetInputManager(inpMgr);

                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                menuNav.SetPrevCursorPos(1);

                Assert::IsTrue(menuNav.HasMoved());
            }

            // ======================================================
            // Held Key Behaviour
            // ======================================================

            TEST_METHOD(MenuNav_HandleNavigation_WhenDescendingRemainsPressed_DoesNotMoveAgain)
            {
                GameManager gm;

                auto inpMgr = std::make_shared<TestableInputManager>(std::make_shared<FakeKeyConverter>());

                gm.SetInputManager(inpMgr);

                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                inpMgr->SetKeyPressedForTesting(KeyCode::Right);

                menuNav.HandleNavigation();

                Assert::AreEqual(rng[1], menuNav.GetCurrCursorPos());

                menuNav.HandleNavigation();

                Assert::AreEqual(rng[1], menuNav.GetCurrCursorPos());
            }

            TEST_METHOD(MenuNav_HandleNavigation_WhenAscendingRemainsPressed_DoesNotMoveAgain)
            {
                GameManager gm;

                auto inpMgr = std::make_shared<TestableInputManager>(std::make_shared<FakeKeyConverter>());

                gm.SetInputManager(inpMgr);

                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                menuNav.SetCurrCursorPos(2);

                inpMgr->SetKeyPressedForTesting(KeyCode::Left);

                menuNav.HandleNavigation();

                Assert::AreEqual(rng[1], menuNav.GetCurrCursorPos());

                menuNav.HandleNavigation();

                Assert::AreEqual(rng[1], menuNav.GetCurrCursorPos());
            }

            // ======================================================
            // Key Release Behaviour
            // ======================================================

            TEST_METHOD(MenuNav_HandleNavigation_WhenAscendingReleased_AllowsNextMove)
            {
                GameManager gm;

                auto inpMgr = std::make_shared<TestableInputManager>(std::make_shared<FakeKeyConverter>());

                gm.SetInputManager(inpMgr);

                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                menuNav.SetCurrCursorPos(2);

                inpMgr->SetKeyPressedForTesting(KeyCode::Left);

                menuNav.HandleNavigation();

                Assert::AreEqual(rng[1], menuNav.GetCurrCursorPos());

                inpMgr->SetKeyReleasedForTesting(KeyCode::Left);

                menuNav.HandleNavigation();

                inpMgr->SetKeyPressedForTesting(KeyCode::Left);

                menuNav.HandleNavigation();

                Assert::AreEqual(rng[0], menuNav.GetCurrCursorPos());
            }

            TEST_METHOD(MenuNav_HandleNavigation_WhenDescendingReleased_AllowsNextMove)
            {
                GameManager gm;

                auto inpMgr = std::make_shared<TestableInputManager>(std::make_shared<FakeKeyConverter>());

                gm.SetInputManager(inpMgr);

                TestableMenuNav menuNav(KeyCode::Left, KeyCode::Right);

                std::vector<int> rng{ 0,1,2 };

                menuNav.SetCursorRange(rng);

                inpMgr->SetKeyPressedForTesting(KeyCode::Right);

                menuNav.HandleNavigation();

                Assert::AreEqual(rng[1], menuNav.GetCurrCursorPos());

                inpMgr->SetKeyReleasedForTesting(KeyCode::Right);

                menuNav.HandleNavigation();

                inpMgr->SetKeyPressedForTesting(KeyCode::Right);

                menuNav.HandleNavigation();

                Assert::AreEqual(rng[2], menuNav.GetCurrCursorPos());
            }
        };
    }
}
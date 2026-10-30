
#include "CppUnitTest.h"

#include <Fakes/Drawables/FakeSprite.h>
#include <Fakes/Renderer/FakeRenderer.h>
#include <Fakes/UI/TestableMenuCursor.h>
#include <Fakes/UI/TestableMenuNav.h>
#include <TestHelpers/TestDefaultLoggerHelper.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace UI
    {
        TEST_CLASS(MenuCursorTests)
        {
        public:
            TEST_METHOD_CLEANUP(TestCleanup)
            {
                TestHelpers::CleanupDefaultLoggerForTests();
            }

            // ======================================================
            // Constructor
            // ======================================================

            TEST_METHOD(IMenuCursor_Constructor_ThrowsIfSpriteIsNull)
            {
                MenuNav nav(KeyCode::Up, KeyCode::Down);

                Assert::ExpectException<std::invalid_argument>([&]
                    {
                        TestableMenuCursor cursor(nullptr, nav);
                    });
            }

            TEST_METHOD(IMenuCursor_Constructor_StoresSprite)
            {
                MenuNav nav(KeyCode::Up, KeyCode::Down);

                auto spr = std::make_shared<FakeSprite>("spr");

                TestableMenuCursor cursor(spr, nav);

                auto retSpr = cursor.GetSprite();

                Assert::IsTrue(spr.get() == retSpr);
            }

            TEST_METHOD(IMenuCursor_Constructor_StoresMenuNavigation)
            {
                TestableMenuNav nav(KeyCode::Up, KeyCode::Down);

                TestableMenuCursor cursor(std::make_shared<FakeSprite>("spr"), nav);

                auto retNav = static_cast<TestableMenuNav&>(cursor.GetMenuNav());

                Assert::AreEqual(nav.GetCurrCursorPos(), retNav.GetCurrCursorPos());
                Assert::AreEqual(nav.GetPrevCurrCursorPosForTesting(), retNav.GetPrevCurrCursorPosForTesting());
                Assert::AreEqual(static_cast<int>(nav.GetAscKeyForTesting()), static_cast<int>(retNav.GetAscKeyForTesting()));
                Assert::AreEqual(static_cast<int>(nav.GetDesKeyForTesting()), static_cast<int>(retNav.GetDesKeyForTesting()));
                Assert::AreEqual(nav.GetCanAscForTesting(), retNav.GetCanAscForTesting());
                Assert::AreEqual(nav.GetCanDesForTesting(), retNav.GetCanDesForTesting());
            }

            // ======================================================
            // Update
            // ======================================================

            TEST_METHOD(IMenuCursor_Update_ForwardsUpdateToSprite)
            {
                MenuNav nav(KeyCode::Up, KeyCode::Down);

                auto spr = std::make_shared<FakeSprite>("spr");

                TestableMenuCursor cursor(spr, nav);

                cursor.Update(0.6f);

                Assert::AreEqual(1, spr->updateCount);
                Assert::AreEqual(0.6f, spr->lastDeltaTime);
            }

            // ======================================================
            // Render
            // ======================================================

            TEST_METHOD(IMenuCursor_Render_DoesNotRenderIfRendererIsNull)
            {
                MenuNav nav(KeyCode::Up, KeyCode::Down);

                auto spr = std::make_shared<FakeSprite>("spr");

                TestableMenuCursor cursor(spr, nav);

                cursor.Render(nullptr);

                Assert::AreEqual(0, spr->renderCount);
            }

            TEST_METHOD(IMenuCursor_Render_ForwardsRenderToSprite)
            {
                MenuNav nav(KeyCode::Up, KeyCode::Down);

                auto spr = std::make_shared<FakeSprite>("spr");

                TestableMenuCursor cursor(spr, nav);

                FakeRenderer renderer;

                cursor.Render(&renderer);

                Assert::AreEqual(1, spr->renderCount);
                Assert::AreEqual(std::string("spr"), spr->renderId);
            }
        };
    }
}
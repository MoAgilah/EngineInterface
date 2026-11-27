
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
                MenuNav nav(KeyCode::Up, KeyCode::Down);

                nav.SetCursorRange({ 0, 1, 2 });
                nav.SetCurrCursorPos(2);
                nav.SetPrevCursorPos(1);

                TestableMenuCursor cursor(
                    std::make_shared<FakeSprite>("spr"), nav);

                const auto& retNav = cursor.GetMenuNav();

                Assert::AreEqual(nav.GetCurrCursorPos(), retNav.GetCurrCursorPos());
                Assert::AreEqual(nav.GetPrevCursorPos(), retNav.GetPrevCursorPos());
                Assert::AreEqual(nav.HasMoved(), retNav.HasMoved());
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
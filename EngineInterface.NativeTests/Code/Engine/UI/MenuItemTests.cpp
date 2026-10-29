#include "CppUnitTest.h"

#include <Engine/UI/MenuItem.h>
#include <Fakes/Drawables/FakeShape.h>
#include <Fakes/Drawables/FakeSprite.h>
#include <Fakes/Drawables/FakeText.h>
#include <Fakes/Renderer/FakeRenderer.h>
#include <TestHelpers/TestDefaultLoggerHelper.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace UI
    {
        TEST_CLASS(MenuItemTests)
        {
        public:
            // ======================================================
            // Constructor
            // ======================================================

            TEST_METHOD(MenuItem_Constructor_ThrowsIfCellSpaceIsInvalid)
            {
                Assert::ExpectException<std::invalid_argument>([&]
                    {
                        MenuItem mi(nullptr);
                    });
            }

            TEST_METHOD(MenuItem_Constructor_DoesNotThrowIfCellSpaceIsValid)
            {
                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );
            }

            // ======================================================
            // Geometry
            // ======================================================

            TEST_METHOD(MenuItem_GetPosition_ReturnsCellSpacePosition)
            {
                auto size = Vector2f(16.f, 16.f);
                auto pos = Vector2f(32.f, 32.f);

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        size,
                        pos
                    )
                );

                auto retPos = mi.GetPosition();

                Assert::AreEqual(pos.x, retPos.x);
                Assert::AreEqual(pos.y, retPos.y);
            }

            TEST_METHOD(MenuItem_SetPosition_SetsCellSpacePosition)
            {
                auto size = Vector2f(16.f, 16.f);

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        size,
                        Vector2f(32.f, 32.f)
                    )
                );

                auto pos = Vector2f(64.f, 64.f);

                mi.SetPosition(pos);

                auto retPos = mi.GetPosition();

                Assert::AreEqual(pos.x, retPos.x);
                Assert::AreEqual(pos.y, retPos.y);
            }

            TEST_METHOD(MenuItem_GetOrigin_ReturnsCellSpaceOrigin)
            {
                auto size = Vector2f(16.f, 16.f);
                auto pos = Vector2f(32.f, 32.f);

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        size,
                        pos
                    )
                );

                auto retOri = mi.GetOrigin();

                Assert::AreEqual(size.x * 0.5f, retOri.x);
                Assert::AreEqual(size.y * 0.5f, retOri.y);
            }

            TEST_METHOD(MenuItem_GetSize_ReturnsCellSpaceSize)
            {
                auto size = Vector2f(16.f, 16.f);
                auto pos = Vector2f(32.f, 32.f);

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        size,
                        pos
                    )
                );

                auto retSize = mi.GetSize();

                Assert::AreEqual(size.x, retSize.x);
                Assert::AreEqual(size.y, retSize.y);
            }

            // ======================================================
            // Menu Slot Management
            // ======================================================

            TEST_METHOD(MenuItem_GetMenuSlotNumber_ReturnsNegativeOneByDefault)
            {
                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                Assert::AreEqual(-1, mi.GetMenuSlotNumber());
            }

            TEST_METHOD(MenuItem_SetMenuSlotNumber_UpdatesSlotNumber)
            {
                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                mi.SetMenuSlotNumber(0);

                Assert::AreEqual(0, mi.GetMenuSlotNumber());
            }

            // ======================================================
            // Text Element
            // ======================================================

            TEST_METHOD(MenuItem_AddTextElement_StoresAndReturnsTextElement)
            {
                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                mi.AddTextElement(text);

                auto retText = mi.GetTextElement();
                Assert::IsNotNull(retText);

                Assert::IsTrue(text.get() == retText);
            }

            TEST_METHOD(MenuItem_AddTextElement_ReturnsAddedTextElement)
            {
                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                auto retText = mi.AddTextElement(text);
                Assert::IsNotNull(retText);

                Assert::IsTrue(text.get() == retText);
            }

            TEST_METHOD(MenuItem_AddTextElement_AcceptsNullptr)
            {
                auto text1 = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt1");

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                mi.AddTextElement(text1);

                auto retText = mi.AddTextElement(nullptr);
                Assert::IsNull(retText);
                Assert::IsNull(mi.GetTextElement());
            }

            TEST_METHOD(MenuItem_AddTextElement_ReplacesExistingTextElement)
            {
                auto text1 = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt1");

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                mi.AddTextElement(text1);

                auto text2= std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt2");

                mi.AddTextElement(text2);

                auto retText = mi.GetTextElement();
                Assert::IsNotNull(retText);

                Assert::IsTrue(text2.get() == retText);
            }

            TEST_METHOD(MenuItem_GetTextElement_ReturnsNullIfUnset)
            {
                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                Assert::IsNull(mi.GetTextElement());
            }

            // ======================================================
            // Sprite Element
            // ======================================================

            TEST_METHOD(MenuItem_AddSpriteElement_StoresAndReturnsSpriteElement)
            {
                auto spr = std::make_shared<FakeSprite>("Spr");

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                mi.AddSpriteElement(spr);

                auto retSpr = mi.GetSpriteElement();
                Assert::IsNotNull(retSpr);

                Assert::IsTrue(spr.get() == retSpr);
            }

            TEST_METHOD(MenuItem_AddSpriteElement_ReturnsAddedSpriteElement)
            {
                auto spr = std::make_shared<FakeSprite>("Spr");

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                auto retSpr = mi.AddSpriteElement(spr);
                Assert::IsNotNull(retSpr);

                Assert::IsTrue(spr.get() == retSpr);
            }

            TEST_METHOD(MenuItem_AddSpriteElement_AcceptsNullptr)
            {
                auto spr = std::make_shared<FakeSprite>("Spr");

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                mi.AddSpriteElement(spr);

                auto retSpr = mi.AddSpriteElement(nullptr);
                Assert::IsNull(retSpr);
                Assert::IsNull(mi.GetSpriteElement());
            }

            TEST_METHOD(MenuItem_AddSpriteElement_ReplacesExistingSpriteElement)
            {
                auto spr1 = std::make_shared<FakeSprite>("Spr1");

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                mi.AddSpriteElement(spr1);

                auto spr2 = std::make_shared<FakeSprite>("Spr2");

                mi.AddSpriteElement(spr2);

                auto retSpr = mi.GetSpriteElement();
                Assert::IsNotNull(retSpr);

                Assert::IsTrue(spr2.get() == retSpr);
            }

            TEST_METHOD(MenuItem_GetSpriteElement_ReturnsNullIfUnset)
            {
                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                Assert::IsNull(mi.GetSpriteElement());
            }

            // ======================================================
            // Update
            // ======================================================

            TEST_METHOD(MenuItem_Update_DoesNotThrowIfElementsUnset)
            {
                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                mi.Update(0.6f);
            }

            TEST_METHOD(MenuItem_Update_UpdatesSpriteElement)
            {
                auto spr = std::make_shared<FakeSprite>("Spr");

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                mi.AddSpriteElement(spr);

                mi.Update(0.6f);

                Assert::AreEqual(1, spr->updateCount);
                Assert::AreEqual(0.6f, spr->lastDeltaTime);
            }

            TEST_METHOD(MenuItem_Update_UpdatesTextElement)
            {
                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                mi.AddTextElement(text);

                mi.Update(0.6f);

                Assert::AreEqual(1, text->updateCount);
                Assert::AreEqual(0.6f, text->lastDeltaTime);
            }

            TEST_METHOD(MenuItem_Update_UpdatesSpriteAndTextElements)
            {
                auto spr = std::make_shared<FakeSprite>("Spr");
                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                mi.AddSpriteElement(spr);
                mi.AddTextElement(text);

                mi.Update(0.6f);

                Assert::AreEqual(1, spr->updateCount);
                Assert::AreEqual(0.6f, spr->lastDeltaTime);
                Assert::AreEqual(1, text->updateCount);
                Assert::AreEqual(0.6f, text->lastDeltaTime);
            }

            // ======================================================
            // Render
            // ======================================================

            TEST_METHOD(MenuItem_Render_DoesNotRenderIfRendererIsNull)
            {
                auto spr = std::make_shared<FakeSprite>("Spr");
                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                mi.AddSpriteElement(spr);
                mi.AddTextElement(text);

                mi.Render(nullptr);

                Assert::AreEqual(0, spr->renderCount);
                Assert::AreEqual(0, text->renderCount);
            }

            TEST_METHOD(MenuItem_Render_DoesNotThrowIfElementsUnset)
            {
                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                FakeRenderer fr;

                mi.Render(&fr);
            }

            TEST_METHOD(MenuItem_Render_RendersTextElement)
            {
                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                mi.AddTextElement(text);

                FakeRenderer fr;

                mi.Render(&fr);

                Assert::AreEqual(1, text->renderCount);
            }

            TEST_METHOD(MenuItem_Render_RendersSpriteElement)
            {
                auto spr = std::make_shared<FakeSprite>("Spr");

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                mi.AddSpriteElement(spr);

                FakeRenderer fr;

                mi.Render(&fr);

                Assert::AreEqual(1, spr->renderCount);
            }

            TEST_METHOD(MenuItem_Render_RendersTextAndSpriteElements)
            {
                auto spr = std::make_shared<FakeSprite>("Spr");
                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                MenuItem mi(
                    std::make_shared<FakeBox>(
                        Vector2f(),
                        Vector2f()
                    )
                );

                mi.AddSpriteElement(spr);
                mi.AddTextElement(text);

                FakeRenderer fr;

                mi.Render(&fr);

                Assert::AreEqual(1, spr->renderCount);
                Assert::AreEqual(1, text->renderCount);
            }

#if defined _DEBUG
            TEST_METHOD(MenuItem_Render_RendersCellSpaceInDebug)
            {
                auto box = std::make_shared<FakeBox>(
                    Vector2f(),
                    Vector2f()
                );

                MenuItem mi(box);

                FakeRenderer fr;

                mi.Render(&fr);

                Assert::AreEqual(1, box->renderCount);
            }
#endif
        };
    }
}
#include "CppUnitTest.h"

#include <Engine/UI/MenuElement.h>
#include <Fakes/Drawables/FakeShape.h>
#include <Fakes/Drawables/FakeSprite.h>
#include <Fakes/Drawables/FakeText.h>
#include <Fakes/Effects/FakeEffect.h>
#include <Fakes/Renderer/FakeRenderer.h>
#include <Fakes/UI/TestableMenu.h>
#include <TestHelpers/TestDefaultLoggerHelper.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace UI
    {
        TEST_CLASS(MenuElementTests)
        {
        public:

            // ======================================================
            // Construction
            // ======================================================

            TEST_METHOD(MenuElement_Constructor_ThrowsIfDrawableIsNull)
            {
                NavigationStyles styles;

                Assert::ExpectException<std::invalid_argument>([&]
                    {
                        MenuElement<IText> element(nullptr, styles);
                    });
            }

            TEST_METHOD(MenuElement_GetDrawable_ReturnsDrawable)
            {
                NavigationStyles styles;

                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                auto expTxt = text.get();
                Assert::IsNotNull(expTxt);

                MenuElement<IText> element(std::move(text), styles);

                auto actTxt = element.GetDrawable();
                Assert::IsNotNull(actTxt);

                Assert::IsTrue(expTxt == actTxt);
            }

            TEST_METHOD(MenuElement_Constructor_AppliesDefaultStyle)
            {
                NavigationStyles styles;
                styles.defaultStyle.colour = Colour::Yellow;
                styles.defaultStyle.effectID = "Flashing";

                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                auto effect = std::make_unique<FakeEffect>();

                auto expEffect = effect.get();
                Assert::IsNotNull(expEffect);

                text->AddEffect(*styles.defaultStyle.effectID, std::move(effect));

                MenuElement<IText> element(std::move(text), styles);

                IText* rawTxt = element.GetDrawable();
                Assert::IsNotNull(rawTxt);

                auto expColour = *styles.defaultStyle.colour;
                auto actColour = rawTxt->GetFillColour();

                Assert::AreEqual(expColour.r, actColour.r);
                Assert::AreEqual(expColour.g, actColour.g);
                Assert::AreEqual(expColour.b, actColour.b);
                Assert::AreEqual(expColour.a, actColour.a);

                auto actEffect = rawTxt->GetActiveEffect();
                Assert::IsNotNull(actEffect);

                Assert::IsTrue(expEffect == actEffect);
            }

            // ======================================================
            // Colour Management
            // ======================================================

            TEST_METHOD(MenuElement_SetSelected_True_AppliesSelectedColour)
            {
                NavigationStyles styles;
                styles.defaultStyle.colour = Colour::Yellow;
                styles.selectedStyle.colour = Colour::Green;

                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                MenuElement<IText> element(std::move(text), styles);

                element.SetSelected(true);

                IText* rawTxt = element.GetDrawable();
                Assert::IsNotNull(rawTxt);

                auto expColour = *styles.selectedStyle.colour;
                auto actColour = rawTxt->GetFillColour();

                Assert::AreEqual(expColour.r, actColour.r);
                Assert::AreEqual(expColour.g, actColour.g);
                Assert::AreEqual(expColour.b, actColour.b);
                Assert::AreEqual(expColour.a, actColour.a);
            }

            TEST_METHOD(MenuElement_SetSelected_False_RestoresDefaultStyleColour)
            {
                NavigationStyles styles;
                styles.defaultStyle.colour = Colour::Yellow;
                styles.selectedStyle.colour = Colour::Green;

                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                MenuElement<IText> element(std::move(text), styles);

                element.SetSelected(true);

                IText* rawTxt = element.GetDrawable();
                Assert::IsNotNull(rawTxt);


                auto expColour = *styles.selectedStyle.colour;
                auto actColour = rawTxt->GetFillColour();

                Assert::AreEqual(expColour.r, actColour.r);
                Assert::AreEqual(expColour.g, actColour.g);
                Assert::AreEqual(expColour.b, actColour.b);
                Assert::AreEqual(expColour.a, actColour.a);

                element.SetSelected(false);

                expColour = *styles.defaultStyle.colour;
                actColour = rawTxt->GetFillColour();

                Assert::AreEqual(expColour.r, actColour.r);
                Assert::AreEqual(expColour.g, actColour.g);
                Assert::AreEqual(expColour.b, actColour.b);
                Assert::AreEqual(expColour.a, actColour.a);
            }

            TEST_METHOD(MenuElement_SetSelected_False_RestoresDrawableDefaultColour)
            {
                NavigationStyles styles;
                styles.selectedStyle.colour = Colour::Green;

                auto expColour = Colour::Blue;

                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f(), expColour),
                    "Txt");

                MenuElement<IText> element(std::move(text), styles);

                element.SetSelected(true);

                IText* rawTxt = element.GetDrawable();
                Assert::IsNotNull(rawTxt);

                expColour = *styles.selectedStyle.colour;
                auto actColour = rawTxt->GetFillColour();

                Assert::AreEqual(expColour.r, actColour.r);
                Assert::AreEqual(expColour.g, actColour.g);
                Assert::AreEqual(expColour.b, actColour.b);
                Assert::AreEqual(expColour.a, actColour.a);

                element.SetSelected(false);

                expColour = Colour::Blue;
                actColour = rawTxt->GetFillColour();

                Assert::AreEqual(expColour.r, actColour.r);
                Assert::AreEqual(expColour.g, actColour.g);
                Assert::AreEqual(expColour.b, actColour.b);
                Assert::AreEqual(expColour.a, actColour.a);
            }

            TEST_METHOD(MenuElement_Sprite_SetSelected_True_AppliesSelectedColour)
            {
                NavigationStyles styles;
                styles.selectedStyle.colour = Colour::Green;

                auto spr = std::make_shared<FakeSprite>("obj");

                MenuElement<ISprite> element(std::move(spr), styles);

                element.SetSelected(true);

                auto expColour = *styles.selectedStyle.colour;

                ISprite* rawSpr = element.GetDrawable();
                Assert::IsNotNull(rawSpr);

                auto actColour = rawSpr->GetColour();

                Assert::AreEqual(expColour.r, actColour.r);
                Assert::AreEqual(expColour.g, actColour.g);
                Assert::AreEqual(expColour.b, actColour.b);
                Assert::AreEqual(expColour.a, actColour.a);
            }

            TEST_METHOD(MenuElement_Sprite_SetSelected_False_RestoresDrawableDefaultColour)
            {
                NavigationStyles styles;
                styles.selectedStyle.colour = Colour::Green;

                auto spr = std::make_shared<FakeSprite>("obj");

                auto expColour = Colour::Blue;

                spr->SetDefaultColour(expColour);

                MenuElement<ISprite> element(std::move(spr), styles);

                element.SetSelected(true);

                ISprite* rawSpr = element.GetDrawable();
                Assert::IsNotNull(rawSpr);

                expColour = *styles.selectedStyle.colour;
                auto actColour = rawSpr->GetColour();

                Assert::AreEqual(expColour.r, actColour.r);
                Assert::AreEqual(expColour.g, actColour.g);
                Assert::AreEqual(expColour.b, actColour.b);
                Assert::AreEqual(expColour.a, actColour.a);

                element.SetSelected(false);

                expColour = Colour::Blue;
                actColour = rawSpr->GetColour();

                Assert::AreEqual(expColour.r, actColour.r);
                Assert::AreEqual(expColour.g, actColour.g);
                Assert::AreEqual(expColour.b, actColour.b);
                Assert::AreEqual(expColour.a, actColour.a);
            }

            // ======================================================
            // Effect Management
            // ======================================================

            TEST_METHOD(MenuElement_SetSelected_True_ActivatesSelectedEffect)
            {
                NavigationStyles styles;
                styles.defaultStyle.effectID = "Flashing";
                styles.selectedStyle.effectID = "Glowing";

                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                auto effect = std::make_unique<FakeEffect>();

                auto expEffect = effect.get();
                Assert::IsNotNull(expEffect);

                text->AddEffect(*styles.defaultStyle.effectID, std::make_unique<FakeEffect>());
                text->AddEffect(*styles.selectedStyle.effectID, std::move(effect));

                MenuElement<IText> element(std::move(text), styles);

                element.SetSelected(true);

                IText* rawTxt = element.GetDrawable();
                Assert::IsNotNull(rawTxt);

                auto actEffect = rawTxt->GetActiveEffect();
                Assert::IsNotNull(actEffect);

                Assert::IsTrue(expEffect == actEffect);
            }

            TEST_METHOD(MenuElement_SetSelected_False_RestoresDefaultEffect)
            {
                NavigationStyles styles;
                styles.defaultStyle.effectID = "Flashing";
                styles.selectedStyle.effectID = "Glowing";

                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                auto effect1 = std::make_unique<FakeEffect>();

                auto defEffect = effect1.get();
                Assert::IsNotNull(defEffect);

                text->AddEffect(*styles.defaultStyle.effectID, std::move(effect1));


                auto effect2 = std::make_unique<FakeEffect>();

                auto selEffect = effect2.get();
                Assert::IsNotNull(selEffect);

                text->AddEffect(*styles.selectedStyle.effectID, std::move(effect2));

                MenuElement<IText> element(std::move(text), styles);

                IText* rawTxt = element.GetDrawable();
                Assert::IsNotNull(rawTxt);

                element.SetSelected(true);

                auto actEffect = rawTxt->GetActiveEffect();
                Assert::IsNotNull(actEffect);

                Assert::IsTrue(selEffect == actEffect);

                element.SetSelected(false);

                actEffect = rawTxt->GetActiveEffect();
                Assert::IsNotNull(actEffect);

                Assert::IsTrue(defEffect == actEffect);
            }

            TEST_METHOD(MenuElement_SetSelected_False_DeactivatesPreviousEffect)
            {
                NavigationStyles styles;
                styles.selectedStyle.effectID = "Glowing";

                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                auto effect = std::make_unique<FakeEffect>();

                auto expEffect = effect.get();
                Assert::IsNotNull(expEffect);

                text->AddEffect(*styles.selectedStyle.effectID, std::move(effect));

                MenuElement<IText> element(std::move(text), styles);

                IText* rawTxt = element.GetDrawable();
                Assert::IsNotNull(rawTxt);

                element.SetSelected(true);

                auto actEffect = rawTxt->GetActiveEffect();
                Assert::IsNotNull(actEffect);

                Assert::IsTrue(expEffect == actEffect);

                element.SetSelected(false);

                actEffect = rawTxt->GetActiveEffect();
                Assert::IsNull(actEffect);
            }

            TEST_METHOD(MenuElement_SetSelected_WithSameEffect_PreservesActiveEffect)
            {
                NavigationStyles styles;
                styles.defaultStyle.effectID = "Flashing";
                styles.selectedStyle.effectID = "Flashing";

                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                auto effect = std::make_unique<FakeEffect>();

                auto expEffect = effect.get();
                Assert::IsNotNull(expEffect);

                text->AddEffect(*styles.defaultStyle.effectID, std::move(effect));

                MenuElement<IText> element(std::move(text), styles);

                element.SetSelected(true);

                IText* rawTxt = element.GetDrawable();
                Assert::IsNotNull(rawTxt);

                auto actEffect = rawTxt->GetActiveEffect();
                Assert::IsNotNull(actEffect);

                Assert::IsTrue(expEffect == actEffect);
            }

            TEST_METHOD(MenuElement_SetSelected_WithInvalidEffect_LeavesNoActiveEffect)
            {
                NavigationStyles styles;
                styles.defaultStyle.effectID = "Flashing";
                styles.selectedStyle.effectID = "Glowing";

                auto text = std::make_shared<FakeText>(TextConfig("fontName", 12, Vector2f()),
                    "Txt");

                auto effect = std::make_unique<FakeEffect>();

                auto expEffect = effect.get();
                Assert::IsNotNull(expEffect);

                text->AddEffect(*styles.defaultStyle.effectID, std::move(effect));

                MenuElement<IText> element(std::move(text), styles);

                IText* rawTxt = element.GetDrawable();
                Assert::IsNotNull(rawTxt);

                auto actEffect = rawTxt->GetActiveEffect();
                Assert::IsNotNull(actEffect);

                element.SetSelected(true);

                actEffect = rawTxt->GetActiveEffect();
                Assert::IsNull(actEffect);
            }
        };
    }
}
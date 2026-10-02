#include "CppUnitTest.h"

#include <Engine/Interface/Effects/IFlashingEffect.h>
#include <Fakes/Resources/FakeShader.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Effects
    {
        TEST_CLASS(IFlashingEffectTests)
        {
        public:
            TEST_METHOD(IFlashingEffect_Constructor_ThrowsIfFlashDurationIsZero)
            {
                FakeShader shader;

                Assert::ExpectException<std::runtime_error>(
                    [&]()
                    {
                        IFlashingEffect shaderEffect(&shader, 0.f);
                    });
            }

            TEST_METHOD(IFlashingEffect_Constructor_ThrowsIfFlashDurationIsNegative)
            {
                FakeShader shader;

                Assert::ExpectException<std::runtime_error>(
                    [&]()
                    {
                        IFlashingEffect shaderEffect(&shader, -1.f);
                    });
            }

            TEST_METHOD(IFlashingEffect_Update_ReducesAlphaOverTime)
            {
                FakeShader shader;

                IFlashingEffect shaderEffect(&shader, 1.f);

                shaderEffect.Update(0.25f);
                Assert::AreEqual(0.75f, shader.storedValue);

                shaderEffect.Update(0.25f);
                Assert::AreEqual(0.50f, shader.storedValue);

                shaderEffect.Update(0.25f);
                Assert::AreEqual(0.25f, shader.storedValue);
            }

            TEST_METHOD(IFlashingEffect_Update_SwitchesToIncreasingAlphaWhenFadeOutCompletes)
            {
                FakeShader shader;

                IFlashingEffect shaderEffect(&shader, 1.f);

                shaderEffect.Update(1.f);
                Assert::AreEqual(0.0f, shader.storedValue);

                shaderEffect.Update(0.25f);
                Assert::AreEqual(0.25f, shader.storedValue);
            }

            TEST_METHOD(IFlashingEffect_Update_IncreasesAlphaOverTime)
            {
                FakeShader shader;

                IFlashingEffect shaderEffect(&shader, 1.f);

                shaderEffect.Update(1.f);
                Assert::AreEqual(0.0f, shader.storedValue);

                shaderEffect.Update(0.25f);
                Assert::AreEqual(0.25f, shader.storedValue);

                shaderEffect.Update(0.25f);
                Assert::AreEqual(0.50f, shader.storedValue);

                shaderEffect.Update(0.25f);
                Assert::AreEqual(0.75f, shader.storedValue);
            }

            TEST_METHOD(IFlashingEffect_Update_RestartsFadeWhenLooping)
            {
                FakeShader shader;

                IFlashingEffect shaderEffect(&shader, 1.f);

                shaderEffect.Update(1.f);
                Assert::AreEqual(0.0f, shader.storedValue);

                shaderEffect.Update(0.25f);
                Assert::AreEqual(0.25f, shader.storedValue);

                shaderEffect.Update(0.75f);
                Assert::AreEqual(1.0f, shader.storedValue);

                shaderEffect.Update(0.25f);
                Assert::AreEqual(0.75f, shader.storedValue);
            }

            TEST_METHOD(IFlashingEffect_Update_StopsWhenNotLooping)
            {
                FakeShader shader;

                IFlashingEffect shaderEffect(&shader, 1.f, false);

                shaderEffect.Update(1.f);
                Assert::AreEqual(0.0f, shader.storedValue);

                shaderEffect.Update(0.25f);
                Assert::AreEqual(0.0f, shader.storedValue);
            }

            TEST_METHOD(IFlashingEffect_Update_DoesNotProgressWhenPaused)
            {
                FakeShader shader;

                IFlashingEffect shaderEffect(&shader, 1.f);

                shaderEffect.Update(0.25f);
                Assert::AreEqual(0.75f, shader.storedValue);

                shaderEffect.SetIsPaused(true);

                shaderEffect.Update(0.25f);
                Assert::AreEqual(0.75f, shader.storedValue);
            }
        };
    }
}
#include "CppUnitTest.h"

#include <Fakes/Effects/FakeEffect.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Effects
    {
        TEST_CLASS(IEffectTests)
        {
        public:
            TEST_METHOD(IEffect_DefaultState_IsActive)
            {
                FakeEffect effect;

                Assert::IsTrue(effect.IsActive());
            }

            TEST_METHOD(IEffect_SetActiveFalse_DeactivatesEffect)
            {
                FakeEffect effect;

                effect.SetActive(false);

                Assert::IsFalse(effect.IsActive());
            }

            TEST_METHOD(IEffect_SetActiveTrue_ActivatesEffect)
            {
                FakeEffect effect;

                effect.SetActive(false);

                Assert::IsFalse(effect.IsActive());

                effect.SetActive(true);

                Assert::IsTrue(effect.IsActive());
            }

            TEST_METHOD(IEffect_SetActive_CallsDerivedOverride)
            {
                FakeEffect effect;

                effect.SetActive(false);

                Assert::IsTrue(effect.overrideCalled);
            }
        };
    }
}
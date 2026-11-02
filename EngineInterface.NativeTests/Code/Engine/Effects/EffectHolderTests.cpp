#include "CppUnitTest.h"

#include <Engine/Effects/EffectHolder.h>
#include <Fakes/Effects/FakeEffect.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Effects
    {
        TEST_CLASS(EffectHolderTests)
        {
        public:
            TEST_METHOD(EffectHolder_AddEffect_ReturnsFalseIfEffectIsNull)
            {
                EffectHolder holder;

                Assert::IsFalse(holder.AddEffect("Null", nullptr));
            }

            TEST_METHOD(EffectHolder_AddEffect_StoresEffect)
            {
                EffectHolder holder;

                Assert::IsTrue(holder.AddEffect("Effect", std::make_unique<FakeEffect>()));
            }

            TEST_METHOD(EffectHolder_AddEffect_ReturnsFalseIfDuplicateNamesDetected)
            {
                EffectHolder holder;

                holder.AddEffect("Effect", std::make_unique<FakeEffect>());

                Assert::IsFalse(holder.AddEffect("Effect", std::make_unique<FakeEffect>()));
            }

            TEST_METHOD(EffectHolder_GetEffect_ReturnsNullIfEmpty)
            {
                EffectHolder holder;

                Assert::IsNull(holder.GetEffect("Effect"));
            }

            TEST_METHOD(EffectHolder_GetEffect_ReturnsNullIfNotFound)
            {
                EffectHolder holder;

                holder.AddEffect("Effect", std::make_unique<FakeEffect>());

                Assert::IsNull(holder.GetEffect("Null"));
            }

            TEST_METHOD(EffectHolder_GetEffect_ReturnsEffect)
            {
                EffectHolder holder;

                holder.AddEffect("Effect", std::make_unique<FakeEffect>());

                auto effect = holder.GetEffect("Effect");

                Assert::IsNotNull(effect);
            }

            TEST_METHOD(EffectHolder_GetEffect_Const_ReturnsEffect)
            {
                EffectHolder holder;

                holder.AddEffect("Effect", std::make_unique<FakeEffect>());

                auto const effect = holder.GetEffect("Effect");

                Assert::IsNotNull(effect);
            }

            TEST_METHOD(EffectHolder_SetEffectActive_ReturnsFalseIfNotFound)
            {
                EffectHolder holder;

                holder.AddEffect("Effect", std::make_unique<FakeEffect>());

                Assert::IsFalse(holder.SetEffectActive("Null", true));
            }

            TEST_METHOD(EffectHolder_SetEffectActive_ActivatesEffect)
            {
                EffectHolder holder;

                holder.AddEffect("Effect", std::make_unique<FakeEffect>());

                Assert::IsTrue(holder.SetEffectActive("Effect", true));

                auto effect = holder.GetEffect("Effect");

                Assert::IsNotNull(effect);
                Assert::IsTrue(effect->IsActive());
            }

            TEST_METHOD(EffectHolder_SetEffectActive_DeactivatesEffect)
            {
                EffectHolder holder;

                holder.AddEffect("Effect", std::make_unique<FakeEffect>());

                Assert::IsTrue(holder.SetEffectActive("Effect", false));

                auto effect = holder.GetEffect("Effect");

                Assert::IsNotNull(effect);
                Assert::IsFalse(effect->IsActive());
            }
        };
    }
}
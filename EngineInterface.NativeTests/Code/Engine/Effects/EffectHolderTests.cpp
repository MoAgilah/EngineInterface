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
            // ======================================================
            // AddEffect
            // ======================================================

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

            // ======================================================
            // GetActiveEffect
            // ======================================================

            TEST_METHOD(EffectHolder_GetActiveEffect_ReturnsNullIfEmpty)
            {
                EffectHolder holder;

                Assert::IsNull(holder.GetActiveEffect());
            }

            TEST_METHOD(EffectHolder_GetActiveEffect_ReturnsNullIfNoneActive)
            {
                EffectHolder holder;

                holder.AddEffect("Effect", std::make_unique<FakeEffect>());

                Assert::IsNull(holder.GetActiveEffect());
            }

            TEST_METHOD(EffectHolder_GetActiveEffect_Const_ReturnsActiveEffect)
            {
                EffectHolder holder;

                holder.AddEffect("Effect", std::make_unique<FakeEffect>());
                Assert::IsTrue(holder.SetEffectActive("Effect", true));

                const EffectHolder& constHolder = holder;

                const auto* effect = constHolder.GetActiveEffect();

                Assert::IsNotNull(effect);
                Assert::IsTrue(effect->IsActive());
            }

            // ======================================================
            // SetEffectActive
            // ======================================================

            TEST_METHOD(EffectHolder_SetEffectActive_ReturnsFalseIfEmpty)
            {
                EffectHolder holder;

                Assert::IsFalse(holder.SetEffectActive("Effect", true));
            }

            TEST_METHOD(EffectHolder_SetEffectActive_ReturnsFalseIfNotFound)
            {
                EffectHolder holder;

                holder.AddEffect("Effect", std::make_unique<FakeEffect>());

                Assert::IsFalse(holder.SetEffectActive("Other", true));
            }

            TEST_METHOD(EffectHolder_SetEffectActive_ActivatesEffect)
            {
                EffectHolder holder;

                holder.AddEffect("Effect", std::make_unique<FakeEffect>());

                Assert::IsTrue(holder.SetEffectActive("Effect", true));

                const auto effect = holder.GetActiveEffect();
                Assert::IsNotNull(effect);
            }

            TEST_METHOD(EffectHolder_SetEffectActive_DeactivatesEffect)
            {
                EffectHolder holder;

                holder.AddEffect("Effect", std::make_unique<FakeEffect>());

                Assert::IsTrue(holder.SetEffectActive("Effect", true));

                auto effect = holder.GetActiveEffect();
                Assert::IsNotNull(effect);

                Assert::IsTrue(holder.SetEffectActive("Effect", false));

                Assert::IsFalse(effect->IsActive());
            }

            TEST_METHOD(EffectHolder_SetEffectActive_DeactivatesOtherEffects)
            {
                EffectHolder holder;

                holder.AddEffect("Effect", std::make_unique<FakeEffect>());
                holder.AddEffect("Other", std::make_unique<FakeEffect>());

                Assert::IsTrue(holder.SetEffectActive("Effect", true));

                auto effect = holder.GetActiveEffect();
                Assert::IsNotNull(effect);

                Assert::IsTrue(holder.SetEffectActive("Other", true));

                auto other = holder.GetActiveEffect();
                Assert::IsNotNull(other);

                Assert::IsTrue(effect != other);

                Assert::IsFalse(effect->IsActive());
                Assert::IsTrue(other->IsActive());
            }

            TEST_METHOD(EffectHolder_SetEffectActive_FalsePreservesOtherEffects)
            {
                EffectHolder holder;

                holder.AddEffect("Effect", std::make_unique<FakeEffect>());
                holder.AddEffect("Other", std::make_unique<FakeEffect>());

                Assert::IsTrue(holder.SetEffectActive("Effect", true));

                auto effect = holder.GetActiveEffect();
                Assert::IsNotNull(effect);

                Assert::IsTrue(holder.SetEffectActive("Other", false));

                Assert::IsTrue(effect->IsActive());
            }
        };
    }
}
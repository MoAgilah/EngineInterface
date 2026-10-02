#include "CppUnitTest.h"

#include <Engine/Core/Constants.h>
#include <Fakes/Drawables/TestableAnimatedSprite.h>
#include <string_view>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Drawables
    {
        TEST_CLASS(IAnimatedSpriteTests)
        {
        public:
            // ======================================================
            // Construction
            // ======================================================

            TEST_METHOD(IAnimatedSprite_Constructor_ThrowsIfFrameDurationIsZero)
            {
                Assert::ExpectException<std::runtime_error>([&]
                    {
                        TestableAnimatedSprite sprite(
                            1.0f,
                            0.0f
                        );
                    });
            }

            TEST_METHOD(IAnimatedSprite_Constructor_ThrowsIfFrameDurationIsNegative)
            {
                Assert::ExpectException<std::runtime_error>([&]
                    {
                        TestableAnimatedSprite sprite(
                            1.0f,
                            -1.0f
                        );
                    });
            }

            TEST_METHOD(IAnimatedSprite_Constructor_ThrowsIfAnimationSpeedIsNegative)
            {
                Assert::ExpectException<std::runtime_error>([&]
                    {
                        TestableAnimatedSprite sprite(
                            -1.0f,
                            1.0f
                        );
                    });
            }

            TEST_METHOD(IAnimatedSprite_Constructor_StoresAnimationSpeed)
            {
                float animSpd = 1.0f;

                TestableAnimatedSprite sprite(
                    animSpd,
                    GameConstants::AnimationFrameDurationMS
                );

                Assert::AreEqual(animSpd, sprite.GetCurrAnimSpeed());
            }

            // ======================================================
            // Set Frames
            // ======================================================

            TEST_METHOD(IAnimatedSprite_SetFrames_ThrowsIfFrameDataIsEmpty)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames;

                Assert::ExpectException<std::runtime_error>([&]
                    {
                        sprite.SetFrames(numFrames);
                    });
            }

            TEST_METHOD(IAnimatedSprite_SetFrames_ThrowsIfFrameCountIsZero)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 1, 2, 0, 3 };

                Assert::ExpectException<std::runtime_error>([&]
                    {
                        sprite.SetFrames(numFrames);
                    });
            }

            TEST_METHOD(IAnimatedSprite_SetFrames_ThrowsIfFrameCountIsNegative)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 1, 2, -1, 3 };

                Assert::ExpectException<std::runtime_error>([&]
                    {
                        sprite.SetFrames(numFrames);
                    });
            }

            TEST_METHOD(IAnimatedSprite_SetFrames_SetsInitialAnimation)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                Assert::AreEqual(0, sprite.GetCurrentAnim());
            }

            TEST_METHOD(IAnimatedSprite_SetFrames_ResetsAnimationState)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                // Complete one cycle
                sprite.Update(0.25f);

                Assert::IsTrue(sprite.PlayedOnce());

                // Advance into the next cycle
                sprite.Update(0.06f);

                Assert::AreEqual(1, sprite.GetCurrentFrame());

                sprite.SetFrames(numFrames);

                Assert::AreEqual(0, sprite.GetCurrentAnim());
                Assert::AreEqual(0, sprite.GetCurrentFrame());
                Assert::IsFalse(sprite.PlayedOnce());
            }

            // ======================================================
            // Change Animation
            // ======================================================

            TEST_METHOD(IAnimatedSprite_ChangeAnim_ThrowsIfAnimationIndexIsNegative)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                Assert::ExpectException<std::runtime_error>([&]
                    {
                        sprite.ChangeAnim(-1);
                    });
            }

            TEST_METHOD(IAnimatedSprite_ChangeAnim_ThrowsIfAnimationIndexExceedsAvailableAnimations)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                Assert::ExpectException<std::runtime_error>([&]
                    {
                        sprite.ChangeAnim(4);
                    });
            }

            TEST_METHOD(IAnimatedSprite_ChangeAnim_ChangesCurrentAnimation)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                int newAnim = 2;

                sprite.ChangeAnim(newAnim);

                Assert::AreEqual(newAnim, sprite.GetCurrentAnim());
            }

            TEST_METHOD(IAnimatedSprite_ChangeAnim_ResetsCurrentFrame)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                sprite.Update(0.06f);

                auto before = sprite.GetCurrentFrame();

                sprite.ChangeAnim(1);

                auto after = sprite.GetCurrentFrame();

                Assert::AreNotEqual(before, after);
                Assert::AreEqual(0, after);
            }

            TEST_METHOD(IAnimatedSprite_ChangeAnim_ResetsAnimationCycle)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                sprite.Update(0.25f);

                Assert::IsTrue(sprite.PlayedOnce());

                sprite.ChangeAnim(1);

                Assert::IsFalse(sprite.PlayedOnce());
            }

            // ======================================================
            // Ensure Animation
            // ======================================================

            TEST_METHOD(IAnimatedSprite_EnsureAnim_ChangesAnimationWhenDifferent)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                auto before = sprite.GetCurrentAnim();

                sprite.EnsureAnim(1);

                auto after = sprite.GetCurrentAnim();

                Assert::AreNotEqual(before, after);
                Assert::AreEqual(1, after);
            }

            TEST_METHOD(IAnimatedSprite_EnsureAnim_DoesNotRestartCurrentAnimation)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                sprite.Update(0.06f);

                auto before = sprite.GetCurrentFrame();

                sprite.EnsureAnim(0);

                auto after = sprite.GetCurrentFrame();

                Assert::AreEqual(before, after);
                Assert::AreNotEqual(0, after);
            }

            // ======================================================
            // Animation Speed
            // ======================================================

            TEST_METHOD(IAnimatedSprite_UpdateAnimSpeed_ThrowsIfAnimationSpeedIsNegative)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                Assert::ExpectException<std::runtime_error>([&]
                    {
                        sprite.UpdateAnimSpeed(-1);
                    });
            }

            TEST_METHOD(IAnimatedSprite_UpdateAnimSpeed_ChangesAnimationSpeed)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                float newSpd = 0.5f;

                sprite.UpdateAnimSpeed(newSpd);

                Assert::AreEqual(newSpd, sprite.GetCurrAnimSpeed());
            }

            // ======================================================
            // Update
            // ======================================================

            TEST_METHOD(IAnimatedSprite_Update_ThrowsIfFramesHaveNotBeenConfigured)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                Assert::ExpectException<std::runtime_error>([&]
                    {
                        sprite.Update(0.67f);
                    });
            }

            TEST_METHOD(IAnimatedSprite_Update_DoesNotAdvanceFrameBeforeFrameDuration)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                auto before = sprite.GetCurrentFrame();

                sprite.Update(0.03f);

                auto after = sprite.GetCurrentFrame();

                Assert::AreEqual(before, after);
                Assert::AreEqual(0, after);
            }

            TEST_METHOD(IAnimatedSprite_Update_AdvancesFrameWhenFrameDurationReached)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                auto before = sprite.GetCurrentFrame();

                sprite.Update(0.06f);

                auto after = sprite.GetCurrentFrame();

                Assert::AreNotEqual(before, after);
                Assert::AreEqual(1, after);
            }

            TEST_METHOD(IAnimatedSprite_Update_AdvancesMultipleFramesWhenElapsedTimeAllows)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                auto before = sprite.GetCurrentFrame();

                sprite.Update(0.18f);

                auto after = sprite.GetCurrentFrame();

                Assert::AreNotEqual(before, after);
                Assert::AreEqual(3, after);
            }

            TEST_METHOD(IAnimatedSprite_Update_PreservesRemainingFrameTime)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                auto before = sprite.GetCurrentFrame();

                sprite.Update(0.09f);

                auto after = sprite.GetCurrentFrame();

                Assert::AreNotEqual(before, after);
                Assert::AreEqual(1, after);

                before = after;

                sprite.Update(0.03f);

                after = sprite.GetCurrentFrame();

                Assert::AreNotEqual(before, after);
                Assert::AreEqual(2, after);
            }

            TEST_METHOD(IAnimatedSprite_UpdateAfterChangeAnim_UsesSelectedAnimation)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                sprite.ChangeAnim(1);

                Assert::AreEqual(1, sprite.GetCurrentAnim());

                auto before = sprite.GetCurrentFrame();

                sprite.Update(0.06f);

                auto after = sprite.GetCurrentFrame();

                Assert::AreNotEqual(before, after);
                Assert::AreEqual(1, after);

                before = after;

                sprite.Update(0.06f);

                after = sprite.GetCurrentFrame();

                Assert::AreNotEqual(before, after);
                Assert::AreEqual(0, after);
            }

            // ======================================================
            // Looping
            // ======================================================

            TEST_METHOD(IAnimatedSprite_UpdateWithLooping_WrapsToFirstFrame)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                auto before = sprite.GetCurrentFrame();

                sprite.Update(0.25f);

                auto after = sprite.GetCurrentFrame();

                Assert::AreEqual(before, after);
                Assert::AreEqual(0, after);
            }

            TEST_METHOD(IAnimatedSprite_UpdateWithLooping_IncrementsAnimationCycle)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                Assert::IsTrue(sprite.PlayedNumTimes(0));

                sprite.Update(0.25f);

                Assert::IsTrue(sprite.PlayedNumTimes(1));
            }

            // ======================================================
            // Non-Looping
            // ======================================================

            TEST_METHOD(IAnimatedSprite_UpdateWithoutLooping_StopsOnLastFrame)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                sprite.SetShouldLoop(false);

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                auto before = sprite.GetCurrentFrame();

                sprite.Update(0.25f);

                auto after = sprite.GetCurrentFrame();

                Assert::AreNotEqual(before, after);
                Assert::AreEqual(3, after);
            }

            TEST_METHOD(IAnimatedSprite_UpdateWithoutLooping_SetsPlayedOnceAfterCompletion)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                sprite.SetShouldLoop(false);

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                Assert::IsFalse(sprite.PlayedOnce());

                sprite.Update(0.25f);

                Assert::IsTrue(sprite.PlayedOnce());
            }

            TEST_METHOD(IAnimatedSprite_UpdateWithoutLooping_DoesNotAdvanceAfterCompletion)
            {
                TestableAnimatedSprite sprite(
                    1.0f,
                    GameConstants::AnimationFrameDurationMS
                );

                sprite.SetShouldLoop(false);

                std::vector<int> numFrames = { 4, 2, 3, 1 };

                sprite.SetFrames(numFrames);

                sprite.Update(0.25f);

                Assert::IsTrue(sprite.PlayedOnce());

                auto before = sprite.GetCurrentFrame();

                sprite.Update(0.06f);

                auto after = sprite.GetCurrentFrame();

                Assert::AreEqual(before, after);
                Assert::AreEqual(3, after);
            }
        };
    }
}
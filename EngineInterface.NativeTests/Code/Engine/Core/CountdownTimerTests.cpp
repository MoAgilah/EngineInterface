#include "CppUnitTest.h"

#include <Engine/Core/CountdownTimer.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Core
    {
        TEST_CLASS(CountdownTimerTests)
        {
        public:

            // ======================================================
            // Max Time
            // ======================================================

            TEST_METHOD(Constructor_ShouldSetMaxTimeBeforeCountdown)
            {
                CountdownTimer timer(3.0f);

                auto maxTime = timer.GetMaxTime();

                Assert::AreEqual(3.0f, maxTime);
            }

            TEST_METHOD(Constructor_WhenMaxTimeIsZero_TimerStartsAtZero)
            {
                CountdownTimer timer(0.0f);

                auto currTime = timer.GetCurrTime();

                Assert::AreEqual(0.0f, currTime);
            }

            TEST_METHOD(Constructor_WhenMaxTimeIsZero_CheckEndReturnsTrue)
            {
                CountdownTimer timer(0.0f);

                auto res = timer.CheckEnd();

                Assert::IsTrue(res);
            }

            // ======================================================
            // Vector Maths
            // ======================================================

            TEST_METHOD(Constructor_WhenMaxTimeIsNegative_ClampsMaxTimeToZero)
            {
                CountdownTimer timer(-1.0f);

                auto maxTime = timer.GetMaxTime();

                Assert::AreEqual(0.0f, maxTime);
            }

            // ======================================================
            // Max Time
            // ======================================================

            TEST_METHOD(Constructor_WhenMaxTimeIsNegative_StartsAtZero)
            {
                CountdownTimer timer(-1.0f);

                auto currTime = timer.GetMaxTime();

                Assert::AreEqual(0.0f, currTime);
            }

            // ======================================================
            // Timer Updates
            // ======================================================

            TEST_METHOD(Update_SingleStep_DecreasesTimeCorrectly)
            {
                CountdownTimer timer(3.0f);

                timer.Update(1.0f);

                Assert::AreEqual(2.0f, timer.GetCurrTime(), 0.001f);
            }

            TEST_METHOD(Update_MultipleStep_DecreasesTimeCorrectly)
            {
                CountdownTimer timer(3.0f);

                for (int i = 0; i < 300; i++)
                    timer.Update(0.01f);

                Assert::IsTrue(timer.GetCurrTime() <= 0.001f);
            }

            // ======================================================
            // Vector Maths
            // ======================================================

            TEST_METHOD(Update_WhenDeltaTimeExceedsRemainingTime_ClampsToZero)
            {
                CountdownTimer timer(3.0f);

                timer.SetCurrTime(0.01f);
                timer.Update(0.02f);

                Assert::IsTrue(timer.CheckEnd());
                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
            }

            // ======================================================
            // Current Time
            // ======================================================

            TEST_METHOD(Update_WhenTimerAlreadyEnded_DoesNotChangeCurrTime)
            {
                CountdownTimer timer(3.0f);

                timer.SetCurrTime(0.0f);

                Assert::IsTrue(timer.CheckEnd());

                timer.Update(0.01f);

                Assert::IsTrue(timer.CheckEnd());
                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
            }

            // ======================================================
            // Pause / Resume
            // ======================================================

            TEST_METHOD(Update_WhenTimerIsPaused_DoesNothing)
            {
                CountdownTimer timer(3.0f);

                timer.Pause();

                auto currTime = timer.GetCurrTime();

                Assert::IsFalse(timer.CheckEnd());

                timer.Update(0.1f);

                Assert::AreEqual(currTime, timer.GetCurrTime(), 0.001f);
            }

            TEST_METHOD(Update_WhenTimerIsResumed_DecreasesCurrTime)
            {
                CountdownTimer timer(3.0f);

                timer.Pause();

                Assert::IsFalse(timer.CheckEnd());

                timer.Update(0.1f);
                Assert::AreEqual(3.0f, timer.GetCurrTime(), 0.001f);

                timer.Resume();

                timer.Update(1.0f);

                Assert::AreEqual(2.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            // ======================================================
            // Current Time
            // ======================================================

            TEST_METHOD(Update_WhenDeltaTimeIsZero_DoesNotChangeCurrTime)
            {
                CountdownTimer timer(3.0f);

                auto currTime = timer.GetCurrTime();

                Assert::IsFalse(timer.CheckEnd());

                timer.Update(0.0f);

                Assert::AreEqual(currTime, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            TEST_METHOD(Update_WhenDeltaTimeIsNegative_DoesNotIncreaseCurrTime)
            {
                CountdownTimer timer(3.0f);

                auto currTime = timer.GetCurrTime();

                Assert::IsFalse(timer.CheckEnd());

                timer.Update(-0.01f);

                Assert::AreEqual(currTime, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            // ======================================================
            // Update
            // ======================================================

            TEST_METHOD(GetCurrTime_UpdateChangesCurrTime)
            {
                CountdownTimer timer(3.0f);

                auto currTime = timer.GetCurrTime();

                timer.Update(1.0f);

                Assert::AreNotEqual(currTime, timer.GetCurrTime(), 0.001f);
                Assert::AreEqual(2.0f, timer.GetCurrTime(), 0.001f);
            }

            // ======================================================
            // Change State
            // ======================================================

            TEST_METHOD(SetCurrTime_ChangesValueOfCurrTime)
            {
                CountdownTimer timer(3.0f);

                Assert::IsFalse(timer.CheckEnd());

                timer.SetCurrTime(2.0f);

                Assert::AreEqual(2.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            // ======================================================
            // Vector Maths
            // ======================================================

            TEST_METHOD(SetCurrTime_WhenSetAboveMax_ClampsToMaxTime)
            {
                CountdownTimer timer(3.0f);

                Assert::IsFalse(timer.CheckEnd());

                timer.SetCurrTime(4.0f);

                Assert::AreEqual(3.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            TEST_METHOD(SetCurrTime_WhenSetBelowZero_ClampsToZero)
            {
                CountdownTimer timer(3.0f);

                timer.SetCurrTime(-1.0f);

                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsTrue(timer.CheckEnd());
            }

            // ======================================================
            // Behaviour
            // ======================================================

            TEST_METHOD(SetCurrTime_WhenSetToZero_CheckEndReturnsTrue)
            {
                CountdownTimer timer(3.0f);

                Assert::IsFalse(timer.CheckEnd());

                timer.SetCurrTime(0.0f);

                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsTrue(timer.CheckEnd());
            }

            // ======================================================
            // Max Time
            // ======================================================

            TEST_METHOD(SetCurrTime_WhenSetToMaxTime_SetsToMaxTime)
            {
                CountdownTimer timer(3.0f);

                Assert::IsFalse(timer.CheckEnd());

                auto max = timer.GetMaxTime();

                timer.SetCurrTime(max);

                Assert::AreEqual(max, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            // ======================================================
            // Finished State
            // ======================================================

            TEST_METHOD(CheckEnd_ReturnsFalseBeforeTimerIsFinished)
            {
                CountdownTimer timer(3.0f);

                Assert::IsFalse(timer.CheckEnd());
            }

            TEST_METHOD(CheckEnd_ReturnsTrueWhenTimerIsFinished)
            {
                CountdownTimer timer(3.0f);

                timer.SetCurrTime(0.0f);

                Assert::IsTrue(timer.CheckEnd());
            }

            // ======================================================
            // Max Time
            // ======================================================

            TEST_METHOD(RestartTimer_RestartsTimeToThatOfMaxTime)
            {
                CountdownTimer timer(3.0f);

                auto max = timer.GetMaxTime();

                timer.SetCurrTime(1.0f);

                Assert::IsFalse(timer.CheckEnd());

                timer.RestartTimer();

                Assert::AreEqual(max, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            // ======================================================
            // Pause / Resume
            // ======================================================

            TEST_METHOD(RestartTimer_AfterPause_ResetsCurrTimeToMaxTime)
            {
                CountdownTimer timer(3.0f);

                auto max = timer.GetMaxTime();

                timer.SetCurrTime(2.0f);

                Assert::AreEqual(2.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());

                timer.Pause();

                Assert::IsFalse(timer.CheckEnd());

                timer.RestartTimer();


                Assert::AreEqual(max, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            TEST_METHOD(RestartTimer_AfterPause_ResumesTimer)
            {
                CountdownTimer timer(3.0f);

                timer.Pause();
                timer.Update(1.0f);

                Assert::AreEqual(3.0f, timer.GetCurrTime(), 0.001f);

                timer.RestartTimer();
                timer.Update(1.0f);

                Assert::AreEqual(2.0f, timer.GetCurrTime(), 0.001f);
            }

            // ======================================================
            // Change State
            // ======================================================

            TEST_METHOD(SetMaxTime_ChangesTheMaxTime)
            {
                CountdownTimer timer(3.0f);

                timer.SetMaxTime(4.0f);

                Assert::AreEqual(4.0f, timer.GetMaxTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            // ======================================================
            // Max Time
            // ======================================================

            TEST_METHOD(GetMaxTime_ReturnsCurrMaxTime)
            {
                CountdownTimer timer(3.0f);

                Assert::AreEqual(3.0f, timer.GetMaxTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            // ======================================================
            // Current Time
            // ======================================================

            TEST_METHOD(SetMaxTime_WhenSetHigherThanCurrTime_DoesNotChangeCurrTime)
            {
                CountdownTimer timer(3.0f);

                timer.SetCurrTime(2.0f);

                timer.SetMaxTime(4.0f);

                Assert::AreEqual(2.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            // ======================================================
            // Vector Maths
            // ======================================================

            TEST_METHOD(SetMaxTime_WhenSetLowerThanCurrTime_ClampsCurrTimeToNewMax)
            {
                CountdownTimer timer(4.0f);

                timer.SetCurrTime(3.0f);
                timer.SetMaxTime(2.0f);

                Assert::AreEqual(2.0f, timer.GetMaxTime(), 0.001f);
                Assert::AreEqual(2.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            // ======================================================
            // Current Time
            // ======================================================

            TEST_METHOD(SetMaxTime_WhenSetToZero_SetsCurrTimeToZero)
            {
                CountdownTimer timer(3.0f);

                timer.SetMaxTime(0.0f);

                Assert::AreEqual(0.0f, timer.GetMaxTime(), 0.001f);
                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsTrue(timer.CheckEnd());
            }

            // ======================================================
            // Vector Maths
            // ======================================================

            TEST_METHOD(SetMaxTime_WhenSetNegative_ClampsMaxTimeAndCurrTimeToZero)
            {
                CountdownTimer timer(3.0f);

                timer.SetMaxTime(-1.0f);

                Assert::AreEqual(0.0f, timer.GetMaxTime(), 0.001f);
                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsTrue(timer.CheckEnd());
            }

            // ======================================================
            // s Curr Time To Zero Access
            // ======================================================

            TEST_METHOD(ForceEnd_SetsCurrTimeToZero_AndTimerIsEnded)
            {
                CountdownTimer timer(3.0f);

                timer.ForceEnd();

                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsTrue(timer.CheckEnd());
            }

            // ======================================================
            // Update
            // ======================================================

            TEST_METHOD(ForceEnd_UpdateDoesNotMakeCurrTimeNegative)
            {
                CountdownTimer timer(3.0f);

                timer.ForceEnd();

                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsTrue(timer.CheckEnd());

                timer.Update(1.0f);

                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsTrue(timer.CheckEnd());
            }
        };
    }
}
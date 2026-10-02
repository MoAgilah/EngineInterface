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
            // Construction
            // ======================================================

            TEST_METHOD(CountdownTimer_Constructor_ShouldSetMaxTimeBeforeCountdown)
            {
                CountdownTimer timer(3.0f);

                auto maxTime = timer.GetMaxTime();

                Assert::AreEqual(3.0f, maxTime);
            }

            TEST_METHOD(CountdownTimer_Constructor_WhenMaxTimeIsZero_TimerStartsAtZero)
            {
                CountdownTimer timer(0.0f);

                auto currTime = timer.GetCurrTime();

                Assert::AreEqual(0.0f, currTime);
            }

            TEST_METHOD(CountdownTimer_Constructor_WhenMaxTimeIsZero_CheckEndReturnsTrue)
            {
                CountdownTimer timer(0.0f);

                auto res = timer.CheckEnd();

                Assert::IsTrue(res);
            }

            TEST_METHOD(CountdownTimer_Constructor_WhenMaxTimeIsNegative_ClampsMaxTimeToZero)
            {
                CountdownTimer timer(-1.0f);

                auto maxTime = timer.GetMaxTime();

                Assert::AreEqual(0.0f, maxTime);
            }

            TEST_METHOD(Constructor_WhenMaxTimeIsNegative_StartsAtZero)
            {
                CountdownTimer timer(-1.0f);

                auto currTime = timer.GetMaxTime();

                Assert::AreEqual(0.0f, currTime);
            }


            // ======================================================
            // Timer Updates
            // ======================================================

            TEST_METHOD(CountdownTimer_Update_SingleStep_DecreasesTimeCorrectly)
            {
                CountdownTimer timer(3.0f);

                timer.Update(1.0f);

                Assert::AreEqual(2.0f, timer.GetCurrTime(), 0.001f);
            }

            TEST_METHOD(CountdownTimer_Update_MultipleStep_DecreasesTimeCorrectly)
            {
                CountdownTimer timer(3.0f);

                for (int i = 0; i < 300; i++)
                    timer.Update(0.01f);

                Assert::IsTrue(timer.GetCurrTime() <= 0.001f);
            }

            TEST_METHOD(CountdownTimer_Update_WhenDeltaTimeExceedsRemainingTime_ClampsToZero)
            {
                CountdownTimer timer(3.0f);

                timer.SetCurrTime(0.01f);
                timer.Update(0.02f);

                Assert::IsTrue(timer.CheckEnd());
                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
            }

            TEST_METHOD(CountdownTimer_Update_WhenTimerAlreadyEnded_DoesNotChangeCurrTime)
            {
                CountdownTimer timer(3.0f);

                timer.SetCurrTime(0.0f);

                Assert::IsTrue(timer.CheckEnd());

                timer.Update(0.01f);

                Assert::IsTrue(timer.CheckEnd());
                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
            }

            TEST_METHOD(CountdownTimer_Update_WhenDeltaTimeIsZero_DoesNotChangeCurrTime)
            {
                CountdownTimer timer(3.0f);

                auto currTime = timer.GetCurrTime();

                Assert::IsFalse(timer.CheckEnd());

                timer.Update(0.0f);

                Assert::AreEqual(currTime, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            TEST_METHOD(CountdownTimer_Update_WhenDeltaTimeIsNegative_DoesNotIncreaseCurrTime)
            {
                CountdownTimer timer(3.0f);

                auto currTime = timer.GetCurrTime();

                Assert::IsFalse(timer.CheckEnd());

                timer.Update(-0.01f);

                Assert::AreEqual(currTime, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            TEST_METHOD(CountdownTimer_GetCurrTime_UpdateChangesCurrTime)
            {
                CountdownTimer timer(3.0f);

                auto currTime = timer.GetCurrTime();

                timer.Update(1.0f);

                Assert::AreNotEqual(currTime, timer.GetCurrTime(), 0.001f);
                Assert::AreEqual(2.0f, timer.GetCurrTime(), 0.001f);
            }


            // ======================================================
            // Pause / Resume
            // ======================================================

            TEST_METHOD(CountdownTimer_Update_WhenTimerIsPaused_DoesNothing)
            {
                CountdownTimer timer(3.0f);

                timer.Pause();

                auto currTime = timer.GetCurrTime();

                Assert::IsFalse(timer.CheckEnd());

                timer.Update(0.1f);

                Assert::AreEqual(currTime, timer.GetCurrTime(), 0.001f);
            }

            TEST_METHOD(CountdownTimer_Update_WhenTimerIsResumed_DecreasesCurrTime)
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

            TEST_METHOD(CountdownTimer_SetCurrTime_ChangesValueOfCurrTime)
            {
                CountdownTimer timer(3.0f);

                Assert::IsFalse(timer.CheckEnd());

                timer.SetCurrTime(2.0f);

                Assert::AreEqual(2.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            TEST_METHOD(CountdownTimer_SetCurrTime_WhenSetAboveMax_ClampsToMaxTime)
            {
                CountdownTimer timer(3.0f);

                Assert::IsFalse(timer.CheckEnd());

                timer.SetCurrTime(4.0f);

                Assert::AreEqual(3.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            TEST_METHOD(CountdownTimer_SetCurrTime_WhenSetBelowZero_ClampsToZero)
            {
                CountdownTimer timer(3.0f);

                timer.SetCurrTime(-1.0f);

                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsTrue(timer.CheckEnd());
            }

            TEST_METHOD(CountdownTimer_SetCurrTime_WhenSetToZero_CheckEndReturnsTrue)
            {
                CountdownTimer timer(3.0f);

                Assert::IsFalse(timer.CheckEnd());

                timer.SetCurrTime(0.0f);

                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsTrue(timer.CheckEnd());
            }

            TEST_METHOD(CountdownTimer_SetCurrTime_WhenSetToMaxTime_SetsToMaxTime)
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

            TEST_METHOD(CountdownTimer_CheckEnd_ReturnsFalseBeforeTimerIsFinished)
            {
                CountdownTimer timer(3.0f);

                Assert::IsFalse(timer.CheckEnd());
            }

            TEST_METHOD(CountdownTimer_CheckEnd_ReturnsTrueWhenTimerIsFinished)
            {
                CountdownTimer timer(3.0f);

                timer.SetCurrTime(0.0f);

                Assert::IsTrue(timer.CheckEnd());
            }


            // ======================================================
            // Restart
            // ======================================================

            TEST_METHOD(CountdownTimer_RestartTimer_RestartsTimeToThatOfMaxTime)
            {
                CountdownTimer timer(3.0f);

                auto max = timer.GetMaxTime();

                timer.SetCurrTime(1.0f);

                Assert::IsFalse(timer.CheckEnd());

                timer.RestartTimer();

                Assert::AreEqual(max, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            TEST_METHOD(CountdownTimer_RestartTimer_AfterPause_ResetsCurrTimeToMaxTime)
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

            TEST_METHOD(CountdownTimer_RestartTimer_AfterPause_ResumesTimer)
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
            // Max Time
            // ======================================================

            TEST_METHOD(CountdownTimer_SetMaxTime_ChangesTheMaxTime)
            {
                CountdownTimer timer(3.0f);

                timer.SetMaxTime(4.0f);

                Assert::AreEqual(4.0f, timer.GetMaxTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            TEST_METHOD(CountdownTimer_GetMaxTime_ReturnsCurrMaxTime)
            {
                CountdownTimer timer(3.0f);

                Assert::AreEqual(3.0f, timer.GetMaxTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            TEST_METHOD(CountdownTimer_SetMaxTime_WhenSetHigherThanCurrTime_DoesNotChangeCurrTime)
            {
                CountdownTimer timer(3.0f);

                timer.SetCurrTime(2.0f);

                timer.SetMaxTime(4.0f);

                Assert::AreEqual(2.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            TEST_METHOD(CountdownTimer_SetMaxTime_WhenSetLowerThanCurrTime_ClampsCurrTimeToNewMax)
            {
                CountdownTimer timer(4.0f);

                timer.SetCurrTime(3.0f);
                timer.SetMaxTime(2.0f);

                Assert::AreEqual(2.0f, timer.GetMaxTime(), 0.001f);
                Assert::AreEqual(2.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsFalse(timer.CheckEnd());
            }

            TEST_METHOD(CountdownTimer_SetMaxTime_WhenSetToZero_SetsCurrTimeToZero)
            {
                CountdownTimer timer(3.0f);

                timer.SetMaxTime(0.0f);

                Assert::AreEqual(0.0f, timer.GetMaxTime(), 0.001f);
                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsTrue(timer.CheckEnd());
            }

            TEST_METHOD(CountdownTimer_SetMaxTime_WhenSetNegative_ClampsMaxTimeAndCurrTimeToZero)
            {
                CountdownTimer timer(3.0f);

                timer.SetMaxTime(-1.0f);

                Assert::AreEqual(0.0f, timer.GetMaxTime(), 0.001f);
                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsTrue(timer.CheckEnd());
            }


            // ======================================================
            // Force End
            // ======================================================

            TEST_METHOD(CountdownTimer_ForceEnd_SetsCurrTimeToZero_AndTimerIsEnded)
            {
                CountdownTimer timer(3.0f);

                timer.ForceEnd();

                Assert::AreEqual(0.0f, timer.GetCurrTime(), 0.001f);
                Assert::IsTrue(timer.CheckEnd());
            }

            TEST_METHOD(CountdownTimer_ForceEnd_UpdateDoesNotMakeCurrTimeNegative)
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
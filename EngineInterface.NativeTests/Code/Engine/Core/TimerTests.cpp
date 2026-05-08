#include "CppUnitTest.h"

#include <Engine/Core/Timer.h>
#include <thread>
#include <chrono>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Core
    {
        TEST_CLASS(TimerTests)
        {
        public:

            // ======================================================
            // Timer Updates
            // ======================================================

            TEST_METHOD(Reset_ShouldStartTimerInUsableState)
            {
                Timer timer;
                timer.Reset();

                double elapsed = timer.TimeElapsed();

                Assert::IsTrue(elapsed >= 0.0 && elapsed <= 0.1);
            }

            TEST_METHOD(Reset_ShouldRestartElapsedTime)
            {
                Timer timer;
                timer.Reset();

                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                double beforeReset = timer.TimeElapsed();

                timer.Reset();
                double afterReset = timer.TimeElapsed();

                Assert::IsTrue(beforeReset > 0.0);
                Assert::IsTrue(afterReset >= 0.0 && afterReset <= 0.05);
            }

            // ======================================================
            // Behaviour
            // ======================================================

            TEST_METHOD(TimeElapsed_ShouldIncreaseOverTime)
            {
                Timer timer;
                timer.Reset();

                double first = timer.TimeElapsed();
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                double second = timer.TimeElapsed();

                Assert::IsTrue(second > first);
            }

            // ======================================================
            // Timer Updates
            // ======================================================

            TEST_METHOD(Tick_ShouldReturnPositiveDeltaAfterDelay)
            {
                Timer timer;
                timer.Reset();

                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                double delta = timer.Tick();

                Assert::IsTrue(delta > 0.0);
                Assert::IsTrue(delta >= 0.0 && delta <= 0.2);
            }

            TEST_METHOD(ConsecutiveTick_ShouldMeasureSeparateIntervals)
            {
                Timer timer;
                timer.Reset();

                std::this_thread::sleep_for(std::chrono::milliseconds(15));
                double firstDelta = timer.Tick();

                std::this_thread::sleep_for(std::chrono::milliseconds(30));
                double secondDelta = timer.Tick();

                Assert::IsTrue(firstDelta > 0.0);
                Assert::IsTrue(secondDelta > 0.0);
                Assert::IsTrue(secondDelta > firstDelta);
            }

            TEST_METHOD(Tick_ShouldUpdatePreviousReferenceWithoutResettingElapsedTime)
            {
                Timer timer;
                timer.Reset();

                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                timer.Tick();

                std::this_thread::sleep_for(std::chrono::milliseconds(15));
                double secondTick = timer.Tick();
                double elapsed = timer.TimeElapsed();

                Assert::IsTrue(secondTick > 0.0);
                Assert::IsTrue(elapsed >= secondTick);
            }

            TEST_METHOD(Reset_AfterTick_ShouldRestartElapsedAndTickBaselines)
            {
                Timer timer;
                timer.Reset();

                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                timer.Tick();

                timer.Reset();

                std::this_thread::sleep_for(std::chrono::milliseconds(15));
                double deltaAfterReset = timer.Tick();
                double elapsedAfterReset = timer.TimeElapsed();

                Assert::IsTrue(deltaAfterReset > 0.0);
                Assert::IsTrue(elapsedAfterReset > 0.0);
                Assert::IsTrue(deltaAfterReset <= 0.2);
                Assert::IsTrue(elapsedAfterReset <= 0.2);
            }
        };
    }
}
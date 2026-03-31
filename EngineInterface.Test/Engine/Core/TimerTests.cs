using System.Threading;
using EngineInterface.Managed.Engine.Core;
using Xunit;

namespace EngineInterface.Tests.Engine.Core
{
    public class TimerTests
    {
        [Fact]
        public void Constructor_ShouldStartTimerInUsableState()
        {
            var timer = new TimerWrapper();

            var elapsed = timer.TimeElapsed();

            Assert.InRange(elapsed, 0.0, 0.1);
        }

        [Fact]
        public void Reset_ShouldRestartElapsedTime()
        {
            var timer = new TimerWrapper();

            Thread.Sleep(20);
            var beforeReset = timer.TimeElapsed();

            timer.Reset();
            var afterReset = timer.TimeElapsed();

            Assert.True(beforeReset > 0.0);
            Assert.InRange(afterReset, 0.0, 0.05);
        }

        [Fact]
        public void TimeElapsed_ShouldIncreaseOverTime()
        {
            var timer = new TimerWrapper();

            var first = timer.TimeElapsed();
            Thread.Sleep(20);
            var second = timer.TimeElapsed();

            Assert.True(second > first);
        }

        [Fact]
        public void Tick_ShouldReturnPositiveDeltaAfterDelay()
        {
            var timer = new TimerWrapper();

            Thread.Sleep(20);
            var delta = timer.Tick();

            Assert.True(delta > 0.0);
            Assert.InRange(delta, 0.0, 0.2);
        }

        [Fact]
        public void ConsecutiveTick_ShouldMeasureSeparateIntervals()
        {
            var timer = new TimerWrapper();

            Thread.Sleep(15);
            var firstDelta = timer.Tick();

            Thread.Sleep(30);
            var secondDelta = timer.Tick();

            Assert.True(firstDelta > 0.0);
            Assert.True(secondDelta > 0.0);
            Assert.True(secondDelta > firstDelta);
        }

        [Fact]
        public void Tick_ShouldUpdatePreviousReferenceWithoutResettingElapsedTime()
        {
            var timer = new TimerWrapper();

            Thread.Sleep(20);
            timer.Tick();

            Thread.Sleep(15);
            var secondTick = timer.Tick();
            var elapsed = timer.TimeElapsed();

            Assert.True(secondTick > 0.0);
            Assert.True(elapsed >= secondTick);
        }

        [Fact]
        public void Reset_AfterTick_ShouldRestartElapsedAndTickBaselines()
        {
            var timer = new TimerWrapper();

            Thread.Sleep(20);
            timer.Tick();

            timer.Reset();

            Thread.Sleep(15);
            var deltaAfterReset = timer.Tick();
            var elapsedAfterReset = timer.TimeElapsed();

            Assert.True(deltaAfterReset > 0.0);
            Assert.True(elapsedAfterReset > 0.0);
            Assert.InRange(deltaAfterReset, 0.0, 0.2);
            Assert.InRange(elapsedAfterReset, 0.0, 0.2);
        }
    }
}
using System.Threading;
using EngineInterface.Managed.Engine.Core;
using Xunit;

namespace EngineInterface.Tests.Engine.Core
{
    public class CountdownTimerTests
    {
        [Fact]
        public void Constructor_ShouldSetMaxTimeBeforeCountDown()
        {
            var timer = new CountdownTimerWrapper(5.0f);

            var maxTime = timer.GetMaxTime();

            Assert.Equal(5.0f, maxTime);
        }

        [Fact]
        public void Constructor_WhenMaxTimeIsZero_TimerStartsAtZero()
        {
            var timer = new CountdownTimerWrapper(0.0f);

            var maxTime = timer.GetMaxTime();

            Assert.Equal(0.0f, maxTime);
        }

        [Fact]
        public void Constructor_WhenMaxTimeIsZero_CheckEndReturnsTrue()
        {
            var timer = new CountdownTimerWrapper(0.0f);

            var res = timer.CheckEnd();

            Assert.True(res);
        }

        [Fact]
        public void Constructor_WhenMaxTimeIsNegative_ClampsMaxTimeToZero()
        {
            var timer = new CountdownTimerWrapper(-1.0f);

            var maxTime = timer.GetMaxTime();

            Assert.Equal(0.0f, maxTime);
        }

        [Fact]
        public void Constructor_WhenMaxTimeIsNegative_StartsAtZero()
        {
            var timer = new CountdownTimerWrapper(-1.0f);

            var currTime = timer.GetCurrTime();

            Assert.Equal(0.0f, currTime);
        }

        [Fact]
        public void Update_SingleStep_DecreasesTimeCorrectly()
        {
            var timer = new CountdownTimerWrapper(3.0f);

            timer.Update(1.0f);

            Assert.Equal(2.0f, timer.GetCurrTime(), 0.001f);
        }

        [Fact]
        public void Update_MultipleStep_DecreasesTimeCorrectly()
        {
            var timer = new CountdownTimerWrapper(3.0f);

            for (int i = 0; i < 300; i++)
            {
                timer.Update(0.01f);
            }

            Assert.True(timer.GetCurrTime() <= 0.001f);
        }

        [Fact]
        public void Update_WhenDeltaTimeExceedsRemainingTime_ClampsToZero()
        {
            var timer = new CountdownTimerWrapper(3.0f);

            timer.SetCurrTime(0.01f);
            timer.Update(0.02f);

            Assert.True(timer.CheckEnd());
            Assert.Equal(0.0f, timer.GetCurrTime(), 0.001f);
        }

        [Fact]
        public void Update_WhenTimerAlreadyEnded_DoesNotChangeCurrTime()
        {
            var timer = new CountdownTimerWrapper(3.0f);

            timer.SetCurrTime(0.0f);

            Assert.True(timer.CheckEnd());

            timer.Update(0.01f);

            Assert.True(timer.CheckEnd());
            Assert.Equal(0.0f, timer.GetCurrTime(), 0.001f);
        }

        [Fact]
        public void Update_WhenTimerIsPaused_DoesNothing()
        {
            var timer = new CountdownTimerWrapper(3.0f);

            timer.Pause();

            var currTime = timer.GetCurrTime();

            Assert.False(timer.CheckEnd());

            timer.Update(0.1f);

            Assert.Equal(currTime, timer.GetCurrTime(), 0.001f);
        }

        [Fact]
        public void Update_WhenTimerIsResumed_DecreasesCurrTime()
        {
            var timer = new CountdownTimerWrapper(3.0f);

            timer.Pause();

            Assert.False(timer.CheckEnd());

            timer.Update(0.1f);
            Assert.Equal(3.0f, timer.GetCurrTime(), 0.001f);

            timer.Resume();

            timer.Update(1.0f);

            Assert.Equal(2.0f, timer.GetCurrTime(), 0.001f);
            Assert.False(timer.CheckEnd());
        }

        [Fact]
        public void Update_WhenDeltaTimeIsZero_DoesNotChangeCurrTime()
        {
            var timer = new CountdownTimerWrapper(3.0f);

            var currTime = timer.GetCurrTime();

            Assert.False(timer.CheckEnd());

            timer.Update(0.0f);

            Assert.Equal(currTime, timer.GetCurrTime(), 0.001f);
            Assert.False(timer.CheckEnd());
        }

        [Fact]
        public void Update_WhenDeltaTimeIsNegative_DoesNotIncreaseCurrTime()
        {
            var timer = new CountdownTimerWrapper(3.0f);

            var currTime = timer.GetCurrTime();

            Assert.False(timer.CheckEnd());

            timer.Update(-0.01f);

            Assert.Equal(currTime, timer.GetCurrTime(), 0.001f);
            Assert.False(timer.CheckEnd());
        }

        [Fact]
        public void GetCurrTime_UpdateChangesCurrTime()
        {
            var timer = new CountdownTimerWrapper(3.0f);

            var currTime = timer.GetCurrTime();

            timer.Update(1.0f);

            Assert.NotEqual(currTime, timer.GetCurrTime(), 0.001f);
            Assert.Equal(2.0f, timer.GetCurrTime(), 0.001f);
        }

        [Fact]
        public void SetCurrTime_ChangesValueOfCurrTime()
        {
            var timer = new CountdownTimerWrapper(3.0f);

            Assert.False(timer.CheckEnd());

            timer.SetCurrTime(2.0f);

            Assert.Equal(2.0f, timer.GetCurrTime(), 0.001f);
            Assert.False(timer.CheckEnd());
        }

        [Fact]
        public void SetCurrTime_WhenSetAboveMax_ClampsToMaxTime()
        {
            var timer = new CountdownTimerWrapper(3.0f);

            Assert.False(timer.CheckEnd());

            timer.SetCurrTime(4.0f);

            Assert.Equal(3.0f, timer.GetCurrTime(), 0.001f);
            Assert.False(timer.CheckEnd());
        }

        [Fact]
        public void SetCurrTime_WhenSetBelowZero_ClampsToZero()
        {
            var timer = new CountdownTimerWrapper(3.0f);

            timer.SetCurrTime(-1.0f);

            Assert.Equal(0.0f, timer.GetCurrTime(), 0.001f);
            Assert.True(timer.CheckEnd());
        }

        [Fact]
        public void SetCurrTime_WhenSetToZero_CheckEndReturnsTrue()
        {
            var timer = new CountdownTimerWrapper(3.0f);

            Assert.False(timer.CheckEnd());

            timer.SetCurrTime(0.0f);

            Assert.Equal(0.0f, timer.GetCurrTime(), 0.001f);
            Assert.True(timer.CheckEnd());
        }

        [Fact]
        public void SetCurrTime_WhenSetToMaxTime_SetsToMaxTime()
        {
            var timer = new CountdownTimerWrapper(3.0f);

            Assert.False(timer.CheckEnd());

            var max = timer.GetMaxTime();

            timer.SetCurrTime(max);

            Assert.Equal(max, timer.GetCurrTime(), 0.001f);
            Assert.False(timer.CheckEnd());
        }
    }
};
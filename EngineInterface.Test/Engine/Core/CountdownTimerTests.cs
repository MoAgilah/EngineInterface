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
    }
};
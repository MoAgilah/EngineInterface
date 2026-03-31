using Xunit;
using EngineInterface.Managed.Interop;

namespace EngineInterface.Tests.Interop
{
    public class InteropSmokeTests
    {
        [Fact]
        public void Add_ShouldReturnCorrectSum()
        {
            var result = InteropSmokeTest.Add(2, 3);

            Assert.Equal(5, result);
        }
    }
}
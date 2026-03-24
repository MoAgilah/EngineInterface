using Xunit;
using EngineInterfaceManaged;

namespace EngineInterface.Tests.Smoke
{
    public class SmokeTests
    {
        [Fact]
        public void Add_ShouldReturnCorrectSum()
        {
            var result = ManagedSmokeTest.Add(2, 3);

            Assert.Equal(5, result);
        }
    }
}
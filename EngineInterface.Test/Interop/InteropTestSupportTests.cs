using Xunit;
using EngineInterface.TestSupport.Interop;

namespace EngineInterface.Test.Interop
{
    public class InteropTestSupportTests
    {
        [Fact]
        public void IsInteropWorking_ShouldBeTrue()
        {
            Assert.True(InteropTestSupport.IsInteropWorking());
        }
    }
}
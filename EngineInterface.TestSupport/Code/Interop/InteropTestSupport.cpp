#include "InteropTestSupport.h"


namespace EngineInterface
{
    namespace TestSupport
    {
        namespace Interop
        {
            int InteropTestSupport::Add(int a, int b)
            {
                return EngineInterface::Managed::Interop::InteropSmokeTest::Add(a, b);
            }

            bool InteropTestSupport::IsInteropWorking()
            {
                return EngineInterface::Managed::Interop::InteropSmokeTest::Add(2, 3) == 5;
            }
        }
    }
}
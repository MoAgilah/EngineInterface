#pragma once

using namespace System;

namespace EngineInterface
{
    namespace TestSupport
    {
        namespace Interop
        {
            public ref class InteropTestSupport abstract sealed
            {
            public:
                static int Add(int a, int b);
                static bool IsInteropWorking();
            };
        }
    }
}
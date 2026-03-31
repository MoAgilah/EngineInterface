#pragma once

#pragma managed(push, off)
#include <Engine/Core/Timer.h>
#pragma managed(pop)

namespace EngineInterface
{
    namespace Managed
    {
        namespace Engine
        {
            namespace Core
            {
                public ref class TimerWrapper
                {
                private:
                    Timer* m_timer;

                public:
                    TimerWrapper();
                    ~TimerWrapper();
                    !TimerWrapper();

                    void Reset();
                    double Tick();
                    double TimeElapsed();
                };
            }
        }
    }
}
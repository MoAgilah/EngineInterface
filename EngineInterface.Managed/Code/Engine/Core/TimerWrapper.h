#pragma once

#include <Engine/Core/Timer.h>

namespace EngineInterfaceManaged
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
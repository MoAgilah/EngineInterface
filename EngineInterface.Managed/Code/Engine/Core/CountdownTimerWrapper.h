#pragma once

#pragma managed(push, off)
#include <Engine/Core/CountdownTimer.h>
#pragma managed(pop)

namespace EngineInterface
{
    namespace Managed
    {
        namespace Engine
        {
            namespace Core
            {
                public ref class CountdownTimerWrapper
                {
                private:
                    CountdownTimer* m_countdownTimer;

                public:
                    CountdownTimerWrapper(float maxTime);
                    ~CountdownTimerWrapper();
                    !CountdownTimerWrapper();

                    void Update(float deltaTime);

                    float GetCurrTime();
                    void SetCurrTime(float time);

                    bool CheckEnd();
                    void ForceEnd();

                    void Pause();
                    void Resume();

                    void RestartTimer();

                    void SetMaxTime(float maxTime);
                    float GetMaxTime();
                };
            }
        }
    }
}
#include "TimerWrapper.h"

namespace EngineInterface
{
    namespace Managed
    {
        namespace Engine
        {
            namespace Core
            {
                TimerWrapper::TimerWrapper()
                {
                    m_timer = new Timer();
                    m_timer->Reset();
                }

                TimerWrapper::~TimerWrapper()
                {
                    this->!TimerWrapper();
                }

                TimerWrapper::!TimerWrapper()
                {
                    if (m_timer != nullptr)
                    {
                        delete m_timer;
                        m_timer = nullptr;
                    }
                }

                void TimerWrapper::Reset()
                {
                    m_timer->Reset();
                }

                double TimerWrapper::Tick()
                {
                    return m_timer->Tick();
                }

                double TimerWrapper::TimeElapsed()
                {
                    return m_timer->TimeElapsed();
                }
            }
        }
    }
}
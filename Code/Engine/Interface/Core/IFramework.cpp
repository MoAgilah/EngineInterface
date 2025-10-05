#include "IFramework.h"

#include "../../Core/Constants.h"
#include "../../../Utilities/Utils.h"
#include <chrono>

int IFrameWork::Run()
{
    using clock = std::chrono::steady_clock;
    using duration = std::chrono::duration<float>;

    const float dt = 1.f / GameConstants::FPS;
    const int subSteps = 4;
    const float subStepDt = dt / static_cast<float>(subSteps);

    float accumulator = 0.0f;
    auto previousTime = clock::now();

    while (m_isRunning)
    {
        PollEvents();

        auto currentTime = clock::now();
        float frameTime = std::chrono::duration_cast<duration>(currentTime - previousTime).count();
        previousTime = currentTime;

        if (frameTime > 0.25f)
            frameTime = 0.25f;

        accumulator += frameTime;

        while (accumulator >= dt)
        {
            for (int i = 0; i < subSteps; ++i)
                Update(subStepDt);

            accumulator -= dt;
        }

        Render();
    }

    Shutdown();

    return 0;
}

void IFrameWork::PollEvents()
{
    GET_OR_RETURN(renderer, m_gameMgr.GetRenderer());
    renderer->PollWindowEvents();

    GET_OR_RETURN(window, renderer->GetWindow());
    if (window->ShouldClose())
        m_isRunning = false;
}

void IFrameWork::Update(float dt)
{
    m_gameMgr.Update(dt);
}

void IFrameWork::Render()
{
    GET_OR_RETURN(renderer, m_gameMgr.GetRenderer());

    renderer->Clear();

    m_gameMgr.Render();

    renderer->Present();
}

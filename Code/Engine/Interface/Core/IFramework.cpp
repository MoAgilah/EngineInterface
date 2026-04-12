#include "IFramework.h"

#include "../../Core/Constants.h"
#include "../../Core/GameManager.h"
#include "../../../Utilities/ThreadContext.h"
#include "../../../Utilities/Utils.h"

void IFrameWork::Initialise()
{
    logger::ThreadContext::SetLabel("Main");
}

int IFrameWork::Run()
{
    const float dt = 1.f / GameConstants::FPS;
    const int subSteps = 4;
    const float subStepDt = dt / static_cast<float>(subSteps);

    float accumulator = 0.0f;

    auto& timer = m_gameMgr.GetTimer();

    timer.Reset();

    while (m_isRunning)
    {
        PollEvents();

        float frameTime = static_cast<float>(timer.Tick());

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
    DECL_GET_OR_RETURN(renderer, m_gameMgr.GetRenderer());
    renderer->PollWindowEvents();

    DECL_GET_OR_RETURN(window, renderer->GetWindow());
    if (window->ShouldClose())
        m_isRunning = false;
}

void IFrameWork::Update(float dt)
{
    m_gameMgr.Update(dt);
}

void IFrameWork::Render()
{
    DECL_GET_OR_RETURN(renderer, m_gameMgr.GetRenderer());
    DECL_GET_OR_RETURN(camera, m_gameMgr.GetCamera());

    camera->Reset(renderer);

    renderer->Clear();

    m_gameMgr.Render();

    renderer->Present();
}

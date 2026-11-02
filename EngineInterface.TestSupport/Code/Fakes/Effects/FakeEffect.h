#pragma once

#include <Engine/Interface/Effects/IEffect.h>

class FakeEffect : public IEffect
{
public:

    void SetActive(bool active) override
    {
        IEffect::SetActive(active);
        overrideCalled = true;
    }

public:

    bool overrideCalled = false;
};


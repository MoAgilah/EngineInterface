#pragma once

class IEffect
{
public:
    virtual ~IEffect() = default;

    virtual void SetActive(bool active)
    {
        m_active = active;
    }

    bool IsActive() const
    {
        return m_active;
    }

protected:

    bool m_active = false;
};


#include "EffectHolder.h"

#include "../../Utilities/Logger.h"
#include "../../Utilities/Guards.h"
#include <algorithm>

bool EffectHolder::AddEffect(const std::string& id, std::unique_ptr<IEffect> effect)
{
    if (!CheckNotNull(effect.get(), "Invalid Pointer 'effect'"))
        return false;

    auto [it, inserted] = m_effects.emplace(id, std::move(effect));

    if (!inserted)
    {
        Logger::GetDefaultLogger().Log(
            LogLevel::Debug,
            std::format("Skipped duplicate effect '{}'", id));
    }

    return inserted;
}

IEffect* EffectHolder::GetActiveEffect()
{
    auto it = std::find_if(m_effects.begin(), m_effects.end(),
        [](const auto& pair)
        {
            return pair.second->IsActive();
        });

    if (it != m_effects.end())
        return it->second.get();

    return nullptr;
}

const IEffect* EffectHolder::GetActiveEffect() const
{
    auto it = std::find_if(m_effects.begin(), m_effects.end(),
        [](const auto& pair)
        {
            return pair.second->IsActive();
        });

    if (it != m_effects.end())
        return it->second.get();

    return nullptr;
}

bool EffectHolder::SetEffectActive(const std::string& id, bool state)
{
    auto effect = GetEffect(id);
    if (!effect)
        return false;

    if (state)
    {
        for (auto& [_, other] : m_effects)
        {
            if (other.get() != effect)
                other->SetActive(false);
        }
    }

    effect->SetActive(state);

    return true;
}

IEffect* EffectHolder::GetEffect(const std::string& id)
{
    auto it = m_effects.find(id);

    if (it != m_effects.end())
        return it->second.get();

    return nullptr;
}
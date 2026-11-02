#pragma once

#include "../Interface/Effects/IEffect.h"
#include <memory>
#include <string>
#include <unordered_map>

class EffectHolder
{
public:
	EffectHolder() = default;
	~EffectHolder() = default;

	bool AddEffect(const std::string& id, std::unique_ptr<IEffect> effect);

	IEffect* GetEffect(const std::string& id);
	const IEffect* GetEffect(const std::string& id) const;

	/// Returns false if the effect was not found.
	bool SetEffectActive(const std::string& id, bool state);

private:

	std::unordered_map<std::string, std::unique_ptr<IEffect>> m_effects;
};
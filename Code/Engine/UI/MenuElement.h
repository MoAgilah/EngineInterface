#pragma once

#include "ElementStyle.h"
#include "NavigationStyles.h"
#include "../Interface/Drawables/IText.h"
#include "../Interface/Drawables/ISprite.h"
#include "../../Utilities/Colour.h"
#include "../../Utilities/Guards.h"
#include "../../Utilities/Logger.h"
#include <concepts>
#include <format>
#include <memory>
#include <stdexcept>
#include <utility>

template<typename T>
concept MenuDrawable =
std::derived_from<T, IText> ||
std::derived_from<T, ISprite>;

template<MenuDrawable T>
class MenuElement
{
public:
    MenuElement(
        std::shared_ptr<T> drawable,
        const NavigationStyles& styles
    )
        : m_drawable(std::move(drawable)), m_styles(styles)
    {

        if (!CheckNotNull(m_drawable.get(), "Invalid Pointer 'm_drawable'"))
            throw std::invalid_argument("MenuElement requires a valid drawable");

        ChangeStyle(m_styles.defaultStyle);
    }

    void SetSelected(bool isSelected)
    {
        if (isSelected)
        {
            ChangeStyle(m_styles.selectedStyle);
        }
        else
        {
            ChangeStyle(m_styles.defaultStyle);
        }
    }

    T* GetDrawable()
    {
        return m_drawable.get();
    }

private:

    void ChangeStyle(const ElementStyle& style)
    {
        ChangeColour(style.colour);
        ChangeEffect(style.effectID);
    }

    void ChangeColour(const std::optional<Colour>& colour)
    {
        if constexpr (std::derived_from<T, IText>)
        {
            m_drawable->SetFillColour(
                colour.value_or(m_drawable->GetDefaultColour())
            );
        }
        else if constexpr (std::derived_from<T, ISprite>)
        {
            m_drawable->SetColour(
                colour.value_or(m_drawable->GetDefaultColour())
            );
        }
    }

    void ChangeEffect(const std::optional<std::string>& effectID)
    {
        if (m_activeStyleEffectID == effectID)
            return;

        if (m_activeStyleEffectID)
        {
            if (!m_drawable->SetEffectActive(*m_activeStyleEffectID, false))
            {
                Logger::GetDefaultLogger().Log(
                    LogLevel::Warning,
                    std::format(
                        "The previous effect {} was not found.",
                        *m_activeStyleEffectID
                    )
                );
            }

            m_activeStyleEffectID.reset();
        }

        if (!effectID)
            return;

        if (m_drawable->SetEffectActive(*effectID, true))
        {
            m_activeStyleEffectID = effectID;
            return;
        }

        Logger::GetDefaultLogger().Log(
            LogLevel::Warning,
            std::format(
                "The effect {} was not found.",
                *effectID
            )
        );
    }

    NavigationStyles m_styles;
    std::optional<std::string> m_activeStyleEffectID;
    std::shared_ptr<T> m_drawable;
};
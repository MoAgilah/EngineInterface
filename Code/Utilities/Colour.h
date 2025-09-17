#pragma once

#include "Defines.h"
#include <cstdint>

#if USE_SFML
namespace sf { class Color; }
#endif

struct Colour
{
    uint8_t r{}, g{}, b{}, a{ 255 };

    constexpr Colour() = default;
    constexpr Colour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {
    }

#if USE_SFML

    // Conversions to/from SFML
    operator sf::Color() const;
    Colour(const sf::Color& c);
    sf::Color ToSFML() const;

#endif

    static const Colour Black;
    static const Colour White;
    static const Colour Red;
    static const Colour Green;
    static const Colour Blue;
    static const Colour Yellow;
    static const Colour Magenta;
    static const Colour Cyan;
    static const Colour Transparent;
};

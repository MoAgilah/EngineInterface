#pragma once

#include "Defines.h"
#include <cstdint>

#if USE_SFML
#include <SFML/Graphics/Color.hpp>
#endif

struct Colour
{
    uint8_t r{}, g{}, b{}, a{ 255 };

    constexpr Colour() = default;
    constexpr Colour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {
    }

#if USE_SFML
    operator sf::Color() const { return sf::Color(r, g, b, a); }
    Colour(const sf::Color& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
    sf::Color ToSFML() const { return sf::Color(r, g, b, a); }
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

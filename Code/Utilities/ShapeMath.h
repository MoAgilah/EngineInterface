#pragma once

#include <numbers>
#include <cmath>
#include "Vector2.h"

namespace ShapeMath
{
    inline void CalculateRotatedRectangleCorners(
        Vector2f corners[4],
        const Vector2f& centre,
        const Vector2f& size,
        float angle)
    {
        float radians = angle * std::numbers::pi_v<float> / 180.0f;
        float cosTheta = std::cos(radians);
        float sinTheta = std::sin(radians);

        float halfWidth = size.x / 2.0f;
        float halfHeight = size.y / 2.0f;

        Vector2f relativeCorners[4] =
        {
            { -halfWidth, -halfHeight },
            {  halfWidth, -halfHeight },
            {  halfWidth,  halfHeight },
            { -halfWidth,  halfHeight }
        };

        for (int i = 0; i < 4; ++i)
        {
            corners[i].x = centre.x + relativeCorners[i].x * cosTheta - relativeCorners[i].y * sinTheta;
            corners[i].y = centre.y + relativeCorners[i].x * sinTheta + relativeCorners[i].y * cosTheta;
        }
    }
}
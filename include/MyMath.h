#pragma once

#define ABS(x) ((x) < 0 ? -(x) : (x))

template <typename T>
T lerp(const T& a, const T& b, const float t)
{
    return a * (1 - t) + b * t;
}
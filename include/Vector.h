#pragma once
#include <cstdint>
#include <cassert>
#include <ostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "MyMath.h"

using std::ostream;
using std::vector;

template <typename T, uint32_t N>
struct Vector
{
    static constexpr uint32_t SIZE = N;
    static_assert(N >= 0);

    T v[N];

    static Vector add(const Vector& l, const Vector& r);
    static Vector sub(const Vector& l, const Vector& r);
    static Vector mul(const Vector v, const float k);
    static Vector linearCombination(const vector<Vector>& vectors, const vector<float>& scalars);

    // 복소수할 때는 특수 템플릿화 
    static T dot(const Vector& l, const Vector& r);
    static Vector cross(const Vector& l, const Vector& r);
    static float cos(const Vector& l, const Vector& r);

    T norm1() const;
    T norm2() const;
    T normInf() const;


    bool operator==(const Vector& rhs) const;
    Vector operator+(const Vector& rhs) const;
    Vector operator-(const Vector& rhs) const;
    Vector operator*(const float rhs) const;

    Vector& operator+=(const Vector& rhs);
    Vector& operator-=(const Vector& rhs);
    Vector& operator*=(const float rhs);
};

template <typename T, uint32_t N>
Vector<T, N> Vector<T, N>::add(const Vector& l, const Vector& r)
{
    static_assert(l.SIZE == r.SIZE);
    Vector<T, N> result;
    for (uint32_t i = 0; i < N; ++i)
    {
        result.v[i] = l.v[i] + r.v[i];
    }
    return result;
}

template <typename T, uint32_t N>
Vector<T, N> Vector<T, N>::sub(const Vector& l, const Vector& r)
{
    static_assert(l.SIZE == r.SIZE);
    Vector<T, N> result;
    for (uint32_t i = 0; i < N; ++i)
    {
        result.v[i] = l.v[i] - r.v[i];
    }
    return result;
}

template <typename T, uint32_t N>
Vector<T, N> Vector<T, N>::mul(const Vector v, const float k)
{
    Vector<T, N> result;
    for (uint32_t i = 0; i < N; ++i)
    {
        result.v[i] = v.v[i] * k;
    }
    return result;
}

template <typename T, uint32_t N>
bool Vector<T, N>::operator==(const Vector& rhs) const
{
    for (uint32_t i = 0; i < N; ++i)
    {
        if (ABS(static_cast<double>(v[i] - rhs.v[i])) > EPSILON)
        {
            return false;
        }
    }
    return true;
}

template <typename T, uint32_t N>
Vector<T, N> Vector<T, N>::operator+(const Vector& rhs) const
{
    static_assert(SIZE == rhs.SIZE);

    return add(*this, rhs);
}

template <typename T, uint32_t N>
Vector<T, N> Vector<T, N>::operator-(const Vector& rhs) const
{
    static_assert(SIZE == rhs.SIZE);

    return sub(*this, rhs);
}

template <typename T, uint32_t N>
Vector<T, N> Vector<T, N>::operator*(const float rhs) const
{
    return mul(*this, rhs);
}

template <typename T, uint32_t N>
Vector<T, N>& Vector<T, N>::operator+=(const Vector& rhs)
{
    static_assert(SIZE == rhs.SIZE);
    for (uint32_t i = 0; i < N; ++i)
    {
        v[i] += rhs.v[i];
    }
    return *this;
}

template <typename T, uint32_t N>
Vector<T, N>& Vector<T, N>::operator-=(const Vector& rhs)
{
    static_assert(SIZE == rhs.SIZE);
    for (uint32_t i = 0; i < N; ++i)
    {
        v[i] -= rhs.v[i];
    }
    return *this;
}

template <typename T, uint32_t N>
Vector<T, N>& Vector<T, N>::operator*=(const float rhs)
{
    for (uint32_t i = 0; i < N; ++i)
    {
        v[i] *= rhs;
    }
    return *this;
}

template <typename T, uint32_t N>
Vector<T, N> Vector<T, N>::linearCombination(const vector<Vector>& vectors, const vector<float>& scalars)
{
    assert(vectors.size() == scalars.size());
    Vector<T, N> result{};
    for (uint32_t i = 0; i < vectors.size(); ++i)
    {
        for (uint32_t j = 0; j < N; ++j)
        {
            // result += vectors[i] * scalars[i];
            result.v[j] = std::fma(vectors[i].v[j], scalars[i], result.v[j]);
        }
    }
    return result;
}

template <typename T, uint32_t N>
T Vector<T, N>::dot(const Vector& l, const Vector& r)
{
    static_assert(l.SIZE == r.SIZE);
    T result{};
    for (uint32_t i = 0; i < N; ++i)
    {
        result = std::fma(l.v[i], r.v[i], result);
    }
    return result;
}

template <typename T, uint32_t N>
T Vector<T, N>::norm1() const
{
    // 맨해튼 거리 합
    T result{};
    for (uint32_t i = 0; i < N; ++i)
    {
        result += ABS(v[i]);
    }
    return result;
}

template <typename T, uint32_t N>
T Vector<T, N>::norm2() const
{
    // 길이 구하기
    T result{};
    for (uint32_t i = 0; i < N; ++i)
    {
        result = std::fma(v[i], v[i], result);
    }
    return std::pow(result, 0.5);
}

template <typename T, uint32_t N>
T Vector<T, N>::normInf() const
{
    // 성분의 절댓값이 제일 큰 거 반환
    T result{};
    for (uint32_t i = 0; i < N; ++i)
    {
        result = std::max(result, ABS(v[i]));
    }
    return result;
}

template <typename T, uint32_t N>
float Vector<T, N>::cos(const Vector& l, const Vector& r)
{
    float length1 = l.norm2();
    float length2 = r.norm2();
    assert(length1 > 0.f && length2 > 0.f);

    float dotValue = Vector<T, N>::dot(l, r);
    return dotValue / (length1 * length2);
}

template <typename T, uint32_t N>
Vector<T, N> Vector<T, N>::cross(const Vector& l, const Vector& r)
{
    static_assert(l.SIZE == 3 && r.SIZE == 3);

    Vector<T, N> result;
    result.v[0] = l.v[1] * r.v[2] - l.v[2] * r.v[1];  // 12 21
    result.v[1] = l.v[2] * r.v[0] - l.v[0] * r.v[2];  // 20 02
    result.v[2] = l.v[0] * r.v[1] - l.v[1] * r.v[0];  // 01 10
    return result;
}


template <typename T, uint32_t N>
ostream& operator<<(ostream& os, const Vector<T, N>& v)
{
    os << "(";
    for (uint32_t i = 0; i < v.SIZE - 1; ++i)
    {
        os << v.v[i] << ", ";
    }
    os << v.v[v.SIZE - 1] << ")" << std::endl;
    return os;
}



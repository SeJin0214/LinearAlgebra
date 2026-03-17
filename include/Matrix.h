#pragma once
#include <cstdint>
#include <cassert>
#include <cstddef>
#include <ostream>
#include <cmath>
#include "MyMath.h"
#include "Vector.h"

using std::ostream;

template <typename T, size_t N, size_t M>
struct Matrix
{
    static constexpr size_t ROW_COUNT = N;
    static constexpr size_t COLUMN_COUNT = M;
    static_assert(ROW_COUNT >= 0 && COLUMN_COUNT >= 0);

    T m[N * M];

    bool operator==(const Matrix& rhs) const;
    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const float rhs) const;
    Vector<T, N> operator*(const Vector<T, M>& rhs) const;

    template <size_t P>
    Matrix<T, N, P> operator*(const Matrix<T, M, P>& rhs) const;

    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    Matrix& operator*=(const float rhs);

    T trace() const;
    Matrix<T, M, N> transpose() const;

    static Matrix add(const Matrix& l, const Matrix& r);
    static Matrix sub(const Matrix& l, const Matrix& r);
    static Matrix mul(const Matrix& v, const float k);
    static Vector<T, N> mul(const Matrix& m, const Vector<T, M>& v);

    template <size_t P>
    static Matrix<T, N, P> mul(const Matrix<T, N, M>& l, const Matrix<T, M, P>& r);
};

template <typename T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::add(const Matrix& l, const Matrix& r)
{
    static_assert(l.ROW_COUNT == r.ROW_COUNT && l.COLUMN_COUNT == r.COLUMN_COUNT);
    Matrix<T, N, M> result{};
    for (uint32_t i = 0; i < ROW_COUNT; ++i)
    {
        for (uint32_t j = 0; j < COLUMN_COUNT; ++j)
        {
            result.m[COLUMN_COUNT * i + j] = l.m[COLUMN_COUNT * i + j] + r.m[COLUMN_COUNT * i + j];
        }
    }
    return result;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::sub(const Matrix& l, const Matrix& r)
{
    static_assert(l.ROW_COUNT == r.ROW_COUNT && l.COLUMN_COUNT == r.COLUMN_COUNT);

    Matrix<T, N, M> result{};
    for (uint32_t i = 0; i < ROW_COUNT; ++i)
    {
        for (uint32_t j = 0; j < COLUMN_COUNT; ++j)
        {
            result.m[COLUMN_COUNT * i + j] = l.m[COLUMN_COUNT * i + j] - r.m[COLUMN_COUNT * i + j];
        }
    }
    return result;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::mul(const Matrix& m, const float k)
{
    Matrix<T, N, M> result{};
    for (uint32_t i = 0; i < ROW_COUNT; ++i)
    {
        for (uint32_t j = 0; j < COLUMN_COUNT; ++j)
        {
            result.m[COLUMN_COUNT * i + j] = m.m[COLUMN_COUNT * i + j] * k;
        }
    }
    return result;
}

template <typename T, size_t N, size_t M>
Vector<T, N> Matrix<T, N, M>::mul(const Matrix& m, const Vector<T, M>& v)
{
    Vector<T, N> result{};
    for (uint32_t i = 0; i < m.ROW_COUNT; ++i)
    {
        for (uint32_t j = 0; j < m.COLUMN_COUNT; ++j)
        {
            result.v[i] = std::fma(m.m[m.COLUMN_COUNT * i + j], v.v[j], result.v[i]);
        }
    }
    return result;
}

template <typename T, size_t N, size_t M>
template <size_t P>
Matrix<T, N, P> Matrix<T, N, M>::mul(const Matrix<T, N, M>& l, const Matrix<T, M, P>& r)
{
    // 행렬을 하나 돌 것
    // 열을 이동할 것
    // 행을 이동할 것
    Matrix<T, N, P> result{};
    for (uint32_t i = 0; i < l.ROW_COUNT; ++i)
    {
        for (uint32_t j = 0; j < r.COLUMN_COUNT; ++j)
        {
            for (uint32_t k = 0; k < l.COLUMN_COUNT; ++k)
            {
                result.m[r.COLUMN_COUNT * i + j] = std::fma(l.m[l.COLUMN_COUNT * i + k], r.m[r.COLUMN_COUNT * k + j], result.m[r.COLUMN_COUNT * i + j]);
            }
        }
    }
    // 1 2 3    3 3
    // 4 5 6    4 4
    //          6 6
    return result;
}

template <typename T, size_t N, size_t M>
bool Matrix<T, N, M>::operator==(const Matrix& rhs) const
{
    constexpr double epsilon = 1e-6;
    for (uint32_t i = 0; i < ROW_COUNT * COLUMN_COUNT; ++i)
    {
        if (ABS(static_cast<double>(m[i] - rhs.m[i])) > epsilon)
        {
            return false;
        }
    }
    return true;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator+(const Matrix& rhs) const
{
    static_assert(ROW_COUNT == rhs.ROW_COUNT && COLUMN_COUNT == rhs.COLUMN_COUNT);

    return add(*this, rhs);
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator-(const Matrix& rhs) const
{
    static_assert(ROW_COUNT == rhs.ROW_COUNT && COLUMN_COUNT == rhs.COLUMN_COUNT);

    return sub(*this, rhs);
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator*(const float rhs) const
{
    return mul(*this, rhs);
}

template <typename T, size_t N, size_t M>
Vector<T, N> Matrix<T, N, M>::operator*(const Vector<T, M>& rhs) const
{
    return mul(*this, rhs);
}

template <typename T, size_t N, size_t M>
template <size_t P>
Matrix<T, N, P> Matrix<T, N, M>::operator*(const Matrix<T, M, P>& rhs) const
{
    return mul(*this, rhs);
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator+=(const Matrix& rhs)
{
    static_assert(ROW_COUNT == rhs.ROW_COUNT && COLUMN_COUNT == rhs.COLUMN_COUNT);

    for (uint32_t i = 0; i < ROW_COUNT; ++i)
    {
        for (uint32_t j = 0; j < COLUMN_COUNT; ++j)
        {
            m[COLUMN_COUNT * i + j] += rhs.m[COLUMN_COUNT * i + j];
        }
    }
    return *this;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator-=(const Matrix& rhs)
{
    static_assert(ROW_COUNT == rhs.ROW_COUNT && COLUMN_COUNT == rhs.COLUMN_COUNT);

    for (uint32_t i = 0; i < ROW_COUNT; ++i)
    {
        for (uint32_t j = 0; j < COLUMN_COUNT; ++j)
        {
            m[COLUMN_COUNT * i + j] -= rhs.m[COLUMN_COUNT * i + j];
        }
    }
    return *this;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator*=(const float rhs)
{
    for (uint32_t i = 0; i < ROW_COUNT; ++i)
    {
        for (uint32_t j = 0; j < COLUMN_COUNT; ++j)
        {
            m[COLUMN_COUNT * i + j] *= rhs;
        }
    }
    return *this;
}

template <typename T, size_t N, size_t M>
T Matrix<T, N, M>::trace() const
{
    static_assert(ROW_COUNT == COLUMN_COUNT);
    T result{};
    for (uint32_t i = 0; i < ROW_COUNT; ++i)
    {
        result += m[COLUMN_COUNT * i + i];
    }
    return result;
}

template <typename T, size_t N, size_t M>
Matrix<T, M, N> Matrix<T, N, M>::transpose() const
{
    Matrix<T, M, N> result;
    for (uint32_t i = 0; i < ROW_COUNT; ++i)
    {
        for (uint32_t j = 0; j < COLUMN_COUNT; ++j)
        {
            // 거꾸로 넣기 
            result.m[ROW_COUNT * j + i] = m[COLUMN_COUNT * i + j];
        }
    }
    // 1 2 3
    // 4 5 6 
    
    // 1 4
    // 2 5
    // 3 6
    return result;
}

template <typename T, size_t N, size_t M>
ostream& operator<<(ostream& os, const Matrix<T, N, M>& m)
{
    for (uint32_t i = 0; i < m.ROW_COUNT; ++i)
    {
        os << "[";
        for (uint32_t j = 0; j < m.COLUMN_COUNT - 1; ++j)
        {
            os << m.m[m.COLUMN_COUNT * i + j] << ", ";
        }
        os << m.m[m.COLUMN_COUNT * i + m.COLUMN_COUNT - 1] << "]" << std::endl;
    }
    return os;
}

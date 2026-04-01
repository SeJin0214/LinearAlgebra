#pragma once
#include <cstdint>
#include <cassert>
#include <cstddef>
#include <climits>
#include <ostream>
#include <cmath>
#include <optional>
#include <type_traits>
#include "MyMath.h"
#include "Vector.h"

using std::ostream;

template <typename T, uint32_t N, uint32_t M>
struct Matrix
{
    static constexpr uint32_t ROW_COUNT = N;
    static constexpr uint32_t COLUMN_COUNT = M;
    static_assert(ROW_COUNT >= 0 && COLUMN_COUNT >= 0);

    T m[N * M];

    bool operator==(const Matrix& rhs) const;
    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const float rhs) const;
    Vector<T, N> operator*(const Vector<T, M>& rhs) const;

    template <uint32_t P>
    Matrix<T, N, P> operator*(const Matrix<T, M, P>& rhs) const;

    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    Matrix& operator*=(const float rhs);

    T trace() const;
    Matrix<T, M, N> transpose() const;
    Matrix toREF() const;
    Matrix toRREF() const;
    T determinant() const;
    T determinant3D() const;
    std::optional<Matrix> inverse() const;
    uint32_t rank() const;

    inline T at(const uint32_t row, const uint32_t column) const
    {
        return m[COLUMN_COUNT * row + column];
    }

    inline void set(const uint32_t row, const uint32_t column, const T value)
    {
        m[COLUMN_COUNT * row + column] = value;
    }

    static Matrix add(const Matrix& l, const Matrix& r);
    static Matrix sub(const Matrix& l, const Matrix& r);
    static Matrix mul(const Matrix& v, const float k);
    static Vector<T, N> mul(const Matrix& m, const Vector<T, M>& v);

    template <uint32_t P>
    static Matrix<T, N, P> mul(const Matrix<T, N, M>& l, const Matrix<T, M, P>& r);

private:
    uint32_t getZeroRows() const;
    
    // zeroRows 찾기 
};

template <typename T, uint32_t N, uint32_t M>
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

template <typename T, uint32_t N, uint32_t M>
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

template <typename T, uint32_t N, uint32_t M>
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

template <typename T, uint32_t N, uint32_t M>
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

template <typename T, uint32_t N, uint32_t M>
template <uint32_t P>
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

template <typename T, uint32_t N, uint32_t M>
bool Matrix<T, N, M>::operator==(const Matrix& rhs) const
{
    for (uint32_t i = 0; i < ROW_COUNT * COLUMN_COUNT; ++i)
    {
        if (ABS(static_cast<double>(m[i] - rhs.m[i])) > EPSILON)
        {
            return false;
        }
    }
    return true;
}

template <typename T, uint32_t N, uint32_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator+(const Matrix& rhs) const
{
    static_assert(ROW_COUNT == rhs.ROW_COUNT && COLUMN_COUNT == rhs.COLUMN_COUNT);

    return add(*this, rhs);
}

template <typename T, uint32_t N, uint32_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator-(const Matrix& rhs) const
{
    static_assert(ROW_COUNT == rhs.ROW_COUNT && COLUMN_COUNT == rhs.COLUMN_COUNT);

    return sub(*this, rhs);
}

template <typename T, uint32_t N, uint32_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator*(const float rhs) const
{
    return mul(*this, rhs);
}

template <typename T, uint32_t N, uint32_t M>
Vector<T, N> Matrix<T, N, M>::operator*(const Vector<T, M>& rhs) const
{
    return mul(*this, rhs);
}

template <typename T, uint32_t N, uint32_t M>
template <uint32_t P>
Matrix<T, N, P> Matrix<T, N, M>::operator*(const Matrix<T, M, P>& rhs) const
{
    return mul(*this, rhs);
}

template <typename T, uint32_t N, uint32_t M>
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

template <typename T, uint32_t N, uint32_t M>
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

template <typename T, uint32_t N, uint32_t M>
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

template <typename T, uint32_t N, uint32_t M>
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

template <typename T, uint32_t N, uint32_t M>
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

// 나무위키 참고
template <typename T, uint32_t N, uint32_t M>
Matrix<T, N, M> Matrix<T, N, M>::toREF() const
{
    // N^3
    Matrix<T, N, M> result = *this;
    uint32_t j = 0;
    uint32_t i = 0;
    // 바깥 j가 증가하거나 i가 증가하거나 N + M
    while (true)
    {
        uint32_t leadingEntry = UINT_MAX;
        // N
        for (uint32_t k = i; k < ROW_COUNT; ++k)
        {
            if (ABS(result.at(k, j)) > EPSILON)
            {
                // 2. 가장 먼저 만나는 LeadingEntry
                leadingEntry = k;
                break;
            }
        }
        // 6. j == m이면 끝내고, j < m이면 ++j 후 2로 실행
        bool isNotFound = leadingEntry == UINT_MAX;
        if (isNotFound)
        {
            ++j;
            if (j == COLUMN_COUNT)
            {
                break;
            }
            continue;
        }

        // M
        // 3. K행과 I행을 바꾼다.
        for (uint32_t k = 0; k < COLUMN_COUNT; ++k)
        {
            T temp = result.at(i, k);
            result.set(i, k, result.at(leadingEntry, k));
            result.set(leadingEntry, k, temp);
        }

        // N
        // 4. 바뀐 행렬에서 i < i` <= n을 만족하는 모든 i`에 대해
        for (uint32_t k = i + 1; k < ROW_COUNT; ++k)
        {
            assert(ABS(result.at(i, j)));
            // (i`행 l열) = (i`행 l열) - (ai`j / aij) * (i행 l열)
            T ratio = result.at(k, j) / result.at(i, j);
            for (uint32_t l = j; l < COLUMN_COUNT; ++l)
            {
                // leadingEntry 아래를 0으로 만드는 행위
                // 그리고 그 행의 중복을 없애는 것
                T iPrime = result.at(k, l);
                result.set(k, l, iPrime - ratio * result.at(i, l));
            }
        }
        // 5. ++i 한다.
        ++i;
    }
    return result;
}

template <typename T, uint32_t N, uint32_t M>
Matrix<T, N, M> Matrix<T, N, M>::toRREF() const
{
    Matrix<T, N, M> result = toREF();

    for (int32_t i = ROW_COUNT - 1; i >= 0; --i)
    {
        int32_t pivot = -1;
        for (int32_t j = 0; static_cast<uint32_t>(j) < COLUMN_COUNT; ++j)
        {
            if (ABS(result.at(i, j)) > EPSILON)
            {
                pivot = j;
                break;
            }
        }
        // 0만 있는 행
        if (pivot == -1)
        {
            continue;
        }

        assert(ABS(result.at(i, pivot)) > EPSILON);
        T pivotValue = result.at(i, pivot);
        // 자기 행 노멀라이즈
        for (int32_t j = pivot; static_cast<uint32_t>(j) < COLUMN_COUNT; ++j)
        {
            result.set(i, j, result.at(i, j) / pivotValue);
        }
        // 위로 올라가면서 
        for (int32_t j = i - 1; j >= 0; --j)
        {
            // pivot 1임
            T ratio = result.at(j, pivot);
            for (int32_t k = 0; static_cast<uint32_t>(k) < COLUMN_COUNT; ++k)
            {
                T iPrime = result.at(j, k);
                result.set(j, k, iPrime - ratio * result.at(i, k));
                // 오차가 생길 수 있나?
            }
        }
    }
    return result;
}
template <typename T, uint32_t N, uint32_t M>
T Matrix<T, N, M>::determinant3D() const
{
    Vector<T, 3> v1{at(0, 0), at(1, 0), at(2, 0)};
    Vector<T, 3> v2{at(0, 1), at(1, 1), at(2, 1)};
    Vector<T, 3> v3{at(0, 2), at(1, 2), at(2, 2)};
    return Vector<T, 3>::dot(v1, Vector<T, 3>::cross(v2, v3));
}

template <typename T, uint32_t N, uint32_t M>
T Matrix<T, N, M>::determinant() const
{
    static_assert(ROW_COUNT == COLUMN_COUNT && ROW_COUNT <= 4);

    T result;
    if (ROW_COUNT == 1)
    {
        return at(0, 0);
    }
    else if (ROW_COUNT == 2)
    {
        // ad - bc
        result = at(0, 0) * at(1, 1) - at(0, 1) * at(1, 0);
    }
    else if (ROW_COUNT == 3)
    {
        result = determinant3D();
    }
    else
    {
        Vector<T, N> temp;
        for (uint32_t i = 0; i < ROW_COUNT; ++i)
        {
            Matrix<T, 3, 3> matrix;
            // a11, a21, a31, a41
            uint32_t j = (i + 1) % ROW_COUNT;
            uint32_t k = 0;
            while (k < matrix.ROW_COUNT)
            {
                matrix.set(k, 0, at(j, 1));
                matrix.set(k, 1, at(j, 2));
                matrix.set(k, 2, at(j, 3));
                j = (j + 1) % ROW_COUNT;
                ++k;
            }
            T determinant3D = matrix.determinant3D();
            temp.v[i] = at(i, 0) * determinant3D;
        }
        result = temp.v[0] - temp.v[1] + temp.v[2] - temp.v[3];
    }
    return result;    
}

template <typename T, uint32_t N, uint32_t M>
std::optional<Matrix<T, N, M>> Matrix<T, N, M>::inverse() const
{
    static_assert(ROW_COUNT == COLUMN_COUNT);
    Matrix<T, N, M + M> temp{};
    // 왼쪽은 기존 행렬
    for (uint32_t i = 0; i < ROW_COUNT; ++i)
    {
        for (uint32_t j = 0; j < COLUMN_COUNT; ++j)
        {
            temp.set(i, j, at(i, j));
        }
    }
    // 오른쪽은 항등 행렬
    for (uint32_t i = 0; i < ROW_COUNT; ++i)
    {
        temp.set(i, i + COLUMN_COUNT, 1);
    }

    Matrix<T, N, M + M> rref = temp.toRREF();
    Matrix<T, N, M> left;
    for (uint32_t i = 0; i < ROW_COUNT; ++i)
    {
        for (uint32_t j = 0; j < COLUMN_COUNT; ++j)
        {
            left.set(i, j, rref.at(i, j));
        }
    }

    bool isSingularMatrix = left.getZeroRows() > 0;
    if (isSingularMatrix)
    {
        return std::nullopt;
    }

    // 오른쪽이 역행렬
    Matrix<T, N, M> result;
    for (uint32_t i = 0; i < ROW_COUNT; ++i)
    {
        for (uint32_t j = 0; j < COLUMN_COUNT; ++j)
        {
            result.set(i, j, rref.at(i, j + COLUMN_COUNT));
        }
    }
    return result;
}

template <typename T, uint32_t N, uint32_t M>
uint32_t Matrix<T, N, M>::getZeroRows() const
{
    uint32_t zeroRows = 0;
    for (uint32_t i = 0; i < ROW_COUNT; ++i)
    {
        bool isOnlyZero = true;
        for (uint32_t j = 0; j < COLUMN_COUNT; ++j)
        {
            if (ABS(at(i, j)) > EPSILON)
            {
                isOnlyZero = false;
                break;
            }
        }
        if (isOnlyZero)
        {
            ++zeroRows;
        }
    }
    return zeroRows;
}

template <typename T, uint32_t N, uint32_t M>
uint32_t Matrix<T, N, M>::rank() const
{
    Matrix<T, N, M> rref = toRREF();
    return static_cast<uint32_t>(ROW_COUNT) - rref.getZeroRows();
}

template <typename T, uint32_t N, uint32_t M>
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

template <typename T>
Matrix<T, 4, 4> perspective(const float fovRadian, const float aspectRatio, const float nearZ, const float farZ)
{
    static_assert(std::is_floating_point_v<T>, "perspective requires a floating-point matrix type");
    assert(fovRadian > EPSILON);
    assert(aspectRatio > EPSILON);
    assert(nearZ > EPSILON);
    assert(farZ > nearZ);

    const T tanHalfFov = static_cast<T>(std::tan(fovRadian * 0.5f));
    assert(ABS(tanHalfFov) > EPSILON);
    Matrix<T, 4, 4> result{};
    result.set(0, 0, static_cast<T>(1) / aspectRatio * tanHalfFov);
    result.set(1, 1, static_cast<T>(1) / tanHalfFov);


    // Az(스케일) + B(이동) n == near, f == far
    // (Az + B) / z,  z로 나눠서 비선형성을 보장함
    // 카메라 전방(z)이 음수, 다시 말해 증가하는 방향이 음수다. OpenGL은 멀수록 -10, -100이 됨
    // 전방으로 갈수록 near(-1) 에서 far(1)가 되도록 해야 한다. 얘는 양수다. 
    // 양수로 보장하고 싶은 것은 -부호를 붙여 양수로 (-z). -10 -> -100이 10 -> 100이 되도록

    // (Az + B) / -z,  near == -1, far == 1

    // Az에 z가 음수가 될수록 증가하는 방향인데, near를 그냥 넣어버리면 오히려 Far보다 멀리 있는 것으로 되어버린다.
    // A(-n) + B / -(-n) = -1  -> -An + B = -n
    // A(-f) + B / -(-f) = 1   -> -Af + B = f

    // 둘이 연립방정식 하기
    // -An + B = -n
    // -Af + B = f
    // A = (-n - f) / (f - n) -> A = - (f + n) / (f - n)
    // A를 대입해서 B 구하기
    // B = -n - n(f + n) / (f - n)
    // B = -n(f - n) + -n(f + n) / (f - n)
    // B = -2nf / (f - n)
    result.set(2, 2, static_cast<T>(-(farZ + nearZ) / (farZ - nearZ)));
    result.set(2, 3, static_cast<T>(-(2.f * farZ * nearZ) / (farZ - nearZ)));

    // Perspective Divide에 사용할 w 값이 양수가 되도록 -1을 넣음
    result.set(3, 2, static_cast<T>(-1));
    return result;
}

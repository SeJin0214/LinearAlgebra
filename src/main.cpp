#include <cassert>
#include <iostream>
#include "Matrix.h"
#include "Vector.h"

void testEx00();
void testEx01();
void testEx02();
void testEx03();
void testEx04();
void testEx05();
void testEx06();
void testEx07();
void testEx08();
void testEx09();
void testEx10();
void testEx11();
void testEx12();
void testEx13();
void testEx14();
void printEntry(const char* str);
void printSubEntry(const char* str);

int main(void)
{
    testEx00();
    testEx01();
    testEx02();
    testEx03();
    testEx04();
    testEx05();
    testEx06();
    testEx07();
    testEx08();
    testEx09();
    testEx10();
    testEx11();
    testEx12();
    testEx13();
    testEx14();

    return 0;
}

void printEntry(const char* str)
{
    std::cout
        << "====================================\n"
        << str << "\n"
        << "====================================\n";
}

void printSubEntry(const char* str)
{
    std::cout
        << "---\n"
        << str << "\n"
        << "---\n";
}

void testEx00()
{
    printEntry("   Ex00 Add, Sub, scalar mul   ");

    // Vector<float, 0> failedV;
    // Matrix<float, 0, 1> failedM;
    // Matrix<float, 1, 0> failedM2;

    printSubEntry("subject vector add");
    Vector<float, 2> su1{2.f, 3.f};
    Vector<float, 2> sv1{5.f, 7.f};
    Vector<float, 2> sr1 = su1 + sv1;
    std::cout << sr1;
    assert((sr1 == Vector<float, 2>{7.f, 10.f}));

    printSubEntry("subject vector sub");
    Vector<float, 2> su2{2.f, 3.f};
    Vector<float, 2> sv2{5.f, 7.f};
    Vector<float, 2> sr2 = su2 - sv2;
    std::cout << sr2;
    assert((sr2 == Vector<float, 2>{-3.f, -4.f}));

    printSubEntry("subject vector scl");
    Vector<float, 2> su3{2.f, 3.f};
    Vector<float, 2> sr3 = su3 * 2.f;
    std::cout << sr3;
    assert((sr3 == Vector<float, 2>{4.f, 6.f}));

    printSubEntry("subject matrix add");
    Matrix<float, 2, 2> sm1{
        1.f, 2.f,
        3.f, 4.f
    };
    Matrix<float, 2, 2> sm2{
        7.f, 4.f,
        -2.f, 2.f
    };
    Matrix<float, 2, 2> smr1 = sm1 + sm2;
    std::cout << smr1 << std::endl;
    assert((smr1 == Matrix<float, 2, 2>{
        8.f, 6.f,
        1.f, 6.f
    }));

    printSubEntry("subject matrix sub");
    Matrix<float, 2, 2> sm3{
        1.f, 2.f,
        3.f, 4.f
    };
    Matrix<float, 2, 2> sm4{
        7.f, 4.f,
        -2.f, 2.f
    };
    Matrix<float, 2, 2> smr2 = sm3 - sm4;
    std::cout << smr2 << std::endl;
    assert((smr2 == Matrix<float, 2, 2>{
        -6.f, -2.f,
        5.f, 2.f
    }));

    printSubEntry("subject matrix scl");
    Matrix<float, 2, 2> sm5{
        1.f, 2.f,
        3.f, 4.f
    };
    Matrix<float, 2, 2> smr3 = sm5 * 2.f;
    std::cout << smr3 << std::endl;
    assert((smr3 == Matrix<float, 2, 2>{
        2.f, 4.f,
        6.f, 8.f
    }));

    printSubEntry("vector 3");
    Vector<float, 3> v1{1.f, 2.f, 3.f};
    Vector<float, 3> v2{4.f, 5.f, 6.f};

    Vector<float, 3> v12Add = v1 + v2;
    Vector<float, 3> v12Sub = v1 - v2;
    Vector<float, 3> v12Mul = v1 * 2.f;

    std::cout << "v1 = " << v1;
    std::cout << "v2 = " << v2;
    std::cout << "v1 + v2 = " << v12Add;
    std::cout << "v1 - v2 = " << v12Sub;
    std::cout << "v1 * 2 = " << v12Mul;

    assert((v12Add == Vector<float, 3>{5.f, 7.f, 9.f}));
    assert((v12Sub == Vector<float, 3>{-3.f, -3.f, -3.f}));
    assert((v12Mul == Vector<float, 3>{2.f, 4.f, 6.f}));

    printSubEntry("vector 4");
    Vector<float, 4> v3{1.f, 2.f, 3.f, 4.f};
    Vector<float, 4> v4{10.f, 20.f, 30.f, 40.f};

    Vector<float, 4> v34Add = v3 + v4;
    Vector<float, 4> v34Sub = v3 - v4;
    Vector<float, 4> v34Mul = v3 * 0.5f;

    std::cout << "v3 = " << v3;
    std::cout << "v4 = " << v4;
    std::cout << "v3 + v4 = " << v34Add;
    std::cout << "v3 - v4 = " << v34Sub;
    std::cout << "v3 * 0.5 = " << v34Mul;

    assert((v34Add == Vector<float, 4>{11.f, 22.f, 33.f, 44.f}));
    assert((v34Sub == Vector<float, 4>{-9.f, -18.f, -27.f, -36.f}));
    assert((v34Mul == Vector<float, 4>{0.5f, 1.f, 1.5f, 2.f}));

    printSubEntry("matrix 2x3");
    Matrix<float, 2, 3> m1{
        1.f, 2.f, 3.f,
        4.f, 5.f, 6.f
    };
    Matrix<float, 2, 3> m2{
        6.f, 5.f, 4.f,
        3.f, 2.f, 1.f
    };

    Matrix<float, 2, 3> m12Add = m1 + m2;
    Matrix<float, 2, 3> m12Sub = m1 - m2;
    Matrix<float, 2, 3> m12Mul = m1 * 2.f;

    std::cout << "m1 =" << std::endl << m1;
    std::cout << "m2 =" << std::endl << m2;
    std::cout << "m1 + m2 =" << std::endl << m12Add;
    std::cout << "m1 - m2 =" << std::endl << m12Sub;
    std::cout << "m1 * 2 =" << std::endl << m12Mul;

    assert((m12Add == Matrix<float, 2, 3>{
        7.f, 7.f, 7.f,
        7.f, 7.f, 7.f
    }));
    assert((m12Sub == Matrix<float, 2, 3>{
        -5.f, -3.f, -1.f,
        1.f, 3.f, 5.f
    }));
    assert((m12Mul == Matrix<float, 2, 3>{
        2.f, 4.f, 6.f,
        8.f, 10.f, 12.f
    }));

    printSubEntry("matrix 3x2");
    Matrix<float, 3, 2> m3{
        1.f, 2.f,
        3.f, 4.f,
        5.f, 6.f
    };
    Matrix<float, 3, 2> m4{
        6.f, 5.f,
        4.f, 3.f,
        2.f, 1.f
    };

    Matrix<float, 3, 2> m34Add = m3 + m4;
    Matrix<float, 3, 2> m34Sub = m3 - m4;
    Matrix<float, 3, 2> m34Mul = m3 * 3.f;

    std::cout << "m3 =" << std::endl << m3;
    std::cout << "m4 =" << std::endl << m4;
    std::cout << "m3 + m4 =" << std::endl << m34Add;
    std::cout << "m3 - m4 =" << std::endl << m34Sub;
    std::cout << "m3 * 3 =" << std::endl << m34Mul;

    assert((m34Add == Matrix<float, 3, 2>{
        7.f, 7.f,
        7.f, 7.f,
        7.f, 7.f
    }));
    assert((m34Sub == Matrix<float, 3, 2>{
        -5.f, -3.f,
        -1.f, 1.f,
        3.f, 5.f
    }));
    assert((m34Mul == Matrix<float, 3, 2>{
        3.f, 6.f,
        9.f, 12.f,
        15.f, 18.f
    }));

    std::cout << "Ex00 assertions passed\n";
}

void testEx01()
{
    printEntry("   Ex01 linear combination   ");

    printSubEntry("basis vectors");
    Vector<float, 3> e1{1.f, 0.f, 0.f};
    Vector<float, 3> e2{0.f, 1.f, 0.f};
    Vector<float, 3> e3{0.f, 0.f, 1.f};

    std::vector<Vector<float, 3> > basisVectors{e1, e2, e3};
    std::vector<float> basisScalars{10.f, -2.f, 0.5f};

    Vector<float, 3> basisResult = Vector<float, 3>::linearCombination(basisVectors, basisScalars);

    std::cout << "linearCombination([e1, e2, e3], [10, -2, 0.5]) = " << basisResult;
    assert((basisResult == Vector<float, 3>{10.f, -2.f, 0.5f}));

    printSubEntry("custom vectors");
    Vector<float, 3> v1{1.f, 2.f, 3.f};
    Vector<float, 3> v2{0.f, 10.f, -100.f};

    std::vector<Vector<float, 3> > customVectors{v1, v2};
    std::vector<float> customScalars{10.f, -2.f};

    Vector<float, 3> customResult = Vector<float, 3>::linearCombination(customVectors, customScalars);

    std::cout << "linearCombination([v1, v2], [10, -2]) = " << customResult;
    assert((customResult == Vector<float, 3>{10.f, 0.f, 230.f}));

    printSubEntry("zero coefficients");
    std::vector<float> zeroScalars{0.f, 0.f};
    Vector<float, 3> zeroResult = Vector<float, 3>::linearCombination(customVectors, zeroScalars);

    std::cout << "linearCombination([v1, v2], [0, 0]) = " << zeroResult;
    assert((zeroResult == Vector<float, 3>{0.f, 0.f, 0.f}));

    std::cout << "Ex01 assertions passed\n";
}

void testEx02()
{
    printEntry("   Ex02 linear interpolation   ");

    constexpr float epsilon = 1e-6f;

    printSubEntry("subject scalar t=0");
    float f0 = lerp(0.f, 1.f, 0.f);
    std::cout << f0 << std::endl;
    assert(ABS(f0 - 0.f) <= epsilon);

    printSubEntry("subject scalar t=1");
    float f1 = lerp(0.f, 1.f, 1.f);
    std::cout << f1 << std::endl;
    assert(ABS(f1 - 1.f) <= epsilon);

    printSubEntry("subject scalar t=0.5");
    float f2 = lerp(0.f, 1.f, 0.5f);
    std::cout << f2 << std::endl;
    assert(ABS(f2 - 0.5f) <= epsilon);

    printSubEntry("subject scalar 21 to 42");
    float f3 = lerp(21.f, 42.f, 0.3f);
    std::cout << f3 << std::endl;
    assert(ABS(f3 - 27.3f) <= epsilon);

    printSubEntry("vector");
    Vector<float, 2> v1{2.f, 1.f};
    Vector<float, 2> v2{4.f, 2.f};

    Vector<float, 2> vr = lerp(v1, v2, 0.3f);
    std::cout << vr << std::endl;
    assert((vr == Vector<float, 2>{2.6f, 1.3f}));

    printSubEntry("matrix");
    Matrix<float, 2, 2> m1{
        2.f, 1.f,
        3.f, 4.f
    };
    Matrix<float, 2, 2> m2{
        20.f, 10.f,
        30.f, 40.f
    };

    Matrix<float, 2, 2> mr = lerp(m1, m2, 0.5f);
    std::cout << mr << std::endl;
    assert((mr == Matrix<float, 2, 2>{
        11.f, 5.5f,
        16.5f, 22.f
    }));

    std::cout << "Ex02 assertions passed\n";
}

void testEx03()
{
    printEntry("   Ex03 dot product   ");

    constexpr float epsilon = 1e-6f;

    printSubEntry("subject zero vector");
    Vector<float, 2> z1{0.f, 0.f};
    Vector<float, 2> z2{1.f, 1.f};
    float zeroDot = Vector<float, 2>::dot(z1, z2);
    std::cout << zeroDot << std::endl;
    assert(ABS(zeroDot - 0.f) <= epsilon);

    printSubEntry("subject ones");
    Vector<float, 2> v1{1.f, 1.f};
    Vector<float, 2> v2{1.f, 1.f};
    float simpleDot = Vector<float, 2>::dot(v1, v2);
    std::cout << simpleDot << std::endl;
    assert(ABS(simpleDot - 2.f) <= epsilon);

    printSubEntry("subject example");
    Vector<float, 3> v3{1.f, 2.f, 3.f};
    Vector<float, 3> v4{4.f, 5.f, 6.f};
    float exampleDot = Vector<float, 3>::dot(v3, v4);
    std::cout << exampleDot << std::endl;
    assert(ABS(exampleDot - 32.f) <= epsilon);

    printSubEntry("negative values");
    Vector<float, 2> v5{-1.f, 6.f};
    Vector<float, 2> v6{3.f, 2.f};
    float negativeDot = Vector<float, 2>::dot(v5, v6);
    std::cout << negativeDot << std::endl;
    assert(ABS(negativeDot - 9.f) <= epsilon);

    std::cout << "Ex03 assertions passed\n";
}

void testEx04()
{
    printEntry("   Ex04 norm   ");

    constexpr float epsilon = 1e-6f;

    printSubEntry("zero vector");
    Vector<float, 3> z{0.f, 0.f, 0.f};
    std::cout << "norm1: " << z.norm1() << ", norm2: " << z.norm2() << ", normInf: " << z.normInf() << std::endl;
    assert(ABS(z.norm1() - 0.f) <= epsilon);
    assert(ABS(z.norm2() - 0.f) <= epsilon);
    assert(ABS(z.normInf() - 0.f) <= epsilon);

    printSubEntry("subject [1,2,3]");
    Vector<float, 3> u{1.f, 2.f, 3.f};
    std::cout << "norm1: " << u.norm1() << ", norm2: " << u.norm2() << ", normInf: " << u.normInf() << std::endl;
    assert(ABS(u.norm1() - 6.f) <= epsilon);
    assert(ABS(u.norm2() - 3.74165738f) <= epsilon);
    assert(ABS(u.normInf() - 3.f) <= epsilon);

    printSubEntry("subject [-1,-2]");
    Vector<float, 2> v{-1.f, -2.f};
    std::cout << "norm1: " << v.norm1() << ", norm2: " << v.norm2() << ", normInf: " << v.normInf() << std::endl;
    assert(ABS(v.norm1() - 3.f) <= epsilon);
    assert(ABS(v.norm2() - 2.236067977f) <= epsilon);
    assert(ABS(v.normInf() - 2.f) <= epsilon);

    printSubEntry("3-4-5 vector");
    Vector<float, 2> w{3.f, 4.f};
    std::cout << "norm1: " << w.norm1() << ", norm2: " << w.norm2() << ", normInf: " << w.normInf() << std::endl;
    assert(ABS(w.norm1() - 7.f) <= epsilon);
    assert(ABS(w.norm2() - 5.f) <= epsilon);
    assert(ABS(w.normInf() - 4.f) <= epsilon);

    std::cout << "Ex04 assertions passed\n";
}

void testEx05()
{
    printEntry("   Ex05 cosine   ");

    constexpr float epsilon = 1e-6f;

    printSubEntry("subject same direction");
    Vector<float, 2> u1{1.f, 0.f};
    Vector<float, 2> v1{1.f, 0.f};
    float cos1 = Vector<float, 2>::cos(u1, v1);
    std::cout << cos1 << std::endl;
    assert(ABS(cos1 - 1.f) <= epsilon);

    printSubEntry("subject orthogonal");
    Vector<float, 2> u2{1.f, 0.f};
    Vector<float, 2> v2{0.f, 1.f};
    float cos2 = Vector<float, 2>::cos(u2, v2);
    std::cout << cos2 << std::endl;
    assert(ABS(cos2 - 0.f) <= epsilon);

    printSubEntry("subject opposite");
    Vector<float, 2> u3{-1.f, 1.f};
    Vector<float, 2> v3{1.f, -1.f};
    float cos3 = Vector<float, 2>::cos(u3, v3);
    std::cout << cos3 << std::endl;
    assert(ABS(cos3 + 1.f) <= epsilon);

    printSubEntry("subject colinear");
    Vector<float, 2> u4{2.f, 1.f};
    Vector<float, 2> v4{4.f, 2.f};
    float cos4 = Vector<float, 2>::cos(u4, v4);
    std::cout << cos4 << std::endl;
    assert(ABS(cos4 - 1.f) <= epsilon);

    printSubEntry("subject 3d example");
    Vector<float, 3> u5{1.f, 2.f, 3.f};
    Vector<float, 3> v5{4.f, 5.f, 6.f};
    float cos5 = Vector<float, 3>::cos(u5, v5);
    std::cout << cos5 << std::endl;
    assert(ABS(cos5 - 0.974631846f) <= epsilon);

    std::cout << "Ex05 assertions passed\n";
}


void testEx06()
{
    printEntry("   Ex06 cross product   ");

    printSubEntry("subject example 1");
    Vector<float, 3> u1{0.f, 0.f, 1.f};
    Vector<float, 3> v1{1.f, 0.f, 0.f};
    Vector<float, 3> r1 = Vector<float, 3>::cross(u1, v1);
    std::cout << r1 << std::endl;
    assert((r1 == Vector<float, 3>{0.f, 1.f, 0.f}));

    printSubEntry("subject example 2");
    Vector<float, 3> u2{1.f, 2.f, 3.f};
    Vector<float, 3> v2{4.f, 5.f, 6.f};
    Vector<float, 3> r2 = Vector<float, 3>::cross(u2, v2);
    std::cout << r2 << std::endl;
    assert((r2 == Vector<float, 3>{-3.f, 6.f, -3.f}));

    printSubEntry("subject example 3");
    Vector<float, 3> u3{4.f, 2.f, -3.f};
    Vector<float, 3> v3{-2.f, -5.f, 16.f};
    Vector<float, 3> r3 = Vector<float, 3>::cross(u3, v3);
    std::cout << r3 << std::endl;
    assert((r3 == Vector<float, 3>{17.f, -58.f, -16.f}));

    printSubEntry("reverse order");
    Vector<float, 3> reverse = Vector<float, 3>::cross(v2, u2);
    std::cout << reverse << std::endl;
    assert((reverse == Vector<float, 3>{3.f, -6.f, 3.f}));

    std::cout << "Ex06 assertions passed\n";
}

void testEx07()
{
    printEntry("   Ex07 matrix multiplication   ");

    printSubEntry("matrix * vector identity");
    Matrix<float, 2, 2> m1{
        1.f, 0.f,
        0.f, 1.f
    };
    Vector<float, 2> v1{4.f, 2.f};
    Vector<float, 2> mv1 = m1 * v1;
    std::cout << mv1 << std::endl;
    assert((mv1 == Vector<float, 2>{4.f, 2.f}));

    printSubEntry("matrix * vector scale");
    Matrix<float, 2, 2> m2{
        2.f, 0.f,
        0.f, 2.f
    };
    Vector<float, 2> v2{4.f, 2.f};
    Vector<float, 2> mv2 = m2 * v2;
    std::cout << mv2 << std::endl;
    assert((mv2 == Vector<float, 2>{8.f, 4.f}));

    printSubEntry("matrix * vector general");
    Matrix<float, 2, 2> m3{
        2.f, -2.f,
        -2.f, 2.f
    };
    Vector<float, 2> v3{4.f, 2.f};
    Vector<float, 2> mv3 = m3 * v3;
    std::cout << mv3 << std::endl;
    assert((mv3 == Vector<float, 2>{4.f, -4.f}));

    printSubEntry("matrix * matrix identity");
    Matrix<float, 2, 2> a1{
        1.f, 0.f,
        0.f, 1.f
    };
    Matrix<float, 2, 2> b1{
        1.f, 0.f,
        0.f, 1.f
    };
    Matrix<float, 2, 2> mm1 = a1 * b1;
    std::cout << mm1 << std::endl;
    assert((mm1 == Matrix<float, 2, 2>{
        1.f, 0.f,
        0.f, 1.f
    }));

    printSubEntry("matrix * matrix right identity");
    Matrix<float, 2, 2> a2{
        1.f, 0.f,
        0.f, 1.f
    };
    Matrix<float, 2, 2> b2{
        2.f, 1.f,
        4.f, 2.f
    };
    Matrix<float, 2, 2> mm2 = a2 * b2;
    std::cout << mm2 << std::endl;
    assert((mm2 == Matrix<float, 2, 2>{
        2.f, 1.f,
        4.f, 2.f
    }));

    printSubEntry("matrix * matrix general");
    Matrix<float, 2, 2> a3{
        3.f, -5.f,
        6.f, 8.f
    };
    Matrix<float, 2, 2> b3{
        2.f, 1.f,
        4.f, 2.f
    };
    Matrix<float, 2, 2> mm3 = a3 * b3;
    std::cout << mm3 << std::endl;
    assert((mm3 == Matrix<float, 2, 2>{
        -14.f, -7.f,
        44.f, 22.f
    }));

    printSubEntry("matrix 2x3 * matrix 3x2");
    Matrix<float, 2, 3> a4{
        1.f, 2.f, 3.f,
        4.f, 5.f, 6.f
    };
    Matrix<float, 3, 2> b4{
        7.f, 8.f,
        9.f, 10.f,
        11.f, 12.f
    };
    Matrix<float, 2, 2> mm4 = a4 * b4;
    std::cout << mm4 << std::endl;
    assert((mm4 == Matrix<float, 2, 2>{
        58.f, 64.f,
        139.f, 154.f
    }));

    // invalid size examples (should not compile)
    // Matrix<float, 2, 3> badM1{
    //     1.f, 2.f, 3.f,
    //     4.f, 5.f, 6.f
    // };
    // Vector<float, 2> badV{1.f, 2.f};
    // auto badMv = badM1 * badV;

    // Matrix<float, 2, 3> badA{
    //     1.f, 2.f, 3.f,
    //     4.f, 5.f, 6.f
    // };
    // Matrix<float, 2, 2> badB{
    //     1.f, 2.f,
    //     3.f, 4.f
    // };
    // auto badMm = badA * badB;

    std::cout << "Ex07 assertions passed\n";
}

void testEx08()
{
    printEntry("   Ex08 trace   ");

    printSubEntry("identity");
    Matrix<float, 2, 2> u1{
        1.f, 0.f,
        0.f, 1.f
    };
    float t1 = u1.trace();
    std::cout << t1 << std::endl;
    assert(ABS(t1 - 2.f) <= 1e-6f);

    printSubEntry("3x3 positive");
    Matrix<float, 3, 3> u2{
        2.f, -5.f, 0.f,
        4.f, 3.f, 7.f,
        -2.f, 3.f, 4.f
    };
    float t2 = u2.trace();
    std::cout << t2 << std::endl;
    assert(ABS(t2 - 9.f) <= 1e-6f);

    printSubEntry("3x3 negative");
    Matrix<float, 3, 3> u3{
        -2.f, -8.f, 4.f,
        1.f, -23.f, 4.f,
        0.f, 6.f, 4.f
    };
    float t3 = u3.trace();
    std::cout << t3 << std::endl;
    assert(ABS(t3 + 21.f) <= 1e-6f);

    // invalid size examples (should not compile)
    // Matrix<float, 2, 3> bad1{
    //     1.f, 2.f, 3.f,
    //     4.f, 5.f, 6.f
    // };
    // std::cout << bad1.trace() << std::endl;

    // Matrix<float, 3, 2> bad2{
    //     1.f, 2.f,
    //     3.f, 4.f,
    //     5.f, 6.f
    // };
    // std::cout << bad2.trace() << std::endl;

    std::cout << "Ex08 assertions passed\n";
}

void testEx09()
{
    printEntry("   Ex09 transpose   ");

    printSubEntry("2x2 identity");
    Matrix<float, 2, 2> m1{
        1.f, 0.f,
        0.f, 1.f
    };
    Matrix<float, 2, 2> t1 = m1.transpose();
    std::cout << t1 << std::endl;
    assert((t1 == Matrix<float, 2, 2>{
        1.f, 0.f,
        0.f, 1.f
    }));

    printSubEntry("2x3 to 3x2");
    Matrix<float, 2, 3> m2{
        1.f, 2.f, 3.f,
        4.f, 5.f, 6.f
    };
    Matrix<float, 3, 2> t2 = m2.transpose();
    std::cout << t2 << std::endl;
    assert((t2 == Matrix<float, 3, 2>{
        1.f, 4.f,
        2.f, 5.f,
        3.f, 6.f
    }));

    printSubEntry("3x2 to 2x3");
    Matrix<float, 3, 2> m3{
        1.f, 4.f,
        2.f, 5.f,
        3.f, 6.f
    };
    Matrix<float, 2, 3> t3 = m3.transpose();
    std::cout << t3 << std::endl;
    assert((t3 == Matrix<float, 2, 3>{
        1.f, 2.f, 3.f,
        4.f, 5.f, 6.f
    }));

    printSubEntry("3x3 general");
    Matrix<float, 3, 3> m4{
        1.f, 2.f, 3.f,
        4.f, 5.f, 6.f,
        7.f, 8.f, 9.f
    };
    Matrix<float, 3, 3> t4 = m4.transpose();
    std::cout << t4 << std::endl;
    assert((t4 == Matrix<float, 3, 3>{
        1.f, 4.f, 7.f,
        2.f, 5.f, 8.f,
        3.f, 6.f, 9.f
    }));

    std::cout << "Ex09 assertions passed\n";
}

void testEx10()
{
    printEntry("   Ex10 row echelon form   ");

    printSubEntry("3x3 identity");
    Matrix<float, 3, 3> m1{
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f
    };
    Matrix<float, 3, 3> r1 = m1.toRREF();
    std::cout << r1 << std::endl;
    assert((r1 == Matrix<float, 3, 3>{
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f
    }));

    printSubEntry("2x2 invertible");
    Matrix<float, 2, 2> m2{
        1.f, 2.f,
        3.f, 4.f
    };
    Matrix<float, 2, 2> r2 = m2.toRREF();
    std::cout << r2 << std::endl;
    assert((r2 == Matrix<float, 2, 2>{
        1.f, 0.f,
        0.f, 1.f
    }));

    printSubEntry("2x2 singular");
    Matrix<float, 2, 2> m3{
        1.f, 2.f,
        2.f, 4.f
    };
    Matrix<float, 2, 2> r3 = m3.toRREF();
    std::cout << r3 << std::endl;
    assert((r3 == Matrix<float, 2, 2>{
        1.f, 2.f,
        0.f, 0.f
    }));

    printSubEntry("3x5 subject example");
    Matrix<float, 3, 5> m4{
        8.f, 5.f, -2.f, 4.f, 28.f,
        4.f, 2.5f, 20.f, 4.f, -4.f,
        8.f, 5.f, 1.f, 4.f, 17.f
    };
    Matrix<float, 3, 5> r4 = m4.toRREF();
    std::cout << r4 << std::endl;
    assert((r4 == Matrix<float, 3, 5>{
        1.f, 0.625f, 0.f, 0.f, -12.1666667f,
        0.f, 0.f, 1.f, 0.f, -3.6666667f,
        0.f, 0.f, 0.f, 1.f, 29.5f
    }));

    std::cout << "Ex10 assertions passed\n";
}

void testEx11()
{
    printEntry("   Ex11 determinant   ");

    constexpr float epsilon = 1e-6f;

    printSubEntry("2x2 singular");
    Matrix<float, 2, 2> m1{
        1.f, -1.f,
        -1.f, 1.f
    };
    float d1 = m1.determinant();
    std::cout << d1 << std::endl;
    assert(ABS(d1 - 0.f) <= epsilon);

    printSubEntry("3x3 diagonal scale");
    Matrix<float, 3, 3> m2{
        2.f, 0.f, 0.f,
        0.f, 2.f, 0.f,
        0.f, 0.f, 2.f
    };
    float d2 = m2.determinant();
    std::cout << d2 << std::endl;
    assert(ABS(d2 - 8.f) <= epsilon);

    printSubEntry("3x3 subject example");
    Matrix<float, 3, 3> m3{
        8.f, 5.f, -2.f,
        4.f, 7.f, 20.f,
        7.f, 6.f, 1.f
    };
    float d3 = m3.determinant();
    std::cout << d3 << std::endl;
    assert(ABS(d3 + 174.f) <= epsilon);

    printSubEntry("4x4 subject example");
    Matrix<float, 4, 4> m4{
        8.f, 5.f, -2.f, 4.f,
        4.f, 2.5f, 20.f, 4.f,
        8.f, 5.f, 1.f, 4.f,
        28.f, -4.f, 17.f, 1.f
    };
    float d4 = m4.determinant();
    std::cout << d4 << std::endl;
    assert(ABS(d4 - 1032.f) <= epsilon);

    std::cout << "Ex11 assertions passed\n";
}

void testEx12()
{
    printEntry("   Ex12 inverse   ");

    printSubEntry("3x3 identity");
    Matrix<float, 3, 3> m1{
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f
    };
    auto inv1 = m1.inverse();
    assert(inv1.has_value());
    std::cout << *inv1 << std::endl;
    assert((*inv1 == Matrix<float, 3, 3>{
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f
    }));

    printSubEntry("3x3 diagonal scale");
    Matrix<float, 3, 3> m2{
        2.f, 0.f, 0.f,
        0.f, 2.f, 0.f,
        0.f, 0.f, 2.f
    };
    auto inv2 = m2.inverse();
    assert(inv2.has_value());
    std::cout << *inv2 << std::endl;
    assert((*inv2 == Matrix<float, 3, 3>{
        0.5f, 0.f, 0.f,
        0.f, 0.5f, 0.f,
        0.f, 0.f, 0.5f
    }));

    printSubEntry("3x3 subject example");
    Matrix<float, 3, 3> m3{
        8.f, 5.f, -2.f,
        4.f, 7.f, 20.f,
        7.f, 6.f, 1.f
    };
    auto inv3 = m3.inverse();
    assert(inv3.has_value());
    std::cout << *inv3 << std::endl;
    assert((*inv3 == Matrix<float, 3, 3>{
        0.649425287f, 0.097701149f, -0.655172414f,
        -0.781609195f, -0.126436782f, 0.965517241f,
        0.143678161f, 0.074712644f, -0.206896552f
    }));

    printSubEntry("singular matrix");
    Matrix<float, 2, 2> m4{
        1.f, 2.f,
        2.f, 4.f
    };
    auto inv4 = m4.inverse();
    assert(!inv4.has_value());

    std::cout << "Ex12 assertions passed\n";
}

void testEx13()
{
    printEntry("   Ex13 rank   ");

    printSubEntry("3x3 identity");
    Matrix<float, 3, 3> m1{
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f
    };
    uint32_t r1 = m1.rank();
    std::cout << r1 << std::endl;
    assert(r1 == 3);

    printSubEntry("3x4 rank 2");
    Matrix<float, 3, 4> m2{
        1.f, 2.f, 0.f, 0.f,
        2.f, 4.f, 0.f, 0.f,
        -1.f, 2.f, 1.f, 1.f
    };
    uint32_t r2 = m2.rank();
    std::cout << r2 << std::endl;
    assert(r2 == 2);

    printSubEntry("4x3 rank 3");
    Matrix<float, 4, 3> m3{
        8.f, 5.f, -2.f,
        4.f, 7.f, 20.f,
        7.f, 6.f, 1.f,
        21.f, 18.f, 7.f
    };
    uint32_t r3 = m3.rank();
    std::cout << r3 << std::endl;
    assert(r3 == 3);

    printSubEntry("zero matrix");
    Matrix<float, 2, 3> m4{
        0.f, 0.f, 0.f,
        0.f, 0.f, 0.f
    };
    uint32_t r4 = m4.rank();
    std::cout << r4 << std::endl;
    assert(r4 == 0);

    printSubEntry("duplicate rows");
    Matrix<float, 3, 3> m5{
        1.f, 2.f, 3.f,
        1.f, 2.f, 3.f,
        2.f, 4.f, 6.f
    };
    uint32_t r5 = m5.rank();
    std::cout << r5 << std::endl;
    assert(r5 == 1);

    std::cout << "Ex13 assertions passed\n";
}

void testEx14()
{
    printEntry("   Ex14 perspective   ");

    printSubEntry("projection matrix");
    const float fov = 3.14159265358979323846f / 2.f;
    Matrix<float, 4, 4> projection = perspective<float>(fov, 1.f, 1.f, 10.f);
    std::cout << projection << std::endl;
    assert((projection == Matrix<float, 4, 4>{
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, -11.f / 9.f, -20.f / 9.f,
        0.f, 0.f, -1.f, 0.f
    }));

    printSubEntry("project point");
    Vector<float, 4> point{0.f, 0.f, -5.f, 1.f};
    Vector<float, 4> clip = projection * point;
    std::cout << clip;
    assert((clip == Vector<float, 4>{0.f, 0.f, 35.f / 9.f, 5.f}));

    std::cout << "Ex14 assertions passed\n";
}



















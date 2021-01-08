//
// Created by Duroy on 08/01/2021.
//

#include <iostream>

class A
{
public:
    A() : m_i(0) { }

protected:
    int m_i;
};

class B
{
public:
    B() : m_d(0.0) { }

protected:
    double m_d;
};

class C
        : public A, public B
{
public:
    C() : m_c('a') { }

private:
    char m_c;
};

int main()
{
    C c;
    A *pa = &c;
    B *pb = &c;

    const int x = (pa == &c) ? 1 : 2;
    const int y = (pb == &c) ? 3 : 4;
    int z;
    if (reinterpret_cast<char *>(pa) == reinterpret_cast<char *>(pb)) {
        z = 5;
    } else {
        z = 6;
    }

    std::cout << x << y << z << std::endl;
    return 0;
}
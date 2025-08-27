#pragma once
#include <iostream>
using namespace std;

class Drob
{
    int num{ 1 };
    int den{ 1 };

    int nod(int left, int right);
    void simply();
    void printDevByZero() { cout << "Деление на 0"; }

public:
    Drob();
    Drob(int pNum, int pDen);
    Drob(Drob&& other);
   
    void input();
    void output() const;

    Drob add(const Drob& right) const;
    Drob sub(const Drob& right) const;
    Drob mul(const Drob& right) const;
    Drob div(const Drob& right) const;
    Drob operator+(const Drob& right) const { return add(right); }
    Drob operator-(const Drob& right) const { return sub(right); }
    Drob operator*(const Drob& right) const { return mul(right); }
    Drob operator/(const Drob& right) const { return div(right); }
    Drob& operator=(Drob&& other);
};

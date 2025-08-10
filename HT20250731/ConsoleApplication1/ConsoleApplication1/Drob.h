#pragma once
#include <iostream>
using namespace std;

class Drob
{
    int num{ 1 };
    int den{ 1 };

    int nod(int left, int right);
    void simply();
    void printDevByZero() {cout << "Деление на 0";}

public:
    Drob();
    Drob(int pNum, int pDen);

    void input();
    void output() const;
    
    Drob add(const Drob& right) const;
    Drob sub(const Drob& right) const;
    Drob mul(const Drob& right) const;
    Drob div(const Drob& right) const;

};

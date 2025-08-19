#include "Drob.h"
using namespace std;

int Drob::nod(int left, int right)
{
    while (right != 0)
    {
        int temp = right;
        right = left % right;
        left = temp;
    }

    return left;
}

void  Drob::simply()
{
    int div = nod(abs(num), abs(den));
    num /= div;
    den /= div;
}

Drob::Drob() : num(1), den(1) {}

Drob::Drob(int pNum, int pDen) : num(pNum), den(pDen)
{
    if (pDen == 0)
    {
        printDevByZero();
        num = 1;
        den = 1;
    }

    simply();
}

void Drob::input()
{
    cout << "¬ведите числитель: ";
    cin >> num;
    cout << "¬ведите знаминатель: ";
    cin >> den;

    if (den == 0)
    {
        printDevByZero();
        num = 1;
        den = 1;
    }
    simply();
}

void Drob::output() const
{
    cout << num;
    if (den != 1)
    {
        cout << "/" << den;
    }
}

Drob Drob::add(const Drob& right) const { return Drob(num * right.den + right.num * den, den * right.den); }
Drob Drob::sub(const Drob& right) const { return Drob(num * right.den - right.num * den, den * right.den); }
Drob Drob::mul(const Drob& right) const { return Drob(num * right.num, den * right.den); }
Drob Drob::div(const Drob& right) const { return Drob(num * right.den, den * right.num); }

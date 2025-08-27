#include <iostream>
#include "Drob.h"
using namespace std;

Drob createDrob(int a, int b) {
    return Drob(a, b); 
}

int main()
{
    setlocale(LC_ALL, "RU");

    Drob drob1, drob2;
    drob1.input();
    drob2.input();

    drob1.output();
    cout << " + ";
    drob2.output();
    cout << " = ";
    (drob1 + drob2).output();
    cout << endl;

    drob1.output();
    cout << " - ";
    drob2.output();
    cout << " = ";
    (drob1 - drob2).output();
    cout << endl;

    drob1.output();
    cout << " * ";
    drob2.output();
    cout << " = ";
    (drob1 * drob2).output();
    cout << endl;

    drob1.output();
    cout << " / ";
    drob2.output();
    cout << " = ";
    (drob1 / drob2).output();
    cout << endl;

    int num{ 0 }, den{ 1 };
    cout << "Введите числитель: ";
    cin >> num;
    cout << "Введите знаминатель: ";
    cin >> den;
    Drob result = createDrob(num, den);
    cout << "Результат переноса: ";
    result.output();
    cout << endl;

    return 0;
}
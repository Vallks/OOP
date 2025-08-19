#include <iostream>
#include "Drob.h"
using namespace std;

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
    (drob1+drob2).output();
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

    return 0;
}



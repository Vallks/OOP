#include <iostream>
#include "Date.h"

int main() 
{
    setlocale(LC_ALL, "Ru");
    
    Date date1;
    std::cout << "Введите дату (DD.MM.YYYY): ";
    std::cin >> date1;
         
    Date date2;
    date2 = date1;

    std::cout << "data1: " << date1 << std::endl;
    std::cout << "data2 скопированая: " << date2 << std::endl;

    ++date1;
    std::cout << "++: " << date1 << std::endl;
    --date2;
    std::cout << "--: " << date2 << std::endl;

    std::cout << "date1 == date2: " << (date1 == date2) << std::endl;
    std::cout << "date1 != date2: " << (date1 != date2) << std::endl;
    std::cout << "date1 > date2: " << (date1 > date2) << std::endl;
    std::cout << "date1 < date2: " << (date1 < date2) << std::endl;

    date1 += 10;
    std::cout << "date1 += 10: " << date1 << std::endl;

    date1 -= 5;
    std::cout << "date1 -= 5: " << date1 << std::endl;

    std::cout << "Функтор: " << date1() << std::endl;

    return 0;
}

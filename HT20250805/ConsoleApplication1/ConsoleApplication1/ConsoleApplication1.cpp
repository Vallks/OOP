#include <iostream>
#include "House.h"

const int countElem{ 100 };

void displayMenu() {
    std::cout << "\nУправление жильцами дома:\n"
        << "1. Заселить жильца\n"
        << "2. Выселить жильца\n"
        << "3. Вывести жильцов квартиры\n"
        << "4. Скоприровать дом и вывести всех жильцов\n"
        << "5. Выход\n"
        << "Выберите действие: ";
}

int main()
{
    setlocale(LC_ALL, "RU");
    int count(0), choice(0);

    std::cout << "Сколько квартир в Вашем доме: ";
    std::cin >> count;

    House house(count);

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int number;
            std::cout << "Введите номер квартиры: ";
            std::cin >> number;
            Apartment* apartment = house.getApartment(number - 1);
            if (apartment != nullptr)
            {
                std::cout << "Введите фио: ";
                char fio[countElem];
                std::cin.ignore();
                std::cin.getline(fio, countElem);
                Person person{ fio };
                apartment->addPerson(person);
            }
            break;
        }
        case 2:
        {
            int number;
            std::cout << "Введите номер квартиры: ";
            std::cin >> number;
            Apartment* apartment = house.getApartment(number - 1);
            if (apartment != nullptr)
            {
                apartment->print();
                std::cout << "Введите номер жильца: ";
                std::cin >> number;
                apartment->removePerson(number - 1);
            }
            break;
        }
        case 3:
        {
            int number;
            std::cout << "Введите номер квартиры: ";
            std::cin >> number;
            Apartment* apartment = house.getApartment(number - 1);
            if (apartment != nullptr)
            {
                apartment->print();
            }
            break;
        }
        case 4:
        {
            House houseCopy = house;
            std::cout << "\nКопия дома:" << std::endl;
            houseCopy.Print();
            break;
        }
        case 5:
        {
            std::cout << "Всего доброго!";
            break;
        }
        default: std::cout << "Не верный выбор!" << std::endl;
        }
    } while (choice != 5);
    return 0;
}

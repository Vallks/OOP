#include <iostream>
#include <string>
#include "Header.h"

void displayMenu() {
    std::cout << "\nУправление водоемами:\n"
        << "1. Добавить водоем\n"
        << "2. Удалить водоем\n"
        << "3. Вывести информацию о водоемах\n"
        << "4. Сравнить площадь водоемов одного типа\n"
        << "5. Сохранить в текстовый файл\n"
        << "6. Загрузить из текстового файла\n"
        << "7. Сохранить в бинарный файл\n"
        << "8. Загрузить из бинарного файла\n"
        << "9. Выход\n"
        << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "RU");
    int choice = 0;
    ManagerReservoir manager;

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1:
        {
            std::string name, type;
            double width, length, depth;

            std::cout << "Введите данные водоема:\n";
            std::cout << "Название: ";
            std::getline(std::cin, name);

            std::cout << "Тип: ";
            std::getline(std::cin, type);

            std::cout << "Ширина: ";
            std::cin >> width;
            std::cout << "Длина: ";
            std::cin >> length;
            std::cout << "Глубина: ";
            std::cin >> depth;

            manager.addReservoir(Reservoir(name, type, width, length, depth));
            break;
        }
        case 2:
        {
            std::string name;
            std::cout << "Введите название водоема для удаления: ";
            std::getline(std::cin, name);
            manager.removeReservoir(name);
            break;
        }
        case 3:
        {
            std::cout << "Список всех водоемов:\n";
            manager.print();
            break;
        }
        case 4:
        {
            std::string name1, name2;
            std::cout << "Введите название первого водоема: ";
            std::getline(std::cin, name1);
            std::cout << "Введите название второго водоема: ";
            std::getline(std::cin, name2);

            Reservoir* r1 = manager.findReservoirByName(name1);
            Reservoir* r2 = manager.findReservoirByName(name2);

            if (r1 && r2) {
                int result = r1->compareArea(*r2);
                switch (result) {
                case 1:
                    std::cout << name1 << " имеет большую площадь, чем " << name2 << std::endl;
                    break;
                case -1:
                    std::cout << name1 << " имеет меньшую площадь, чем " << name2 << std::endl;
                    break;
                case 0:
                    std::cout << "Водоемы имеют одинаковую площадь" << std::endl;
                    break;
                case -2:
                    std::cout << "Ошибка: водоемы разных типов" << std::endl;
                    break;
                }
            }
            else {
                std::cout << "Один из водоемов не найден!" << std::endl;
            }
            break;
        }
        case 5:
        {
            std::string filename;
            std::cout << "Введите имя файла для сохранения: ";
            std::getline(std::cin, filename);
            manager.saveReservoirs(filename);
            break;
        }
        case 6:
        {
            std::string filename;
            std::cout << "Введите имя файла для загрузки: ";
            std::getline(std::cin, filename);
            manager.loadReservoirs(filename);
            break;
        }
        case 7:
        {
            std::string filename;
            std::cout << "Введите имя бинарного файла для сохранения: ";
            std::getline(std::cin, filename);
            manager.saveReservoirsBinary(filename);
            break;
        }
        case 8:
        {
            std::string filename;
            std::cout << "Введите имя бинарного файла для загрузки: ";
            std::getline(std::cin, filename);
            manager.loadReservoirsBinary(filename);
            break;
        }
        case 9:
        {
            std::cout << "Всего доброго!";
            break;
        }
        default:
            std::cout << "Неверный выбор!" << std::endl;
        }
    } while (choice != 9);

    return 0;
}
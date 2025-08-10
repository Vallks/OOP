#include <iostream>
#include "Phonebook.h"

const int countElem{ 100 };

void displayMenu() {
    std::cout << "\nМеню телефонной книги:\n"
        << "1. Добавить контакт\n"
        << "2. Удалить контакт\n"
        << "3. Найти контакт\n"
        << "4. Показать все контакты\n"
        << "5. Сохранить в файл\n"
        << "6. Загрузить из файла\n"
        << "7. Выход\n"
        << "Выберите действие: ";
}

int main()
{
    setlocale(LC_ALL, "RU");
    PhoneBook phoneBook;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice)
        {
            case 1: 
            {
                phoneBook.add();
                break;
            }
            case 2:
            {
                int ind;
                std::cout << "Введите индекс для удаления: ";
                std::cin >> ind;
                phoneBook.deleteElem(ind);
                break;
            }
            case 3:
            {
                char fio[countElem];
                std::cout << "Введите фио для поиска: ";
                std::cin.ignore();
                std::cin.getline(fio, countElem);
                phoneBook.find(fio);
                break;
            }
            case 4:
            {
                phoneBook.display();
                break;
            }
            case 5:
            {
                char file[countElem];
                std::cout << "Введите путь к файлу: ";
                std::cin.ignore();
                std::cin.getline(file, countElem);
                phoneBook.saveToFile(file);
                break;
            }
            case 6:
            {
                char file[countElem];
                std::cout << "Введите путь к файлу: ";
                std::cin.ignore();
                std::cin.getline(file, countElem);
                phoneBook.loadFromFile(file);
                break;
            }
            case 7:
            {
                std::cout << "Всего доброго!";
                break;
            }
            default: std::cout << "Не верный выбор!" << std::endl;
        }
    }
    while (choice != 7);
    return 0;
}

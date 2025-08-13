#include <iostream>
#include "House.h"

Person::Person(const char* fio) 
{
    if (fio) 
    {
        this->fio = new char[strlen(fio) + 1];
        strcpy_s(this->fio, strlen(fio) + 1, fio);
    }
}

Person::Person(const Person& other) 
{
    if (other.fio) 
    {
        fio = new char[strlen(other.fio) + 1];
        strcpy_s(fio, strlen(other.fio) + 1, other.fio);
    }
}

Person& Person::operator=(const Person& other) 
{
    if (this != &other) 
    {
        delete[] fio;
        if (other.fio) 
        {
            fio = new char[strlen(other.fio) + 1];
            strcpy_s(fio, strlen(other.fio) + 1, other.fio);
        }
        else 
        {
            fio = nullptr;
        }
    }
    return *this;
}

Person::~Person(){ delete[] fio; }

void Person::Print() const 
{
    if (fio)
    {
        std::cout << fio;
    }
    else
    {
        std::cout << "Неизвестный";
    }
}

Apartment::Apartment(const Apartment& other) : count(other.count)
{
    if (count > 0) 
    {
        residents = new Person[count];
        for (int i = 0; i < count; i++) 
{
            residents[i] = other.residents[i];
        }
    }
}

Apartment& Apartment::operator=(const Apartment& other) 
{
    if (this != &other) 
    {
        delete[] residents;
        count = other.count;
        if (count > 0)
        {
            residents = new Person[count];
            for (int i = 0; i < count; ++i) 
            {
                residents[i] = other.residents[i];
            }
        }
        else
        {
            residents = nullptr;
        }
    }
    return *this;
}

Apartment::~Apartment() { delete[] residents; }

void Apartment::addPerson(const Person& resident)
{
    Person* newResidents = new Person[count + 1];
    for (int i = 0; i < count; ++i) 
    {
        newResidents[i] = residents[i];
    }
    newResidents[count] = resident;
    delete[] residents;
    residents = newResidents;
    count++;
    std::cout << "Вписан!" << std::endl;
}

void Apartment::removePerson(int indx)
{
    if (indx < 0 || indx >= count) {
        std::cout << ("Индекс за границей.");
    }

    Person* newResidents = count > 1 ? new Person[count - 1] : nullptr;

    for (int i = 0, j = 0; i < count; ++i) {
        if (i != indx) {
            newResidents[j++] = residents[i];
        }
    }

    delete[] residents;
    residents = newResidents;
    count--;
    std::cout << "Выписан!" << std::endl;
}

void Apartment::print() const 
{
    std::cout << "Квартира (" << count << " жильцов):" << std::endl;
    for (int i = 0; i < count; ++i) 
    {
        std::cout << "  ";
        residents[i].Print();
        std::cout << std::endl;
    }
}

House::House(int count) : count(count) 
{
    if (count > 0) 
    {
        apartments = new Apartment[count];
    }
}

House& House::operator=(const House& other) 
{
    if (this != &other) 
    {
        delete[] apartments;
        count = other.count;
        if (count > 0) 
        {
            apartments = new Apartment[count];
            for (int i = 0; i < count; ++i) 
            {
                apartments[i] = other.apartments[i];
            }
        }
        else 
        {
            apartments = nullptr;
        }
    }
    return *this;
}

House::House(const House& other) : count(other.count) 
{
    if (count > 0) 
    {
        apartments = new Apartment[count];
        for (int i = 0; i < count; ++i) 
        {
            apartments[i] = other.apartments[i];
        }
    }
}

House::~House() { delete[] apartments; }

Apartment* House::getApartment(int index)
{
    if (index < 0 || index >= count) 
    {
        std::cout << ("Индекс за границей.");
        return nullptr;
    }
    return &apartments[index];
}

void House::Print() const 
{
    std::cout << "Дом (" << count << " квартир):" << std::endl;
    for (int i = 0; i < count; ++i)
    {
        std::cout << "Квартира #" << i + 1 << ":" << std::endl;
        apartments[i].print();
    }
}

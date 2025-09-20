#include <iostream>
#include <string>

class Pet {
protected:
    std::string name;
    int age;

public:
    Pet(std::string n, int a) : name(n), age(a) {}

    virtual ~Pet() {}

    virtual void displayInfo() const
    {
        std::cout << "Имя: " << name << std::endl;
        std::cout << "Возраст: " << age << " лет" << std::endl;
    }
};

class Dog : public Pet
{
private:
    std::string size;
    bool isTrained;

public:
    Dog(std::string n, int a, std::string s, bool t) : Pet(n, a), size(s), isTrained(t) {}
    void displayInfo() const override
    {
        std::cout << "=== СОБАКА ===" << std::endl;
        Pet::displayInfo();
        std::cout << "Размер: " << size << std::endl;
        std::cout << "Дрессирована: " << (isTrained ? "Да" : "Нет") << std::endl;
    }
};

class Cat : public Pet
{
private:
    std::string temperament;
   
public:
    Cat(std::string n, int a, std::string t) : Pet(n, a), temperament(t) {}
    void displayInfo() const override
    {
        std::cout << "=== КОШКА ===" << std::endl;
        Pet::displayInfo();
        std::cout << "Характер: " << temperament << std::endl;
    }
};

class Parrot : public Pet
{
private:
    bool canTalk;

public:
    Parrot(std::string n, int a, bool t) : Pet(n, a), canTalk(t) {}
    void displayInfo() const override 
    {
        std::cout << "=== ПОПУГАЙ ===" << std::endl;
        Pet::displayInfo();
        std::cout << "Умеет говорить: " << (canTalk ? "Да" : "Нет") << std::endl;
    }
};

int main()
{
    setlocale(LC_ALL, "RU");
    Dog dog("Бобик", 3, "Крупный", true);
    Cat cat("Мурка", 2, "Игривый");
    Parrot parrot("Кеша", 1, true);

    const int SIZE = 3;
    Pet* pets[SIZE];
    pets[0] = &dog;
    pets[1] = &cat;
    pets[2] = &parrot;

    for (int i = 0; i < SIZE; ++i)
    {
        pets[i]->displayInfo();
    }

    return 0;
}


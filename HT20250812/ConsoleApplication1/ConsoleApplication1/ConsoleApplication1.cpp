#include <iostream>
#include <string>

class Overcoat
{
	std::string type;
	double price{ 0 };
public:
	Overcoat(const std::string& type, double price) : type(type), price(price) {}
	Overcoat(): Overcoat("",0){}
	
	Overcoat operator=(const Overcoat& other)
	{
		if (this != &other) 
		{ 
			type = other.type;
			price = other.price;
		}
		return *this;
	}

	bool operator>(const Overcoat& other) const 
	{
		if (this->type != other.type) 
		{
			std::cout << "Разные типы!" << std::endl;
			return false;
		}
		return this->price > other.price;
	}

	bool operator==(const Overcoat& other) const
	{
		return this->type == other.type;
	}

	void display() const {
		std::cout << "Type: " << type << ", Price: " << price << std::endl;
	}
};

int main() {
	
	setlocale(LC_ALL, "RU");
	
	Overcoat coat1("Пальто", 15000);
    Overcoat coat2("Пальто", 12000);
	Overcoat coat3("Куртка", 8000);
	
	coat1.display();
	coat2.display();
	coat3.display();

    Overcoat coat4;

    coat4 = coat1;
    std::cout << "После присваивания:" << std::endl;
    coat4.display();

    std::cout << "Сравнение типов:" << std::endl;
    std::cout << "1 и 2 : " << (coat1 == coat2) << std::endl;
    std::cout << "1 и 3 : " << (coat1 == coat3) << std::endl;

	std::cout << "Сравнение цен:" << std::endl;
    std::cout << "1 > 2: " << (coat1 > coat2) << std::endl;
    std::cout << "2 > 1: " << (coat2 > coat1) << std::endl;

    return 0;
}

#include <iostream>
#include <fstream>
#include "Header.h"

int Reservoir::compareArea(const Reservoir& other) const
{
	if (!isSameType(other))
	{
		std::cout << "Разные типы водоемов!" << std::endl;
		return -2;
	}
	if (calculateArea() > other.calculateArea()) { return 1; }
	if (calculateArea() < other.calculateArea()) { return 1; }
	return 0;
}

void Reservoir::print() const
{
	std::cout << "Водоем " << name
		<< " тип " << type
		<< " ширина " << width
		<< " длинна " << length
		<< " глубина " << depth
		<< " площадь " << calculateArea()
		<< " объем " << calculateVolume() 
		<<  std::endl;
}

void ManagerReservoir::addReservoir(const Reservoir& reservoir)
{
	Reservoir* newReservoirs = new Reservoir[count + 1];
	for (unsigned int i = 0; i < count; ++i)
	{
		newReservoirs[i] = reservoirs[i];
	}
	newReservoirs[count] = reservoir;
	delete[] reservoirs;
	reservoirs = newReservoirs;
	count++;
}

void ManagerReservoir::removeReservoir(const std::string& name)
{
	unsigned int j = 0, countRemoved = 0;
	for (unsigned int i = 0; i < count; i++) 
	{
		if (reservoirs[i].getName() == name) 
		{
			countRemoved++;
		}
	}
	if (countRemoved > 0)
	{
		Reservoir* newReservoirs = new Reservoir[count - countRemoved];
		for (unsigned int i = 0; i < count; i++)
		{
			if (reservoirs[i].getName() != name)
			{
				newReservoirs[j] = reservoirs[i];
				j++;
			}
		}
		delete[] reservoirs;
		reservoirs = newReservoirs;
		count -= countRemoved;
	}
	
}

void ManagerReservoir::print() const
{
	for (unsigned int i = 0; i < count; i++)
	{
		reservoirs[i].print();
	}
}

void ManagerReservoir::saveReservoirs(const std::string& fileName)
{
    std::ofstream file(fileName);
    if (!file.is_open()) return;

    for (unsigned int i = 0; i < count; ++i) {
        file << reservoirs[i].getName() << "\n"
            << reservoirs[i].getType() << "\n"
            << reservoirs[i].getWidth() << "\n"
            << reservoirs[i].getLength() << "\n"
            << reservoirs[i].getDepth() << "\n";
    }
}

void ManagerReservoir::saveReservoirsBinary(const std::string& fileName) 
{
    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open()) return;

    for (unsigned int i = 0; i < count; ++i) 
    {
        const auto& r = reservoirs[i];
        size_t nameSize = r.getName().size();
        size_t typeSize = r.getType().size();

        file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        file.write(r.getName().c_str(), nameSize);

        file.write(reinterpret_cast<const char*>(&typeSize), sizeof(typeSize));
        file.write(r.getType().c_str(), typeSize);

        double width = r.getWidth();
        double length = r.getLength();
        double depth = r.getDepth();

        file.write(reinterpret_cast<const char*>(&width), sizeof(width));
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file.write(reinterpret_cast<const char*>(&depth), sizeof(depth));
    }
}

void ManagerReservoir::loadReservoirs(const std::string& fileName) 
{
    std::ifstream file(fileName);
    if (!file.is_open()) return;

    delete[] reservoirs;
    reservoirs = nullptr;
    count = 0;

    std::string name, type;
    double width, length, depth;

    while (std::getline(file, name) && std::getline(file, type) && file >> width >> length >> depth) 
    {
        file.ignore();
        addReservoir(Reservoir(name, type, width, length, depth));
    }
}

void ManagerReservoir::loadReservoirsBinary(const std::string& fileName) 
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) return;

    delete[] reservoirs;
    reservoirs = nullptr;
    count = 0;

    while (file.peek() != EOF) 
    {
        size_t nameSize, typeSize;
        file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));

        std::string name(nameSize, '\0');
        file.read(&name[0], nameSize);

        file.read(reinterpret_cast<char*>(&typeSize), sizeof(typeSize));
        std::string type(typeSize, '\0');
        file.read(&type[0], typeSize);

        double width, length, depth;
        file.read(reinterpret_cast<char*>(&width), sizeof(width));
        file.read(reinterpret_cast<char*>(&length), sizeof(length));
        file.read(reinterpret_cast<char*>(&depth), sizeof(depth));

        addReservoir(Reservoir(name, type, width, length, depth));
    }
}

Reservoir* ManagerReservoir::findReservoirByName(const std::string& name) {
    for (size_t i = 0; i < count; ++i) {
        if (reservoirs[i].getName() == name) {
            return &reservoirs[i];
        }
    }
    return nullptr;
}
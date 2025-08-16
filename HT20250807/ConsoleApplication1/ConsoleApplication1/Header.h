#pragma once

#include<string>

class Reservoir
{
	std::string name;
	std::string type;
	double width{ 0 };
	double length{ 0 };
	double depth{ 0 };

public:
	Reservoir(const std::string& pName,const std::string& pType,double pWidth, double pLength, double pDepth) : name(pName), type(pType), width(pWidth), length(pLength), depth(pDepth) {}
	Reservoir(): Reservoir("","",0,0,0) {}
	double calculateVolume() const { return width * length * depth; }
	double calculateArea() const { return width * length; }
	bool isSameType(const Reservoir& other) const { return type == other.type; }
	int compareArea(const Reservoir& other) const;
	std::string getName() const { return name; }
	std::string getType() const { return type; }
	double getWidth() const { return width; }
	double getLength() const { return length; }
	double getDepth() const { return depth; }
	void setName(const std::string& pName) { name = pName; }
	void setType(const std::string& pType) { type = pType; }
	void setWidth(double pWidth) { width = pWidth; }
	void setLength(double pLength) { length= pLength; }
	void setDepth(double pDepth) { depth= pDepth; }
	void print() const;
};

class ManagerReservoir
{
	Reservoir* reservoirs{ nullptr };
	unsigned int count{ 0 };
public:
	ManagerReservoir(): reservoirs(nullptr), count(0){}
	~ManagerReservoir() { delete[] reservoirs; }
	void addReservoir(const Reservoir& reservoir);
	void removeReservoir(const std::string& name);
	void saveReservoirs(const std::string& fileName);
	void saveReservoirsBinary(const std::string& fileName);
	void loadReservoirs(const std::string& fileName);
	void loadReservoirsBinary(const std::string& fileName);
	void print() const;
	Reservoir* findReservoirByName(const std::string& name);
};

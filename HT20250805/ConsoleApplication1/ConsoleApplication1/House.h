#pragma once

class Person
{
	char* fio{ nullptr };
public:

	Person() : fio(nullptr) {}
	Person(const char* fio);
	Person(const Person& other);
	Person& operator=(const Person& other);
	~Person();
	void Print() const;
};

class Apartment
{
	Person* residents{ nullptr };
	int count{ 0 };
public:
	Apartment() : residents(nullptr), count(0) {}
	Apartment(const Apartment& other);
	Apartment& operator=(const Apartment& other);
	~Apartment();
	void addPerson(const Person& resident);
	void removePerson(int indx);
	void print() const;
};

class House
{
	Apartment* apartments{ nullptr };
	int count{ 0 };
public:
	House(int count);
	House(const House& other);
	House& operator=(const House& other);
	~House();
	Apartment* getApartment(int index);
	void Print() const;
};






#pragma once
#include <iostream>

class Contact
{
	char* fio;
	char* homeNumber;
	char* workNumber;
	char* mobileNumber;
	char* info;

public:
	Contact(const char* fio, const char* homeNumber, const char* workNumber, const char* mobileNumber, const char* info);
	~Contact();
	void display() const;
	const char* getFio() const;
	const char* getHomeNumber() const;
	const char* getWorkNumber() const;
	const char* getMobileNumber() const;
	const char* getInfo() const;
};

class PhoneBook
{
	Contact** contacts{ nullptr };
	int count{ 0 };

public:
	
	void add();
	void add(const char* fio, const char* homeNumber, const char* workNumber, const char* mobileNumber, const char* info);
	void display();
	void deleteElem(int ind);
	void find(const char* fio);
	void saveToFile(const char* filename) const;
	void loadFromFile(const char* filename);
	~PhoneBook()
	{
		for (int i = 0; i < count; ++i)
		{
			delete contacts[i];
		}
		delete[] contacts;
	}

};



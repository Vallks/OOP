#include <iostream>
#include <fstream> 
#include "Phonebook.h"
const int countElem{ 100 };

Contact::Contact(const char* fio, const char* homeNumber, const char* workNumber, const char* mobileNumber, const char* info)
{
	this->fio = new char[strlen(fio) + 1];
	strcpy_s(this->fio, strlen(fio) + 1, fio);

	this->homeNumber = new char[strlen(homeNumber) + 1];
	strcpy_s(this->homeNumber, strlen(homeNumber) + 1, homeNumber);

	this->workNumber = new char[strlen(workNumber) + 1];
	strcpy_s(this->workNumber, strlen(workNumber) + 1, workNumber);

	this->mobileNumber = new char[strlen(mobileNumber) + 1];
	strcpy_s(this->mobileNumber, strlen(mobileNumber) + 1, mobileNumber);

	this->info = new char[strlen(info) + 1];
	strcpy_s(this->info, strlen(info) + 1, info);
}

Contact::~Contact()
{
	delete[] fio;
	delete[] homeNumber;
	delete[] workNumber;
	delete[] mobileNumber;
	delete[] info;
}

const char* Contact::getFio() const { return fio; }
const char* Contact::getHomeNumber() const { return homeNumber; }
const char* Contact::getWorkNumber() const { return workNumber; }
const char* Contact::getMobileNumber() const { return mobileNumber; }
const char* Contact::getInfo() const { return info; }

void Contact::display() const
{
	std::cout << std::endl 
		<< "------------------------------------\n"
		<< "ФИО: " << fio << "\n"
		<< "Домашний телефон: " << homeNumber << "\n"
		<< "Рабочий телефон: " << workNumber << "\n"
		<< "Мобильный телефон: " << mobileNumber << "\n"
		<< "Дополнительная информация: " << info << "\n"
		<< "------------------------------------\n";
}

void PhoneBook::add()
{
	char fio[countElem], homeNumber[countElem], workNumber[countElem], mobileNumber[countElem], info[countElem];
	std::cin.ignore();
	std::cout << "Введите ФИО: ";
	std::cin.getline(fio, countElem);
	std::cout << "Введите домашний телефон: ";
	std::cin.getline(homeNumber, countElem);
	std::cout << "Введите рабочий телефон: ";
	std::cin.getline(workNumber, countElem);
	std::cout << "Введите мобильный телефон: ";
	std::cin.getline(mobileNumber, countElem);
	std::cout << "Введите дополнительную информацию: ";
	std::cin.getline(info, countElem);

	if (contacts == nullptr)
	{
		count++;
		contacts = new Contact*[count];
		
		contacts[0] = new Contact(fio, homeNumber, workNumber, mobileNumber, info);
	}
	else
	{
		count++;
		Contact** temp = new Contact * [count];
		for (int i = 0; i < count; i++)
		{
			temp[i] = contacts[i];
		}
		delete[] contacts;

		temp[count-1] = new Contact(fio, homeNumber, workNumber, mobileNumber, info);
		contacts = temp;
	}
}

void PhoneBook::add(const char* fio, const char* homeNumber, const char* workNumber, const char* mobileNumber, const char* info)
{
	if (contacts == nullptr)
	{
		count++;
		contacts = new Contact * [count];

		contacts[0] = new Contact(fio, homeNumber, workNumber, mobileNumber, info);
	}
	else
	{
		count++;
		Contact** temp = new Contact * [count];
		for (int i = 0; i < count; i++)
		{
			temp[i] = contacts[i];
		}
		delete[] contacts;

		temp[count - 1] = new Contact(fio, homeNumber, workNumber, mobileNumber, info);
		contacts = temp;
	}
}

void PhoneBook::display()
{
	if (contacts == nullptr) return;
	
	for (int i = 0; i < count; i++)
	{
		contacts[i]->display();
	}
}

void PhoneBook::deleteElem(int ind)
{
	if (ind >= count || ind < 0)
	{
		std::cout << "Индекс за гарницами!" << std::endl;
		return; 
	}
	if (count == 1)
	{
		delete contacts[0];
		delete[] contacts;
		contacts = nullptr;
		count--;
		std::cout << "Удалено!" << std::endl;
		return;
	}

	Contact** temp = new Contact * [count-1];
	int j = 0;
	for (int i = 0; i < count; i++)
	{
		if (i != ind)
		{
			temp[j] = contacts[i];
			j++;
		}
		else
		{
			delete contacts[i];
		}
	}
	delete[] contacts;
	count--;
	contacts = temp;
	std::cout << "Удалено!" << std::endl;
}

void PhoneBook::find(const char* fio)
{
	bool fined{ false };
	for (int i = 0; i < count; i++)
	{
		if (strcmp(contacts[i]->getFio(), fio) == 0)
		{
			contacts[i]->display();
			fined = true;
		}
	}

	if (!fined)
	{
		std::cout << "Не найдено!" << std::endl;
	}
}

void PhoneBook::saveToFile(const char* filename) const {
	std::ofstream out(filename);
	if (!out) {
		std::cerr << "Не удалось открыть файл для записи.\n";
		return;
	}

	for (int i = 0; i < count; i++) {
		out << contacts[i]->getFio() << "\n"
			<< contacts[i]->getHomeNumber() << "\n"
			<< contacts[i]->getWorkNumber() << "\n"
			<< contacts[i]->getMobileNumber() << "\n"
			<< contacts[i]->getInfo() << "\n";
	}

	out.close();
	std::cout << "Сохранено!" << std::endl;
}

void PhoneBook::loadFromFile(const char* filename) {
	std::ifstream in(filename);
	if (!in.is_open()) {
		std::cerr << "Не удалось открыть файл для чтения.\n";
		return;
	}

	for (int i = 0; i < count; ++i) {
		delete contacts[i];
	}
	delete[] contacts;
	contacts = nullptr;
	count = 0;

	char fio[countElem], homeNumber[countElem],
		workNumber[countElem], mobileNumber[countElem], info[countElem];

	while (in.getline(fio, countElem)) {
		in.getline(homeNumber, countElem);
		in.getline(workNumber, countElem);
		in.getline(mobileNumber, countElem);
		in.getline(info, countElem);

		Contact** newContacts = new Contact * [count + 1];

		for (int i = 0; i < count; ++i) {
			newContacts[i] = contacts[i];
		}

		newContacts[count] = new Contact(fio, homeNumber, workNumber, mobileNumber, info);

		if (contacts) {
			delete[] contacts;
		}

		contacts = newContacts;
		count++;
	}

	in.close();
	std::cout << "Загруужено!" << std::endl;
}
#pragma once
#include <iostream>

class Date
{
	int day{ 1 };
	int month{ 1 };
	int year{ 1 };

	bool isValidDate(int pDay, int pMonth, int pYear);
	void normalize();
	int dayInMonth(int pMonth, int pYear);

public:

	Date(int pDay, int pMonth, int pYear);
	Date() : Date(1, 1, 1) {};
	Date(const Date& other) : day(other.day), month(other.month), year(other.year) {};
	void increaseDay();
	void decreaseDay();
	int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }
	void setDay(int pDay);
	void setMonth(int pMonth);
	void setYear(int pYear);
	Date& operator++();
	Date operator++(int);
	Date& operator--();
	Date operator--(int);
	Date& operator+=(int days);
	Date& operator-=(int days);
	Date& operator=(const Date& other);
	std::string operator()();
	friend bool operator==(const Date& lhs, const Date& rhs);
	friend bool operator!=(const Date& lhs, const Date& rhs);
	friend bool operator<(const Date& lhs, const Date& rhs);
	friend bool operator>(const Date& lhs, const Date& rhs);
	friend bool operator<=(const Date& lhs, const Date& rhs);
	friend bool operator>=(const Date& lhs, const Date& rhs);
	friend std::ostream& operator<<(std::ostream& os, const Date& date);
	friend std::istream& operator>>(std::istream& is, Date& date);	
};

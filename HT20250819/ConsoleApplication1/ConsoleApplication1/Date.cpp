#include <iostream>
#include "Date.h"
#include <string>

bool Date::isValidDate(int pDay, int pMonth, int pYear)
{
    if (pYear < 0 || pMonth < 1 || pMonth > 12 || pDay < 1) return false;

    int days = dayInMonth(pMonth, pYear);
    return pDay <= days;
}

int Date::dayInMonth(int pMonth, int pYear) {
    switch (pMonth) {
    case 2:
        return (pYear % 4 == 0 && (pYear % 100 != 0 || pYear % 400 == 0)) ? 29 : 28;
    case 4: case 6: case 9: case 11:
        return 30;
    default:
        return 31;
    }
}

void Date::normalize() {
    while (day > dayInMonth(month, year)) {
        day -= dayInMonth(month, year);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }

    while (day < 1) {
        month--;
        if (month < 1) {
            month = 12;
            year--;
        }
        day += dayInMonth(month, year);
    }
}

Date::Date(int pDay, int pMonth, int pYear) {
    if (!isValidDate(pDay, pMonth, pYear))
    {
        std::cout << "Неверный формат даты!";
    }
    else
    {
        day = pDay;
        month = pMonth;
        year = pYear;
    } 
}

void Date::increaseDay() 
{
    day++;
    normalize();
}

void Date::decreaseDay() 
{
    day--;
    normalize();
}

void Date::setDay(int pDay)
{
    if (!isValidDate(pDay, month, year))
    {
        std::cout << "Неверный формат даты!";
    }
    else
    {
        day = pDay;
    }
}

void Date::setMonth(int pMonth)
{
    if (!isValidDate(day, pMonth, year))
    {
        std::cout << "Неверный формат даты!";
    }
    else
    {
        month = pMonth;
    }
}

void Date::setYear(int pYear)
{
    if (!isValidDate(day, pYear, year))
    {
        std::cout << "Неверный формат даты!";
    }
    else
    {
        year = pYear;
    }
}

Date& Date::operator++() 
{
    increaseDay();
    return *this;
}

Date Date::operator++(int) 
{
    Date temp(*this);
    increaseDay();
    return temp;
}

Date& Date::operator--() 
{
    decreaseDay();
    return *this;
}

Date Date::operator--(int) 
{
    Date temp(*this);
    decreaseDay();
    return temp;
}

Date& Date::operator+=(int days) 
{
    day += days;
    normalize();
    return *this;
}

Date& Date::operator-=(int days) 
{
    day -= days;
    normalize();
    return *this;
}

Date& Date::operator=(const Date& other) 
{
    if (this != &other) 
    {
        day = other.day;
        month = other.month;
        year = other.year;
    }
    return *this;
}

std::string Date::operator()()
{
    std::string result;
    result = std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
    return result;
}

bool operator==(const Date& lhs, const Date& rhs) 
{
    return lhs.day == rhs.day && lhs.month == rhs.month && lhs.year == rhs.year;
}

bool operator!=(const Date& lhs, const Date& rhs) 
{
    return !(lhs == rhs);
}

bool operator<(const Date& lhs, const Date& rhs) 
{
    if (lhs.year != rhs.year) return lhs.year < rhs.year;
    if (lhs.month != rhs.month) return lhs.month < rhs.month;
    return lhs.day < rhs.day;
}

bool operator>(const Date& lhs, const Date& rhs) 
{
    return rhs < lhs;
}

bool operator<=(const Date& lhs, const Date& rhs) 
{
    return !(lhs > rhs);
}

bool operator>=(const Date& lhs, const Date& rhs) 
{
    return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << date.day << "." << date.month << "." << date.year;
    return os;
}

std::istream& operator>>(std::istream& is, Date& date) 
{
    char dot1, dot2;
    int d, m, y;

    is >> d >> dot1 >> m >> dot2 >> y;

    if (dot1 != '.' || dot2 != '.') 
    {
        std::cout << "Неверный формат даты!";
        return is;
    }

    if (date.isValidDate(d, m, y)) 
    {
        date.day = d;
        date.month = m;
        date.year = y;
    }
    else 
    {
        std::cout << "Неверный формат даты!";
    }

    return is;
}

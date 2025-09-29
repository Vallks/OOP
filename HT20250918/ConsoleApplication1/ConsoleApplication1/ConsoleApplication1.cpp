#include <iostream>
#include <list>
#include <stdexcept>

namespace Exceptions 
{
    class EmptyListException : public std::exception
    {
    public:
        const char* what() const noexcept override
        {
            return "Ошибка: попытка удаления из пустого списка";
        }
    };
}
namespace Containers 
{
    template<typename T>
    class SafeDoublyLinkedList {
    private:
        std::list<T> data;

        void checkEmpty() const
        {
            if (data.empty())
            {
                throw EmptyListException();
            }
        }

    public:
        void pushBack(const T& value)
        {
            data.push_back(value);
        }

        void pushFront(const T& value)
        {
            data.push_front(value);
        }

        void popBack()
        {
            checkEmpty();
            data.pop_back();
        }

        void popFront()
        {
            checkEmpty();
            data.pop_front();
        }

        void remove(const T& value)
        {
            checkEmpty();
            data.remove(value);
        }

        bool empty() const
        {
            return data.empty();
        }

        size_t size() const
        {
            return data.size();
        }

        void print() const
        {
            for (const auto& item : data)
            {
                std::cout << item << " <-> ";
            }
            std::cout << "NULL" << std::endl;
        }
    };
}

int main()
{
    setlocale(LC_ALL, "RU");

    Containers::SafeDoublyLinkedList<int> list;

    list.pushBack(1);
    list.pushBack(2);
    list.pushFront(0);
    list.print(); 

    list.popFront();
    list.popBack();
    list.print(); 

    list.popBack(); 
    try 
    {
        list.popBack(); 
    }
    catch (const Exceptions::EmptyListException& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
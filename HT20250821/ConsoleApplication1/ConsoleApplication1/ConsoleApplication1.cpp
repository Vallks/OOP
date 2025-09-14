#define _CRT_SECURE_NO_WARNINGS  
#include <iostream>
#include <cstring> 

template <typename T>
T findMax(const T arr[], size_t size)
{
    T max = arr[0];
    for (size_t i = 1; i < size; ++i)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

template <>
char* findMax(char* const arr[], size_t size)
{
    char* max = arr[0];
    for (size_t i = 1; i < size; ++i)
    {
        if (strcmp(arr[i], max) > 0)
        {
            max = arr[i];
        }
    }
    return max;
}

template <typename T>
T findMin(const T arr[], size_t size)
{
    T min = arr[0];
    for (size_t i = 1; i < size; ++i)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}

template <>
char* findMin(char* const arr[], size_t size)
{
    char* min = arr[0];
    for (size_t i = 1; i < size; ++i)
    {
        if (strcmp(arr[i], min) < 0)
        {
            min = arr[i];
        }
    }
    return min;
}

template <typename T>
void bubbleSort(T arr[], size_t size)
{
    for (size_t i = 0; i < size - 1; ++i)
    {
        bool swapped = false;
        for (size_t j = 0; j < size - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

template <>
void bubbleSort(char* arr[], size_t size)
{
    for (size_t i = 0; i < size - 1; ++i)
    {
        bool swapped = false;
        for (size_t j = 0; j < size - i - 1; ++j)
        {
            if (strcmp(arr[j], arr[j + 1]) > 0)
            {
                char* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

template <typename T>
int binarySearch(const T arr[], size_t size, const T& value)
{
    int left = 0;
    int right = static_cast<int>(size) - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == value)
        {
            return mid;
        }
        else if (arr[mid] < value)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}

int binarySearch(char* const arr[], size_t size, const char value[])
{
    int left = 0;
    int right = static_cast<int>(size) - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(arr[mid], value);

        if (cmp == 0)
        {
            return mid;
        }
        else if (cmp < 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}

template <typename T>
void replaceElement(T arr[], size_t size, size_t index, const T& newValue)
{
    if (index < size)
    {
        arr[index] = newValue;
    }
}

void replaceElement(char* arr[], size_t size, size_t index, const char newValue[])
{
    if (index < size)
    {
        delete[] arr[index];
        size_t len = strlen(newValue) + 1;
        arr[index] = new char[len];
        strcpy(arr[index], newValue);
    }
}

template <typename T>
void printArray(const T arr[], size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <>
void printArray(char* const arr[], size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << "\"" << arr[i] << "\" ";
    }
    std::cout << std::endl;
}

int main()
{
    setlocale(LC_ALL, "RU");

    int intArr[] = { 5, 2, 8, 1, 9, 3 };
    size_t intSize = sizeof(intArr) / sizeof(intArr[0]);

    std::cout << "Массив int: ";
    printArray(intArr, intSize);
    std::cout << "Max: " << findMax(intArr, intSize) << std::endl;
    std::cout << "Min: " << findMin(intArr, intSize) << std::endl;

    bubbleSort(intArr, intSize);
    std::cout << "Отсортированный: ";
    printArray(intArr, intSize);

    int searchValue = 8;
    int intIndex = binarySearch(intArr, intSize, searchValue);
    std::cout << "Поиск " << searchValue << ": индекс " << intIndex << std::endl;

    replaceElement(intArr, intSize, 2, 100);
    std::cout << "После замены: ";
    printArray(intArr, intSize);

    const size_t strCount = 5;
    char* strings[strCount];

    strings[0] = new char[10];
    strcpy(strings[0], "банан");
    strings[1] = new char[10];
    strcpy(strings[1], "яблоко");
    strings[2] = new char[10];
    strcpy(strings[2], "ананас");
    strings[3] = new char[10];
    strcpy(strings[3], "груша");
    strings[4] = new char[10];
    strcpy(strings[4], "дыня");

    std::cout << "Массив си-строк: ";
    printArray(strings, strCount);

    std::cout << "Max: \"" << findMax(strings, strCount) << "\"" << std::endl;
    std::cout << "Min: \"" << findMin(strings, strCount) << "\"" << std::endl;

    bubbleSort(strings, strCount);
    std::cout << "Отсортированный: ";
    printArray(strings, strCount);

    int strIndex = binarySearch(strings, strCount, "груша");
    std::cout << "Поиск \"груша\": индекс " << strIndex << std::endl;

    replaceElement(strings, strCount, 2, "киви");
    std::cout << "После замены: ";
    printArray(strings, strCount);

    for (size_t i = 0; i < strCount; ++i)
    {
        delete[] strings[i];
    }

    return 0;
}
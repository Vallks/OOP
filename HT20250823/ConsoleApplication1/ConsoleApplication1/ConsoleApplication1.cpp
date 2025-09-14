#include <iostream>

template <typename T>
class Matrix
{
private:
    T** data{ nullptr };
    size_t rows{ 0 };
    size_t cols{ 0 };
    void clearMemory()
    {
        if (data != nullptr)
        {
            for (size_t i = 0; i < rows; ++i)
            {
                delete[] data[i];
            }
            delete[] data;
            data = nullptr;
        }
        rows = 0;
        cols = 0;
    }

    void allocateMemory(size_t r, size_t c)
    {
        rows = r;
        cols = c;
        data = new T * [rows];
        for (size_t i = 0; i < rows; ++i) {
            data[i] = new T[cols];
        }
    }
public:
    Matrix() : data(nullptr), rows(0), cols(0) {}
    Matrix(size_t r, size_t c) : data(nullptr), rows(0), cols(0) 
    {
        allocateMemory(r, c);
    }
    ~Matrix()
    {
        clearMemory();
    }
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }
    void fillFromKeyboard() 
    {
        std::cout << "Введите элементы матрицы " << rows << "x" << cols << ":\n";
        for (size_t i = 0; i < rows; ++i) 
        {
            for (size_t j = 0; j < cols; ++j) 
            {
                std::cout << "Элемент [" << i << "][" << j << "]: ";
                std::cin >> data[i][j];
            }
        }
    }
    void fillRandom()
    {
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j) 
            {
                data[i][j] = rand();
            }
        }
    }

    void display() const 
    {
        std::cout << "Матрица " << rows << "x" << cols << ":\n";
        for (size_t i = 0; i < rows; ++i) 
        {
            for (size_t j = 0; j < cols; ++j) 
            {
                std::cout << data[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    T findMax() const 
    {
        T max = data[0][0];
        for (size_t i = 0; i < rows; ++i) 
        {
            for (size_t j = 0; j < cols; ++j) 
            {
                if (data[i][j] > max) 
                {
                    max = data[i][j];
                }
            }
        }
        return max;
    }

    T findMin() const 
    {
       
        T min = data[0][0];
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (data[i][j] < min) {
                    min = data[i][j];
                }
            }
        }
        return min;
    }

    Matrix operator+(const Matrix& other) const 
    {
        if (rows != other.rows || cols != other.cols) 
        {
            throw std::invalid_argument("Размеры матриц не совпадают для сложения");
        }

        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) 
        {
            for (size_t j = 0; j < cols; ++j) 
            {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }
    
    Matrix operator-(const Matrix& other) const 
    {
        if (rows != other.rows || cols != other.cols) 
        {
            throw std::invalid_argument("Размеры матриц не совпадают для вычитания");
        }

        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) 
        {
            for (size_t j = 0; j < cols; ++j) 
            {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const 
    {
        if (cols != other.rows) 
        {
            throw std::invalid_argument("Количество столбцов первой матрицы должно равняться количеству строк второй");
        }

        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) 
        {
            for (size_t j = 0; j < other.cols; ++j) 
            {
                result.data[i][j] = T();
                for (size_t k = 0; k < cols; ++k) 
                {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator/(T scalar) const 
    {
        if (scalar == 0) 
        {
            throw std::invalid_argument("Деление на ноль");
        }

        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) 
        {
            for (size_t j = 0; j < cols; ++j) 
            {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }
};


int main()
{
    setlocale(LC_ALL, "RU");

    Matrix<int> mat1(2, 3);
    Matrix<int> mat2(2, 3);
    Matrix<int> mat3(3, 2);

    mat1.fillRandom();
    mat2.fillRandom();
    mat3.fillFromKeyboard();

    std::cout << "Матрица 1:\n";
    mat1.display();

    std::cout << "\nМатрица 2:\n";
    mat2.display();

    std::cout << "\nМатрица 3:\n";
    mat3.display();

    std::cout << "\nСложение матриц 1 и 2:\n";
    Matrix<int> sum = mat1 + mat2;
    sum.display();

    std::cout << "\nВычитание матриц 1 и 2:\n";
    Matrix<int> diff = mat1 - mat2;
    diff.display();

    std::cout << "\nУмножение матриц 1 и 3:\n";
    Matrix<int> product = mat1 * mat3;
    product.display();

    std::cout << "\nДеление матрицы 1 на 2:\n";
    Matrix<int> division = mat1 / 2;
    division.display();
    
    return 0;
}
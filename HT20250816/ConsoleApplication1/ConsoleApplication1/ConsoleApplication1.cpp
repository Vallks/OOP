#include <iostream>
class Matrix
{
	int sizeY;
	int sizeX;
	int* data;
	int index2D(int y, int x) const { return y * sizeX + x; }
	int index2D(int y, int x, int sizeXP) const	{ return y * sizeXP + x; }
public:
	Matrix(int sizeYP, int sizeXP): sizeY{ sizeYP }, sizeX{ sizeXP },data{ new int[sizeYP * sizeXP] } {	}
	int operator()(int y, int x) const {return *(data + index2D(y, x));	}
	int& operator()(int y, int x){	return *(data + index2D(y, x));	}
	void deleteColumn(int columnPos)
	{
		--sizeX;
		int* newData{ new int[sizeY * sizeX] };
		int sm = 0;
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x <= sizeX; ++x)
			{
				if (x == columnPos)
				{
					sm++;
				}
				else
				{
					*(newData + index2D(y, x)) =
						*(data + index2D(y, x + sm));
				}
			}
		}
		delete[] data;
		data = newData;
	}
	void addColumn(int columnPos, int* newCol = nullptr)
	{
		int* newData{ new int[sizeY * (sizeX + 1)] };
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				*(newData + index2D(y, x + (x >= columnPos),
					sizeX + 1)) = *(data + index2D(y, x));
			}
			*(newData + index2D(y, columnPos, sizeX + 1)) =
				newCol ? *(newCol + y) : 0;
		}
		delete[] data;
		data = newData;
		++sizeX;
	}
	void deleteRow(int rowPos)
	{
		--sizeY;
		int* newData{ new int[sizeY * sizeX] };
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				*(newData + index2D(y, x)) = *(data + index2D(y + (y >= rowPos),x));
			}
		}
		delete[] data;
		data = newData;
	}
	void addRow(int rowPos, int* newRow = nullptr)
	{
		int* newData{ new int[(sizeY + 1) * sizeX] };
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				*(newData + index2D(y + (y >= rowPos), x)) =
					*(data + index2D(y, x));
			}
		}

			for (int x{ 0 }; x < sizeX; ++x)
			{
				*(newData + index2D(rowPos, x)) =
					newRow ? *(newRow + x) : 0;
			}
			delete[] data;
			data = newData;
			++sizeY;
		}
		void print() const
		{
			for (int y{ 0 }; y < sizeY; ++y)
			{
				for (int x{ 0 }; x < sizeX; ++x)
				{
					std::cout << (*this)(y, x) << '\t';
				}
				std::cout << '\n';
			}
			std::cout << '\n';
		}
		~Matrix() { delete[] data; }
	};
	int main()
	{
		/* Установите значение USER_INPUT в 1 чтоб разрешить
		пользовательский ввод размеров матрицы */
#define USER_INPUT 0;
		int rows{ 3 };
		int columns{ 3 };
		int counter{ 1 };
#if USER_INPUT == 1
		std::cout << "Enter matrix rows count\n";
		std::cin >> rows;
		std::cout << "Enter matrix columns count\n";
		std::cin >> rows;
#endif
		Matrix matrix{ rows, columns };
		for (int y{ 0 }; y < rows; ++y)
		{
			for (int x{ 0 }; x < columns; ++x)
			{
				matrix(y, x) = counter++;
			}
		}
		matrix.print();
		matrix.deleteColumn(2);
		matrix.print();
		int* newColumn{ new int[columns] {11,22,33} };
		matrix.addColumn(0, newColumn);
		matrix.print();
		matrix.deleteRow(2);
		matrix.print();
		int* newRow{ new int[rows] {111,222,333} };
		matrix.addRow(2, newRow);
		matrix.print();
		delete[] newRow;
		delete[] newColumn;
		return 0;
	}

//Создайте консольную версию игры «Виселица».
//Важно:
//■ Слово выбирается компьютером из списка слов.
//■ Список слов находится в файле в зашифрованном виде.
//■ По завершении игры на экран выводится статистика игры :
//• количество времени;
//• количество попыток;
//• искомое слово;
//• буквы игрока.
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <fstream>
#include <iostream>
#include <filesystem> 
#include <stdio.h>

using namespace std;
using namespace filesystem;


class GAME
{
	fstream Fail;
	fstream Fail2;
	//Кол-во попыток
	int Tries = 10;
	//Кол-во угаданных слов
	int CountWords = 0;
	int i = 0;
	string slovo;
	//Загрузка слова
	bool LoadWord(string& word);
	void Game(string& word);
	string code(const string& text, const string& text1);
	void decode(string& word);
	void Delete(const string& path);
public:
	GAME(string& names, string& names2)
	{
		path f = names;
		//Открываем файл
		Fail.open(names, ios_base::in | ios_base::out);
		//Если файл не открылся
		if (!exists(f))
		{
			cout << "Ошибка - файл со словами не создан" << endl;
			exit(1);
		}
		if (!Fail.is_open())
		{
			cout << "Ошибка открытия файла!" << endl;
		}
		//Максимальная длина слова
		string s = " ";
		//Кол-во слов в файле
		static int count = -1;
		if (count == -1)
		{
			//Подсчет количества слов
			while (!Fail.eof())
			{
				getline(Fail, s);
				cout << s << endl;
				count++;
			}
			//Слов нет?
			if (count == 0)
			{
				cout << "Недостаточно слов!" << endl;
				return;
			}
		}
		Fail.clear();
		Fail.seekg(0, ios::beg);
		code(names, names2);
	}
	~GAME()
	{
		Fail.close();
	}
	void Start();

};
// функция осуществляет шифрование методом Цезаря
string GAME::code(const string& text, const string& text1)
{
	string encryptedText = "";
	Fail2.open(text1, ios_base::out);
		if (!Fail.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	else if (Fail.is_open())
	{
		while (getline(Fail, encryptedText))
		{
			for (int i = 0; i < encryptedText.size(); i++)
			{
				encryptedText[i] += 3;
			}
			Fail2 << encryptedText << endl;
			cout << encryptedText << endl;
		}
	}
	Fail2.close();
	Fail2.open(text1, ios_base::in);
	Fail2.clear();
	Fail2.seekg(0, ios::beg);
	Fail.close();
	Delete(text);
	return encryptedText;
}
void GAME::Delete(const string& path)
{
	try
	{
		remove_all(path);
		cout << "Папка/файл удалён: " << path << endl;
	}
	catch (filesystem_error& e)
	{
		cout << "Ошибка: " << e.what() << endl;
	}
}

// функция осуществляет дешифрование методом Цезаря (то же, что и шифрование с обратным сдвигом)
void GAME::decode(string& word)
{
	string encryptedText = " ";
	for (int i = 0; i < word.size(); i++)
	{
		word[i] -= 3;
	}
	cout << word << endl;
}


void GAME::Start()
{
	string Word = " ";

	//Пытаемся загрузить слово
	if (!LoadWord(Word))
	{
		//Если неудачно
		cout << "Ошибка!" << endl;
	}
	GAME::Game(Word);
	char answer;
	//Играем, пока не надоест
	do
	{
		//Если попыток не осталось, то выход
		if (Tries == 0)
		{
			cout << "Количество отгаданных слов: " << CountWords << endl;
			cout << "Слово которое Вы не отгадали: " << Word << endl;
			cout << "Пока-пока" << endl;
			break;
		}
		//Если остались
		cout << "Продолжить ??? (Y/N)\t";
		cin >> answer;

		//Еще играем?
		if (answer == 'Y' || answer == 'y')
			Start();
		else if (answer == 'N' || answer == 'n')
			break;

	} while (answer == 'Y' || answer == 'Y');
}

bool GAME::LoadWord(string& word)
{

	string s = " ";
	//Случайное слово
	int n = rand() % 5 + 1;
	//Поиск слова
	for (int i = 0; i < n; i++)
	{
		getline(Fail2, s);
		cout << s << endl;
	}
	decode(s);

	int wordlen = s.size();
	//Минимальная длина слова 2 буквы
	if (wordlen <= 1)
		return false;
	//Убираем Enter (в DOS'е 2 байта 13 10)
	if (s[wordlen - 1] == 10)
		s[wordlen - 2] = 0;
	else if (s[wordlen - 1] == 13)
		s[wordlen - 1] = 0;
	//Копируем слово
	word = s;
	Fail2.clear();
	Fail2.seekg(0, ios::beg);
	return true;
}
//Игра
void GAME::Game(string& word)
{
	//Перевод в большие буквы	
	transform(word.begin(), word.end(), word.begin(), ::toupper);
	int len = word.size();
	//Строка-копия
	char* copy = new char[len + 1];
	memset(copy, '*', len);
	copy[len] = 0;
	//Алфавит + пробелы
	char letters[52];
	int i, j = 0;
	for (i = 0; i < 26; i++)
	{
		letters[j++] = i + 'A';
		letters[j++] = ' ';
	}
	//Замыкающий ноль
	letters[51] = 0;
	//Буква
	char letter;
	char* pos;
	bool replace = false;
	slovo = "";

	do {
		//Очистка экрана
		system("cls");
		cout << copy << endl << endl;
		cout << letters << endl << endl;
		cout << "Количество попыток: " << Tries << endl
			<< endl;
		cout << "Введите букву из списка:\t";
		cin >> letter;
		slovo += letter;
		//Звуковой сигнал
		Beep(500, 200);
		//if(letter >= 'A' && letter <= 'Z'
		//|| letter >= 'a' && letter <= 'z')
		//Буква?
		if (!isalpha(letter))
		{
			cout << "Нет такой буквы" << endl;
			//Задержка на 1 секунду
			Sleep(1000);
			continue;
		}
		//Перевод буквы в большую
		letter = toupper(letter);
		//Поиск буквы в алфавите
		pos = strchr(letters, letter);
		//Такая буква уже была
		if (pos == 0)
		{
			cout << "Такая буква уже была" << endl;
			Sleep(1000);
			continue;
		}
		else
		{
			//Убираем букву из алфавита
			pos[0] = ' ';
		}
		//Поиск буквы в слове
		for (i = 0; i < len; i++)
		{
			if (word[i] == letter)
			{
				copy[i] = letter;
				replace = true;
			}
		}
		if (replace == false)
			Tries--;
		else
			replace = false;
		//Условие победы
		if (strcmp(word.c_str(), copy) == 0)
		{
			system("cls");
			cout << copy << endl << endl;
			cout << letters << endl << endl;
			cout << "Количество попыток: " << Tries << endl << endl;
			cout << "Поздравляем вы отгадали !!! Слово ->" << word << endl << endl;
			cout << "Буквы которы вы вводили ->" << slovo << endl << endl;
			CountWords++;
			break;
		}
	} while (Tries != 0);
	delete[] copy;
}


using namespace std;

int main()
{
	srand(time(NULL));
	SetConsoleCP(1251);//Функция устанавливает нужную кодовую таблицу на поток ввода
	SetConsoleOutputCP(1251);//на поток вывода
	setlocale(LC_ALL, "Rus");//Русский язык  if (Fail[i] == space || int(Fail[i]) == 32)
	string name = "D:\\old.txt";
	string name1 = "D:\\cod.txt";
	GAME game(name, name1);
	srand(time(0));
	auto start = chrono::high_resolution_clock::now();
	game.Start();
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	cout << endl;
	printf_s("Время которое провели в игре %.2f", duration.count());
	cout << " сек";
	cout << endl;
	return 0;
}
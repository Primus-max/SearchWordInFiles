#include <iostream>
#include <windows.h>
using namespace std;

struct SearchDetails
{
	int line = 0;
	int repetitions = 0;
	char fileName[20];
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Для поиска слова в файлах:\n";

	char searchWord[20];
	cout << "1. Напишите искомое слово: ";
	cin.getline(searchWord, 20);
	cout << endl;
	char path[253];
	cout << "2. Укажите корневую директорию для поиска: ";
	cin.getline(path, 253);
	cout << endl;
	cout << "Будем искать " << searchWord << "По пути " << path;

}

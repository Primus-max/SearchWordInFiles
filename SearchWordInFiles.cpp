#include <iostream>
#include <fstream>
#include <windows.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

struct SearchDetails
{
	int line = 0;
	int repetitions = 0;
	char fileName[20];
};

SearchDetails searchWordIntoFile(ifstream& file, const char* searchWord);
char* getFileNameFromPath(const char* path);

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
	cout << "Будем искать " << searchWord << "По пути " << path << endl;

	if (!fs::exists(path))
		cout << "Ошибка, директория не найдена, проверьте существует ли директория и попробуйте снова";

	for (fs::directory_entry file:fs::directory_iterator(path))
	{
		if (!fs::is_regular_file(file.path()))
			continue;

		ifstream if_file(file.path());
		if (!if_file.is_open())
			continue;

		SearchDetails newDetail = searchWordIntoFile(if_file, searchWord);

		cout << file.path() << endl;
	}

}

SearchDetails searchWordIntoFile(ifstream& file, const char* searchWord) {	

	SearchDetails fileDetail;
	char buff[1024];
	int line = 0;
	while (!file.eof())
	{
		++line;		
		cin.getline(buff, sizeof(buff));

		if (strstr(buff, searchWord)) {
			fileDetail.line = line;
			++fileDetail.repetitions;			
		}
	}

	return fileDetail;
}

char* getFileNameFromPath(const char* path) {
	if (path == NULL)
		return NULL;

	const char* lastSlash = strrchr(path, '/');
	if (!lastSlash)
		lastSlash = strrchr(path, '\\');

	if (lastSlash)
		return (char*)lastSlash + 1;

	return NULL;
}
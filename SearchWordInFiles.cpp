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
char* getFileNameFromPath(const wchar_t* path);

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
		
	int counter = 0;
	for (fs::directory_entry file:fs::directory_iterator(path))
	{
		if (!fs::is_regular_file(file.path()))
			continue;

		ifstream if_file(file.path());
		if (!if_file.is_open())
			continue;

		cout << "Текущий каталог: " << file.path() << endl;

		SearchDetails newDetail = searchWordIntoFile(if_file, searchWord);
		strcpy_s(newDetail.fileName, 20, getFileNameFromPath(file.path().c_str()));

		if (newDetail.repetitions == 0)
			continue;

		cout << "Детальная информация о поиске: " << "\n"
			<< "Слово было найдено на строке: " << newDetail.line << "\n"
			<< "Всего было найдено: " << newDetail.repetitions << " " << " слов" << "\n"
			<< "Слово было найдено в файле: " << newDetail.fileName << endl;		
	}

}

SearchDetails searchWordIntoFile(ifstream& file, const char* searchWord) {	

	SearchDetails fileDetail;
	char buff[1024];
	int line = 0;

	while (!file.eof())
	{
		++line;		
		file.getline(buff, sizeof(buff));
		cout << buff;
		if (strstr(buff, searchWord)) {
			fileDetail.line = line;
			++fileDetail.repetitions;			
		}
	}

	return fileDetail;
}


char* getFileNameFromPath(const wchar_t* path) {
	if (path == NULL)
		return NULL;

	const wchar_t* lastSlash = wcsrchr(path, L'/');
	if (!lastSlash)
		lastSlash = wcsrchr(path, L'\\');

	if (lastSlash)
		return (char*)lastSlash + 1;

	return NULL;
}

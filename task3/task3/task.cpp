//В консоли, когда находимся в папке проекта, идем в папку x64, а оттуда - в папку Debug
//Запускаем task3.exe с именами файлов:
//task3 out.csv
//out.csv - файл, откуда считывается таблица

#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
	std::string file = argv[1];
	std::ifstream ifStream(file), ifStreamN(file);
	std::string line, cell;
	char delimiter = ';';
	long double H = 0.0;
	if (ifStream.is_open()) {
		long double n = 0;
		while (getline(ifStreamN, line))
			n += 1;
		while (getline(ifStream, line)) {
			std::stringstream stringStream(line); // Преобразование строки в поток
			long double H_i = 0.0;
			for (int i = 0; i < 5; i++) {
				getline(stringStream, cell, delimiter);
				long double l = std::stold(cell);
				if (l != 0) H_i -= l / (n - 1) * log2(l / (n - 1));
			}
			H += H_i;
		}
	}
	std::cout << H;
	ifStreamN.close();
	ifStream.close();
	return 0;
}
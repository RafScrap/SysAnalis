#include <fstream> 
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	std::ifstream fileInfo(argv[1]);
	std::ifstream tableC(argv[2]);
	std::string line, cell;
	int x, y;
	char delimiter = ';';
	if (tableC.is_open()) {
		getline(tableC, line); // Считываем строку
		std::stringstream streamCountN(line); // Преобразование строки в поток
		getline(streamCountN, cell, delimiter);
		x = std::stoi(cell);
		getline(streamCountN, cell, delimiter);
		y = std::stoi(cell);
		tableC.close();
	}	

	if (fileInfo.is_open()) {
		for (int i = 0; i < x + 1; i++) {
			getline(fileInfo, line); // Считываем строку
		}
		std::stringstream streamCountN(line); // Преобразование строки в поток
		for (int i = 0; i < y + 1; i++) {
			getline(streamCountN, cell, delimiter);
		}
		std::cout << cell;
	}
	fileInfo.close();
}
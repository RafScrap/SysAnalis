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
		getline(ifStreamN, line);
		while (getline(ifStreamN, line))
			n += 1;
		getline(ifStream, line);
		while (getline(ifStream, line)) {
			std::stringstream stringStream(line); // Преобразование строки в поток
			long double H_i = 0.0;
			getline(stringStream, cell, delimiter);
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
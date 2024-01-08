#include <iostream> 
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

double truncDouble(double x) {
	return std::trunc(x * 100) * 0.01;
}

int main(int argc, char* argv[]) {
	unsigned int n1 = 6, n2 = 6;
	unsigned int count = n1 * n2;
	double HA = 0, HB = 0, HAB = 0, H_A_B = 0, I_A_B = 0;
	std::map<unsigned int, std::vector <unsigned int>> matrix;
	std::map<unsigned int, unsigned int> countB;
	std::vector <unsigned int> countA = std::vector <unsigned int>(n1 + n2 - 1, 0);
	std::vector <double> P_A = std::vector <double>(n1 + n2 - 1, 0);
	std::vector <double> H = std::vector <double>(n1 + n2 - 1, 0);

	for (int i = 0; i < n1; i++) {
		for (int k = 0; k < n2; k++) {
			unsigned int umn = (i + 1) * (k + 1);
			if (matrix.find(umn) == matrix.end()) {
				matrix[umn] = std::vector <unsigned int> (n1 + n2 - 1, 0);
			}
			countB[umn] += 1;
			matrix[umn][i + k] += 1;
			countA[i + k] += 1;
		}
	}

	for (int i = 0; i < countA.size(); i++) {
		P_A[i] = (double)countA[i] / count;
		HA -= P_A[i] * log2(P_A[i]);
	}
	for (auto i = countB.begin(); i != countB.end(); i++) {
		double P = (double)i->second / count;
		HB -= P * log2(P);
	}

	for (auto i = matrix.begin(); i != matrix.end(); i++) {
		for (int k = 0; k < matrix[i->first].size(); k++) {
			if (matrix[i->first][k] != 0) {
				double P = (double)matrix[i->first][k] / count;
				HAB -= P * log2(P);
				P = (double)matrix[i->first][k] / countA[k];
				H[k] -= P * log2(P);
			}
		}
	}
	for (int i = 0; i < H.size(); i++) {
		H_A_B += H[i] * P_A[i];
	}
	I_A_B = HB - H_A_B;
	std::cout << truncDouble(HAB) << " " << truncDouble(HA) << " " << truncDouble(HB) << " " << truncDouble(H_A_B) << " " 
		<< truncDouble(I_A_B) << "\n";
	system("pause");
	return 0;
}
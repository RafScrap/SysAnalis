//В консоли, когда находимся в папке task2, идем в папку x64, а оттуда - в папку Debug
//Как это сделать в Windows: cd ./x64/Debug
//Запускаем task2.exe с именами файлов:
//task2 in.csv out.csv
//out.csv - файл для вывода таблицы, его можно поменять по вашему усмотрению

#include <fstream> 
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(vector<int> a, vector<int> b) {
	return a[0] < b[0];
}

vector<vector<int>> readCSV(std::string file) {
	std::ifstream ifStream(file);
	std::string line, cell1, cell2;
	vector <vector<int>> graph;
	char delimiter = ';';
	if (ifStream.is_open()) {
		while (getline(ifStream, line)) {
			std::stringstream stringStream(line); // Преобразование строки в поток
			getline(stringStream, cell1, delimiter);
			getline(stringStream, cell2, delimiter);
			vector <int> pair = { std::stoi(cell1) - 1, std::stoi(cell2) - 1 };
			graph.push_back(pair);
		}
	}
	ifStream.close();
	return graph;
}

void writeCSV(std::string file, vector <vector<vector<int>>>& nodes) {
	ofstream fout(file);
	std::string line, cell1, cell2;
	char delimiter = ';';
	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes[i].size(); j++) {
			fout << nodes[i][j].size() << delimiter;
		}
		fout << endl;
	}
	fout.close();
	return;
}

int maxNode(vector<vector<int>>& spisok) {
	int maxNode = 0;
	for (int i = 0; i < spisok.size(); i++) {
		maxNode = max(maxNode, max(spisok[i][0], spisok[i][1]));
	}
	return maxNode;
}

void nodes12_and_G12(vector<vector<int>>& graph, vector <vector<bool>>& G, vector <vector<vector<int>>> nodes) {
	for (int i = 0; i < graph.size(); i++) {
		G[0][graph[i][0]] = true;
		G[1][graph[i][1]] = true;
		nodes[graph[i][0]][0].push_back(graph[i][1]);
		nodes[graph[i][1]][1].push_back(graph[i][0]);
	}
}

void G34(vector<vector<int>>& graph, vector <vector<bool>>& G) {
	for (int i = 0; i < graph.size(); i++) {
		if (G[1][graph[i][0]]) {
			G[3][graph[i][1]] = true;
		}
		if (G[0][graph[i][1]]) {
			G[2][graph[i][0]] = true;
		}
	}
}

void nodes3(vector<vector<int>>& graph, vector <vector<vector<int>>>& nodes, int parent, int source) {
	for (int i = 0; i < graph.size(); i++) {
		if (graph[i][0] == parent) {
			nodes[source][2].push_back(graph[i][1]);
			nodes3(graph, nodes, graph[i][1], source);
		}
	}
}

void nodes4(vector<vector<int>>& graph, vector <vector<vector<int>>>& nodes, int child, int source) {
	for (int i = 0; i < graph.size(); i++) {
		if (graph[i][1] == child) {
			nodes[source][3].push_back(graph[i][0]);
			nodes4(graph, nodes, graph[i][0], source);
		}
	}
}

void nodes5(vector<vector<int>>& graph, vector <vector<vector<int>>>& nodes) {
	int nodeNow = graph[0][0];
	for (int i = 0; i < graph.size(); i++) {
		for (int j = i + 1; j < graph.size() && graph[i][0] == graph[j][0]; i++) {
			nodes[graph[j][1]][4].push_back(graph[i][1]);
			nodes[graph[i][1]][4].push_back(graph[j][1]);
		}
	}
}

void G5(vector<vector<int>>& graph, vector <vector<bool>>& G) {
	for (int i = 0; i < graph.size() - 1; i++) {
		if (graph[i][0] == graph[i + 1][0]) {
			G[4][graph[i][1]] = true;
			G[4][graph[i + 1][1]] = true;
		}
	}
}

int main(int argc, char* argv[]) {
	std::string file = argv[1];
	vector<vector<int>> graph = readCSV(file);
	int countNodes = maxNode(graph) + 1;
	vector <vector<bool>> G = vector <vector<bool>>(5, vector<bool>(countNodes, false));
	vector <vector<vector<int>>> nodes = vector <vector<vector<int>>>(countNodes, vector<vector<int>>(5, vector <int>(0)));
	nodes12_and_G12(graph, G, nodes);
	G34(graph, G);
	std::sort(graph.begin(), graph.end(), cmp);
	G5(graph, G);
	for (int i = 0; i < G.size(); i++) {
		cout << "Nodes with G" << i + 1 << ": ";
		for (int j = 0; j < G[i].size(); j++) {
			if (G[i][j]) {
				cout << j + 1 << " ";
			}
		}
		cout << endl;
	}
	vector <bool> nodeWas3 = vector<bool>(countNodes, false);
	vector <bool> nodeWas4 = vector<bool>(countNodes, false);
	for (int i = 0; i < graph.size(); i++) {
		if (!nodeWas3[graph[i][0]]) {
			nodeWas3[graph[i][0]] = true;
			nodes3(graph, nodes, graph[i][0], graph[i][0]);
		}
		if (!nodeWas4[graph[i][1]]) {
			nodeWas4[graph[i][0]] = true;
			nodes4(graph, nodes, graph[i][1], graph[i][1]);
		}
	}
	nodes5(graph, nodes);
	for (int i = 0; i < nodes.size(); i++) {
		cout << "Node " << i + 1 << ":\n";
		for (int j = 0; j < nodes[i].size(); j++) {
			cout << "G" << j + 1 << ": ";
			for (int k = 0; k < nodes[i][j].size(); k++) {
				cout << nodes[i][j][k] + 1 << " ";
			}
			cout << endl;
		}
	}
	writeCSV(argv[2], nodes);
	return 0;
}
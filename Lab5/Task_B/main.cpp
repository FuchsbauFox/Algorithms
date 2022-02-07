#include <iostream>
#include <fstream>

using namespace std;

bool  Check(int** Tree, int i, int max, int min, bool flag) {
	int max_buf = max, min_buf = min;
	if (Tree[i][1] != 0) {
		max_buf = Tree[i][0];
		if (!Check(Tree, Tree[i][1] - 1, max_buf, min, flag))
			flag = false;
		if (max <= min)
			return (Tree[i][0] < max && flag) ? true : false;
	}
	if (Tree[i][2] != 0) {
		min_buf = Tree[i][0];
		if (!Check(Tree, Tree[i][2] - 1, max, min_buf, flag))
			flag = false;
		if (max <= min)
			return (Tree[i][0] < max && flag) ? true : false;
	}
	return (Tree[i][0] < max && Tree[i][0] > min && flag) ? true : false;
}

int main() {
	ifstream fin("check.in");
	ofstream fout("check.out");
	int n;
	fin >> n;
	int** Tree = new int* [n];
	for (int i = 0; i < n; i++) {
		Tree[i] = new int[3];
		fin >> Tree[i][0] >> Tree[i][1] >> Tree[i][2];
	}
	if (n == 0)
		fout << "YES";
	else {
		Check(Tree, 0, 1000000001, -1000000001, true) ? fout << "YES" : fout << "NO";
	}
	fin.close();
	fout.close();
	return 0;
}
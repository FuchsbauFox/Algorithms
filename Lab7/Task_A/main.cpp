#include <iostream>
#include <fstream>

using namespace std;

int Height(int** Tree, int i, int left, int right) {
    if (Tree[i][1] != 0) {
        left = Height(Tree, Tree[i][1] - 1, left, right);
        Tree[i][3] = right - left;
    }
    else
        left = 0;
    if (Tree[i][2] != 0) {
        right = Height(Tree, Tree[i][2] - 1, left, right);
        Tree[i][3] = right - left;
    }
    else
        right = 0;
    return (right > left) ? 1 + right : 1 + left;
}

int Balance(int** Tree, int i, int left, int right) {
    if (Tree[i][3] != 200001) {
        return Tree[i][3];
    }
    if (Tree[i][1] != 0)
        left = Height(Tree, Tree[i][1] - 1, left, right);
    else
        left = 0;
    if (Tree[i][2] != 0)
        right = Height(Tree, Tree[i][2] - 1, left, right);
    else
        right = 0;
    return right - left;
}

int main() {
    ifstream fin("balance.in");
    ofstream fout("balance.out");
    int n, left = 0, right = 0;
    fin >> n;
    int** Tree = new int* [n];
    for (int i = 0; i < n; i++) {
        Tree[i] = new int[4];
        fin >> Tree[i][0] >> Tree[i][1] >> Tree[i][2];
        Tree[i][3] = 200001;
    }
    if (n == 0)
        fout << 0;
    else {
        for (int i = 0; i < n; i++) {
            fout << Balance(Tree, i, left, right) << endl;
        }
    }
    fin.close();
    fout.close();
    return 0;
}
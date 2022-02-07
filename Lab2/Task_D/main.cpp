#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void antiQuickSort(vector<int> &antiArray, int size) {
    for (int i = 2; i < size; i++) {
        swap(antiArray[i], antiArray[i / 2]);
    }
}

int main() {
    int size;
    ifstream fin("antiqs.in");
    ofstream fout("antiqs.out");
    fin >> size;
    vector<int> antiArr(size);
    for (int i = 0; i < size; i++) {
        antiArr[i] = i + 1;
    }
    antiQuickSort(antiArr, size);
    for (int i = 0; i < size; i++) {
        fout << antiArr[i] << " ";
    }
    return 0;
}
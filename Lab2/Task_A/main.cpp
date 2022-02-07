#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void merge(vector<int>& array, int left, int middle, int right) {
    int it_left = 0;
    int it_right = 0;
    vector <int> buffer;
    while (buffer.size() < right - left) {
        if (it_left + left >= middle || (it_right + middle < right && array[it_right + middle] <= array[it_left + left])) {
            buffer.push_back(array[it_right + middle]);
            ++it_right;
        }
        else {
            buffer.push_back(array[it_left + left]);
            ++it_left;
        }
    }
    for (int i = 0; i < it_left + it_right; i++)
        array[left + i] = buffer[i];
}

void mergeSort(vector <int>& array, int left, int right) {
    if (right - left < 2)
        return;
    mergeSort(array, left, left + (right - left) / 2);
    mergeSort(array, left + (right - left) / 2, right);
    merge(array, left, left + (right - left) / 2, right);
}

int main() {
    int size, element;
    ifstream fin("sort.in");
    ofstream fout("sort.out");
    fin >> size;
    vector <int> arr;
    while (fin >> element) {
        arr.push_back(element);
    }
    mergeSort(arr, 0, size);
    for (int i = 0; i < size; i++) {
        fout << arr[i] << " ";
    }
    return 0;
}
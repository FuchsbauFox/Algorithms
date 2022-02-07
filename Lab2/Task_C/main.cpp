#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void merge(vector<int>& array, int left, int middle, int right, long long int& inversions) {
    int it_left = 0;
    int it_right = 0;
    vector <int> buffer;
    while (buffer.size() < right - left) {
        if (it_left + left >= middle || (it_right + middle < right && array[it_right + middle] < array[it_left + left])) {
            buffer.push_back(array[it_right + middle]);
            ++it_right;
            inversions += (long long int)middle - (long long int)it_left - (long long int)left;
        }
        else {
            buffer.push_back(array[it_left + left]);
            ++it_left;
        }
    }
    for (int i = 0; i < it_left + it_right; i++)
        array[left + i] = buffer[i];
}

void mergeSort(vector <int>& array, int left, int right, long long int& inversions) {
    if (right - left < 2)
        return;
    mergeSort(array, left, left + (right - left) / 2, inversions);
    mergeSort(array, left + (right - left) / 2, right, inversions);
    merge(array, left, left + (right - left) / 2, right, inversions);
}

int main() {
    long long int invers = 0;
    int size;
    ifstream fin("inversions.in");
    ofstream fout("inversions.out");
    fin >> size;
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        fin >> arr[i];
    }
    mergeSort(arr, 0, size, invers);
    fout << invers;
    return 0;
}
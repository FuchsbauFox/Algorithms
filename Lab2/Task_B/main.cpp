#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Sportsman {
	string country;
	string surname;
};

void merge(vector<Sportsman>& array, int left, int middle, int right) {
    int it_left = 0;
    int it_right = 0;
    vector <Sportsman> buffer;
    while (buffer.size() < right - left) {
        if (it_left + left >= middle || (it_right + middle < right && array[it_right + middle].country < array[it_left + left].country)) {
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

void mergeSort(vector <Sportsman>& array, int left, int right) {
    if (right - left < 2)
        return;
    mergeSort(array, left, left + (right - left) / 2);
    mergeSort(array, left + (right - left) / 2, right);
    merge(array, left, left + (right - left) / 2, right);
}

int main() {
	int size;
	string element = "";
	ifstream fin("race.in");
	ofstream fout("race.out");
	fin >> size;
	vector<Sportsman> sportsmans(size);
	for (int i = 0; i < size; i++) {
		fin >> sportsmans[i].country >> sportsmans[i].surname;
	}
    mergeSort(sportsmans, 0, size);
	for (int i = 0; i < size; i++) {
        if (element != sportsmans[i].country)
            fout << "=== " << sportsmans[i].country << " ===\n";
        element = sportsmans[i].country;
		fout << sportsmans[i].surname << "\n";
	}
	return 0;
}
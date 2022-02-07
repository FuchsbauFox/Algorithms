#include "iostream"
#include <fstream>

using namespace std;

void RadixSort(string *array, int size, int lenght, int phase)
{
	lenght--;
	if (phase == 0) {
		return;
	}
	string** buffer = new string * [(int)26];
	int it_buffer[26] = { 0 };
	for (int i = 0; i < 26; i++) {
		buffer[i] = new string[(int)size];
	}
	for (int j = 0; j < size; j++) {
		buffer[(int)array[j][lenght] - 97][it_buffer[(int)array[j][lenght] - 97]] = array[j];
		it_buffer[(int)array[j][lenght] - 97]++;
	}
	int current = 0;
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < it_buffer[i]; j++) {
			array[current] = buffer[i][j];
			current++;
		}
	}
	for (int i = 0; i < 26; i++) {
		delete[] buffer[i];
	}
	delete[] buffer;
	if (it_buffer[0] != size) {
		RadixSort(array, size, lenght, phase - 1);
	}
}

int main()
{
    int n, k, m;
	ifstream fin("radixsort.in");
	ofstream fout("radixsort.out");
	fin >> n >> m >> k;
	string* arr = new string[(int)n];
	for (int i = 0; i < n; i++) {
		fin >> arr[i];
	}
	RadixSort(arr, n, m, k);
	for (int i = 0; i < n; i++) {
		fout << arr[i] << endl;
	}
	fin.close();
    fout.close();
    return 0;
}
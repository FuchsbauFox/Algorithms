#include <iostream>
#include <fstream>

using namespace std;

int Left(int i) {
	return 2 * i + 1;
}

int Right(int i) {
	return 2 * i + 2;
}

void Heapify(int* array, int heap_size, int i) {
	int l = Left(i), r = Right(i), temp;
	if (l < heap_size && array[l] > array[i]) {
		temp = l;
	}
	else {
		temp = i;
	}
	if (r < heap_size && array[r] > array[temp]) {
		temp = r;
	}
	if (temp != i) {
		swap(array[i], array[temp]);
		Heapify(array, heap_size, temp);
	}
}

void Build_Max_Heap(int* array, int heap_size) {
	for (int i = heap_size / 2 - 1; i >= 0; i--) {
		Heapify(array, heap_size, i);
	}
}

void HeapSort(int* array, int heap_size) {
	Build_Max_Heap(array, heap_size);
	for (int i = heap_size; i >= 1; i--) {
		cout << "\n==== Array before ====\n";
		for (int j = 0; j < 10; j++) {
			cout << array[j] << " ";
		}
		cout << "\n==== Array after ====\n";
		for (int j = 0; j < 10; j++) {
			cout << array[j] << " ";
		}
		swap(array[0], array[i]);
		heap_size--;
		Heapify(array, heap_size, 0);
	}
}

int main() {
	int n;
	ifstream fin("sort.in");
	ofstream fout("sort.out");
	fin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		fin >> arr[i];
	}
	HeapSort(arr, n);
	for (int i = 0; i < n; i++) {
		fout << arr[i] << " ";
	}
	fin.close();
	fout.close();
	return 0;
}
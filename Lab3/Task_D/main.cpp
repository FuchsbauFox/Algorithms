#include <iostream>
#include <fstream>
#include <string>

using namespace std;

static const int MAX_SIZE = 1000000;

struct PriorityQueue {
	int val;
	int it_val;
} queue[MAX_SIZE];

int Left(int i) {
	return 2 * i + 1;
}

int Right(int i) {
	return 2 * i + 2;
}

void Heapify(PriorityQueue* array, int head, int tail, int i) {
	int l = Left(i) + head, r = Right(i) + head, temp;

	if (l < tail && array[l].val < array[i + head].val) {
		temp = l;
	}
	else {
		temp = i + head;
	}
	if (r < tail && array[r].val < array[temp].val) {
		temp = r;
	}
	if (temp != i + head) {
		swap(array[i + head], array[temp]);
	}
}

void Build_Min_Heap(PriorityQueue* array, int head, int tail) {
	for (int i = (tail - head) / 2 - 1; i >= 0; i--) {
		Heapify(array, head, tail, i);
	}
}

void Push(PriorityQueue* arr, int& head, int& tail, int value, int it) {
	if (head == tail) {
		if (head == MAX_SIZE - 1) {
			head = 0;
		}
		else if (empty(queue)) {
			head++;
		}
	}
	arr[tail].val = value;
	arr[tail].it_val = it;
	if (tail == MAX_SIZE) {
		tail = 0;
	}
	else {
		tail++;
	}
}

int Extract_Min(PriorityQueue* arr, int& head, int& tail) {
	if (tail == head || empty(queue)) {
		return 1000000001;
	}
	if (head == MAX_SIZE - 1) {
		head = 0;
		return queue[MAX_SIZE - 1].val;
	}
	else {
		head++;
		return queue[head - 1].val;
	}
}

void Decrease_Key(PriorityQueue* arr, int x, int y, int& head, int& tail) {
	for (int i = head; i < tail; i++) {
		if (arr[i].it_val == x) {
			arr[i].val = y;
		}
	}
}

int main() {
	string command;
	int size = 0, head = 0, tail = 0, x, del, y, counter = 0;
	ifstream fin("priorityqueue.in");
	ofstream fout("priorityqueue.out");
	while (fin >> command) {
		counter++;
		if (command == "push") {
			fin >> x;
			Push(queue, head, tail, x, counter);
		}
		if (command == "extract-min") {
			del = Extract_Min(queue, head, tail);
			if (del == 1000000001) {
				fout << "*\n";
			}
			else {
				fout << del << "\n";
			}
		}
		if (command == "decrease-key") {
			fin >> x >> y;
			Decrease_Key(queue, x, y, head, tail);
		}
		Build_Min_Heap(queue, head, tail);
	}
	fin.close();
	fout.close();
	return 0;
}
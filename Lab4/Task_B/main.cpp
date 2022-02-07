#include <iostream>
#include <fstream>

using namespace std;

class Queue {
private:
	int variable;
	Queue* next;
public:
	Queue();
	~Queue();

	void Push_back(Queue*&, int);
	int Pop_first(Queue*&);
	void Print();
};

Queue::Queue()
	: next(NULL), variable(0) {}

Queue::~Queue() {
	delete next;
}

void Queue::Push_back(Queue*& current, int variable) {
	Queue* fresh = new Queue;
	current->variable = variable;
	current->next = fresh;
	current = fresh;
}

void Queue::Print() {
	Queue* current = this;
	while (current->next != NULL) {
		cout << current->variable << endl;
		current = current->next;
	}
}

int Queue::Pop_first(Queue*& first) {
	Queue* foll = first->next;
	int temp = first->variable;

	first->next = NULL;
	delete first->next;
	int* it = &first->variable;
	delete it;

	first = foll;
	return temp;
}

int main() {
	int size, value;
	string command;
	Queue* queue = new Queue;
	Queue* head = queue;
	ifstream fin("queue.in");
	ofstream fout("queue.out");
	fin >> size;
	for (int i = 0; i < size; i++) {
		fin >> command;
		if (command == "+") {
			fin >> value;
			queue->Push_back(queue, value);
		}
		else {
			fout << queue->Pop_first(head) << endl;
		}
	}
	fin.close();
	fout.close();
	delete head;
	return 0;
}
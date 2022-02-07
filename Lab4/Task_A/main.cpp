#include <iostream>
#include <fstream>

using namespace std;

class Stack {
private:
	int variable;
	Stack* previous;
public:
	Stack();
	~Stack();

	void Push_back(Stack*&, int);
	int Pop_back(Stack*&);
	void Print();
};

Stack::Stack()
	: previous(NULL) {}

Stack::~Stack() {
	delete previous;
}

void Stack::Push_back(Stack*& current, int variable) {
	Stack* fresh = new Stack;
	current->variable = variable;
	fresh->previous = current;
	current = fresh;
}

void Stack::Print() {
	Stack *current = this->previous;
	while (current != NULL) {
		cout << current->variable << endl;
		current = current->previous;
	}
}

int Stack::Pop_back(Stack*& current) {
	Stack* last = current->previous;
	int temp = last->variable;

	current->previous = NULL;
	delete current->previous;
	last->variable = 0;
	int* it = &current->variable;
	delete it;

	current = last;
	return temp;
}

int main() {
	int size, value;
	string command;
	Stack* stack = new Stack;
	ifstream fin("stack.in");
	ofstream fout("stack.out");
	fin >> size;
	for (int i = 0; i < size; i++) {
		fin >> command;
		if (command == "+") {
			fin >> value;
			stack->Push_back(stack, value);
		}
		else {
			fout << stack->Pop_back(stack) << endl;
		}
	}
	fin.close();
	fout.close();
	delete stack;
	return 0;
}
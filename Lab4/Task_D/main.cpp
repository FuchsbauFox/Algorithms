#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Stack {
private:
	int variable;
	Stack* previous;
public:
	Stack();
	~Stack();

	void Push(Stack*&, int);
	void Pop(Stack*&);
	void Procedure_Sum();
	void Procedure_Sub();
	void Procedure_Multi();
	char Top();
	bool Empty();
	void Print();
	int getVar();
};

Stack::Stack()
	: previous(NULL), variable() {}

Stack::~Stack() {
	delete previous;
}

void Stack::Push(Stack*& current, int variable) {
	Stack* fresh = new Stack;
	current->variable = variable;
	fresh->previous = current;
	current = fresh;
}

void Stack::Print() {
	Stack* current = this->previous;
	while (current != NULL) {
		cout << current->variable << endl;
		current = current->previous;
	}
}

void Stack::Pop(Stack*& current) {
	Stack* last = current->previous;

	current->previous = NULL;
	delete current->previous;
	last->variable = 0;
	int* it = &current->variable;
	delete it;

	current = last;
}

char Stack::Top() {
	if (this->previous == NULL) {
		return '\0';
	}
	return this->previous->variable;
}

bool Stack::Empty() {
	return (this->previous == NULL ? true : false);
}

void Stack::Procedure_Sum() {
	this->previous->previous->variable += this->previous->variable;
}

void Stack::Procedure_Sub() {
	this->previous->previous->variable -= this->previous->variable;
}

void Stack::Procedure_Multi() {
	this->previous->previous->variable *= this->previous->variable;
}

int Stack::getVar() {
	return this->previous->variable;
}

int main() {
	string count;
	Stack* stack = new Stack;
	ifstream fin("postfix.in");
	ofstream fout("postfix.out");
	while (fin >> count) {
		if (count == "+") {
			stack->Procedure_Sum();
			stack->Pop(stack);
		}
		else if (count == "-") {
			stack->Procedure_Sub();
			stack->Pop(stack);
		}
		else if (count == "*") {
			stack->Procedure_Multi();
			stack->Pop(stack);
		}
		else {
			stack->Push(stack, atoi(count.c_str()));
		}
	}
	fout << stack->getVar();
	delete stack;
	fin.close();
	fout.close();
	return 0;
}
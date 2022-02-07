#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Stack {
private:
	char variable;
	Stack* previous;
public:
	Stack();
	~Stack();

	void Push(Stack*&, char);
	void Pop(Stack*&);
	char Top();
	bool Empty();
	void Print();
};

Stack::Stack()
	: previous(NULL), variable('\0') {}

Stack::~Stack() {
	delete previous;
}

void Stack::Push(Stack*& current, char variable) {
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
	char* it = &current->variable;
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

inline bool LeftBracket(char c) {
	return ('(' == c || '[' == c);
}

inline bool Fit(char left_bracket, char right_bracket) {
	return ('(' == left_bracket && ')' == right_bracket) || ('[' == left_bracket && ']' == right_bracket);
}

int main() {
	string line;
	ifstream fin("brackets.in");
	ofstream fout("brackets.out");
	while (fin >> line) {
		Stack* stack = new Stack;
		for (string::const_iterator it = line.begin(); it != line.end(); ++it) {
			if (LeftBracket(*it)) {
				stack->Push(stack, *it);
			}
			else if (Fit(stack->Top(), *it)) {
				stack->Pop(stack);
			}
			else {
				stack->Push(stack, *it);
				break;
			}
		}
		fout << (stack->Empty() ? "YES\n" : "NO\n");
		delete stack;
	}
	fin.close();
	fout.close();
	return 0;
}
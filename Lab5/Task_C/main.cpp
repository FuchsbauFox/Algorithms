#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template<typename T>
class Tree {
private:
	T key;
	Tree* left;
	Tree* right;
public:
	Tree(T);
	Tree* Insert(T);
	Tree* Remove(T);
	Tree* Min();
	bool Exists(T);
	T Next(T);
	T Prev(T);
};

template<typename T>
Tree<T>::Tree(T k)
	: key(k), left(NULL), right(NULL) {}

template<typename T>
Tree<T>* Tree<T>::Insert(T k) {
	if (this == NULL)
		return new Tree(k);
	else if (k < key)
		left = left->Insert(k);
	else if (k > key)
		right = right->Insert(k);
	return this;
}

template<typename T>
Tree<T>* Tree<T>::Min() {
	if (left == NULL)
		return this;
	return left->Min();
}

template<typename T>
Tree<T>* Tree<T>::Remove(T k) {
	if (this == NULL)
		return this;
	if (k < key)
		left = left->Remove(k);
	else if (k > key)
		right = right->Remove(k);
	else if (left != NULL && right != NULL) {
		key = right->Min()->key;
		right = right->Remove(key);
	}
	else {
		if (left != NULL)
			return left;
		else
			return right;
	}
	return this;
}

template<typename T>
bool Tree<T>::Exists(T k) {
	Tree* current = this;
	while (current != NULL) {
		if (k < current->key)
			current = current->left;
		else if (k > current->key)
			current = current->right;
		else
			return true;
	}
	return false;
}

template<typename T>
T Tree<T>::Next(T k) {
	Tree* current = this;
	int out = 1000000001;
	while (current != NULL) {
		if (current->key > k) {
			out = current->key;
			current = current->left;
		}
		else
			current = current->right;
	}
	return out;
}

template<typename T>
T Tree<T>::Prev(T k) {
	Tree* current = this;
	int out = -1000000001;
	while (current != NULL) {
		if (current->key >= k)
			current = current->left;
		else {
			out = current->key;
			current = current->right;
		}
	}
	return out;
}

int main() {
	ifstream fin("bstsimple.in");
	ofstream fout("bstsimple.out");
	string command;
	Tree<int>* binary_tree = NULL;
	int counter = 0, x, i = 0, out;
	while (fin >> command) {
		counter++;
		if (command == "insert") {
			fin >> x;
			binary_tree = binary_tree->Insert(x);
		}
		else if (command == "delete") {
			fin >> x;
			binary_tree = binary_tree->Remove(x);
		}
		else if (command == "exists") {
			fin >> x;
			binary_tree->Exists(x) ? fout << "true\n" : fout << "false\n";
		}
		else if (command == "next") {
			fin >> x;
			out = binary_tree->Next(x);
			out == 1000000001 ? fout << "none\n" : fout << out << "\n";
		}
		else if (command == "prev") {
			fin >> x;
			out = binary_tree->Prev(x);
			out == -1000000001 ? fout << "none\n" : fout << out << "\n";
		}
	}
	fin.close();
	fout.close();
	return 0;
}
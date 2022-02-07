#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

class Set {
private:
	vector<vector <int>> hash;
public:
	Set();
	void Insert(int);
	void Delete(int);
	bool Exists(int);

	int Hash(int);
};

Set::Set() {
	hash.resize(1000000, vector<int>());
}

int Set::Hash(int element) {
	int hashCode = abs(element % 1000000);
	return hashCode;
}

void Set::Insert(int element) {
	unsigned int hashCode = Hash(element);
	if (hash[hashCode].empty()) {
		hash[hashCode].push_back(element);
		return;
	}
	for (unsigned int i = 0; i < hash[hashCode].size(); i++) {
		if (hash[hashCode][i] == element) {
			return;
		}
	}
	hash[hashCode].push_back(element);
	int i = hash[hashCode].size() - 1;
	while (hash[hashCode][i] < hash[hashCode][i - 1]) {
		swap(hash[hashCode][i], hash[hashCode][i - 1]);
		if (i == 1)
			break;
		i--;
	}
}

void Set::Delete(int element) {
	unsigned int hashCode = Hash(element);
	if (hash[hashCode].empty())
		return;
	for (unsigned int i = 0; i < hash[hashCode].size(); i++) {
		if (hash[hashCode][i] == element) {
			hash[hashCode].erase(hash[hashCode].begin() + i);
			return;
		}
	}
}

bool Set::Exists(int element) {
	unsigned int hashCode = Hash(element);
	if (hash[hashCode].empty())
		return false;
	for (unsigned int i = 0; i < hash[hashCode].size(); i++) {
		if (hash[hashCode][i] == element) {
			return true;
		}
	}
	return false;
}


int main() {
	ifstream fin("set.in");
	ofstream fout("set.out");
	
	Set mySet;
	string command;
	int number;
	while (fin >> command) {
		if (command == "insert") {
			fin >> number;
			mySet.Insert(number);
		}
		else if (command == "delete") {
			fin >> number;
			mySet.Delete(number);
		}
		else if (command == "exists") {
			fin >> number;
			mySet.Exists(number) ? fout << "true\n" : fout << "false\n";
		}
	}
	fin.close();
	fout.close();
	return 0;
}
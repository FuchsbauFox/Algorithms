#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits.h>

using namespace std;

template <typename T, typename U>
T BinSearch(vector<U> Array, U element, int n, vector<T> Array1) {
	int l = -1;
	int r = n - 1;
	int middle;
	while (l < r - 1) {
		middle = (l + r) / 2;
		if (Array[middle] < element)
			l = middle;
		else
			r = middle;
	}
	if (Array[r] == element)
		return Array1[r];
	else
		return "none";
}


template <typename T, typename U>
class Set {
private:
	vector<vector <T>> keys;
	vector<vector <U>> elements;
public:
	Set();
	void Insert(T, U);
	void Delete(U);
	T Exists(U);
	int Hash(U);
};

template <typename T, typename U>
Set<T, U>::Set() {
	keys.resize(1000000, vector<U>());
	elements.resize(1000000, vector<T>());
}

template <typename T, typename U>
int Set<T, U>::Hash(U key) {
	unsigned long long int Code_of_hash = 0;
	unsigned long long int p_pow = 1;
	for (int i = 0; i < key.size(); ++i) {
		Code_of_hash += ((abs((int)key[i])) * p_pow) % LLONG_MAX;
		p_pow = (p_pow * 31) % LLONG_MAX;
	}
	return Code_of_hash % 1000000;
}

template <typename T, typename U>
void Set<T, U>::Insert(T element, U key) {
	unsigned int Code_of_hash = Hash(key);
	if (elements[Code_of_hash].empty()) {
		elements[Code_of_hash].push_back(element);
		keys[Code_of_hash].push_back(key);
		return;
	}
	for (unsigned int i = 0; i < elements[Code_of_hash].size(); i++) {
		if (elements[Code_of_hash][i] == element) {
			return;
		}
	}
	elements[Code_of_hash].push_back(element);
	keys[Code_of_hash].push_back(key);
	int i = elements[Code_of_hash].size() - 1;
	while (elements[Code_of_hash][i] < elements[Code_of_hash][i - 1]) {
		swap(elements[Code_of_hash][i], elements[Code_of_hash][i - 1]);
		swap(keys[Code_of_hash][i], keys[Code_of_hash][i - 1]);
		if (i == 1)
			break;
		i--;
	}
}

template <typename T, typename U>
void Set<T, U>::Delete(U key) {
	int Code_of_hash = Hash(key);
	if (elements[Code_of_hash].empty())
		return;
	for (int i = 0; i < elements[Code_of_hash].size(); i++) {
		if (keys[Code_of_hash][i] == key) {
			elements[Code_of_hash].erase(elements[Code_of_hash].begin() + i);
			keys[Code_of_hash].erase(keys[Code_of_hash].begin() + i);
			return;
		}
	}
}


template <typename T, typename U>
T Set<T, U>::Exists(U key) {
	int hashCode = Hash(key);
	if (elements[hashCode].empty())
		return "none";
	return BinSearch(keys[hashCode], key, keys[hashCode].size(), elements[hashCode]);
}


int main() {
	ifstream fin("map.in");
	ofstream fout("map.out");
	Set<string, string> Main_Map;
	string Key1, Key2, Command;
	while (fin >> Command) {
		if (Command == "put") {
			fin >> Key1 >> Key2;
			Main_Map.Insert(Key2, Key1);
		}
		else if (Command == "delete") {
			fin >> Key1;
			Main_Map.Delete(Key1);
		}
		else if (Command == "get") {
			fin >> Key1;
			fout << Main_Map.Exists(Key1) << endl;
		}
	}
	fin.close();
	fout.close();
	return 0;
}
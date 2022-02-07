#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Labels {
	string label;
	int pos;
};

int main() {
	ifstream fin("quack.in");
	ofstream fout("quack.out");
	int reg[26] = { 0 };
	vector<string> commands;
	vector<Labels> labels;
	string command;
	int queue[100001] = { 0 };
	int head = 0, pos = 0;
	int i = 0;
	while (fin >> command) {
		commands.push_back(command);
		if (command[0] == ':') {
			Labels label;
			label.label = command;
			label.pos = i;
			labels.push_back(label);
		}
		i++;
	}
	vector<string>::iterator it1 = commands.begin();
	vector<Labels>::iterator it2 = labels.begin();
	while (it1 != commands.end()) {
		command = *it1;
		it1++;
		if (command[0] == ':')
			continue;
		else if (command == "+") {
			unsigned long long int sum = ((unsigned long long int)queue[head] + (unsigned long long int)queue[head + 1]) % 65536;
			queue[pos] = (int)sum;
			pos++;
			head += 2;
		}
		else if (command == "-") {
			unsigned long long int sub = ((unsigned long long int)queue[head] - (unsigned long long int)queue[head + 1]) % 65536;
			queue[pos] = (int)sub;
			pos++;
			head += 2;
		}
		else if (command == "*") {
			unsigned long long int multy = ((unsigned long long int)queue[head] * (unsigned long long int)queue[head + 1]) % 65536;
			queue[pos] = (int)multy;
			pos++;
			head += 2;
		}
		else if (command == "/") {
			if (queue[head + 1] == 0) {
				queue[pos] = 0;
				pos++;
				head += 2;
			}
			else {
				queue[pos] = queue[head] / queue[head + 1];
				pos++;
				head += 2;
			}
		}
		else if (command == "%") {
			if (queue[head + 1] == 0) {
				queue[pos] = 0;
				pos++;
				head += 2;
			}
			else {
				queue[pos] = queue[head] % queue[head + 1];
				pos++;
				head += 2;
			}
		}
		else if (command[0] == '>')
			reg[(int)command[1] - 97] = queue[head++];
		else if (command[0] == '<')
			queue[pos++] = reg[(int)command[1] - 97];
		else if (command == "P")
			fout << queue[head++] << endl;
		else if (command[0] == 'P')
			fout << reg[(int)command[1] - 97] << endl;
		else if (command == "C")
			fout << (char)(queue[head++] % 256);
		else if (command[0] == 'C')
			fout << (char)(reg[(int)command[1] - 97] % 256);
		else if (command[0] == 'J') {
			command.erase(0, 1);
			while (":" + command != it2->label)
				it2++;
			it1 = commands.begin() + it2->pos;
			it2 = labels.begin();
		}
		else if (command[0] == 'Z') {
			if (reg[(int)command[1] - 97] == 0) {
				command.erase(0, 2);
				while (":" + command != it2->label)
					it2++;
				it1 = commands.begin() + it2->pos;
				it2 = labels.begin();
			}
		}
		else if (command[0] == 'E') {
			if (reg[(int)command[1] - 97] == reg[(int)command[2] - 97]) {
				command.erase(0, 3);
				while (":" + command != it2->label)
					it2++;
				it1 = commands.begin() + it2->pos;
				it2 = labels.begin();
			}
		}
		else if (command[0] == 'G') {
			if (reg[(int)command[1] - 97] > reg[(int)command[2] - 97]) {
				command.erase(0, 3);
				while (":" + command != it2->label)
					it2++;
				it1 = commands.begin() + it2->pos;
				it2 = labels.begin();
			}
		}
		else if (command == "Q")
			break;
		else {
			queue[pos] = stoi(command) % 65536;
			pos++;
		}
		if (pos == 100000)
			pos = 0;
		if (head == 100000)
			head = 0;
	}
	fin.close();
	fout.close();
	return 0;
}
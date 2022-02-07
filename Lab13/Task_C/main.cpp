#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> prefixFunction(string s) {

    vector<int> ans;
    ans.resize(s.size(), 0);
    for (int i = 1; i < s.size(); ++i) {
        int j = ans[i - 1];
        while (j > 0 && s[i] != s[j])
            j = ans[j - 1];
        if (s[i] == s[j])  ++j;
        ans[i] = j;
    }
    return ans;
}

int main() {

    ifstream fin("prefix.in");
    ofstream fout("prefix.out");

    string s;
    fin >> s;

    vector<int> ans;
    ans = prefixFunction(s + " abaa");

    fout << s + " abc" << '\n';

    for (auto& pos : ans) {
        fout << pos << ' ';
    }

    fin.close();
    fout.close();
    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> zFunction(string s) {

    vector<int> z;
    z.resize(s.size(), 0);
    for (int i = 1, left = 0, right = 0; i < s.size(); ++i) {
        if (i <= right)
            z[i] = min(right - i + 1, z[i - left]);
        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > right)
            left = i, right = i + z[i] - 1;
    }

    return z;
}

int main() {
    ifstream fin("search1.in");
    ofstream fout("search1.out");

    string p, t;
    fin >> p >> t;

    vector<int> prefPos;
    prefPos = zFunction(p + "1" + t);

    vector<int> ans;

    for (int i = 0; i < prefPos.size(); ++i) {
        if (prefPos[i] == p.size()) {
            ans.push_back(i - p.size());
        }
    }

    fout << ans.size() << '\n';
    for (auto& pos : ans) {
        fout << pos <<' ';
    }

    fin.close();
    fout.close();
    return 0;
}
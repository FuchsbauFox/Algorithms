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

void KMP(string s, int n) {

    vector<int> pref;
    pref = prefixFunction(s);
    vector<vector<int>> ans;
    ans.resize(s.size() + 1, vector<int>(n));

    int j = 0;
    for (int i = 0; i <= s.size(); ++i) {
        for (char c = 'a'; c < 'a' + n; ++c) {
            int j = i;
            if (i > 0 && c != s[i])
                ans[i][c - 'a'] = ans[pref[i - 1]][c - 'a'];
            else {
                if (c == s[i])
                    ans[i][c - 'a']++;
                ans[i][c - 'a'] += i;
            }
            cout << ans[i][c - 'a'] << ' ';
        }
        cout << '\n';
    }

}

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    KMP(s, n);

    return 0;
}
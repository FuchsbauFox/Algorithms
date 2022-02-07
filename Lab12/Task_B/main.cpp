#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct data {
    int number;
    int position;
    int prev;

};

int BinarySearch(int* container, int value, int right) {
    int left = -1;
    while (left < right - 1) {
        int middle = (left + right) / 2;
        container[middle] < value ? left = middle : right = middle;
    }
    return right;
}

int main() {
    int n, max_subsequence = 0;
    cin >> n;

    int* sequence = new int[n];
    for (int i = 0; i < n; ++i)
        cin >> sequence[i];

    int* position = new int[n + 1];
    position[0] = -1;

    int* temp = new int[n + 1];
    fill(temp, temp + n + 1, INT_MAX);
    temp[0] = INT_MIN;

    int* previous = new int[n];

    for (int i = 0; i < n; ++i) {
        int j = BinarySearch(temp, sequence[i], n);
        if (sequence[i] < temp[j] && temp[j - 1] < sequence[i]) {
            temp[j] = sequence[i];
            previous[i] = position[j - 1];
            position[j] = i;
            max_subsequence = max(j, max_subsequence);
        }
    }

    vector<int> answer;
    int t = position[max_subsequence];
    while (t != -1) {
        answer.push_back(sequence[t]);
        t = previous[t];
    }

    cout << max_subsequence << endl;
    for (int i = answer.size() - 1; i >= 0; --i)
        cout << answer[i] << " ";
    return 0;
}
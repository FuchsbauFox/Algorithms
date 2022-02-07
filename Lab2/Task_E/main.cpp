#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int quickSort(vector<int>& array, int size, int searchPosition) {
    int left = 0, right = size - 1;
    while (true)
    {
        if (left + 1 >= right)
        {
            if (left + 1 == right && array[left] > array[right])
            {
                swap(array[left], array[right]);
            }
            return array[searchPosition];
        }
        int middle = (left + right) / 2;
        swap(array[middle], array[left + 1]);
        if (array[left] > array[right])
            swap(array[left], array[right]);

        if (array[left + 1] > array[right])
            swap(array[left + 1], array[right]);

        if (array[left] > array[left + 1])
            swap(array[left], array[left + 1]);
        int it_left = left + 1;
        int it_right = right;
        int value = array[it_left];
        while (true)
        {
            do
            {
                it_left++;
            } while (array[it_left] < value);
            do
            {
                it_right--;
            } while (array[it_right] > value);
            if (it_left > it_right)
            {
                break;
            }
            swap(array[it_left], array[it_right]);
        }
        array[left + 1] = array[it_right];
        array[it_right] = value;
        if (it_right >= searchPosition)
        {
            right = it_right - 1;
        }
        if (it_right <= searchPosition)
        {
            left = it_left;
        }
    }
}

int main() {
    int n, k, a, b, c, firstElement, secondElement;
    ifstream fin("kth.in");
    ofstream fout("kth.out");
    fin >> n >> k >> a >> b >> c >> firstElement >> secondElement;
    vector < int> arr(n);
    arr[0] = firstElement;
    if (n > 1) {
        arr[1] = secondElement;
    }
    cout << arr[0] << "\n";
    cout << arr[1] << "\n";
    for (int i = 2; i < n; i++) {
        arr[i] = a * arr[i - 2] + b * arr[i - 1] + c;
        cout << arr[i] << "\n";
    }
    int u = 0;
    cout << "======\n" << arr[u++] << "\n=========";
    fout << quickSort(arr, n, k - 1);
    return 0;
}
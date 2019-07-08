#include <iostream>
#include <cmath>

using namespace std;

const int N = 1000007;
int n;
int a[N];
int dp[N];

int lower_bound(int *array, int size, int key) {
    int first = 0, middle;
    int half, len;
    len = size;

    while (len > 0) {
        half = len >> 1;
        middle = first + half;
        if (array[middle] < key) {
            first = middle + 1;
            len = len - half - 1;
        } else
            len = half;
    }
    return first;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    int len = 1;
    dp[0] = a[0];
    for (int i = 1; i < n; i++) {
        int pos = lower_bound(dp, len, a[i]);
        dp[pos] = a[i];
        len = max(len, pos + 1);
    }

    cout << len;

    return 0;
}
#include<iostream>
#include<iomanip>

using namespace std;

int main() {
    int nn;

    cin >> nn;
    const int n=nn;
    int a[n][n]={0};

    int cnt = 1;
    int layer = 0;
    while (a[layer][layer]==0) {
        int size = n - layer * 2;

        for (int j = 0; j < size - 1; ++j) a[layer][layer + j] = cnt++;
        for (int j = 0; j <size-1; j++) a[layer +j][layer + size-1] = cnt++;
        for (int i = size - 1; i > 0; --i) a[layer + size-1][layer + i] = cnt++;
        for (int i = size-1; i >0; --i) a[i + layer][layer] = cnt++;

        if (a[layer][layer] == 0)
            a[layer][layer] = cnt++;

        layer++;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(6) << a[i][j];
        }
        cout << endl;
    }

    return 0;
}

#include <iostream>

#define N 35

using namespace std;

int f[N][N], root[N][N], a[N];

void print(int i, int j) {
    if (i > j) return;
    cout << root[i][j] << ' ';
    print(i, root[i][j] - 1);
    print(root[i][j] + 1, j);
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        f[i][i] = a[i];
        root[i][i] = i;
        if (i > 1) {
            f[i - 1][i] = a[i - 1] + a[i];
            root[i - 1][i] = i - 1;
        }
    }

    for (int i = n; i > 0; i--) {
        for (int j = i + 1; j <= n; j++) {
            for (int k = i; k <= j; k++) {
                if (f[i][k - 1] * f[k + 1][j] + a[k] > f[i][j]) {
                    f[i][j] = f[i][k - 1] * f[k + 1][j] + a[k];
                    root[i][j] = k;
                }
            }
        }
    }
    cout << f[1][n] << endl;
    print(1, n);
    return 0;
}
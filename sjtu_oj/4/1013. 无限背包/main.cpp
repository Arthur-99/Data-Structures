#include <iostream>

using namespace std;

const int MAX = 1007;
int v[MAX];
int w[MAX];
int f[1007] = {0};
//int d[1007][1007] = {0};

int max(int a, int b, int c) {
    int d = (a > b) ? a : b;
    return (d > c) ? d : c;
}

int main() {
    int V, N;
    cin >> V >> N;

    for (int i = 0; i < N; i++) {
        cin >> v[i] >> w[i];
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= V; j++) {
            f[j]=max(f[j],f[j-v[i]]+w[i]);
//            for (int k = 0; j >= k * v[i - 1]; k++) {
//                d[i][j] = max(d[i - 1][j - k * v[i - 1]] + k * w[i - 1], d[i][j], d[i - 1][j]);
//            }
        }
    }
    cout << f[V];
    //cout << d[N][V];

    return 0;
}

#include <iostream>

using namespace std;

int n;

const int N = 2018;
int d[N][N]={0},p[N][N]={0};
int a[N], b[N], c[N];

void Qsort(int *A, int l, int r) {
    if (l >= r) return;
    int x = A[r];
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    Qsort(A, l, i);
    Qsort(A, i + 2, r);
}
int abs(int x) {
    if (x > 0) return x;
    else return -x;
}
int min(int a,int b){
    if (a>b) return b;
    else return a;
}

int cost(int* x,int* y){
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            d[i][j]=p[i][j]=0;
        }
    }

    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            d[i][j]=p[i-1][j]+abs(x[i]-y[j]);
            if (j==1) p[i][j]=d[i][j];
            else p[i][j]=min(d[i][j],p[i][j-1]);
        }
    }

    int minn=~(1<<31);
    for (int i=1;i<=n;i++){
        if (minn>d[n][i]) minn=d[n][i];
    }
    return minn;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) c[n + 1 - i] = b[i] = a[i];
    Qsort(a, 1, n);

    int cost_b = cost(b,a), cost_c = cost(c,a);


//    cout << cost_b << endl;
//    cout << cost_c << endl;
    cout << min(cost_b, cost_c);

    return 0;
}
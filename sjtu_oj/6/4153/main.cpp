#include <iostream>
 
using namespace std;
 
void Qsort(int *A, int p, int r) {
    if (p >= r) return;
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    Qsort(A, p, i);
    Qsort(A, i + 2, r);
}
 
const int N = 100007;
 
int n, m, k;
int a[N];
 
bool check(int x) {
    int ans_l = 0;
    int last_l = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] - last_l < x){
            ans_l++;
        } else last_l = a[i];
    }
//    return ans_l >= m - k;
	int ans_r = 0;
    int last_r = a[n-1];
    for (int i = n-2; i >=0; i--) {
        if (last_r-a[i] < x){
            ans_r++;
        } else last_r = a[i];
    }
    
    return (ans_l <= n-m + k-1) || (ans_r <= n-m + k-1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    Qsort(a, 0, n - 1);
 
 
    int max = a[n - 1] - a[0];

    int l = 0, r = max, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (check(mid)) l = mid + 1;
        else r = mid - 1;
    }

    cout << r;
  
 
    return 0;
}


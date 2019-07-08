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
    int ans = 0;
    int last = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] - last < x)
            ans++;
        else last = a[i];
    }
    if (ans > n - m) return false;
    else return true;
}

bool check20(int x){
    for (int i=0;i<n-1;i++){
        bool flag = true;
        if (a[i+1]-a[i]<=x){
            int ans = 0;
            int last_left = a[i];
            for (int j=i-1;j>=0;j--){
                if (last_left - a[j] < x){
                    ans++;
                    if (ans > n - m) {
                        flag = false;
                        break;
                    }
                }
                else last_left = a[j];
            }
            if (!flag) continue;

            int last_right = a[i+1];
            for (int j = i+2;j<n;j++){
                if (a[j]-last_right < x){
                    ans++;
                    if (ans > n - m) {
                        flag = false;
                        break;
                    }
                }
                else last_right = a[j];
            }
            if (!flag) continue;

            if (ans <= n - m) return true;
        }
    }
    return false;
}

bool check2(int x){

    int min = a[1]-a[0],t = 0;
    for (int i=0;i<n-1;i++){
        if (a[i+1]-a[i]<min){
            min = a[i+1] -a[i];
            t = i;
        }
    }

    int ans = 0;
    int last_left = a[t];
    for (int j=t-1;j>=0;j--){
        if (last_left - a[j] < x){
            ans++;
            if (ans > n - m) {
                return false;
            }
        }
        else last_left = a[j];
    }

    int last_right = a[t+1];
    for (int j = t+2;j<n;j++){
        if (a[j]-last_right < x){
            ans++;
            if (ans > n - m) {
                return false;
            }
        }
        else last_right = a[j];
    }

    return true;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    Qsort(a, 0, n - 1);


    if (k == 1) {
        int max = a[n - 1] - a[0];

        int l = 0, r = max;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(mid)) l = mid + 1;
            else r = mid - 1;
        }

        cout << r;
    } else if (k == 2 && n > 1000) {
        int max = a[n - 1] - a[0];

        int l = 0, r = max;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check2(mid)) l = mid + 1;
            else r = mid - 1;
        }

        cout << r;
    } else if (k == 2 && n <= 1000){
        int max = a[n - 1] - a[0];

        int l = 0, r = max;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check20(mid)) l = mid + 1;
            else r = mid - 1;
        }

        cout << r;
    }

    return 0;
}
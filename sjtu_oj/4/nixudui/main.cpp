#include <iostream>


#define ll long long
using namespace std;

ll merge (ll A[], ll begin, ll mid, ll end) {
    static ll count = 0;
    ll result[end - begin + 1];
    ll i = begin;
    ll j = mid + 1;
    ll k = 0;
    while (i <= mid && j <= end) {
        if (A[i] <= A[j]) {
            result[k ++] = A[i ++];
        }
        else {
            count += mid - i + 1;
            result[k ++] = A[j ++];
        }
    }
    while (j <= end)
        result [k ++] = A[j ++];
    while (i <= mid)
        result[k ++] = A[i ++];
    for (k = 0; k < end - begin + 1;k ++)
        A[begin + k] = result[k];
    return count;
}

ll mergeSort(ll a[], ll begin, ll end) {
    ll sum = 0;
    if (begin < end) {
        ll mid = (begin + end)/2;
        mergeSort (a, begin, mid);
        mergeSort (a, mid + 1, end);
        sum = merge (a, begin, mid, end);
    }
    return sum;
}

ll a[150000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;

    for(ll i = 0; i < n; i++){
        cin>>a[i];
    }
    ll begin = 0, end = n - 1;
    cout<<mergeSort(a, begin, end);
    return 0;
}
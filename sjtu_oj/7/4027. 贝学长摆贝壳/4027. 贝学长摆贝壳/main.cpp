#include <iostream>

using namespace std;

int n;
const int N=1e5+7;
int A[N],B[N];

void Qsort(int* arr,int* b,int l,int r){
    if (l>=r) return ;

    int x=arr[r];
    int i=l;
    for (int j=l;j<r;j++){
        if (arr[j]<x) {
            swap(arr[i],arr[j]);
            swap(b[i],b[j]);
            i++;
        }
    }
    swap(arr[i],arr[r]);
    swap(b[i],b[r]);

    Qsort(arr,b,l,i-1);
    Qsort(arr,b,i+1,r);
}

int dp[N]={0};


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

int main()
{
    cin>>n;
    for (int i=0;i<n;i++) {
        int x;cin>>x;
        A[x]=i;
    }
    for (int i=0;i<n;i++) {
        int x;cin>>x;
        B[i]=A[x];
    }

//    Qsort(A,B,0,n-1);

    //
//    for (int i=0;i<n;i++) cout<<A[i];cout<<endl;
//    for (int i=0;i<n;i++) cout<<B[i];cout<<endl;



    int len = 1;
    dp[0] = B[0];
    for (int i = 1; i < n; i++) {
        int pos = lower_bound(dp, len, B[i]);
        dp[pos] = B[i];
        len = max(len, pos + 1);
    }

    cout << len;

    return 0;
}

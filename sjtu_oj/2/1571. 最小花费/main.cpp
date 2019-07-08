#include <iostream>
#include <cstdio>
#include <cmath>

#define ll long long
#define MOD 99999997

using namespace std;

ll ans=0;

struct node{
    ll data,p;
    bool operator<(const node& n){ return data< n.data;}
    friend ostream& operator<<(ostream& os, const node& n) {os<<n.data<<' '; return os;}
};

template <class T>
void merge(T* a,int left,int mid,int right)
{
    T* tmp=new T[right-left+1];

    int i=left,j=mid+1,cur=0;

    while(i<=mid && j<=right) {
        if(a[i]<a[j]) tmp[cur++]=a[i++];
        else {
            tmp[cur++]=a[j++];
            if (sizeof(T)==sizeof(ll))ans += mid-i+1;
        }
    }
    if(i<=mid) while(i<=mid) tmp[cur++]=a[i++];
    else while(j<=right) tmp[cur++]=a[j++];

    for(int k=0;k<cur;k++) a[left++]=tmp[k];

    delete[] tmp;
}

template <class T>
void mergeSort(T* a,int first,int last)
{
    if(first==last)
        return;
    int mid=(first+last)/2;
    mergeSort(a,first,mid);
    mergeSort(a,mid+1,last);
    merge(a,first,mid,last);
}


int main() {
    ios::sync_with_stdio(false);

    int n;cin>>n;
    const int N=n;

    node X[N],Y[N];
    for (int i=0;i<N;i++) {
        cin>>X[i].data;
        X[i].p=i;
    }
    for (int i=0;i<N;i++) {
        cin>>Y[i].data;
        Y[i].p=i;
    }

    mergeSort(X,0,N-1);
    mergeSort(Y,0,N-1);

//    for (int i=0;i<N;i++) cout<<X[i]<<' ';
//    cout<<endl;
//    for (int i=0;i<N;i++) cout<<X[i].p<<' ';
//    cout<<endl;
//    for (int i=0;i<N;i++) cout<<Y[i]<<' ';
//    cout<<endl;
//    for (int i=0;i<N;i++) cout<<Y[i].p<<' ';
//    cout<<endl;

    ll Z[N];
    for (int i=0;i<N;i++) {
        Z[X[i].p]=Y[i].p;
    }

//    for (int i=0;i<N;i++) cout<<Z[i]<<' ';
//    cout<<endl;

    mergeSort(Z,0,N-1);

//    for (int i=0;i<N;i++) cout<<Z[i]<<' ';
//    cout<<endl;

    cout<<ans%MOD;

    return 0;
}
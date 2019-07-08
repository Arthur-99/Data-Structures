#include <iostream>

using namespace std;

#define ll long long


struct hill {
    ll x,h;
};


void qsort(hill* a,int l,int r){
    if (l>=r) return;
    ll x=a[r].x;
    int i=l;
    for (int j=l;j<r;j++){
        if (a[j].x<x) {
            swap(a[j],a[i]);
            i++;
        }
    }
    swap(a[i],a[r]);
    qsort(a,l,i-1);
    qsort(a,i+1,r);
}

const int N=1e5+7;

hill H[N];

int main()
{
    int n;
    cin>>n;

    if (n==1){
        cout<<1<<endl;
        return 0;
    }

    for (int i=0;i<n;i++) cin>>H[i].x;
    for (int i=0;i<n;i++) cin>>H[i].h;

    qsort(H,0,n-1);

    int res=2;
    for (int i=1;i<n-1;i++){
        if (H[i].x-H[i].h>H[i-1].x) res++;
        else if (H[i].x+H[i].h<H[i+1].x){
            res++;
            H[i].x+=H[i].h;
        }
    }

    cout<<res<<endl;

    return 0;
}

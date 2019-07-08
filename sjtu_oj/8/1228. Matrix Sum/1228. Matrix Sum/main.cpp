#include <iostream>
//#include <cstdint>

using namespace std;

#define ll long long

const int N=407;
int A[N][N]={0};

ll cnt(int* a,int n){
    ll res=0;

    ll seq0[N];
    int num0=0,id=-1;
    for (int i=0;i<n;i++){
        if (a[i]&1) {
            seq0[num0++]=i-id;
            id=i;
        }
    }
    seq0[num0++]=n-id;

    for (int i=0;i<num0;i++){
        for (int step=1;step+i<num0;step+=2){
            res+=seq0[i]*seq0[i+step];
        }
    }
    return res;
}
//#include <cstdlib>
//#include <ctime>
int main()
{
//    srand(time(0));
    ll n;cin>>n;
    int x;
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            cin>>x;
//            x=rand();
            A[i][j]=x&1;
        }
    }

    ll odd=0;
    for (int i=0;i<n;i++) {
        odd += cnt(A[i],n);

        for (int k=i+1;k<n;k++){
            for (int j=0;j<n;j++){
                A[i][j]=(A[i][j]+A[k][j])&1;
            }
            odd += cnt(A[i],n);
        }
    }

    cout<<odd<<' '<<(n*(n+1)*n*(n+1)/4-odd);

    return 0;
}

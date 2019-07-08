#include <iostream>

using namespace std;

const int N = 1e5+7;

int r[N],c[N];

struct array{
    int x,y,z;
} a[N];

int n;

int find(int rr,int cc){
    for (int i=0;i<n;i++){
        if (a[i].x==rr && a[i].y==cc){
            return a[i].z;
        }
    }
    return 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    for (int i=0;i<N;i++) r[i]=c[i]=i;

    cin>>n;
    int x,y,z;
    for (int i=0;i<n;i++){
        cin>>x>>y>>z;
        a[i]={x,y,z};
    }

    int m;
    cin>>m;
    int op;
    for (int i=0;i<m;i++){
        cin>>op>>x>>y;
        switch (op){
        case 0:
            swap(r[x],r[y]);
            break;
        case 1:
            swap(c[x],c[y]);
            break;
        case 2:
            cout<<find(r[x],c[y])<<'\n';
        }
    }

    cout<<flush;

    return 0;
}

#include <iostream>

using namespace std;

const int n=1e6+7;

class ds{
public:
    int parent[n];
public:
    ds(){for (int i=0;i<n;i++) parent[i]=-1;}
    void Union(int p,int q){
        int rt1=Find(p),rt2=Find(q);
        if (rt1==rt2) return;
        if (parent[rt1]>parent[rt2]){
            parent[rt2]+=parent[rt1];
            parent[rt1]=rt2;
        } else {
            parent[rt1]+=parent[rt2];
            parent[rt2]=rt1;
        }
    }

    int Find1(int x){
        //return (parent[x]<0)?x:(parent[x]=Find(parent[x]));
        if (parent[x]<0) return x;
        else return parent[x]=Find(parent[x]);
    }
    int Find(int x){
        int start=x,tmp;
        while (parent[x]>=0) x=parent[x];
        while (start!=x){
            tmp=start[parent];
            start[parent]=x;
            start=tmp;
        }
        return x;
    }

};

ds d;

#define ll long long

int main()
{
    ll N,m;cin>>N>>m;
    int u,v;
    for (int i=0;i<m;i++){
        cin>>u>>v;
        d.Union(u,v);
    }

    ll sum=0;
    for (int i=0;i<=N;i++){
        if (d.parent[i]<0) {
            ll sz=-d.parent[i];
            sum += sz*(sz-1)/2;
        }
    }
    cout<<sum - m<<endl;
    return 0;
}

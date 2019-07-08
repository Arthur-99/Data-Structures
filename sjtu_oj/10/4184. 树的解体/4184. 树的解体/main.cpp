#include <iostream>

using namespace std;


struct node{
    int size;
    int p;
    node(int sz=1,int pp=0){size=sz;p=pp;}
};

const int maxn=1e5+7;
node n[maxn];


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T;cin>>T;
    while (T--){
        int N,K;cin>>N>>K;

        int u,v;

        if (N%K){
            for (int i=0;i<N-1;i++){
                cin>>u>>v;
            }
            cout<<"NO\n";
            continue;
        }

        for (int i=0;i<N-1;i++){
            cin>>u>>v;

            n[u].p=v;
            int parent=v,son=u;
            while (parent){
                n[parent].size+=n[son].size;
                parent=n[parent].p;
            }
        }

        int sz=0;
        for (int i=1;i<=N;i++){
            if (n[i].size%K==0) sz++;
        }

        if (sz == N/K) cout<<"YES\n";
        else cout<<"NO\n";

        for (int i=0;i<maxn;i++) n[i].p=0,n[i].size=1;
    }

    cout<<flush;

    return 0;
}

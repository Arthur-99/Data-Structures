#include <iostream>
#include <cstring>

using namespace std;

const int n=3e6+5;

class trie{
private:
    int son[n][3];
    int cnt;
public:
    trie(){
        memset(son,0,sizeof(son));
        cnt=0;
    }
    void insert(int a){
        int x=0;
        for (int i=31;i>=0;i--){
            int alp=(a>>i)&1;
            if (!son[x][alp]) son[x][alp]=++cnt;
            x=son[x][alp];
        }
    }
    int find(int a){
        int x=0;
        int ret=0;
        for (int i=31;i>=0;i--){
            int alp=!((a>>i)&1);
            ret<<=1;
            if (son[x][alp]) x=son[x][alp],ret++;
            else x=son[x][!alp];
        }
        return ret;
    }
};

int max(int a,int b){return (a>b)?a:b;}


trie t;

int main()
{
    int N,M;
    cin>>N>>M;

    for (int i=0;i<N;i++) {
        int x;cin>>x;
        t.insert(x);
    }

    int MAX=-1;
    for (int i=0;i<M;i++) {
        int x;cin>>x;
        MAX=max(MAX,t.find(x));
    }

    cout<<MAX;

    return 0;
}

#include <iostream>

using namespace std;

struct nodeE{
    int end;
    nodeE* next;
    nodeE(int e=0,nodeE* n=nullptr){end=e;next=n;}
};
struct nodeV{
    nodeE* head;
    int ver;
    nodeV(nodeE* h=nullptr,int v=0){head=h;ver=v;}
};

class graph{
    int Vers;
public:
    nodeV* listV;
    graph(int sz=10){
        listV = new nodeV[sz];
        Vers=sz;
        for (int i=0;i<sz;i++){
            listV[i].ver=i;
        }
    }
    ~graph(){
        for (int i=0;i<Vers;i++){
            nodeE* p = listV[i].head;
            nodeE* q;
            while (p){
                q=p->next;
                delete p;
                p=q;
            }
        }
        delete []listV;
    }
    void insert(int u,int v){
        nodeE* p=listV[u].head;
        listV[u].head = new nodeE(v,p);
    }
    bool exist(int u,int v){
        nodeE* p=listV[u].head;
        while (p){
            if (p->end==v) return true;
            p=p->next;
        }
        return false;
    }
};

const int maxn=17;
graph g(maxn);
int ans=0;
bool vis[maxn]={0};
void dfs(int start,int curr,int M){
    if (M==0 && start!=curr){
        ans++;
    }
    vis[curr]=1;
    nodeE* p=g.listV[curr].head;
    while (p){
        if (!vis[p->end]){
            vis[p->end]=1;
            dfs(start,p->end,M-1);
            vis[p->end]=0;
        }
        p=p->next;
    }
}

int main()
{
    int n,m,start,M;cin>>n>>m>>start>>M;
    int u,v;
    for (int i=0;i<m;i++){
        cin>>u>>v;
        if (!g.exist(u,v)){
            g.insert(u,v);
        }
    }
    dfs(start,start,M);
    cout<<ans;
    return 0;
}

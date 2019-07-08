#include <iostream>

using namespace std;

class ds{
    int* parent;
public:
    ds(int sz=10){
        parent = new int[sz+10];
        for (int i=0;i<sz+10;i++) parent[i]=-1;
    }
    ~ds(){delete []parent;}
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

template <class T>
class lheap{
    struct node{
        T data;
        node* l;
        node* r;
        int npl;

        node(const T& d):data(d){
            l=r=nullptr;
            npl=0;
        }
    };

    node* root;
public:
    lheap(node* rt=nullptr){root=rt;}
    ~lheap(){clear(root);}

    T& getHead(){return root->data;}

    void enQueue(const T& x){
        node* p=new node(x);
        root=merge(root,p);
    }
    T deQueue(){
        T ret=root->data;
        node* rl=root->l;
        node* rr=root->r;
        delete root;
        root=merge(rl,rr);
        return ret;
    }

private:
    void clear(node* rt){
        if (rt){
            clear(rt->l);
            clear(rt->r);
            delete rt;
        }
    }

    int npl(node* rt){return (rt)?rt->npl:-1;}

    node* merge(node* h1,node* h2){
        if (h1==nullptr) return h2;
        if (h2==nullptr) return h1;

        if (h2->data < h1->data) swap(h1,h2);
        h1->r=merge(h1->r,h2);

        if (npl(h1->r)>npl(h1->l)) swap(h1->r,h1->l);
        h1->npl=npl(h1->l)+1;

        return h1;
    }
};

struct nodeE{
    int end;
    int w;
    nodeE* next;
    nodeE(int e=0,int ww=0,nodeE* n=nullptr){end=e;w=ww;next=n;}
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
        for (int i=1;i<sz;i++){
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
    void insert(int u,int v,int w){
        nodeE* p=listV[u].head;
        listV[u].head = new nodeE(v,w,p);
    }
    bool exist(int u,int v){
        nodeE* p=listV[u].head;
        while (p){
            if (p->end==v) return true;
            p=p->next;
        }
        return false;
    }


    struct edge{
        int beg,end;
        int w;
        bool operator<(const edge& rp) const {
            return w<rp.w;
        }
    };

    int kruskal(){
        int edgeAccepted=0,u,v;
        nodeE* p;
        edge e;
        ds djs(Vers);
        lheap<edge> lh;

        for (int i=0;i<Vers;i++){
            for (p=listV[i].head;p!=0;p=p->next){
                if (i<p->end){
                    e.beg=i;
                    e.end=p->end;
                    e.w=p->w;
                    lh.enQueue(e);
                }
            }
        }

        int ans=0;
        while (edgeAccepted < Vers - 1){
            e=lh.deQueue();
            u=djs.Find(e.beg);
            v=djs.Find(e.end);
            if (u!=v){
                edgeAccepted++;
                djs.Union(u,v);
                cout<<'('<<listV[u].ver<<','<<listV[v].ver<<')'<<endl;
                ans += e.w;
            }
        }

        return ans;
    }
};

const int maxn = 1e4+7;
const int maxm = 1e5+7;

int main()
{
    int n,m;
    cin>>n>>m;
    graph g(n);
    for (int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g.insert(u,v,w);
        g.insert(v,u,w);
    }

    cout<<g.kruskal();

    return 0;
}

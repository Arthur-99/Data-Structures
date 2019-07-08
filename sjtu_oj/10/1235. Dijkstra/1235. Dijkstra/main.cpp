#include <iostream>

using namespace std;

template <class T>
class queue{
    T* storage;
    int maxSize;
    int _front,_rear;
    void dbSpace(){
        T* tmp=storage;
        storage=new T[2*maxSize];
        for (int i=1;i<maxSize;i++) storage[i]=tmp[(_front+i)%maxSize];
        _front=0;_rear=maxSize-1;
        maxSize*=2;
        delete []tmp;
    }
public:
    queue(int initSize=10){
        storage = new T[initSize];
        maxSize=initSize;
        _front=_rear=0;
    }
    ~queue(){delete []storage;}

    bool empty(){return _front==_rear;}

    void push(const T& x){
        if ((_rear+1)%maxSize==_front) dbSpace();
        _rear=(_rear+1)%maxSize;
        storage[_rear]=x;
    }
    T& front(){return storage[(_front+1)%maxSize];}
    T pop(){
        _front=(_front+1)%maxSize;
        return storage[_front];
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
    bool empty(){return root==0;}

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
        listV = new nodeV[sz+1];
        Vers=sz;
        for (int i=1;i<=sz;i++){
            listV[i].ver=i;
        }
    }
    ~graph(){
        for (int i=1;i<=Vers;i++){
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
        listV[u].head = new nodeE(v,w,listV[u].head);
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

    void printPath(int s,int e,int p[]) const {
        if (s==e){
            cout<<listV[s].ver;
            return;
        }
        printPath(s,p[e],p);
        cout<<' '<<listV[e].ver;
    }

    void dijkstra(int start, int end) const {
        int noEdge = ~(1<<31);


        int* distance = new int[Vers+10];
        int* prev = new int[Vers+10];
        bool* known = new bool[Vers+10];

        int u, sNo, i, j;
        nodeE* p;
        int min;

        for (int i=1;i<=Vers;i++){
            known[i]=0;
            distance[i]=noEdge;
        }

        for (sNo=1;sNo<=Vers;sNo++){
            if (listV[sNo].ver==start) break;
        }
        if (sNo == Vers+1){
            return;
        }

        distance[sNo]=0;
        prev[sNo]=sNo;

        for (i=1;i<Vers;i++){
            min=noEdge;
            for (j=1;j<=Vers;j++){
                if (!known[j] && distance[j]<min){
                    min = distance[j];
                    u=j;
                }
            }

            known[u]=1;
            for (p=listV[u].head;p;p=p->next){
                if (!known[p->end] && distance[p->end]>min+p->w){
                    distance[p->end]=min+p->w;
                    prev[p->end]=u;
                }
            }
        }

        cout<<distance[end]<<endl;
        printPath(sNo,end,prev);
        cout<<endl;

        delete []prev;
        delete []distance;
        delete []known;
    }

    struct qNode{
        int dist;
        int node;
        bool operator<(const qNode& rp) const {return dist<rp.dist;}
    };

    void D(int start, int end){
        int noEdge = ~(1<<31);

        int* distance = new int [Vers + 10];
        int* prev = new int[Vers+10];
        bool* known = new bool[Vers+10];

        bool in_queue[Vers+10]={0};


        int sNo,i;
        nodeE* p;

        lheap<qNode> lh;
        qNode min,succ;

        for (i=1;i<=Vers;i++){
            known[i]=0;
            distance[i]=noEdge;
        }

        for (sNo=1;sNo<=Vers;sNo++){
            if (sNo==start) break;
        }
        if (sNo==Vers+1) return;

        distance[sNo]=0;
        prev[sNo]=sNo;

        min.dist=0;
        min.node = sNo;

//        lh.enQueue(min);
//
//        while (!lh.empty()){
//            min=lh.deQueue();
//            if (known[min.node]) continue;
//
//            known[min.node]=1;
//            for (p=listV[min.node].head;p;p=p->next){
//                if (!known[p->end] && distance[p->end] > min.dist+p->w){
//                    succ.dist=distance[p->end] = min.dist+p->w;
//                    prev[p->end]=min.node;
//                    succ.node=p->end;
//                    lh.enQueue(succ);
//                }
//            }
//        }

        queue<int> q;

        q.push(start);
        distance[start]=0;
        in_queue[start]=true;

        while(!q.empty()){
            int cur = q.pop();
            in_queue[cur]=0;
            for(nodeE* p=listV[cur].head;p;p=p->next){
                if(distance[p->end]>distance[cur]+p->w){
                    distance[p->end]=distance[cur]+p->w;
                    prev[p->end]=cur;
                    if(!in_queue[p->end]){
                        q.push(p->end);
                        in_queue[p->end]=1;
                    }
                }
            }
        }

        cout<<distance[end]<<endl;
        printPath(sNo,end,prev);
        cout<<endl;

        delete []prev;
        delete []distance;
        delete []known;
    }
};

int main()
{
    int n,m,start,end;
    cin>>n>>m>>start>>end;

    graph g(n);

    for (int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g.insert(u,v,w);
    }

    g.D(start,end);

    return 0;
}

/**
7 12 4 7
1 2 2
3 1 4
1 4 1
2 4 3
4 5 2
2 5 10
3 6 5
4 6 8
4 7 4
5 7 6
7 6 1
4 3 2

6 10 1 6
1 2 6
1 4 5
1 3 1
2 3 5
3 4 5
2 5 3
3 5 6
3 6 4
4 6 2
5 6 6
*/

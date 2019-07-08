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


struct nodeE{
    int end;
    int weight;
    nodeE* next;
    nodeE(int e=0,int w=0,nodeE* n=nullptr){end=e;weight=w;next=n;}
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
};

const int maxn=20007;
graph g(maxn);

int disA[maxn]={0},disB[maxn]={0},disC[maxn]={0};
bool visA[maxn]={0},visB[maxn]={0},visC[maxn]={0};

void bfs(int x,int* disx,bool* visx){
    queue<int> curr,next;
    curr.push(x);
    while (!curr.empty()){
        int tmp=curr.pop();
        visx[tmp]=1;

        nodeE* p=g.listV[tmp].head;
        while (p){
            if (!visx[p->end]) {
                next.push(p->end);
                disx[p->end]=disx[tmp]+p->weight;
            }
            p=p->next;
        }

        if (curr.empty()){
            while(!next.empty()){
                curr.push(next.pop());
            }
        }
    }
}

int main()
{
    int N,A,B,C;cin>>N>>A>>B>>C;
    int u,v,w;
    for (int i=0;i<N-1;i++){
        cin>>u>>v>>w;
        g.insert(u,v,w);
        g.insert(v,u,w);
    }

    bfs(A,disA,visA);
    bfs(B,disB,visB);
    bfs(C,disC,visC);

    int sum=~(1<<31);
    int ans=0;
    for (int i=1;i<=N;i++){
        if (disA[i]+disB[i]+disC[i]<sum){
            sum=disA[i]+disB[i]+disC[i];
            ans=i;
        }
    }

    cout<<ans<<endl;
    cout<<sum<<endl;

    return 0;
}

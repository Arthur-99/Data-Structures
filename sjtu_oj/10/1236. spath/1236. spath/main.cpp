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
        for (int i=0;i<=Vers;i++){
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


    void weightNegative(int start,int end){
        int distance[Vers+2];
        int prev[Vers+2];
        bool in_queue[Vers+2]={0};

        int inf = ~(1<<31);
        for (int i=1;i<=Vers;i++) distance[i]=inf;

        distance[start]=0;

        queue<int> q;
        q.push(start);
        in_queue[start]=1;

        while (!q.empty()){
            int u = q.pop();
            in_queue[u]=0;
            for (nodeE* p=listV[u].head;p;p=p->next){
                if (distance[u] + p->w < distance[p->end]){
                    distance[p->end] = distance[u] + p->w;
                    prev[p->end] = u;
                    if (!in_queue[p->end]){
                        q.push(p->end);
                        in_queue[p->end]=1;
                    }
                }
            }
        }

        cout<<distance[end]<<endl;
    }
};

graph g(13);

int main()
{
    int n,m,start,end;
    cin>>n>>m>>start>>end;

    for (int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g.insert(u,v,w);
    }

    g.weightNegative(start,end);

    return 0;
}

#include <iostream>

using namespace std;

template<class T>
class vector {
private:
    T *storage;
    int maxSize;
    int currentSize;

    void dbSpace() {
        T *tmp = storage;
        storage = new T[maxSize *= 2];
        for (int i = 0; i < currentSize; i++) storage[i] = tmp[i];
        delete tmp;
    }

public:
    explicit vector(int initSize = 10) {
        maxSize = initSize;
        currentSize = 0;
        storage = new T[maxSize];
    }

    vector(const vector &v) {
        maxSize = v.maxSize;
        currentSize = v.currentSize;
        storage = new T[maxSize];
        for (int i = 0; i < currentSize; i++) storage[i] = v.storage[i];
    }

    vector& operator=(const vector& v){
        if (this==&v) return *this;
        maxSize = v.maxSize;
        currentSize = v.currentSize;
        delete []storage;
        storage = new T[maxSize];
        for (int i = 0; i < currentSize; i++) storage[i] = v.storage[i];
    }

    ~vector() { delete[]storage; }

    void insert(int p, const T &x) {
        if (currentSize == maxSize) dbSpace();
        for (int i = currentSize; i > p; i--) storage[i] = storage[i - 1];
        storage[p] = x;
        currentSize++;
    }

    void remove(int p) {
        for (int i = p; i < currentSize - 1; i++) storage[i] = storage[i + 1];
        currentSize--;
    }

    void push_back(const T &x) { insert(currentSize, x); }

    void pop_back() { remove(currentSize - 1); }

    void push_front(const T &x) { insert(0, x); }

    void pop_front() { remove(0); }

    T &operator[](int p) { return storage[p]; }

    int size() { return currentSize; }

    int capacity() { return maxSize; }

    void trav() {
        for (int i = 0; i < currentSize; i++) {
            cout << storage[i] << ' ';
        }
        cout << endl;
    }
};

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

struct item {
    int val;
    bool isTreasure;
    int TreasureNum;

    item(int v=0,bool i=0,int T=0){val=v;isTreasure=i;TreasureNum=T;}
};

struct point {
    int x,y;
    point(int xx=0,int yy=0){x=xx;y=yy;}
};

const int maxn = 107;

item mmp[maxn][maxn];

int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};

int dis[10][10];

vector<point> treasure;

inline int min(int& a,int& b){return (a>b)?b:a;}

int ans=~(1<<31);
int sum=0;
bool vis[10]={1};
void dfs(int i){
    bool f=false;
    for (int j=0;j<treasure.size();j++){
        if (!vis[j] && j!=i){
            vis[j]=1;sum+=dis[i][j];
            dfs(j);
            vis[j]=0;sum-=dis[i][j];
            f=true;
        }
    }
    if (!f){
        ans=min(ans,sum);
    }
}

int main()
{
    for (int i=0;i<10;i++){
        for (int j=0;j<10;j++){
            dis[i][j]=1e6;
        }
    }

    int N,M;cin>>N>>M;

    int x;
    int num=1;
    point start;
    for (int i=1;i<=N;i++){
        for (int j=1;j<=M;j++){
            cin>>x;
            if (x==0) mmp[i][j].val=1;
            else if (x==1){
                mmp[i][j].val=1;
                mmp[i][j].isTreasure=1;
                mmp[i][j].TreasureNum=num++;
                treasure.push_back(point(i,j));
            }
            else if (x==-1){}
            else if (x==2){
                mmp[i][j].val=1;
                mmp[i][j].isTreasure=1;
                start = point(i,j);
                treasure.push_front(start);
            }
        }
    }


    for (int i=0;i<treasure.size();i++){
        bool Vis[maxn][maxn]={0};

        queue<point> curr,next;
        curr.push(treasure[i]);
        Vis[treasure[i].x][treasure[i].y]=1;
        int d=0;

        while (!curr.empty()){
            point tmp=curr.front();curr.pop();
            int x=tmp.x,y=tmp.y;
            if (mmp[x][y].isTreasure) {
                dis[i][mmp[x][y].TreasureNum]=d;
            }
            for (int k=0;k<4;k++){
                int X=x+dir[k][0],Y=y+dir[k][1];
                if (!Vis[X][Y] && mmp[X][Y].val){
                    Vis[X][Y]=1;
                    next.push(point(X,Y));
                }
            }

            if (curr.empty()){
                while (!next.empty()){
                    curr.push(next.front());next.pop();
                }
                d++;
            }
        }
    }

    dfs(0);
    if (ans>=1e6) cout<<-1;
    else cout<<ans;

    return 0;
}

#include <iostream>

using namespace std;

struct point{
    int i,j;
    point(int ii=1,int jj=1){i=ii;j=jj;}
};

const int N = 507;
int a[N][N]={0};

int dir[4][2]={{-1,0},{0,-1},{0,1},{1,0}};
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
    T& front(){return storage[_front+1];}
    T pop(){
        _front=(_front+1)%maxSize;
        return storage[_front];
    }
};

#include <stdio.h>

int main()
{
    int n,m;cin>>n>>m;
    int x;
    for (int i=1;i<=m;i++){
        for (int j=1;j<=n;j++){
            cin>>x;
            if (x==0) a[i][j]=1;
        }
    }

    int ans=0;
    for (int i=1;i<=m;i++){
        for (int j=1;j<=n;j++){
            if (a[i][j]==1){
                queue<point> q;
                q.push(point(i,j));
                while (!q.empty()){
                    point tmp = q.front();
                    q.pop();
                    int ii=tmp.i,jj=tmp.j;
                    for (int k=0;k<4;k++){
                        int I=ii+dir[k][0],J=jj+dir[k][1];
                        if (a[I][J]==1) q.push(point(I,J));
                    }
                    a[ii][jj]=0;
                }
                ans++;
            }
        }
    }

    cout<<ans;

    return 0;
}

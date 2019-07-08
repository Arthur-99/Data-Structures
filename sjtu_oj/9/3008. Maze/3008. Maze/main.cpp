#include <iostream>

using namespace std;

struct point{
    int x,y;
    point(int xx=1,int yy=1){x=xx;y=yy;}
};

const int N = 107;
char a[N][N]={0};
bool vis[N][N]={0};

int dir_wasd[4][2]={{-1,0},{0,-1},{0,1},{1,0}};
int dir_ad[2][2]={{0,-1},{0,1}};
int dir_ws[2][2]={{-1,0},{1,0}};

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

int main()
{
    int n,m;cin>>n>>m;
    int x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;

    char c;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            cin>>c;
            if (c=='*') a[i][j]=0;
            else a[i][j]=c;
        }
    }

    int ans=0;

    queue<point> curr_q,next_q;
    curr_q.push(point(x1,y1));
    vis[x1][y1]=1;
    while (!curr_q.empty()){
        point tmp = curr_q.pop();
        int x=tmp.x,y=tmp.y;

        if (x==x2 && y==y2){
            cout<<ans;
            return 0;
        }

        switch (a[x][y]){
            case '|':{
                for (int k=0;k<2;k++){
                    int X=x+dir_ws[k][0],Y=y+dir_ws[k][1];
                    if (!vis[X][Y] && (a[X][Y] == '.' || a[X][Y] == '|')) {
                        next_q.push(point(X,Y));
                        vis[X][Y]=1;
                    }
                }
//                a[x][y]=0;
                break;
            }
            case '-':{
                for (int k=0;k<2;k++){
                    int X=x+dir_ad[k][0],Y=y+dir_ad[k][1];
                    if (!vis[X][Y] && (a[X][Y] == '.' || a[X][Y] == '-')) {
                        next_q.push(point(X,Y));
                        vis[X][Y]=1;
                    }
                }
//                a[x][y]=0;
                break;
            }
            case '.':{
//                for (int k=0;k<4;k++){
//                    int X=x+dir_wasd[k][0],Y=y+dir_wasd[k][1];
//                    if (a[X][Y]) next_q.push(point(X,Y));
//                }
                for (int k=0;k<2;k++){
                    int X=x+dir_ws[k][0],Y=y+dir_ws[k][1];
                    if (!vis[X][Y] && (a[X][Y] == '.' || a[X][Y] == '|')) {
                        next_q.push(point(X,Y));
                        vis[X][Y]=1;
                    }
                }
                for (int k=0;k<2;k++){
                    int X=x+dir_ad[k][0],Y=y+dir_ad[k][1];
                    if (!vis[X][Y] && (a[X][Y] == '.' || a[X][Y] == '-')) {
                        next_q.push(point(X,Y));
                        vis[X][Y]=1;
                    }
                }
//                a[x][y]=0;
                break;
            }
        }



        if (curr_q.empty()) {
            while (!next_q.empty()) {
                curr_q.push(next_q.pop());
            }
            ans++;
//            cout<<endl<<endl;
//            for (int q=1;q<=n;q++){
//                for (int w=1;w<=m;w++){
//                    if (a[q][w]) cout<<a[q][w];
//                    else cout<<'0';
//                }cout<<endl;
//            }
//            cout<<endl;
        }
    }

    cout<<-1;

    return 0;
}

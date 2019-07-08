#include <iostream>

using namespace std;

struct Point{
    int x,y;
    Point(int xx=0,int yy=0){x=xx;y=yy;}
};

template <class T>
class seqQueue {
    friend ostream&operator<<(ostream& os,const seqQueue& s){
        for (int i=s.front+1;i<=s.rear;i++) os<<s.storage[i]<<'\t';
        return os;
    }
protected:
    T* storage;
    int maxSize;
    void dbSpace(){
        maxSize*=2;
        T* tmp=new T[maxSize];
        for (int i=0;i<size();i++){
            tmp[i]=storage[front+1+i];
        }

        rear=rear-front-1;
        front=-1;
        delete[]storage;
        storage=tmp;
    }

    int front;
    int rear;
public:
    seqQueue(int initSize = 5){
        maxSize=initSize;
        storage=new T[maxSize];
        front=-1;
        rear=-1;
    }
    ~seqQueue(){delete[]storage;}

    void enQueue(const T& x){
        if (rear==maxSize-1) dbSpace();
        storage[++rear]=x;
    }
    T deQueue(){return storage[++front];}
    T& getHead(){ return storage[front+1]; }
    bool isEmpty(){ return front==rear; }
    int size(){return rear-front;}
};

void disp(int d[][1050],int m,int n){
    for (int i=0;i<m+2;i++){
        for (int j=0;j<n+2;j++){
            cout<<d[i][j]<<'\t';
        }cout<<endl;
    }cout<<"\n\n\n";
}

void getd(int d[][1050],int m,int n,int x,int y){
    seqQueue<Point> s;
    s.enQueue(Point(x,y));

    while (!s.isEmpty()){
        Point k=s.deQueue();
        int step = d[k.x][k.y];

        if (d[k.x-1][k.y]==0) {
            d[k.x-1][k.y]=step+1;
            s.enQueue(Point(k.x-1,k.y));
        }
        if (d[k.x+1][k.y]==0) {
            d[k.x+1][k.y]=step+1;
            s.enQueue(Point(k.x+1,k.y));
        }
        if (d[k.x][k.y-1]==0) {
            d[k.x][k.y-1]=step+1;
            s.enQueue(Point(k.x,k.y-1));
        }
        if (d[k.x][k.y+1]==0) {
            d[k.x][k.y+1]=step+1;
            s.enQueue(Point(k.x,k.y+1));
        }
    }

    for (int i=0;i<m+2;i++){
        for (int j=0;j<n+2;j++){
            if (d[i][j]==0) d[i][j]=500000;
        }
    }
    //disp(d,m,n);
}

int d24[1050][1050]={{0}};
int d34[1050][1050]={{0}};

int x4[2000000]={0},y4[2000000]={0};

int main() {
//    seqQueue<int> s;
//    for (int i=0;i<15;i++) s.enQueue(i);
//    s.deQueue();
//    for (int i=0;i<15;i++) s.enQueue(i);
//    cout<<s;
//    return 0;
    ios::sync_with_stdio(false);
    //input
    int n,m;cin>>n>>m;

    //1 padding
    for (int i=0;i<n+2;i++) d24[0][i]=d24[m+1][i]=-1;
    for (int i=0;i<m+2;i++) d24[i][0]=d24[i][n+1]=-1;
    for (int i=0;i<n+2;i++) d34[0][i]=d34[m+1][i]=-1;
    for (int i=0;i<m+2;i++) d34[i][0]=d34[i][n+1]=-1;

    int x2,y2,x3,y3;
    int k=0;

    for (int i=1;i<m+1;i++){
        for (int j=1;j<n+1;j++){
            cin>>d24[i][j];
            if (d24[i][j]==1) {d24[i][j]=-1;}
            else if (d24[i][j]==2) { x2=i;y2=j; d24[i][j]=0; }
            else if (d24[i][j]==3) { x3=i;y3=j; d24[i][j]=0; }
            else if (d24[i][j]==4) { x4[k]=i;y4[k]=j;k++; d24[i][j]=0; }
            d34[i][j]=d24[i][j];
        }
    }

    //dp get d24,d34

    getd(d34,m,n,x2,y2);
    getd(d24,m,n,x3,y3);

    //output
    int min=1000000;
    for (int i=0;i<k;i++){
        //cout<<d34[x4[i]][y4[i]]<<'\t'<<map[x4[i]][y4[i]]<<endl;
        int d = d24[x4[i]][y4[i]]+d34[x4[i]][y4[i]];
        if (min>d) min=d;
    }
    cout<<min<<endl;
    return 0;
}


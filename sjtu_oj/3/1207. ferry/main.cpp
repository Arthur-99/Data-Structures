#include <iostream>
#include <iomanip>

using namespace std;

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
        for (int i=front+1;i<=rear;i++){
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
    seqQueue(int initSize = 20005){
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

int main() {
    //input
    seqQueue<int> bus,van;
    int bus_waittime=0,van_waittime=0;


    int n;cin>>n;
    int type,time;
    for (int i=0;i<n;i++){
        cin>>type>>time;
        if (type==0) bus.enQueue(time);
        else if (type==1) van.enQueue(time);
    }

    int bus_num=bus.size(),van_num=van.size();
    int ship=0;
    for (int t=0;!bus.isEmpty() || !van.isEmpty();t+=10){
        for (ship=0;ship<8 && !bus.isEmpty() && bus.getHead()<=t;ship++){
            bus_waittime+=t-bus.deQueue();
        }
        for (;ship<10 && !van.isEmpty() && van.getHead()<=t;ship++){
            van_waittime+=t-van.deQueue();
        }
        for (;ship<10 && !bus.isEmpty() && bus.getHead()<=t;ship++){
            bus_waittime+=t-bus.deQueue();
        }
//        cout<<"busnum,vannum:"<<bus_num<<' '<<van_num<<endl;
//        cout<<"buswt,vanwt:"<<bus_waittime<<' '<<van_waittime<<endl;
    }

    cout<<fixed<<setprecision(3)<<bus_waittime/(bus_num*1.0)<<' '<<van_waittime/(van_num*1.0);

    return 0;
}
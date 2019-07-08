#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

#define ll long long

template<class T>
class queue {
private:
    T *storage;
    int front, rear;
    int maxSize;

    void dbSpace() {
        T *tmp = storage;

        storage = new T[maxSize * 2];
        for (int i = 1; i < maxSize; i++) storage[i] = tmp[(front + i) % maxSize];

        front = 0;
        rear = maxSize - 1;
        maxSize *= 2;
        delete[]tmp;
    }

public:
    explicit queue(int initSize = 1000000) {
        maxSize = initSize;
        storage = new T[maxSize];
        front = rear = 0;
    }

    ~queue() { delete[]storage; }

    bool isEmpty() { return front == rear; }


    void enQueue(const T &x) {
        if ((rear + 1) % maxSize == front) dbSpace();
        rear = (rear + 1) % maxSize;
        storage[rear] = x;
    }
    void push(const T &x){
        enQueue(x);
    }

    T deQueue() {
        front = (front + 1) % maxSize;
        return storage[front];
    }
    T pop(){
        T ret = storage[rear];
        if (rear) rear--;
        else rear = maxSize-1;
        return ret;
    }

    T &getHead() { return storage[(front + 1) % maxSize]; }

    void trav() {
        for (int i = 0; i < (rear - front) % maxSize; i++) {
            T out = storage[(front + 1 + i) % maxSize];
            if (out == '@') cout << "NULL ";
            else cout << out << ' ';
        }
        cout << endl;
    }

    void cutTail(T x) {
        for (int i = rear; storage[rear] == x; rear = (rear - 1) % maxSize);
    }
};

void swap(ll& a,ll& b){ll t=a;a=b;b=t;}
void Qsort(ll *A, int p, int r) {
    if (p>=r) return;
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    Qsort(A, p, i);
    Qsort(A, i + 2, r);
}

ll l[150007]={0};
ll bt[150007],gt[150007];

int main() {
    queue<ll> b,g;
    int n;cin>>n;

    ll totalTime =0;
    for (int i =0;i<n;i++) {
        cin>>l[i];
        totalTime+=l[i];
    }

    int m;cin>>m;

    int sex,numb=0,numg=0;
    for (int i=0;i<m;i++){
        ll time;
        cin>>sex>>time;
        if (sex==1) {
            bt[numb++]=time;
        }
        else {
            gt[numg++]=time;
        }
    }

    Qsort(bt,0,numb-1);
    Qsort(gt,0,numg-1);
    for (int i=0;i<numb;i++) b.enQueue(bt[i]);
    for (int i=0;i<numg;i++) g.enQueue(gt[i]);


    ll totalb=0,totalg=0;
    ll i,j;
    for (i=0,j=0;j<n;i+=l[j++]){
        for (;(b.getHead()<=i && g.getHead()<=i) && !(b.isEmpty() || g.isEmpty());){
            totalb+=i-b.deQueue();
            totalg+=i-g.deQueue();
        }
    }

    for (;b.getHead()<=i && !b.isEmpty();) totalb+=i-l[j-1]-b.deQueue();
    for (;g.getHead()<=i && !g.isEmpty();) totalg+=i-l[j-1]-g.deQueue();

    cout<<fixed<<setprecision(2)<<1.0*totalb/numb<<' '<<1.0*totalg/numg;

    return 0;
}
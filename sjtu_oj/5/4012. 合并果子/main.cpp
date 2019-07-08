#include <iostream>

using namespace std;

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
    explicit queue(int initSize = 5) {
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

    void push(const T &x) {
        enQueue(x);
    }

    T deQueue() {
        front = (front + 1) % maxSize;
        return storage[front];
    }

    T pop() {
        T ret = storage[rear];
        if (rear) rear--;
        else rear = maxSize - 1;
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

const int N = 2e4+7;

struct node{
    int data;
    node* p;
    node* l;
    node* r;
    node(){p=l=r=NULL;}
};

node nodes[N];

int main() {

    int n;
    cin>>n;

    for (int i=n;i<2*n;i++) cin>>nodes[i].data;

    int min1,min2;
    node*p1,*p2;
    for (int i=n-1;i>0;i--){
        min1=min2=~(1<<31);
        p1=p2=NULL;

        for (int j=i+1;j<2*n;j++){
            if (!nodes[j].p){
                if (nodes[j].data<min1){
                    min2=min1;
                    min1=nodes[j].data;
                    p2=p1;
                    p1=&nodes[j];
                } else if (nodes[j].data<min2){
                    min2=nodes[j].data;
                    p2=&nodes[j];
                }
            }
        }
        nodes[i].data=min1+min2;
        nodes[i].l=p2;
        nodes[i].r=p1;

        p2->p=&nodes[i];
        p1->p=&nodes[i];
    }

    int result=0;
    for (int i=1;i<n;i++) result+=nodes[i].data;

    cout<<result;

    return 0;
}
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

    T deQueue() {
        front = (front + 1) % maxSize;
        return storage[front];
    }

    T &getHead() { return storage[(front + 1) % maxSize]; }

    void trav() {
        for (int i = 0; i < (rear - front) % maxSize; i++) {
            T out = storage[(front + 1 + i) % maxSize];
            if (out == '@') cout<<"NULL ";
            else cout << out << ' ';
        }
        cout << endl;
    }
    void cutTail(T x){
        for (int i = rear; storage[rear]==x; rear = (rear -1) % maxSize);
    }
};

struct node {
    int W;

    node *P;

    node *L;
    node *R;

    node() {P = L = R = nullptr; }
};

node n[100007];

int main() {
    int N;
    cin>>N;

    if (N==1) {
        int l,r,w;
        cin>>l>>r>>w;
        cout<<w<<' ';
        return 0;
    }

    int l,r,w;
    for (int i=0;i<N;i++) {
        cin>>l>>r>>w;
        if (l) {
            n[i].L=&n[l-1];
            n[l-1].P = &n[i];
        }
        if (r) {
            n[i].R=&n[r-1];
            n[r-1].P = &n[i];
        }
        n[i].W=w;
    }

    node root = n[0];
    while (root.P){
        root = *root.P;
    }

    queue<node*> q;

    q.enQueue(&root);
    while (!q.isEmpty()) {
        node* tmp = q.deQueue();
        cout<<tmp->W<<' ';

        if (tmp->L) q.enQueue(tmp->L);
        if (tmp->R) q.enQueue(tmp->R);
    }

    return 0;
}
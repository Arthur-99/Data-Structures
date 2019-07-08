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
    node *P;

    node *L;
    node *R;

    node() {P = L = R = nullptr; }
};

node n[100007];

bool isCMT(node* r){
    queue<node*> q;
    q.enQueue(r);

    while (!q.isEmpty()){
        node* t = q.deQueue();
        if (t == nullptr) break;
        q.enQueue(t->L);
        q.enQueue(t->R);
    }

    while (!q.isEmpty()){
        node* t = q.deQueue();
        if (t != nullptr) return false;
    }
    return true;
}

int main() {
    int N;
    cin>>N;

    int l,r;
    for (int i=0;i<N;i++) {
        cin>>l>>r;
        if (l) {
            n[i].L=&n[l-1];
            n[l-1].P = &n[i];
        }
        if (r) {
            n[i].R=&n[r-1];
            n[r-1].P = &n[i];
        }
    }

    node root = n[0];
    while (root.P){
        root = *root.P;
    }

    if (isCMT(&root)) cout<<"Y";
    else cout<<"N";

    return 0;
}
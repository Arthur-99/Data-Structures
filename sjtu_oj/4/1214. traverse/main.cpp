#include <iostream>


using namespace std;

template<class T>
class stack {
    T *storage;
    int top_p;
    int maxSize;

    void dbSpace() {
        T *tmp = storage;
        storage = new T[maxSize *= 2];
        for (int i = 0; i <= top_p; i++) storage[i] = tmp[i];
        delete tmp;
    }

public:
    stack(int initSize = 5) {
        maxSize = initSize;
        storage = new T[maxSize];
        top_p = -1;
    }

    ~stack() { delete[]storage; }

    void push(const T &x) {
        if (top_p == maxSize - 1) dbSpace();
        storage[++top_p] = x;
    }

    T pop() { return storage[top_p--]; }

    void trav() {
        for (int i = 0; i <= top_p; i++) cout << storage[i] << ' ';
        cout << endl;
    }

    bool empty() { return top_p == -1; }

    T &top() { return storage[top_p]; }
};

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
            if (out == '@') cout << "NULL ";
            else cout << out << ' ';
        }
        cout << endl;
    }

    void cutTail(T x) {
        for (int i = rear; storage[rear] == x; rear = (rear - 1) % maxSize);
    }
};

struct node {
    int W;

    node *P;

    node *L;
    node *R;

    node() { P = L = R = nullptr; }
};

struct stnode {
    node *N;
    int timesPop;

    stnode(node *n = nullptr) : N(n), timesPop(0) {}
};


class BinaryTree {
private:
    node *root;
public:
    explicit BinaryTree(node *p) : root(p) {}

    void preOrder() const {
        stack<node *> s;
        node *curr = root;
        if (curr == nullptr) return ;

        s.push(curr);
        while (!s.empty()) {
            curr = s.pop();
            cout << curr->W << ' ';
            if (curr->R) s.push(curr->R);
            if (curr->L) s.push(curr->L);
        }
        cout << endl;
    }

    void postOrder() const {
        stack<stnode> s;
        stnode curr(root);

        if (curr.N == nullptr) return ;

        s.push(stnode(curr));
        while (!s.empty()) {
            curr = s.pop();

            if (++curr.timesPop == 3) {
                cout << curr.N->W << ' ';
                continue;
            }
            s.push(curr);

            if (curr.timesPop == 1) {
                if (curr.N->L) s.push(stnode(curr.N->L));
            } else {
                if (curr.N->R) s.push(stnode(curr.N->R));
            }
        }
        cout << endl;
    }

    void clear(node *n) {
        if (n->L) clear(n->L);
        if (n->R) clear(n->R);
        delete n;
        n = nullptr;
    }
};

node n[100007];

int main() {
    int N;
    cin >> N;

    if (N == 1) {
        int l, r, w;
        cin >> l >> r >> w;
        cout << w << endl;
        cout << w << endl;
        cout << w << endl;
        return 0;
    }

    int l, r, w;
    for (int i = 1; i <= N; i++) {
        cin >> l >> r >> w;
        if (l) {
            n[i].L = &n[l];
            n[l].P = &n[i];
        }
        if (r) {
            n[i].R = &n[r];
            n[r].P = &n[i];
        }
        n[i].W = w;
    }

    node root = n[1];

    while (root.P) {
        root = *(root.P);
    }

    BinaryTree b(&root);

    b.preOrder();
    b.postOrder();


    queue<node *> q;

    q.enQueue(&root);
    while (!q.isEmpty()) {
        node *tmp = q.deQueue();
        cout << tmp->W << ' ';

        if (tmp->L) q.enQueue(tmp->L);
        if (tmp->R) q.enQueue(tmp->R);
    }

    return 0;
}
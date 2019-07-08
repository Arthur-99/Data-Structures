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

struct node {
    int W;

    node *P;
    node *S;
    node *B;
    node *elder_brother;

    node* tmp;

    node() { P = S = B = elder_brother = tmp = nullptr; }
};

struct stnode {
    node *N;
    int timesPop;

    stnode(node *n = nullptr) : N(n), timesPop(0) {}
};

int num_of_sons(stnode* n){
    node* n_s = n->N->S;
    int num=0;
    while (n_s){
        n_s=n_s->B;
        num++;
    }
    return num;
}

class BinaryTree {
private:
    node *root;
public:
    explicit BinaryTree(node *p) : root(p) {}

    void preOrder() const {
        queue<node*> q;
        node* tmp;

        if (root== nullptr) return;
        q.enQueue(root);

        while (!q.isEmpty()){
            tmp = q.pop();
            cout<<tmp->W<<' ';

            tmp = tmp->S;
            if (tmp) {
                while (tmp->B) {
                    tmp = tmp->B;
                }
                while (tmp) {
                    q.push(tmp);
                    tmp = tmp->elder_brother;
                }
            }
        }
        cout<<endl;
    }

    void postOrder(){
        stack<stnode> s;
        stnode curr = root;

        s.push(curr);

        while (!s.empty()) {
            curr = s.pop();

            if (curr.N->tmp == nullptr){
                cout<< curr.N->W<<' ';
                continue;
            }

            node* t = curr.N->tmp;
            curr.N->tmp = curr.N->tmp->B;
            s.push(curr);

            if (curr.N->tmp) s.push(stnode(curr.N->tmp->elder_brother));
            else s.push(stnode(t));
        }
        cout<<endl;
        //postOrder(root);
    }

    void levelOrder() const {
        queue<node*> q;
        node* tmp;

        if (root== nullptr)  return ;
        q.enQueue(root);

        while(!q.isEmpty()){
            tmp = q.deQueue();
            cout<<tmp->W<<' ';
            tmp = tmp->S;
            while (tmp) {
                q.enQueue(tmp);
                tmp = tmp->B;
            }
        }
        cout<<endl;
    }

    void postOrder(node* t){
        if (t == nullptr) return;
        postOrder(t->S);
        cout<<t->W<<' ';
        postOrder(t->B);
    }
};

node n[100007];

int main() {
    int N;
    cin >> N;

    int s, b, w;
    for (int i = 1; i <= N; i++) {
        cin >> s >> b >> w;
        if (s) {
            n[i].S = n[i].tmp = &n[s];
            n[s].P = &n[i];
        }
        if (b) {
            n[i].B = &n[b];
            n[b].elder_brother = &n[i];
        }
        n[i].W = w;
    }

    node root = n[N];

    while (root.elder_brother || root.P) {
        if (root.elder_brother) root = *(root.elder_brother);
        if (root.P) root = *(root.P);
    }

    BinaryTree tree(&root);

    tree.preOrder();
    tree.postOrder();
    tree.levelOrder();

    return 0;
}
#include <iostream>

using namespace std;

template<class T>
class stack {
private:
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
    stack(int initSize = 100007) {
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
    explicit queue(int initSize = 100007) {
        maxSize = initSize;
        storage = new T[maxSize];
        front = rear = 0;
    }

    ~queue() { delete[]storage; }

    bool isEmpty() { return front == rear; }

    int size(){ return (rear-front)%maxSize;}


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

struct node{
    int no;

    node* p;
    node* l;
    node* r;

    node(int n=0):no(n){p=l=r= nullptr;}
};

class BinaryTree {
public:
    node *root;
public:
    BinaryTree(node *p) : root(p) {}
    BinaryTree(int i){root = new node(i);}
    //~BinaryTree(){clear(root);}

    node* find(node* t,int no){
        stack<node *> s;
        node *curr = root;
        if (curr == nullptr) return nullptr;

        s.push(curr);
        while (!s.empty()) {
            curr = s.pop();
            if (curr->no == no) return curr;
            if (curr->r) s.push(curr->r);
            if (curr->l) s.push(curr->l);
        }

        return nullptr;
    }
    node* find(int no){
        return find(root,no);
    }

    void preOrder() const {
        queue<int> res;

        stack<node *> s;
        node *curr = root;
        if (curr == nullptr) return ;

        s.push(curr);
        while (!s.empty()) {
            curr = s.pop();
            res.enQueue(curr->no);
            if (curr->r) s.push(curr->r);
            if (curr->l) s.push(curr->l);
        }

        while (res.size()>1) cout<<res.deQueue()<<' ';
        cout<<res.deQueue();
    }

    void clear(node *n) {
        if (n->l) clear(n->l);
        if (n->r) clear(n->r);
        delete n;
        n = nullptr;
    }
};

node nodes[100007];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    nodes[1].no=1;

    BinaryTree tree(&nodes[1]);

    int m;
    cin>>m;

    for (int i=0;i<m;i++){
        int operation;
        cin>>operation;

        if (operation==1) {
            int a,b,c;
            cin>>a>>b>>c;

            if (b==c) { cout<< "Error!\n"; continue;}

//            node* pa = tree.find(a);
//            node* pb = tree.find(b);
//            node* pc = tree.find(c);


            if (nodes[a].no && !nodes[a].l && !nodes[a].r && !nodes[b].no && !nodes[c].no ){
//                pa->l = new node(b);
//                pa->r = new node(c);
//
//                pa->l->p=pa;
//                pa->r->p=pa;
                nodes[b].no=b;
                nodes[c].no=c;

                nodes[a].l=&nodes[b];
                nodes[a].r=&nodes[c];

                nodes[b].p=&nodes[a];
                nodes[c].p=&nodes[a];


                cout<<"Ok!\n";


            } else { cout<< "Error!\n"; }

        }
        else if (operation == 2){
            int a;
            cin>>a;

            if (a<1 || a>100000) { cout<< "Error!\n"; continue;}

//            node* pa = tree.find(a);

            if (nodes[a].no) {
                if (nodes[a].p) cout<<nodes[a].p->no<<' ';
                else cout<<"0 ";

                if (nodes[a].l) cout<<nodes[a].l->no<<' ';
                else cout<<"0 ";

                if (nodes[a].r) cout<<nodes[a].r->no<<'\n';
                else cout<<"0\n";

            } else { cout<< "Error!\n"; }

        }

        else if (operation == 3){
            int a;
            cin>>a;

            if (a<=1 || a>100000) { cout<< "Error!\n"; continue;}

//            node* pa = tree.find(a);

            if (nodes[a].no && nodes[a].p->no) {
                node* pa_p = nodes[a].p;

                node* tmp = pa_p->l;

                if (&nodes[a]!=tmp) cout<<pa_p->l->no<<'\n';

                else cout<<pa_p->r->no<<'\n';

                pa_p->l = pa_p->r;
                pa_p->r = tmp;
            } else { cout<< "Error!\n"; }

        }
    }



    //preOrder
    tree.preOrder();



    cout<<flush;



    return 0;
}
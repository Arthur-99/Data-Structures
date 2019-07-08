#include <iostream>
#include <cstring>

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

struct stint{
    int data;
    int popTimes;
    stint(int d=0):data(d),popTimes(0){}
};

char str[1500007] = {0};

struct node{
    char data;
    node* L;
    node* R;
    node(char d):data(d){L=R= nullptr;}
};
void clear(node* t){
    if (t){
        clear(t->R);
        clear(t->L);
        delete t;
    }
}


node* pre(char* s,int l,int r){
    if (l>=r) {
        return nullptr;
    }

    node* root = new node(s[l]);

    int k=1;// = mylog2(r - l) + 1;
    int tmp1 = r-l;
    while(tmp1/=2) k++;


    int num;// = (r-l) - (mypow(2, k - 1) - 1);
    int tmp2=1;
    for (int i=0;i<k-1;i++) tmp2*=2;
    num = r-l -(tmp2-1);


    int pivot;

    int mypow2k2=1,mypow2k1=1;
    for (int i=0;i<k-2;i++) {mypow2k2*=2;mypow2k1*=2;} mypow2k1*=2;

    if (num > (mypow2k2)) pivot = l + mypow2k1;
    else pivot = r - (mypow2k2 -1);

    root->L=pre(s,l+1,pivot);
    root->R=pre(s,pivot,r);

    return root;
}

node* in(char* s,int l,int r) {
    if (l >= r) {
        return nullptr;
    }

    int k=1;// = mylog2(r - l) + 1;
    int tmp1 = r-l;
    while(tmp1/=2) k++;


    int num;// = (r-l) - (mypow(2, k - 1) - 1);
    int tmp2=1;
    for (int i=0;i<k-1;i++) tmp2*=2;
    num = r-l -(tmp2-1);


    int mypow2k2=1,mypow2k1=1;
    for (int i=0;i<k-2;i++) {mypow2k2*=2;mypow2k1*=2;} mypow2k1*=2;

    int pivot;
    if (num > (mypow2k2)) pivot = l + mypow2k1 - 1;
    else pivot = r - (mypow2k2);

    node *root = new node(s[pivot]);

    root->L = in(s, l, pivot);
    root->R = in(s, pivot+1, r);

    return root;
}

node* post(char* s,int l,int r) {
    if (l >= r) {
        return nullptr;
    }

    node *root = new node(s[r-1]);

    int k=1;// = mylog2(r - l) + 1;
    int tmp1 = r-l;
    while(tmp1/=2) k++;


    int num;// = (r-l) - (mypow(2, k - 1) - 1);
    int tmp2=1;
    for (int i=0;i<k-1;i++) tmp2*=2;
    num = r-l -(tmp2-1);


    int mypow2k2=1,mypow2k1=1;
    for (int i=0;i<k-2;i++) {mypow2k2*=2;mypow2k1*=2;} mypow2k1*=2;

    int pivot;
    if (num > mypow2k2) pivot = l + mypow2k1 - 1;
    else pivot = r - 1 - (mypow2k2 - 1);

    root->L = post(s, l, pivot);
    root->R = post(s, pivot, r-1);

    return root;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int len;
        char order[15], coding[15];
        cin >> len >> order >> coding;

        cin >> str;

        if (strcmp(order, "PREORDER") == 0 && strcmp(coding, "ENCODE") == 0) {
            stack<int> index;
            int root = 0;
            index.push(root);
            while (!index.empty()){
                root = index.pop();
                cout<<str[root];
                int ls=2*root+1;
                int rs = 2*root+2;
                if (rs<len) index.push(rs);
                if (ls<len) index.push(ls);
            }
            cout<<'\n';
        }
        else if (strcmp(order, "INORDER") == 0 && strcmp(coding, "ENCODE") == 0) {
            stack<stint> index;
            int root = 0;
            stint curr(root);
            index.push(curr);
            while (!index.empty()){
                curr = index.pop();
                if (++curr.popTimes == 2){
                    cout<<str[curr.data];
                    if (2*curr.data+2<len) index.push(2*curr.data+2);
                }else {
                    index.push(curr);
                    if (2*curr.data+1<len) index.push(2*curr.data+1);
                }
            }
            cout<<'\n';
        } else if (strcmp(order, "POSTORDER") == 0 && strcmp(coding, "ENCODE") == 0) {
            stack<stint> index;
            int root = 0;
            stint curr(root);
            index.push(curr);
            while (!index.empty()){
                curr = index.pop();
                if (++curr.popTimes == 3){
                    cout<<str[curr.data];
                    continue;
                }
                index.push(curr);
                if (curr.popTimes == 1){
                    if (2*curr.data+1<len) index.push(2*curr.data+1);
                }
                else {
                    if (2*curr.data+2<len) index.push(2*curr.data+2);
                }
            }
            cout<<'\n';
        } else if (strcmp(order, "PREORDER") == 0 && strcmp(coding, "DECODE") == 0) {
            node* root = pre(str,0,len);
            queue<node*> q;

            q.enQueue(root);
            while (!q.isEmpty()){
                node* tmp = q.deQueue();
                cout<<tmp->data;

                if (tmp->L) q.enQueue(tmp->L);
                if (tmp->R) q.enQueue(tmp->R);
            }
            cout<<'\n';
            clear(root);
        } else if (strcmp(order, "INORDER") == 0 && strcmp(coding, "DECODE") == 0) {
            node* root = in(str,0,len);
            queue<node*> q;

            q.enQueue(root);
            while (!q.isEmpty()){
                node* tmp = q.deQueue();
                cout<<tmp->data;

                if (tmp->L) q.enQueue(tmp->L);
                if (tmp->R) q.enQueue(tmp->R);
            }
            cout<<'\n';
            clear(root);
        } else if (strcmp(order, "POSTORDER") == 0 && strcmp(coding, "DECODE") == 0) {
            node* root = post(str,0,len);
            queue<node*> q;

            q.enQueue(root);
            while (!q.isEmpty()){
                node* tmp = q.deQueue();
                cout<<tmp->data;

                if (tmp->L) q.enQueue(tmp->L);
                if (tmp->R) q.enQueue(tmp->R);
            }
            cout<<'\n';
            clear(root);
        }
    }

    return 0;
}

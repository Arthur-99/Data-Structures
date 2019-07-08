#include <iostream>
#include <cmath>
#include <cstring>

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

struct node{
    char data;

    node* L;
    node* R;

    node(char d,node* l= nullptr,node* r= nullptr){
        data = d;
        L = l;
        R = r;
    }
};

char pre[30]={0};
char mid[30]={0};

void clear(node* t){
    if (t){
        clear(t->R);
        clear(t->L);
        delete t;
    }
}

node* create(char* p,char* m,int len){
    if (len<=0) return 0;

    node* root = new node(p[0]);

    int i;
    for (i=0;i<len;i++){
        if (m[i]==root->data) break;
    }

    root->L = create(p+1,m,i);
    root->R = create(p+i+1,m+i+1,len-i-1);

    return root;
}

int height(node* t){
    if (t==0) return 0;
    return 1+ max(height(t->L),height(t->R));
}


int main() {
    cin>>pre>>mid;
    int len = (int)strlen(pre);

    node* root = create(pre,mid,len);
    int h0 = height(root);

    queue<node*> q;
    queue<char> qq;

    q.enQueue(root);
    while (!q.isEmpty() && height(root)<=h0+1){
        node* tmp = q.deQueue();
        qq.enQueue(tmp->data);

        if (tmp->L) q.enQueue(tmp->L);
        else {
            node* zero = new node('@');
            q.enQueue(zero);
            tmp->L=zero;
        }
        if (tmp->R) q.enQueue(tmp->R);
        else {
            node* zero = new node('@');
            q.enQueue(zero);
            tmp->R=zero;
        }
    }

    qq.cutTail('@');
    qq.trav();

    clear(root);

    return 0;
}
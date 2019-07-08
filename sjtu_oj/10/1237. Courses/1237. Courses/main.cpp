#include <iostream>

using namespace std;

template<class T>
class vector {
private:
    T *storage;
    int maxSize;
    int currentSize;

    void dbSpace() {
        T *tmp = storage;
        storage = new T[maxSize *= 2];
        for (int i = 0; i < currentSize; i++) storage[i] = tmp[i];
        delete tmp;
    }

public:
    explicit vector(int initSize = 5) {
        maxSize = initSize;
        currentSize = 0;
        storage = new T[maxSize];
    }

    vector(const vector &v) {
        maxSize = v.maxSize;
        currentSize = v.currentSize;
        storage = new T[maxSize];
        for (int i = 0; i < currentSize; i++) storage[i] = v.storage[i];
    }

    vector& operator=(const vector& v){
        if (this==&v) return *this;
        maxSize = v.maxSize;
        currentSize = v.currentSize;
        delete []storage;
        storage = new T[maxSize];
        for (int i = 0; i < currentSize; i++) storage[i] = v.storage[i];
    }

    ~vector() { delete[]storage; }

    void insert(int p, const T &x) {
        if (currentSize == maxSize) dbSpace();
        for (int i = currentSize; i > p; i--) storage[i] = storage[i - 1];
        storage[p] = x;
        currentSize++;
    }

    void remove(int p) {
        for (int i = p; i < currentSize - 1; i++) storage[i] = storage[i + 1];
        currentSize--;
    }

    void push_back(const T &x) { insert(currentSize, x); }

    void pop_back() { remove(currentSize - 1); }

    void push_front(const T &x) { insert(0, x); }

    void pop_front() { remove(0); }

    T &operator[](int p) { return storage[p]; }

    int size() { return currentSize; }

    int capacity() { return maxSize; }

    void trav() {
        for (int i = 0; i < currentSize; i++) {
            cout << storage[i] << ' ';
        }
        cout << endl;
    }
};

template <class T>
class queue{
    T* storage;
    int maxSize;
    int _front,_rear;
    void dbSpace(){
        T* tmp=storage;
        storage=new T[2*maxSize];
        for (int i=1;i<maxSize;i++) storage[i]=tmp[(_front+i)%maxSize];
        _front=0;_rear=maxSize-1;
        maxSize*=2;
        delete []tmp;
    }
public:
    queue(int initSize=10){
        storage = new T[initSize];
        maxSize=initSize;
        _front=_rear=0;
    }
    ~queue(){delete []storage;}

    bool empty(){return _front==_rear;}

    void push(const T& x){
        if ((_rear+1)%maxSize==_front) dbSpace();
        _rear=(_rear+1)%maxSize;
        storage[_rear]=x;
    }
    T& front(){return storage[(_front+1)%maxSize];}
    T pop(){
        _front=(_front+1)%maxSize;
        return storage[_front];
    }
};


struct _course{
    int in_degree;
    vector<int> children;
    _course(){in_degree=0;}
};

const int maxn=1e4+7;

_course c[maxn];

int main()
{
    int n,m;cin>>n>>m;
    int a,b;
    for (int i=0;i<m;i++){
        cin>>a>>b;
        c[b].children.push_back(a);
        c[a].in_degree++;
    }

    queue<int> curr,next;
    for (int i=1;i<=n;i++){
        if (c[i].in_degree==0){
            curr.push(i);
        }
    }

    int ans=0;
    while (!curr.empty()){
        int tmp=curr.pop();
        for (int i=0;i<c[tmp].children.size();i++){
            c[c[tmp].children[i]].in_degree--;
            if (c[c[tmp].children[i]].in_degree==0){
                next.push(c[tmp].children[i]);
            }
        }
        if (curr.empty()){
            while (!next.empty()){
                curr.push(next.pop());
            }
            ans++;
        }
    }

    cout<<ans;

    return 0;
}

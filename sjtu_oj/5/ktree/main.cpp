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
        delete[]tmp;
    }

public:
    stack(int initSize = 30000) {
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

    bool empty() { return top_p == -1; }

    T &top() { return storage[top_p]; }

    void clear() { top_p = -1; }
};


const int N = 100;

class bigint {
    friend istream &operator>>(istream &is, bigint &b) {
        stack<int> tmp;
        char c;
        while ((c = is.get()) != '\n') tmp.push(c - '0');
        int len = 0;
        while (!tmp.empty()) b.data[len++] = tmp.pop();
        b.len = len;
        return is;
    }

    friend ostream &operator<<(ostream &os, const bigint &b) {
        for (int i = 0; i < b.len; i++) os << b.data[b.len - 1 - i];
        return os;
    }
public:
    int data[N];
    int len;
public:
    bigint() = default;

    bigint(const bigint &b) {
        len = b.len;
        for (int i = 0; i < len; i++) data[i] = b.data[i];
    }

    explicit bigint(int d[], int l) {
        len = l;
        for (int i = 0; i < len; i++) {
            data[i] = d[i];
        }
    }

    explicit bigint(int x) {
        for (int i = 0; i < N; i++)data[i] = 0;
        len = 0;
        while (x) {
            data[len++] = x % 10;
            x /= 10;
        }
    }

    bigint operator+(const bigint &b) {
        int rdata[N] = {0};
        int rlen = len > b.len ? len : b.len;
        for (int i = 0; i < rlen; i++) {
            rdata[i] += data[i] + b.data[i];
            rdata[i + 1] += rdata[i] / 10;
            rdata[i] = rdata[i] % 10;
        }
        rlen++;
        while ((rdata[rlen] == 0) && (rlen > 0)) rlen--;
        rlen++;
        return bigint(rdata, rlen);
    }

    bigint &operator=(const bigint &b) {
        if (this == &b) return *this;
        for (int i = 0; i < N; i++)data[i] = 0;
        len = b.len;
        for (int i = 0; i < len; i++) data[i] = b.data[i];
        return *this;
    }
};



int main() {
    bigint a[55];
    bigint b[55];


    int k,h;
    cin>>k>>h;

    for (int i=0;i<55;i++) {
        a[i]=bigint(0);
        b[i]=bigint(0);
    }

    a[0]=bigint(1);

    for (int i=1;i<h;i++){
        //b=0
        for (int j=0;j<k;j++) {
            b[j]=bigint(0);
        }

        //a->b
        for (int j=0;j<k;j++){
            if (a[j].len){
                for (int t=0;t<k-j;t++){
                    b[t]=b[t]+a[j];
                }
            }
        }

        //a=b
        for (int j=0;j<k;j++) a[j]=b[j];
    }

    bigint res=bigint(0);
    for (int i=0;i<k;i++) res=res+a[i];
    cout<<res;

    return 0;
}
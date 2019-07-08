#include <iostream>
#include <cmath>

using namespace std;

// for inputting
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


const int N = 2018;

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

    friend bool operator>(const bigint &B, const bigint &b) {
        if (B.len > b.len) return true;
        else if (B.len < b.len) return false;
        else {
            int i = B.len - 1;
            while ((B.data[i] == b.data[i]) && i >= 0) i--;
            if (i < 0) return false;
            else return B.data[i] > b.data[i];
        }
    }

    friend bool operator<=(const bigint &B, const bigint &b) {
        return !(B > b);
    }

    friend bool operator==(const bigint& b, long long l){
        int t = 0;
        while (t<b.len){
            if (b.data[t] != l%10) return false;
            l/=10;
            t++;
        }
        return true;
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

    bigint(int d[], int l) {
        len = l;
        for (int i = 0; i < len; i++) {
            data[i] = d[i];
        }
    }

    bigint(int x) {
        for (int i = 0; i < N; i++)data[i] = 0;
        len = 0;
        while (x) {
            data[len++] = x % 10;
            x /= 10;
        }
    }

    bool isOdd() {
        if (len > 0 && data[0] % 2 != 0) return true;
        else return false;
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

    bigint operator-(const bigint &b) {
        int rdata[N] = {0};
        int rlen = len > b.len ? len : b.len;
        for (int i = 0; i < rlen; i++) {
            rdata[i] += data[i] - b.data[i] + 10;
            rdata[i + 1] += rdata[i] / 10 - 1;
            rdata[i] = rdata[i] % 10;
        }
        rlen++;
        while ((rdata[rlen] == 0) && (rlen > 0)) rlen--;
        rlen++;
        return bigint(rdata, rlen);
    }

    bigint operator*(const bigint &b) {
        int rdata[N] = {0};
        int rlen = 0;

        for (int i = 0; i < len; i++) {
            for (int j = 0; j < b.len; j++) {
                rdata[i + j] += b.data[j] * data[i];
            }
        }

        for (int i = 0; i < len + b.len + 5; i++) {
            rdata[i + 1] += rdata[i] / 10;
            rdata[i] = rdata[i] % 10;
            rlen++;
        }

        while ((rdata[rlen] == 0) && rlen > 0) rlen--;
        rlen++;

        return bigint(rdata, rlen);
    }

    bigint div2() {
        int rdata[N] = {0}, rlen = len;
        for (int i = 0; i < len; i++) rdata[i] = data[i];

        for (int i = len - 1; i > 0; i--) {
            rdata[i - 1] += (rdata[i] % 2) * 10;
            rdata[i] = rdata[i] / 2;
        }
        rdata[0] /= 2;

        rlen++;
        while ((rdata[rlen] == 0) && rlen > 0) rlen--;
        rlen++;
        return bigint(rdata, rlen);
    }

    bigint &operator=(const bigint &b) {
        if (this == &b) return *this;
        for (int i=0;i<N;i++) data[i]=0;
        len = b.len;
        for (int i = 0; i < len; i++) data[i] = b.data[i];
        return *this;
    }

    bigint find_m() {
        // m(m-1)/2 < n <= m(m+1)/2
        bigint m(9);

        bigint n_mult_2 = bigint(2) * (*this);

        while (n_mult_2 > (m * m + m)) {
            m.data[m.len++] = 9;
        }

        //example : find 3495 : 9 -> 99 -> 999 -> 9999
        //                      9999 -> 8999 -> ... -> 2999, 2999 -> 3999
        //                      3999 -> 3899 -> ... -> 3399, 3399 -> 3499
        //                      3499 -> 3489, 3489 -> 3499
        //                      3499 -> 3498 -> ... -> 3495

        bool a = n_mult_2 > (m * m + m);  //m is smaller
        bool b = n_mult_2 <= (m * m - m); //m is bigger
        int t = m.len - 1;
        while (a || b) {
            if (a) {
                m.data[t]++;
                t--;
            }
            if (b) {
                if (m.data[t]) m.data[t]--;
                else t--;
            }

            bigint m_by_m = m * m;
            a = n_mult_2 > (m_by_m + m);
            b = n_mult_2 <= (m_by_m - m);
        }

        return m;
    }
};

long long pow(int a,int b){
    long long res =1;
    for (int i=0;i<b;i++) res *= a;
    return res;
}

int main() {
//    for (int q = 1;q<99999999;q++){
//        bigint n(q);
//        long long l=0;
//        for (int i = 0; i < n.len; i++) {
//           l += n.data[i] * pow(10, i);
//        }
//
//        if (!(n.div2() == l/2)) cout<<l<<endl;
//    }
//
//    return 0;
//    for (int q=1;q<9999999;q++) {
//       bigint n(q);
////       cin >> n;
//
//       long long l = 0;
//       for (int i = 0; i < n.len; i++) {
//           l += n.data[i] * pow(10, i);
//       }
//
//       long long mm = (1 + sqrt(1 + 8 * l))/2;
//       while ((mm*(mm-1)) >= 2 * l) mm--;
//        while ((mm*(mm+1)) < 2 * l) mm++;
//
//
//       bigint m = n.find_m();
//
//       if (!(m == mm)) cout<<n<<endl;
//
//    }

    bigint n;
    cin>>n;

    bigint m = n.find_m();
    bigint num = n - ((m * (m - bigint(1))).div2());

    if (m.isOdd()) cout << m + 1 - num << '/' << num;
    else cout << num << '/' << m + 1 - num;

    return 0;
}
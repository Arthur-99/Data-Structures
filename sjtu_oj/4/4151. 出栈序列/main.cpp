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
        delete []tmp;
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

    bool empty() { return top_p == -1; }

    T &top() { return storage[top_p]; }

    void clear(){ top_p = -1; }
};

int a[100007];
stack<int> input;
stack<int> save;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin>>T;
    for (int q=0;q<T;q++){
        int n;
        cin>>n;

        input.clear();

        for (int i=0;i<n;i++) {
            cin>>a[i];
            input.push(n-i);
        }

        save.clear();

        bool flag = true;

        for(int i=0;i<n;){
            //a[i];
            if (!input.empty() && !save.empty()) {
                if (a[i] != input.top() && a[i] != save.top()) {
                    save.push(input.top());
                    input.pop();
                }
            }

            else if (!input.empty() && save.empty()) {
                if (a[i] != input.top()) {
                    save.push(input.top());
                    input.pop();
                    continue;
                }
            }

            else if (input.empty() && !save.empty()){
                if (a[i]!=save.top()){
                    flag = false;
                    break;
                }
            }

            else {
                flag = false;
                break;
            }




            if (!input.empty() && a[i]==input.top()) {
                input.pop();
                i++;
            }
            else if (!save.empty() && a[i]==save.top()) {
                save.pop();
                i++;
            }
        }

        if (flag) cout<<"Yes\n";
        else cout<<"No\n";
    }

    cout<<flush;

    return 0;
}
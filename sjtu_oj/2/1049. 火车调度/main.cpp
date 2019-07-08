#include <iostream>

using namespace std;

template <class T>
class stack {
private:
    T* elem;
    int top_p;
    int maxSize;
/*
    void doubleSpace(){
        maxSize *= 2;

        T* tmp = elem;
        elem = new T[maxSize];

        for (int i=0;i<maxSize;i++) elem[i]=tmp[i];

        delete []elem;
    }
*/
public:
    stack(int initSize=10){
        elem = new T[initSize];
        maxSize = initSize;
        top_p = -1;
    }
    bool isFull() {return top_p == maxSize-1; }
    bool isEmpty() { return top_p==-1; }
    void push(const T& x){
        //if (top_p == maxSize-1) doubleSpace();
        top_p++;
        elem[top_p] = x;
    }
    T pop() { return elem[top_p--]; }
    T top() { return elem[top_p]; }

    ~stack() { delete[]elem; }

    void trav(){
        int p=-1;
        while (p!=top_p){
            p++;
            cout<<elem[p]<<' ';
        }
        cout<<endl;
    }
};

int main() {
    int T;cin>>T;
    for (int q=0;q<T;q++){

        int n,M;cin>>n>>M;
        const int N=n;

        int target[N];
        for (int i=0;i<N;i++) cin>>target[i];

        stack<int> before(N);
        for (int i=N-1;i>=0;i--) before.push(i);

        stack<int> station(M);

        bool flag=1;
        for (int i=0;i<N;i++){

            if (station.isEmpty() && !before.isEmpty())
            {
                while (target[i]!=before.top() && !before.isEmpty() && !station.isFull())
                    station.push(before.pop());
                if (target[i]==before.top())
                    before.pop();
                else if (before.isEmpty()){
                    flag=0;
                    break;
                } else if (station.isFull()){
                    flag=0;
                    break;
                }
            }
            else if (before.isEmpty() && !station.isEmpty())
            {
                if (target[i]==station.top())
                    station.pop();
                else{
                    flag=0;
                    break;
                }
            }
            else if (before.isEmpty() && station.isEmpty())
            {
                flag=0;
                break;
            }
            else
            {
                if (target[i]==station.top())
                    station.pop();
                else if (target[i]==before.top())
                    before.pop();
                else{
                    while (target[i]!=before.top() && !before.isEmpty() && !station.isFull())
                        station.push(before.pop());
                    if (target[i]==before.top())
                        before.pop();
                    else if (before.isEmpty()){
                        flag=0;
                        break;
                    } else if (station.isFull()){
                        flag=0;
                        break;
                    }
                }
            }


            //station.trav();
            //before.trav();
        }

        if (flag) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }

    return 0;
}
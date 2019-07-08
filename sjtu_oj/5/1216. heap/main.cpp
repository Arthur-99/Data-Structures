#include <iostream>
#include <cstring>

using namespace std;

template <class T>
class priorityQueue{
public:
    int currentSize;
    int maxSize;
    T* array;

    void dbSpace(){
        T* tmp = array;
        array = new T[maxSize*=2];
        for (int i=0;i<=currentSize;i++) array[i]=tmp[i];
        delete []tmp;
    }
    void percolateDown(int hole){
        //cout<<"percolateDown:\n";
        int child;
        T tmp = array[hole];
        for (;hole * 2 <= currentSize;hole = child){
            child = hole*2;
            if (child!=currentSize && array[child+1]<array[child]){
                child++;
            }
            if (array[child]<tmp){
                array[hole]=array[child];
                // trav();
            } else {
                break;
            }
        }
        array[hole]=tmp;
        // trav();
    }

    void buildHeap(){
        for (int i=currentSize/2;i>0;i--){
            percolateDown(i);
        }
    }

public:
    priorityQueue(int capacity=20007){
        array = new T[capacity];
        maxSize=capacity;
        currentSize=0;
    }
    ~priorityQueue(){delete[]array;}

    void enQueue(const T& x){
        if (currentSize == maxSize-1) dbSpace();

        int hole = ++currentSize;
        for (;hole>1 && x<array[hole/2];hole/=2){
            array[hole]=array[hole/2];
        }
        array[hole]=x;
    }
    T deQueue(){
        T minItem = array[1];
        array[1] = array[currentSize--];
        percolateDown(1);
        return minItem;
    }
    T& getHead(){return array[1];}

    bool isEmpty(){return currentSize==0;}

    void trav(){
        for (int i=1;i<=currentSize;i++) cout<<array[i]<<' ';
        cout<<endl;
    }
};

#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int M;
    cin>>M;

    priorityQueue<ll> p;

    for (int i=0;i<M;i++){
        char operation[15];
        cin>>operation;

        if (strcmp(operation,"insert")==0){
            ll x;
            cin>>x;
            p.enQueue(x);
            //p.trav();
        }else if (strcmp(operation,"find")==0){
            ll x;
            cin>>x;

            ll min=~(1<<31);
            ll index = 0;
            for (int i=1;i<=p.currentSize;i++) {
                if (p.array[i]>x && p.array[i]<min) {
                    min = p.array[i];
                    index=i;
                }
            }
            if (index) cout<<index<<'\n';

            //p.trav();
        }else if (strcmp(operation,"decrease")==0){
            ll i,v;
            cin>>i>>v;

            p.array[i]-=v;

            int hole = i;
            while (hole/2){
                if (p.array[hole/2]>p.array[hole]){
                    ll tmp = p.array[hole];
                    p.array[hole]=p.array[hole/2];
                    p.array[hole/2]=tmp;
                    hole/=2;
                } else {
                    break;
                }
            }


            //p.trav();
        }
    }

    cout<<flush;

    return 0;
}
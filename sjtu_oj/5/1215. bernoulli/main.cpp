#include <iostream>
#include <cstring>

using namespace std;

template <class T>
class priorityQueue{
private:
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
        }else if (strcmp(operation,"delete")==0){
            if (!p.isEmpty()) p.deQueue();
            //p.trav();
        }else if (strcmp(operation,"min")==0){
            if (!p.isEmpty()) cout<<p.getHead()<<'\n';
            //p.trav();
        }
    }

    cout<<flush;

    return 0;
}
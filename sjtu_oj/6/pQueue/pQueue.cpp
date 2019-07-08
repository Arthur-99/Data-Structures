#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template<class T>
class pQueue {
	private:
		T* storage;
		int currSize;
		int maxSize;

		void dbSpace(){
			T* tmp = storage;
			storage = new T[maxSize * 2];
			for (int i=1;i<maxSize;i++){
				storage[i]=tmp[i];
			}
			maxSize *= 2;
			delete []tmp;
		}
		void percolateDown(int hole){
			int child;
			T tmp = storage[hole];
			
			for (;hole*2<=currSize;hole=child){
				child=hole*2;
				if (child!=currSize && storage[child+1]<storage[child]) child++;
				
				if (storage[child]<tmp) storage[hole] = storage[child];
				else break; 
			}
			storage[hole]=tmp;
		}

	public:
		pQueue(int initSize = 100) {
			storage = new T[initSize];
			maxSize = initSize;
			currSize = 0;
		}
		pQueue(T* data,int size){
			maxSize=size+10;
			currSize=size;
			storage=new T[maxSize];
			for (int i=1;i<=size;i++) storage[i]=data[i-1];
			buildHeap();
		}
		~pQueue() {
			delete []storage;
		}
		
		bool empty(){
			return currSize == 0;
		}
		T& getHead(){
			return storage[1];
		}
		
		void enQueue(const T& x){
			if (currSize == maxSize-1) dbSpace(); 
			
			int hole = ++currSize;
			
			for (;hole > 1 && x < storage[hole/2]; hole/=2){
				storage[hole] = storage[hole/2];
			}
			storage[hole] = x;
		} 
		
		T deQueue(){
			T ret = storage[1];
			
			storage[1] = storage[currSize--];
			percolateDown(1);
			
			return ret;
		}

		void buildHeap(){
			for (int i=currSize/2;i>0;i--){
				percolateDown(i);
			}
		}
		void disp(){
			for (int i=1;i<=currSize;i++) cout<<storage[i]<<'\t';
			cout<<endl;
		}
};

template<class T>
class max_pQueue {
	private:
		T* storage;
		int currSize;
		int maxSize;

		void dbSpace(){
			T* tmp = storage;
			storage = new T[maxSize * 2];
			for (int i=1;i<maxSize;i++){
				storage[i]=tmp[i];
			}
			maxSize *= 2;
			delete []tmp;
		}
		void percolateDown(int hole){
			int child;
			T tmp = storage[hole];
			
			for (;hole*2<=currSize;hole=child){
				child=hole*2;
				if (child!=currSize && storage[child+1]>storage[child]) child++;
				
				if (storage[child]>tmp) storage[hole] = storage[child];
				else break; 
			}
			storage[hole]=tmp;
		}

	public:
		max_pQueue(int initSize = 100) {
			storage = new T[initSize];
			maxSize = initSize;
			currSize = 0;
		}
		max_pQueue(T* data,int size){
			maxSize=size+10;
			currSize=size;
			storage=new T[maxSize];
			for (int i=1;i<=size;i++) storage[i]=data[i-1];
			buildHeap();
		}
		~max_pQueue() {
			delete []storage;
		}
		
		bool empty(){
			return currSize == 0;
		}
		T& getHead(){
			return storage[1];
		}
		
		void enQueue(const T& x){
			if (currSize == maxSize-1) dbSpace(); 
			
			int hole = ++currSize;
			
			for (;hole > 1 && x > storage[hole/2]; hole/=2){
				storage[hole] = storage[hole/2];
			}
			storage[hole] = x;
		} 
		
		T deQueue(){
			T ret = storage[1];
			
			storage[1] = storage[currSize--];
			percolateDown(1);
			
			return ret;
		}

		void buildHeap(){
			for (int i=currSize/2;i>0;i--){
				percolateDown(i);
			}
		}
		void disp(){
			for (int i=1;i<=currSize;i++) cout<<storage[i]<<'\t';
			cout<<endl;
		}
};


int main(){
	srand(time(0));
	
	int n;
	cin>>n;
	int a[100];
	for (int i=0;i<n;i++) a[i]=rand()%20;
	for (int i=0;i<n;i++) cout<<a[i]<<'\t';
	cout<<endl;
	
	pQueue<int> pQ(a,n);
	pQ.disp();
	
	max_pQueue<int> mpQ(a,n);
	mpQ.disp();
	
	int nn=n;
	
	while (n--){
		cout<<pQ.deQueue()<<'\t';
	} cout<<endl;
	
	while (nn--){
		cout<<mpQ.deQueue()<<'\t';
	} cout<<endl;
	
	return 0;
}

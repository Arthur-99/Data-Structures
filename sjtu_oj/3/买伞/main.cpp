#include <iostream>
 
using namespace std;
 
template <class T>
class vector {
private:
    T* storage;
    int current_size;
    int max_size;
 
    void double_space(){
        max_size *= 2;
 
        T* tmp = new T[max_size];
        for (int i=0;i<current_size;i++){
            tmp[i] = storage[i];
        }
 
        delete []storage;
        storage = tmp;
    }
public:
    vector(int init_size = 1000000){
        max_size = init_size;
        current_size = 0;
        storage = new T[init_size];
    }
 
    vector(const vector<T>& v){
        current_size = v.current_size;
        max_size = v.max_size;
 
        storage = new T[max_size];
 
        for (int i=0;i<current_size;i++){
            storage[i]= v.storage[i];
        }
    }
    ~vector(){delete []storage;}
 
    int size() const {return current_size;}
 
    void insert(int i, const T& x){
        if (current_size == max_size){
            double_space();
        }
 
        for (int j=current_size;j>i;j--){
            storage[j]=storage[j-1]; //not storage[j+1] = storage[j]
        }
 
        storage[i] = x;
 
        current_size++;
    }
    void remove(int i){
        current_size--;
 
        for (int j=i;j<current_size;j++){
            storage[j]=storage[j+1];
        }
    }
 
    void push_back(const T& x){insert(current_size,x);}
    void pop_back(){remove(current_size-1);}
 
    int find(const T& x) const{
        for  (int i=0;i<current_size;i++){
            if (storage[i] == x) return i;
        }
 
        return -1;
    }
 
    T& operator[](int i){ return storage[i]; }
 
    friend ostream& operator<<(ostream& os, const vector<T>& v){
        for (int i=0;i<v.current_size;i++) os<<v.storage[i]<<' ';
        return os;
    }
};
 
bool reach(int b[][1050],int x4i,int y4i,int num);
void reproduct(int b[][1050],int i,int j,int grownup,int infant);
void grow(int b[][1050],int m,int n,int grownup,int infant);
int count_grownup(int map[][1050], int m, int n, int grownup);
int distance(int map[][1050],int m,int n,int x2,int y2,int infant,int grownup,int x4i,int y4i);
void disp(int map[][1050],int m,int n);
 
int map[1050][1050];
 
int main() {
    ios::sync_with_stdio(false);
 
    //input
    int n,m;cin>>n>>m;
    //1 padding
    for (int i=0;i<n+2;i++) map[0][i]=map[m+1][i]=1;
    for (int i=0;i<m+2;i++) map[i][0]=map[i][n+1]=1;
 
    int x2,y2,x3,y3;
    vector<int> x4,y4;
 
    for (int i=1;i<m+1;i++){
        for (int j=1;j<n+1;j++){
            cin>>map[i][j];
 
            if (map[i][j]==2) { x2=i;y2=j; }
            else if (map[i][j]==3) { x3=i;y3=j; }
            else if (map[i][j]==4) { x4.push_back(i);y4.push_back(j); }
        }
    }
 
    //output
    int min=1000000;
    for (int i=0;i<x4.size();i++){
        int d24=distance(map,m,n,x2,y2,22+i*5,222+i*5,x4[i],y4[i]);
        int d34=distance(map,m,n,x3,y3,33+i*5,333+i*5,x4[i],y4[i]);
        int d = d24+d34;
        if (min>d) min=d;
        //cout<<d24<<'\t'<<d34<<endl;
    }
 
    cout<<min<<endl;
 
    return 0;
}
 
bool reach(int b[][1050],int x4i,int y4i,int num){
    //detect if there is any 6 around 4
    if (b[x4i-1][y4i]==num) return true;
    if (b[x4i+1][y4i]==num) return true;
    if (b[x4i][y4i+1]==num) return true;
    if (b[x4i][y4i-1]==num) return true;
 
    return false;
}
 
void reproduct(int b[][1050],int i,int j,int grownup,int infant){
    if (b[i-1][j]!=1 && b[i-1][j]!=grownup) b[i-1][j]=infant;
    if (b[i][j-1]!=1 && b[i][j-1]!=grownup) b[i][j-1]=infant;
    if (b[i+1][j]!=1 && b[i+1][j]!=grownup) b[i+1][j]=infant;
    if (b[i][j+1]!=1 && b[i][j+1]!=grownup) b[i][j+1]=infant;
}
 
void grow(int b[][1050],int m,int n,int grownup,int infant){
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            if (b[i][j]==infant) b[i][j]=grownup;
        }
    }
}
 
int count_grownup(int map[][1050], int m, int n, int grownup){
    int cnt=0;
    for (int i=1;i<m+1;i++){
        for (int j=1;j<n+1;j++){
            if (map[i][j]==grownup) cnt++;
        }
    }
    return cnt;
}
 
int distance(int map[][1050],int m,int n,int x2,int y2,int infant,int grownup,int x4i,int y4i){
    int step=0;
    while(!reach(map, x4i, y4i, grownup)){
        int cnt0=0,cnt1=0;
 
        cnt0= count_grownup(map, m, n, grownup);
 
        for (int i=1;i<m+1;i++){
            for (int j=1;j<n+1;j++){
                if ((i==x2 && j==y2) || map[i][j]==grownup) reproduct(map,i,j,grownup,infant);
            }
        }
        grow(map,m+2,n+2,grownup,infant);
 
        cnt1= count_grownup(map, m, n, grownup);
        if (cnt0==cnt1) return 1000000;
        step++;
        //disp(map,m,n);
    }
    return step+1;
}
 
void disp(int map[][1050],int m,int n){
    for (int i=0;i<m+2;i++){
        for (int j=0;j<n+2;j++){
            cout<<map[i][j]<<'\t';
        }cout<<endl;
    }cout<<"\n\n\n";
}

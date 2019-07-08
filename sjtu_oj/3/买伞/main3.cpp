#include <iostream>

using namespace std;

struct Point{
    int x,y;
    Point(int xx=0,int yy=0){x=xx;y=yy;}
};

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
    vector(int init_size = 1000){
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
    vector& operator=(const vector<T>& v){
        if (this==&v) return *this;

        current_size = v.current_size;
        max_size = v.max_size;

        delete []storage;
        storage = new T[max_size];

        for (int i=0;i<current_size;i++){
            storage[i]= v.storage[i];
        }
        return *this;
    }
    ~vector(){delete []storage;}

    int size() const {return current_size;}
    void clear(){current_size=0;}

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

void disp(int map[][1050],int m,int n){
    for (int i=0;i<m+2;i++){
        for (int j=0;j<n+2;j++){
            cout<<map[i][j]<<'\t';
        }cout<<endl;
    }cout<<"\n\n\n";
}

void reproduct(int b[][1050],vector<Point>& this_generation,vector<Point>& new_generation,int grownup,int infant){
    new_generation.clear();

    for (int p=0;p<this_generation.size();p++) {
        int i=this_generation[p].x,j=this_generation[p].y;

        if (b[i - 1][j] != 1 && !(10 < b[i - 1][j] && b[i - 1][j] <= grownup)) {
            b[i - 1][j] = infant;
            new_generation.push_back(Point(i - 1, j));
        }
        if (b[i][j - 1] != 1 && !(10 < b[i][j - 1] && b[i][j - 1] <= grownup)) {
            b[i][j - 1] = infant;
            new_generation.push_back(Point(i, j - 1));
        }
        if (b[i + 1][j] != 1 && !(10 < b[i + 1][j] && b[i + 1][j] <= grownup)) {
            b[i + 1][j] = infant;
            new_generation.push_back(Point(i + 1, j));
        }
        if (b[i][j + 1] != 1 && !(10 < b[i][j + 1] && b[i][j + 1] <= grownup)) {
            b[i][j + 1] = infant;
            new_generation.push_back(Point(i, j + 1));
        }
    }
}
void grow(int b[][1050],vector<Point>& p,int grownup,bool& flag){
    for (int i=0;i<p.size();i++) {
        b[p[i].x][p[i].y]=grownup;
        flag=true;
    }
}
void getd(int MAP[][1050],int m,int n,int x,int y){
    int step=10;

    step++;
    vector<Point> this_generation;
    this_generation.push_back(Point(x,y));
    vector<Point> new_generation;
    reproduct(MAP,this_generation,new_generation,step-1,-1);

    bool f=false; grow(MAP,new_generation,step,f);
    this_generation = new_generation;

    while (f){
        step++;

        reproduct(MAP,this_generation,new_generation,step-1,-1);

        f=false; grow(MAP,new_generation,step,f);

        this_generation = new_generation;
        //disp(MAP,m,n);
    }

    for (int i=1;i<m+1;i++){
        for (int j=1;j<n+1;j++){
            if (MAP[i][j]>10){
                MAP[i][j]-=10;
            }
            else if (MAP[i][j]==0 || MAP[i][j]==2 || MAP[i][j]==3 || MAP[i][j]==4)
                MAP[i][j]=50000;
        }
    }
    //disp(MAP,m,n);
}

int map[1050][1050]={{0}};
int MAP[1050][1050]={{0}};

int x4[1000000]={0},y4[1000000]={0};

int main() {
    ios::sync_with_stdio(false);
    //input
    int n,m;cin>>n>>m;

    //1 padding
    for (int i=0;i<n+2;i++) map[0][i]=map[m+1][i]=1;
    for (int i=0;i<m+2;i++) map[i][0]=map[i][n+1]=1;
    for (int i=0;i<n+2;i++) MAP[0][i]=MAP[m+1][i]=1;
    for (int i=0;i<m+2;i++) MAP[i][0]=MAP[i][n+1]=1;

    int x2,y2,x3,y3;
    int k=0;

    for (int i=1;i<m+1;i++){
        for (int j=1;j<n+1;j++){
            cin>>map[i][j];
            if (map[i][j]==2) { x2=i;y2=j; }
            else if (map[i][j]==3) { x3=i;y3=j; }
            else if (map[i][j]==4) { x4[k]=i;y4[k]=j;k++; }
            MAP[i][j]=map[i][j];
        }
    }

    //dp get d24,d34

    getd(MAP,m,n,x2,y2);
    getd(map,m,n,x3,y3);

    //output
    int min=100000;
    for (int i=0;i<k;i++){
        //cout<<MAP[x4[i]][y4[i]]<<'\t'<<map[x4[i]][y4[i]]<<endl;
        int d = MAP[x4[i]][y4[i]]+map[x4[i]][y4[i]];
        if (min>d) min=d;
    }
    cout<<min<<endl;
    return 0;
}



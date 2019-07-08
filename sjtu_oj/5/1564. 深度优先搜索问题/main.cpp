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
    explicit vector(int initSize = 500) {
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

int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
int map[6][6];
int vis[6][6]={0};

void disp(int a[][6]){
    for (int j=0;j<6;j++){
        for (int k=0;k<6;k++){
            cout<<a[j][k]<<'\t';
        }cout<<'\n';
    }
    cout<<'\n';
}

vector<int> pathx;
vector<int> pathy;
int minn = ~(1<<31);

int calc(vector<int> px, vector<int> py){
    int status = 1;
    int total_cost = 0;

    int len = px.size();
    for (int i=0;i<len;i++){
        int cost = map[px[i]][py[i]] * status;
        total_cost += cost;
        status = cost % 4 + 1;
    }

    return total_cost;
}

void dfs(int x1,int y1,int x2,int y2){
    if (x1==x2 && y1==y2){
        int status = 1;
        int total_cost = 0;

        int len = pathx.size();
        for (int i=0;i<len;i++){
            int cost = map[pathx[i]][pathy[i]] * status;
            total_cost += cost;
            status = cost % 4 + 1;
        }

        if (total_cost < minn) minn = total_cost;
        return ;
    }

    for (int i=0;i<4;i++){
        int x=x1+dir[i][0];
        int y=y1+dir[i][1];

        if (vis[x][y]==0 && x>=0 && x<6 && y>=0 && y<6){

            vis[x][y]=1;
            pathx.push_back(x);
            pathy.push_back(y);

            dfs(x,y,x2,y2);

            vis[x][y]=0;
            pathx.pop_back();
            pathy.pop_back();
        }
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin>>n;

    for (int q=0;q<n;q++){
        //set map
        for (int j=0;j<6;j++){
            for (int k=0;k<6;k++){
                cin>>map[j][k];
            }
        }
        //get start & end
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        //reset minn
        minn = ~(1<<31);

        dfs(x1,y1,x2,y2);
        cout<<minn<<'\n';
    }

    cout << flush;

    return 0;
}
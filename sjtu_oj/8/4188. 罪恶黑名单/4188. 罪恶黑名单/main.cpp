#include <iostream>
#include <cstdio>
//#include <vector>

using namespace std;

const int N = 3e5+3;

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
    vector(int initSize = 5) {
        maxSize = initSize;
        currentSize = 0;
        storage = new T[maxSize];
    }
    ~vector() { delete[]storage; }

    void insert(int p, const T &x) {
        if (currentSize == maxSize - 1) dbSpace();
        for (int i = currentSize; i > p; i--) storage[i] = storage[i - 1];
        storage[p] = x;
        currentSize++;
    }
    void push_back(const T &x) { insert(currentSize, x); }

    T &operator[](int p) { return storage[p]; }
    T& back(){return storage[currentSize-1];}

    int size() { return currentSize; }
};

#define ll long long

int p1=31,p2=37;
int md=1e9+9;
ll bin1[N],bin2[N];

string ss[N];
vector<ll> hash1[N],hash2[N];
int Size[N];


bool hh1[N]={0},hh2[N]={0};
ll HH(ll h){return 59*h%299993;}
bool flag[N]={0};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
//    freopen("list0.in","r",stdin);
//    freopen("list.out","w",stdout);

    int n;cin>>n;

    // precomputing the powers of p1 & p2
    bin1[0]=bin2[0]=1;
    for (int i=1;i<N;i++){
        bin1[i]=(bin1[i-1]*p1)%md;
        bin2[i]=(bin2[i-1]*p2)%md;
    }

    for (int i=1;i<=n;i++) {
        cin>>ss[i];

        hash1[i].push_back(ss[i][0]-'a'+1);
        hash2[i].push_back(ss[i][0]-'a'+1);
        int j=1;
        while (ss[i][j]){
            hash1[i].push_back(( hash1[i].back() + (ss[i][j]-'a'+1) * bin1[j] ) % md);
            hash2[i].push_back(( hash2[i].back() + (ss[i][j]-'a'+1) * bin2[j] ) % md);
            j++;
        }
        Size[i]=j;

        if (hh1[HH(hash1[i][Size[i]-1])]==1 && hh2[HH(hash2[i][Size[i]-1])]==1) flag[i]=1;
        else hh1[HH(hash1[i][Size[i]-1])]=1,hh2[HH(hash2[i][Size[i]-1])]=1;
    }

    int m;cin>>m;
    for (int i=0;i<m;i++){
        int op;cin>>op;
        if (op==1){
            int x;cin>>x;
            if (flag[x]) cout<<"yes\n";
            else cout<<"no\n";

        } else if (op==2){
            int x,y;cin>>x>>y;
            int minlen=min(Size[x],Size[y]);
            int l=0,r=minlen-1;
            while (l<=r){
                int m=(l+r)>>1;
                if (hash1[x][m]==hash1[y][m] && hash2[x][m]==hash2[y][m]) l=m+1;
                else r=m-1;
            }
            cout<<l<<'\n';

        } else if (op==3){
            int x,y;cin>>x>>y;
            if (Size[x]>Size[y]){
                int offset=Size[x]-Size[y];
                int l=0,r=Size[y]-1;
                while (l<=r){
                    int m=(l+r)>>1;
                    ll hash1_x_m = hash1[x][Size[x]-1] - hash1[x][offset+m]; if (hash1_x_m < 0) hash1_x_m += md;
                    ll hash1_y_m = hash1[y][Size[y]-1] - hash1[y][m]; if (hash1_y_m < 0) hash1_y_m += md;
                    hash1_y_m = (hash1_y_m * bin1[offset]) % md;

                    ll hash2_x_m = hash2[x][Size[x]-1] - hash2[x][offset+m]; if (hash2_x_m < 0) hash2_x_m += md;
                    ll hash2_y_m = hash2[y][Size[y]-1] - hash2[y][m]; if (hash2_y_m < 0) hash2_y_m += md;
                    hash2_y_m = (hash2_y_m * bin2[offset]) % md;

                    if (hash1_x_m == hash1_y_m && hash2_x_m == hash2_y_m) r=m-1;
                    else l=m+1;
                }
                cout<<Size[y]-1-l<<'\n';
            } else {
                int offset=Size[y]-Size[x];
                int l=0,r=Size[x]-1;
                while (l<=r){
                    int m=(l+r)>>1;
                    ll hash1_x_m = hash1[x][Size[x]-1] - hash1[x][m]; if (hash1_x_m < 0) hash1_x_m += md;
                    ll hash1_y_m = hash1[y][Size[y]-1] - hash1[y][offset+m]; if (hash1_y_m < 0) hash1_y_m += md;
                    hash1_x_m = (hash1_x_m * bin1[offset]) % md;

                    ll hash2_x_m = hash2[x][Size[x]-1] - hash2[x][m]; if (hash2_x_m < 0) hash2_x_m += md;
                    ll hash2_y_m = hash2[y][Size[y]-1] - hash2[y][offset+m]; if (hash2_y_m < 0) hash2_y_m += md;
                    hash2_x_m = (hash2_x_m * bin2[offset]) % md;

                    if (hash1_x_m == hash1_y_m && hash2_x_m == hash2_y_m) r=m-1;
                    else l=m+1;
                }
                cout<<Size[x]-1-l<<'\n';
            }
        }
    }

    cout<<flush;
//    fclose(stdout);
    return 0;
}

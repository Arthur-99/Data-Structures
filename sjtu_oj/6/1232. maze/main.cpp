#include <iostream>
#include <cstring>

using namespace std;

const int n = 1e5+7;

int N;
#include <cmath>
inline int des(int P,int Q){
    int p=P;
    int i=0;
    for (i=1;;i++){
        if (p>i) p-=i;
        else break;
    }

    if (p==1){
        switch (Q){
            case 0:return P;
            case 1:return P-i+1;
            case 2:return P+i;
            case 3:return P+i+1;
        }
    } else if (p==i){
        switch (Q){
            case 0:return P-i;
            case 1:return P;
            case 2:return P+i;
            case 3:return P+i+1;
        }
    } else if (i==N){
        switch (Q){
            case 0:return P-i;
            case 1:return P-i+1;
            case 2:return P;
            case 3:return P;
        }
    } else {
        switch (Q){
            case 0:return P-i;
            case 1:return P-i+1;
            case 2:return P+i;
            case 3:return P+i+1;
        }
    }
}

struct Point{
    int dir[4];

    Point(){memset(dir,0,sizeof(dir));}
};

class ds{
    int parent[n];
public:
    ds(){for (int i=0;i<n;i++) parent[i]=-1;}
    void Union(int p,int q){
        int rt1=Find(p),rt2=Find(q);
        if (rt1==rt2) return;
        if (parent[rt1]>parent[rt2]){
            parent[rt2]+=parent[rt1];
            parent[rt1]=rt2;
        } else {
            parent[rt1]+=parent[rt2];
            parent[rt2]=rt1;
        }
    }

    int Find1(int x){
        //return (parent[x]<0)?x:(parent[x]=Find(parent[x]));
        if (parent[x]<0) return x;
        else return parent[x]=Find(parent[x]);
    }
    int Find(int x){
        int start=x,ret,tmp;
        while (parent[x]>=0) x=parent[x];
        while (start!=x){
            tmp=start[parent];
            start[parent]=x;
            start=tmp;
        }
        return x;
    }
};

ds maze;
Point point[n];
bool visited[n]={0};

int s[n];int top_p=-1;
void dfs(int A,int B);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int A,B;cin>>N>>A>>B;


    while (maze.Find(A) != maze.Find(B)){
        int P,Q;cin>>P>>Q;
        int d=des(P,Q); //cout<<"d:"<<d<<endl;
        if (d!=P){
            maze.Union(P,d);
            point[P].dir[Q]=1;
            point[d].dir[3-Q]=1;
        }
        //cout<<"maze.Find(A) == maze.Find(B) : "<<(maze.Find(A) == maze.Find(B) )<<endl;
    }

//cout<<"fuck"<<endl;

    s[++top_p]=A;
    visited[A]=1;
    dfs(A,B);

    return 0;
}


void dfs(int A,int B){
    if (A==B) {
        for (int i=0;i<=top_p;i++) cout<<s[i]<<' ';
        cout<<flush;
        exit(0);
    }

    for (int q=0;q<=3;q++){
        int d=des(A,q);

        if (point[A].dir[q]==1 && visited[d]==0){
            s[++top_p]=d;
            visited[d]=1;

            dfs(d,B);

            --top_p;
            visited[d]=0;
        }
    }
}

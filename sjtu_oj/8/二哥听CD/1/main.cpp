#include <iostream>

int _clock=0;

using namespace std;

struct CD {
    int val,id;
    int timer;
};

const int N = 2e6+1;
CD cd[4*N];

#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1

inline void pushup(int rt){
    if (cd[rt<<1].val < cd[rt<<1|1].val) cd[rt]=cd[rt<<1];
    else if (cd[rt<<1].val > cd[rt<<1|1].val) cd[rt]=cd[rt<<1|1];
    else if (cd[rt<<1].timer > cd[rt<<1|1].timer) cd[rt]=cd[rt<<1];
    else cd[rt]=cd[rt<<1|1];
}

void build(int l,int r,int rt){
    if (l==r){
        cin>>cd[rt].val;
        cd[rt].id=l;
        cd[rt].timer=0;
    } else {
        int m=(l+r)>>1;
        build(lson);
        build(rson);
        pushup(rt);
    }
}

void update(int x,int y,int l,int r,int rt){
    if (l==r && l==x){
        cd[rt].val+=y;
        cd[rt].timer=++_clock;
    } else {
        int m=(l+r)>>1;
        if (x<=m) update(x,y,lson);
        else update(x,y,rson);
        pushup(rt);
    }
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n,m;
    cin>>n>>m;
    build(1,n,1);

    for (int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        update(x,y,1,n,1);
        cout<<cd[1].id<<'\n';
    }

    cout<<flush;

    return 0;
}

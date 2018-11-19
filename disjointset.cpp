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
        int start=x,tmp;
        while (parent[x]>=0) x=parent[x];
        while (start!=x){
            tmp=start[parent];
            start[parent]=x;
            start=tmp;
        }
        return x;
    }
};
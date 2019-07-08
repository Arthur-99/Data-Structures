#include <iostream>

using namespace std;

const int N=1e6+7;

void qsort(int* a,int l,int r){
    if (l>=r) return;
    int x=a[r];
    int i=l;
    for (int j=l;j<r;j++){
        if (a[j]<x){
            swap(a[i],a[j]);
            i++;
        }
    }
    swap(a[i],a[r]);
    qsort(a,l,i-1);
    qsort(a,i+1,r);
}

int A[N];
int B[N];
int C[N];

template <class T>
class lheap{
    struct node{
        T data;
        node* l;
        node* r;
        int npl;

        node(const T& d):data(d){
            l=r=nullptr;
            npl=0;
        }
    };

    node* root;
public:
    lheap(node* rt=nullptr){root=rt;}
    ~lheap(){clear(root);}

    T& getHead(){return root->data;}

    void enQueue(const T& x){
        node* p=new node(x);
        root=merge(root,p);
    }
    T deQueue(){
        T ret=root->data;
        node* rl=root->l;
        node* rr=root->r;
        delete root;
        root=merge(rl,rr);
        return ret;
    }

private:
    void clear(node* rt){
        if (rt){
            clear(rt->l);
            clear(rt->r);
            delete rt;
        }
    }

    int npl(node* rt){return (rt)?rt->npl:0;}

    node* merge(node* h1,node* h2){
        if (h1==nullptr) return h2;
        if (h2==nullptr) return h1;

        if (h1->data > h2->data) swap(h1,h2);
        h1->r=merge(h1->r,h2);

        if (npl(h1->r)>npl(h1->l)) swap(h1->r,h1->l);
        if (h1->r==nullptr) h1->npl=0;
        else h1->npl=npl(h1->l)+1;

        return h1;
    }
};

struct item{
    int value;
    int ai;
    int bi;

    item(int v,int a,int b){value=v;ai=a;bi=b;}
    bool operator>(const item& i){return value>i.value;}
    bool operator<(const item& i){return value<i.value;}
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin>>n;
    for (int i=1;i<=n;i++) cin>>A[i];
    for (int i=1;i<=n;i++) cin>>B[i];

    qsort(A,1,n);
    qsort(B,1,n);

    int a=1;
    int b=1;
/*
    while (a*b<=n){
        if (A[a+1]+B[b]>A[a]+B[b+1]) a++;
        else if (A[a+1]+B[b]<A[a]+B[b+1]) b++;
        else {
            a++;b++;
        }
    }

    int k=1;
    for (int i=1;i<=a;i++){
        for (int j=1;j<=b;j++){
            C[k++]=A[i]+B[j];
        }
    }

    qsort(C,1,k-1);
    for (int i=1;i<=n;i++) cout<<C[i]<<' ';
*/

    lheap<item> q;
    for (int i=1;i<=n;i++)q.enQueue(item(A[i]+B[1],i,1));

    for (int i=1;i<=n;i++){
        item tmp=q.deQueue();
        cout<<tmp.value<<' ';

        int tmp_v=tmp.value,tmp_a=tmp.ai,tmp_b=tmp.bi;

        if (tmp_b+1<=n) q.enQueue(item(tmp_v-B[tmp_b]+B[tmp_b+1],tmp_a,tmp_b+1));
    }

    cout<<flush;

    return 0;
}

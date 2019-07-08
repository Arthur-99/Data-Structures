#include <iostream>

using namespace std;

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
    bool empty(){return root==nullptr;}

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

    int npl(node* rt){return (rt)?rt->npl:-1;}

    node* merge(node* h1,node* h2){
        if (h1==nullptr) return h2;
        if (h2==nullptr) return h1;

        if (h1->data < h2->data) swap(h1,h2);
        h1->r=merge(h1->r,h2);

        if (npl(h1->r)>npl(h1->l)) swap(h1->r,h1->l);
        h1->npl=npl(h1->l)+1;

        return h1;
    }
};

struct _person{
    int val;
    int num;
    bool inQueue;

    _person(int v=0,int n=0,bool a=0){val=v;num=n;inQueue=a;}
    bool operator<(const _person& p){return val<p.val;}
    bool operator>(const _person& p){return val>p.val;}
    bool operator==(const _person& p){return val==p.val;}
};

const int N =1e3+7;
_person person[N];

int mat[N][N]={0};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n,k;cin>>n>>k;
    for (int i=1;i<=n;i++) {
        cin>>person[i].val;
        person[i].num=i;
        person[i].inQueue=0;
    }

    lheap<_person> lh;
    int x;
    for (int i=0;i<k;i++) {
        cin>>x;
        lh.enQueue(person[x]);
        person[x].inQueue=1;
    }

    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            cin>>mat[i][j];
        }
    }

    while (!lh.empty()){
        _person tmp = lh.deQueue();
        int number=tmp.num;
        cout<<number<<'\n';

        for (int i=1;i<=n;i++){
            if (mat[number][i]==1 && person[i].inQueue==0){
                lh.enQueue(person[i]);
                person[i].inQueue=1;
            }
        }
    }

    cout<<flush;

    return 0;
}

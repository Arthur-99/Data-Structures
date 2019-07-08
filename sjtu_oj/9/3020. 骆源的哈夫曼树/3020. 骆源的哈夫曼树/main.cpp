#include <iostream>

using namespace std;

#define ll long long

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
    bool finish(){return npl(root)==0;}

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

        if (h1->data > h2->data) {
            node* tmp=h1;h1=h2;h2=tmp;
//            swap(h1,h2);
        }
        h1->r=merge(h1->r,h2);

        if (npl(h1->r)>npl(h1->l)) {
//            swap(h1->r,h1->l);
            node* tmp=h1->r;h1->r=h1->l;h1->l=tmp;
        }
        h1->npl=npl(h1->l)+1;

        return h1;
    }
};


lheap<ll> lh;
int main()
{
    int n,k;cin>>n>>k;

    int num = (k-1)-(n-1)%(k-1);
    if (num!=(k-1)) for (int i=0;i<num;i++) lh.enQueue(0);

    for (int i=0;i<n;i++){
        ll x;cin>>x;
        lh.enQueue(x);
    }

    ll sum=0;
    while (!lh.finish()){
        ll tmp=0;
        for (int i=0;i<k;i++) tmp+=lh.deQueue();
        lh.enQueue(tmp);
        sum+=tmp;
    }
    cout<<sum;

    return 0;
}

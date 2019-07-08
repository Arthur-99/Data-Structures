#include <iostream>

using namespace std;

template <class T>
class minheap{
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
    minheap(node* rt=nullptr){root=rt;}
    ~minheap(){clear(root);}

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

    int npl(node* rt){return (rt)?rt->npl:-1;}

    node* merge(node* h1,node* h2){
        if (h1==nullptr) return h2;
        if (h2==nullptr) return h1;

        if (h1->data > h2->data) swap(h1,h2);
        h1->r=merge(h1->r,h2);

        if (npl(h1->r)>npl(h1->l)) swap(h1->r,h1->l);
        h1->npl=npl(h1->l)+1;

        return h1;
    }
};

template <class T>
class maxheap{
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
    maxheap(node* rt=nullptr){root=rt;}
    ~maxheap(){clear(root);}

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

#include <cstdio>
int main()
{
//    freopen("poi0.in","r",stdin);
//    freopen("poi0.out","w",stdout);

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    minheap<int> minh;
    maxheap<int> maxh;

    int N;
    cin>>N;

    int t0;
    cin>>t0;
    maxh.enQueue(t0);
    cout<<maxh.getHead()<<'\n';

    int a,b;
    for (int k=1;2*k+1<=N;k++){
        cin>>a>>b;
        if (a>b) swap(a,b);

        if (a<=maxh.getHead() && b>=maxh.getHead()){
            maxh.enQueue(a);
            minh.enQueue(b);
        } else if (a<=maxh.getHead() && b<=maxh.getHead()) {
            maxh.enQueue(a);
            maxh.enQueue(b);
            minh.enQueue(maxh.deQueue());
        } else if (a>=maxh.getHead() && b>=maxh.getHead()) {
            minh.enQueue(a);
            minh.enQueue(b);
            maxh.enQueue(minh.deQueue());
        }

        cout<<maxh.getHead()<<'\n';
    }

    cout<<flush;

//    fclose(stdout);

    return 0;
}

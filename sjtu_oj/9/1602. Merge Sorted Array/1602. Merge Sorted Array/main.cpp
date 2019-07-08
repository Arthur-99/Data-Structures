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

int main()
{
    lheap<int> lh;
    int m,n;cin>>m>>n;
    int x;
    for (int i=0;i<m+n;i++) {
        cin>>x;
        lh.enQueue(x);
    }
    for (int i=0;i<m+n;i++) cout<<lh.deQueue()<<' ';
    return 0;
}

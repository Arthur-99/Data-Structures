#include <iostream>

using namespace std;

template<class T>
class pQueue{
    struct node{
        T data;
        node* l;
        node* r;
        int npl;

        node(const T& d):data(d){l=r=NULL;npl=0;}
    };

    node* root;
public:
    pQueue(node* rt):root(rt){}
    pQueue(const T& x){root=new node(x);}
    ~pQueue(){clear(root);}

    bool empty(){return root==NULL;}
    void inOrder(){inOrder(root);}

    T& getHead(){return root->data;}
    void enQueue(const T& x){
        node* p=new node(x);
        root=merge(root,p);
    }
    T deQueue(){
        int ret=root->data;
        node* l=root->l;
        node* r=root->r;
        delete root;
        root=merge(l,r);
        return ret;
    }

private:
    void clear(node* t){
        if (t){
            if (t->l) clear(t->l);
            if (t->r) clear(t->r);
            delete t;
        }
    }
    void inOrder(node* t){
        if (t){
            inOrder(t->l);
            cout<<t->data<<' ';
            inOrder(t->r);
        }
    }
    int npl(node* t){return (t)?t->npl:0;}
    node* merge(node* l1,node* l2){
        if (l1==NULL) return l2;
        if (l2==NULL) return l1;

        if (l1->data > l2->data) swap(l1,l2);
        l1->r=merge(l1->r,l2);

        if (npl(l1->r) > npl(l1->l)) swap(l1->r,l1->l);
        if (l1->r==NULL) l1->npl=0;
        else l1->npl=l1->r->npl+1;

        return l1;
    }
};

int main() {
	pQueue<int> p(5);
	for (int i=0; i<10; i++) {
		int n;
		cin>>n;
		p.enQueue(n);
		cout<<"head: "<<p.getHead()<<endl;
		p.inOrder();
		cout<<endl;
	}
	while (!p.empty()){
        cout<<p.deQueue()<<' ';
	}cout<<endl;

	return 0;
}
/*
node* merge(node* l1,node* l2){
    if (l1==NULL) return l2;
    if (l2==NULL) return l1;

    if (l1->data > l2->data) swap(l1,l2);

    l1->R=merge(l1->R,l2);

    if (npl(l1->L)<npl(l1->R)) swap(l1->L,l1->R);

    if (l1->R==NULL) l1->npl=0;
    else l1->npl=l1->R->npl+1;

    return l1;
}
*/
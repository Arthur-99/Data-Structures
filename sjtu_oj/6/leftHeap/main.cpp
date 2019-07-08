#include <iostream>

using namespace std;

struct node {
	int data;
	node* L;
	node* R;
	int npl;

	node(int d) {
		data=d;
		L=R=NULL;
		npl=0;
	}
};
int npl(node* t) {
	return (t)?t->npl:0;
}
void swap(node* l1,node* l2) {
	node* t=l1;
	l1=l2;
	l2=t;
}
node* merge(node* l1,node* l2) {
	if (l1==NULL || l2==NULL) return (l1==NULL)?l2:l1;

	if (l1->data > l2->data) swap(l1,l2);
	l1->R=merge(l1->R,l2);

	if (npl(l1->R) > npl(l1->L)) swap(l1->R,l1->L);//
	if (l1->R == NULL) l1->npl=0;
	else l1->npl=npl(l1->R)+1;
	return l1;
}

void enQueue(node* root,const int& x) {
	node* p = new node(x);
	root = merge(root,p);
}

int deQueue(node* root) {
	int ret = root->data;
	node* l=root->L;
	node* r=root->R;
	delete root;
	root = merge(l,r);
	return ret;
}

void inOrder(node* t) {
	if (t==NULL) return ;
	inOrder(t->L);
	cout<<t->data<<' ';
	inOrder(t->R);
}

void clear(node* t) {
	if (t->L) clear(t->L);
	if (t->R) clear(t->R);
	delete t;
}

int getHead(node* root) {
	return root->data;
}

int info(node* root){
	cout<<"data: "<<root->data<<endl;
	cout<<"npl: "<<root->npl<<endl;
}

int main() {
	node* root=new node(0);
	for (int i=0; i<10; i++) {
		int n;
		cin>>n;
		enQueue(root,n);
		cout<<"head: "<<getHead(root)<<endl;
		inOrder(root);
		cout<<endl;
	}

	clear(root);
	return 0;
}

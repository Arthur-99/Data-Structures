#include <iostream>

using  namespace std;

class Joseph {
private:
    struct node {
        int data;
        node* prev;
        node* next;

        node(int d, node*p=NULL,node* n= NULL):data(d),prev(p),next(n){}
    };

    node* curr;
public:
    Joseph (int M){
        curr=new node(1);
        node* p=curr;


        for (int i=2;i<=M;i++){
            node* q=new node(i);
            p->next=q;
            q->prev=p;
            p=q;
        }
        p->next=curr;
        curr->prev=p;
    }
    ~Joseph(){
        node* p=curr->next;
        node* q=curr;
        while (p!=q){
            node* r=p->next;
            delete p;
            p=r;
        }
        delete q;
    }

    void kill(int k){
        int len=length();
        int t=(k-1)%len;

        if(t<len/2) {
            for (int i = 0; i < t; i++) curr = curr->next;
        }else {
            for (int i = 0; i < len - t; i++) curr = curr->prev;
        }
        node* p=curr->prev;
        node* q=curr->next;

        p->next=q;
        q->prev=p;

        delete curr;
        curr=q;
    }
    int length(){
        int l=1;
        node* p=curr->next;
        node* q=curr;
        while (p!=q){
            p=p->next;
            l++;
        }
        return l;
    }

    int king(){
        return curr->data;
    }
};

int main() {
    int m;cin>>m; const int M=m;
    int K[M-1]; for (int i=0;i<M-1;i++) cin>>K[i];

    Joseph J(M);
    for (int i=0;i<M-1;i++) J.kill(K[i]);

    cout<<J.king()<<endl;

    return 0;
}
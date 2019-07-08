#include <iostream>

using namespace std;

template<class T>
class stack {
    T *storage;
    int top_p;
    int maxSize;

    void dbSpace() {
        T *tmp = storage;
        storage = new T[maxSize *= 2];
        for (int i = 0; i <= top_p; i++) storage[i] = tmp[i];
        delete tmp;
    }
public:
    stack(int initSize = 6666) {
        maxSize = initSize;
        storage = new T[maxSize];
        top_p = -1;
    }
    ~stack() { delete[]storage; }

    void push(const T &x) {
        if (top_p == maxSize - 1) dbSpace();
        storage[++top_p] = x;
    }
    T pop() { return storage[top_p--]; }
    bool isEmpty() { return top_p == -1; }
    T &top() { return storage[top_p]; }
};


template <class T>
class AVLtree{
private:
    struct node{
        node* left;
        node* right;
        int height;
        T data;

        node(const T& x,int h=0,node* l=nullptr,node* r=nullptr)
            :data(x),height(h),left(l),right(r){}
    };

    node* root;
    size_t Size;

public:
    AVLtree(){root=nullptr;Size=0;}
    AVLtree(node* rt):root(rt){Size=1;}
    AVLtree(const AVLtree& tree){root=copy(tree.root);Size=tree.Size;}
    ~AVLtree(){clear(root);Size=0;}

    node* find(const T& value){return find(value,root);}

    void insert(const T& value){insert(value,root);++Size;}
    void remove(const T& value){remove(value,root);}

    bool empty(){return root==nullptr;}
    size_t size(){return Size;}

    int height(){return height(root);}
    void inOrder(){
        printf("inOrder:\n");
        inOrder(root);
        printf("\n");
    }

    void fdith(int i){
        if (i<1 || i>Size) {
            cout<<"N\n";
            return ;
        }

        stack<node*> s;
        node* t=root;
        while (t || !s.isEmpty()){
            while (t){
                s.push(t);
                t=t->left;
            }

            t=s.pop();
            i--;
            if (i==0) {
                cout<<t->data<<'\n';
                return ;
            }
            t=t->right;
        }
    }

    void delete_greater_than(int a){
        node* t=root;
        while (t->right) t=t->right;

        int MAX = t->data;

        for (int i=a+1;i<=MAX;i++) {
            remove(i);
            if (find(i)) i--;
        }
    }
    void delete_less_than(int a){
        node* t=root;
        while (t->left) t=t->left;

        int MIN = t->data;

        for (int i=MIN;i<a;i++) {
            remove(i);
            if (find(i)) i--;
        }
    }
    void delete_interval(int a,int b){
        for (int i=a+1;i<b;i++) {
            remove(i);
            if (find(i)) i--;
        }
    }

private:

    node* copy(node* t){
        if (t){
            node* copy_t=new node(t->data,t->height);
            copy_t->left=copy(t->left);
            copy_t->right=copy(t->right);
            return copy_t;
        } else return nullptr;
    }
    void clear(node* t){
        if (t){
            clear(t->left);
            clear(t->right);
            delete t;
            --Size;
        }
    }

    node* find(const T& value,node* rt){
        if (rt) {
            if (rt->data==value) return rt;
            else if (rt->data > value) return find(value,rt->left);
            else if (rt->data < value) return find(value,rt->right);
        } else return nullptr;
    }

    void insert(const T& value,node*& rt){
        if (rt==nullptr) rt=new node(value);
        else if (value < rt->data) {
            insert(value,rt->left);
            //LL or LR
            if (height(rt->left)-height(rt->right)==2){
                if (value < rt->left->data) LL(rt);
                else LR(rt);
            }
        }
        else if (value >= rt->data) {
            insert(value,rt->right);
            //RL or RR
            if (height(rt->right)-height(rt->left)==2){
                if (value < rt->right->data) RL(rt);
                else RR(rt);
            }
        }
        rt->height=max(height(rt->left),height(rt->right))+1;
    }
    void remove(const T& value,node*& rt){
        if (rt==nullptr) return ;
        else if (rt->data < value){
            remove(value,rt->right);
            //
            if (height(rt->left)-height(rt->right)==2){
                if (height(rt->left->left)>height(rt->left->right)) LL(rt);
                else LR(rt);//
            }
        }
        else if (rt->data > value){
            remove(value,rt->left);
            //
            if (height(rt->right)-height(rt->left)==2){
                if (height(rt->right->right)>height(rt->right->left)) RR(rt);
                else RL(rt);//
            }
        }
        // rt->data == value
        else if (rt->left && rt->right){
            node* tmp=rt->right;
            while (tmp->left) tmp=tmp->left;
            rt->data=tmp->data;
            remove(tmp->data,rt->right);
        }
        else {
            node* tmp=(rt->left)?(rt->left):rt->right;
            delete rt; --Size;
            rt=tmp;
        }
        if (rt) rt->height = max(height(rt->left),height(rt->right)) + 1;
    }

    int height(node* t){return (t)?t->height:-1;}

    int max(int a,int b){return (a>b)?a:b;}

    void LL(node*& t){
        node* tl=t->left;
        t->left=tl->right;
        tl->right=t;
        t->height=max(height(t->left),height(t->right))+1;
        tl->height=max(height(tl->left),height(t))+1;
        t=tl;
    }
    void RR(node*& t){
        node* tr=t->right;
        t->right=tr->left;
        tr->left=t;
        t->height=max(height(t->right),height(t->left))+1;
        tr->height=max(height(tr->right),height(t))+1;
        t=tr;
    }
    void LR(node*& t){
        RR(t->left);
        LL(t);
    }
    void RL(node*& t){
        LL(t->right);
        RR(t);
    }

    void inOrder(node* rt){
        if (rt){
            inOrder(rt->left);
            printf("%d ",rt->data);
            inOrder(rt->right);
        }
    }
};

#include <cstring>
//#include <cstdlib>
//#include <ctime>
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

//    srand(time(0));
    AVLtree<int> a;

//    for (int i=0;i<1000;i++) a.insert(rand()%2000);
//    a.inOrder();
//    cout<<a.size()<<endl;cout<<"\n\n\n";
//
//    a.delete_greater_than(1800);
//    a.inOrder();
//    cout<<a.size()<<endl;cout<<"\n\n\n";
//
//    a.delete_less_than(400);
//    a.inOrder();
//    cout<<a.size()<<endl;cout<<"\n\n\n";
//
//    a.delete_interval(700,1000);
//    a.inOrder();
//    cout<<a.size()<<endl;cout<<"\n\n\n";
//
//    for (int i=0;i<a.size();i++){
//        a.fdith(i);
//    }
//
//
//    return 0;

    int n;cin>>n;
    for (int i=0;i<n;i++){
        char operation[20];
        cin>>operation;

        if (strcmp(operation,"insert")==0){
            int x;cin>>x;a.insert(x);
        } else if (strcmp(operation,"delete")==0){
            int x;cin>>x;a.remove(x);
        } else if (strcmp(operation,"find")==0){
            int x;cin>>x;
            if (a.find(x)) cout<<"Y\n";
            else cout<<"N\n";
        } else if (strcmp(operation,"find_ith")==0){
            int i;cin>>i;
            a.fdith(i);
        } else if (strcmp(operation,"delete_greater_than")==0){
            int x;cin>>x;
            a.delete_greater_than(x);
        } else if (strcmp(operation,"delete_less_than")==0){
            int x;cin>>x;
            a.delete_less_than(x);
        } else if (strcmp(operation,"delete_interval")==0){
            int x,y;cin>>x>>y;
            a.delete_interval(x,y);
        } else if (strcmp(operation,"io")==0){
            a.inOrder();
        }
    }

    cout<<flush;

    return 0;
}

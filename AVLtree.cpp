#include <iostream>
#include <queue>

using namespace std;

template <class T>
class AVLtree{
private:
    struct node{
        node* left;
        node* right;
        int height;
        T data;

        node(const T& x,int h=0,node* l=nullptr,node* r=nullptr):data(x),height(h),left(l),right(r){}
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
    void remove(const T& value){remove(value,root);}//bug : --Size 不应该在这

    bool empty(){return root==nullptr;}
    size_t size(){return Size;}

    int height(){return height(root);}
    void inOrder(){
        printf("inOrder:\n");
        inOrder(root);
        printf("\n");
    }
    void levelOrder(){
        printf("levelOrder:\n");
        if (root==nullptr) return ;
        queue<node*> thisLevel,nextLevel;
        thisLevel.push(root);
        while (!thisLevel.empty()){
            node* tmp=thisLevel.front();
            printf("%d ",tmp->data);
            thisLevel.pop();
            if (tmp->left) nextLevel.push(tmp->left);
            if (tmp->right) nextLevel.push(tmp->right);

            if (thisLevel.empty()){
                printf("\n");
                thisLevel=nextLevel;
                while (!nextLevel.empty())nextLevel.pop();
            }
        }
        printf("\n");
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
        else if (value > rt->data) {
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
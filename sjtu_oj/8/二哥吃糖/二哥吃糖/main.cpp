#include <iostream>

using namespace std;

template<class T>
class BST{
private:
    struct node{
        T data;
        node * left;
        node * right;
        int height;
        node(const T& otherdata, node * otherl, node * otherr):data(otherdata), left(otherl), right(otherr), height(1){}
    };
public:
    BST(node * t = nullptr){root = t;}
    ~BST() {makeEmpty(root);}
    bool find(const T& x)const{
        return find(x, root);
    }
    void insert(const T& x){
        insert(x, root);
    }
    void remove(const T& x){
        remove(x, root);
    }
    T& findkth(int i){
        return findkth(i, root);
    }
private:
    node * root;
    void insert(const T& x, node * &t){
        if (t==nullptr) t = new node(x, nullptr, nullptr);
        else if (x>t->data) {
            insert(x, t->left);
            if (h(t->left)-h(t->right) == 2){
                if (x > t->left->data){
                    LL(t);
                }
                else LR(t);
            }
            t->height = h(t->left) + h(t->right) + 1;
        }
        else {
            insert(x, t->right);
            if (h(t->right)-h(t->left) == 2){
                if (x <= t->right->data){
                    RR(t);
                }
                else RL(t);
            }
            t->height = h(t->left) + h(t->right) + 1;
        }
    }
    void remove(const T& x, node * &t){
        if (t == nullptr) return;
        if (x>t->data) {
            remove(x, t->left);
            if (h(t->right) - h(t->left) == 2){
                node *r =  t->right;
                if (h(r->left) > h(r->right))
                    RL(t);
                else
                    RR(t);
            }
            t->height = h(t->left) + h(t->right) + 1;
        }
        else if (x<t->data) {
            remove(x, t->right);
            if (h(t->left) - h(t->right) == 2){
                node *r =  t->left;
                if (h(r->right) > h(r->left))
                    LR(t);
                else
                    LL(t);
            }
            t->height = h(t->left) + h(t->right) + 1;
        }
        else if (t->left != nullptr && t->right != nullptr){
            if (h(t->left) <= h(t->right)){
                node * tmp = t->right;
                while(tmp->left != nullptr) tmp = tmp->left;
                t->data = tmp->data;
                remove(t->data, t->right);
                t->height = h(t->left) + h(t->right) + 1;
            }
            else{
                node * tmp = t->left;
                while (tmp->right != nullptr) tmp = tmp->right;
                t->data = tmp->data;
                remove(t->data, t->left);
                t->height = h(t->left) + h(t->right) + 1;
            }
        }
        else{
            node * old = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete old;
        }
    }
    bool find(const T& x, node * t)const{
        if (t == nullptr) return false;

        if (x>t->data) return find(x, t->left);
        if (x<t->data) return find(x, t->right);

        return true;
    }
    void makeEmpty(node * &t){
        if (t == nullptr) return;
        node * tmp = t;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete tmp;
        t = nullptr;
    }
    T& findkth(int i, node *&t){
        int rs = h(t->left);
        if (rs == i-1){
            return t->data;
        }

        if (rs >= i) return findkth(i, t->left);
        else return findkth(i-rs-1, t->right);
    }
    int h(node * t){
        return t==nullptr ? 0 : t->height;
    }
    void LL(node *&t){
        node * t1 = t->left;
        t->left = t1->right;
        t1->right = t;
        t->height = h(t->left) + h(t->right) + 1;
        t1->height = h(t1->left) + h(t)+1;
        t = t1;
    }
    void RR(node *&t){
        node * t1 = t->right;
        t->right = t1->left;
        t1->left = t;
        t->height = h(t->left) + h(t->right) + 1;
        t1->height = h(t1->right) + h(t)+1;
        t = t1;
    }
    void LR(node *&t){
        RR(t->left);
        LL(t);
    }
    void RL(node *&t){
        LL(t->right);
        RR(t);
    }
};


const int n=5e5+7;
int box[n];
int sugar[n];
int movebox[n]={0};
int boxnum;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N,M;cin>>N>>M;

    boxnum=N;

    BST<int> t;
    for (int i=1;i<=N;i++){
        t.insert(1);
        box[i]=1;
        sugar[i]=i;
    }

    for (int i=0;i<M;i++){
        char op;cin>>op;
        if (op=='C'){
            int x,y;cin>>x>>y;
            while (movebox[sugar[x]] != 0){//找到x糖果现在在几号盒子;
                sugar[x] = movebox[sugar[x]];
            }
            while (movebox[sugar[y]] != 0){//找到y糖果现在在几号盒子;
                sugar[y] = movebox[sugar[y]];
            }
            if (sugar[y] != sugar[x] && box[sugar[x]] != 0 && box[sugar[y]] != 0){
                t.remove(box[sugar[x]]);
                t.remove(box[sugar[y]]);
                box[sugar[x]] += box[sugar[y]];
                t.insert(box[sugar[x]]);
                box[sugar[y]] = 0;
                movebox[sugar[y]] = sugar[x];//y的盒子移动到x的盒子;
                boxnum--;
            }
        } else if (op=='D') {
            int x;cin>>x;
            while (movebox[sugar[x]] != 0){//同上;
                sugar[x] = movebox[sugar[x]];
            }
            if (box[sugar[x]] != 0){
                t.remove(box[sugar[x]]);
                box[sugar[x]] = 0;
                boxnum--;
            }
        } else if (op=='Q') {
            int x;cin>>x;
            if (boxnum < x) cout<<0<<'\n';
            else{
                cout<<t.findkth(x)<<'\n';
            }
        }
    }

    cout<<flush;

    return 0;
}

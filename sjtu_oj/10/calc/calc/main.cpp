#include <iostream>

using namespace std;

template<class T>
class queue{
    int currSize;
    int maxSize;
    T* storage;
    int _front;
    int _rear;
    void dbSpace(){
        T* tmp=storage;
        storage=new T[maxSize*2];
        for (int i=1;i<maxSize;i++) storage[i]=tmp[(_front+i)%maxSize];
        _front=0;
        _rear=currSize;
        maxSize*=2;
        delete []tmp;
    }
public:
    queue(int sz=10){
        _front=_rear=0;
        currSize=0;
        storage = new T[maxSize=sz];
    }
    ~queue(){delete[]storage;}

    bool empty(){return _front==_rear;}

    void enQ(const T& x){
        if ((_rear+1)%maxSize==_front)dbSpace();
        currSize++;
        _rear=(_rear+1)%maxSize;
        storage[_rear]=x;
    }
    T deQ(){
        currSize--;
        _front=(_front+1)%maxSize;
        return storage[_front];
    }
};

class calc{
    enum Type{
        DATA,ADD,SUB,MUL,DIV,OPAR,CPAR,EOL
    };

    struct node{
        Type type;
        int val;
        node* l;
        node* r;

        node(Type dT,int v=0,node* ll=0,node* rr=0){
            type=dT;
            val=v;
            l=ll;
            r=rr;
        }
    };

    node* root;

public:
    calc(){root=nullptr;}
    calc(char*s){root=create(s);}
    ~calc(){clear(root);}
    node* create(char*& s){
        node* rt=0;
        int value;
        node* p;
        while (*s){
            Type t=getToken(s,value);
            switch (t){
            case DATA:case OPAR:{
                if (t==DATA) p=new node(DATA,value);
                else p=create(s);

                if (rt==nullptr) rt=p;
                else if (rt->r==0) rt->r=p;
                else rt->r->r=p;

                break;
            }
            case CPAR:case EOL:
                return rt;
            case ADD:case SUB:
                rt = new node(t,0,rt);
                break;
            case MUL:case DIV:
                if (rt->type==ADD || rt->type==SUB) rt->r=new node(t,0,rt->r);
                else rt = new node(t,0,rt);
            }
        }
        return rt;
    }
    int result(){
        if (root==nullptr) return 0;
        else return result(root);
    }

    void levelOrder(){
        cout<<"levelOrder:\n";
        if (root==0) {
            cout<<endl;
            return ;
        }
        queue<node*> q1,q2;
        q1.enQ(root);
        while (!q1.empty()){
            node* tmp=q1.deQ();
            cout<<tmp->type<<':'<<tmp->val<<'\t';
            if (tmp->l) q2.enQ(tmp->l);
            if (tmp->r) q2.enQ(tmp->r);
            if (q1.empty()){
                while (!q2.empty()){
                    q1.enQ(q2.deQ());
                }
                cout<<endl;
            }
        }
        cout<<endl;
    }

    void preOrder(){
        cout<<"preOrder:\n";
        preOrder(root);
        cout<<endl;
    }
    void inOrder(){
        cout<<"inOrder:\n";
        inOrder(root);
        cout<<endl;
    }
    void postOrder(){
        cout<<"postOrder:\n";
        postOrder(root);
        cout<<endl;
    }
private:
    char mmp[10]={'.','+','-','*','/'};
    void print(node* rt){
        if (rt->type==DATA) cout<<rt->val;
        else cout<<mmp[rt->type];
    }
    void preOrder(node* rt){
        if (rt){
            print(rt);
            preOrder(rt->l);
            preOrder(rt->r);
        }
    }
    void inOrder(node* rt){
        if (rt){
            inOrder(rt->l);
            print(rt);
            inOrder(rt->r);
        }
    }
    void postOrder(node* rt){
        if (rt){
            postOrder(rt->l);
            postOrder(rt->r);
            print(rt);
        }
    }
    Type getToken(char*& s,int& value){
        while (*s==' ') s++;
        if (*s>='0' && *s<='9'){
            int res=0;
            while (*s>='0' && *s<='9'){
                res=10*res+*s-'0';
                s++;
            }
            value=res;
            return DATA;
        }

        char type=*s;
        s++;
        switch (type){
            case '+':return ADD;
            case '-':return SUB;
            case '*':return MUL;
            case '/':return DIV;
            case '(':return OPAR;
            case ')':return CPAR;
            default:return EOL;
        }
    }

    int result(node* t){
        switch(t->type){
            case DATA: return t->val;
            case ADD: return result(t->l)+result(t->r);
            case SUB: return result(t->l)-result(t->r);
            case MUL: return result(t->l)*result(t->r);
            case DIV: return result(t->l)/result(t->r);
        }
    }

    void clear(node* rt){
        if (rt){
            clear(rt->l);
            clear(rt->r);
            delete rt;
        }
    }
};

#include <cstring>

int main()
{
    char s[1000]={0};cin.getline(s,1000);
    calc cc(s);
    cout<<"result:\n";
    cout<<cc.result()<<endl;

    cc.levelOrder();
    cc.preOrder();
    cc.inOrder();
    cc.postOrder();

    return 0;
}
//2*3+(1*2*3+6*6)*(2+3)/5+2/2

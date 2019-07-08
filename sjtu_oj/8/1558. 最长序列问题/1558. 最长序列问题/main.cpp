#include <iostream>

using namespace std;

#define nullptr 0

int mmax(int x, int y){
    return x>y ? x:y;
}

template <class T>
void qsort(T *A, int p, int r) {
    if (p>=r) return;
    T x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] < x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    qsort(A, p, i);
    qsort(A, i + 2, r);
}

struct mypair{
    int first;
    int second;
    mypair(){}
    mypair(int f, int s):first(f), second(s){}
    bool operator>(const mypair & other)const{
        return first > other.first;
    }
};

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
        h1->npl=npl(h1->r)+1;

        return h1;
    }
};

struct node{
    int v;//��ǩ��;
    int bh;//ԭ���ڵڼ�λ;
    bool operator<(const node &other)const{
        return v < other.v;
    }
};

node P[100005];
int N,K;
int v[100005],cnt[100005] = {0};
void _init()
{
    cin>>N>>K;
    for(int i=1;i<=N;i++){
        cin>>P[i].v;
        P[i].bh = i;
    }
    qsort(P,1,N);//��ͬ��ǩ�ķ���һ����;
    int bh=0;
    P[0].v=-1;v[0]=-1;
    for(int i=1;i<=N;i++)
    {
        if(P[i].v != P[i-1].v) bh++;
        v[P[i].bh]=bh;//���ݱ�ǩ˳�����´�123��ʼ��Ǳ�ǩ;
    }
}
lheap<mypair> my_q;
void _solve()
{
    while(!my_q.empty()) my_q.deQueue();
    int now,ans;
    now=ans=cnt[v[1]]=1;
    my_q.enQueue(mypair(cnt[v[1]],v[1]));//first��v[i]��ǩ�ų��ֵĴ���;
    for(int i=1,j=1;i<=N&&j<=N;)
    {
        while(j<N&&now<K+1)//�Ҷ˵�����;
        {
            j++;
            if(!cnt[v[j]]) now++;
            cnt[v[j]]++;
            my_q.enQueue(mypair(cnt[v[j]],v[j]));
        }
        while(now==K+1&&j<N&&cnt[v[j+1]]!=0)//�Ҳ໹�����б�ǩ,��������;
        {
            j++;
            cnt[v[j]]++;
            my_q.enQueue(mypair(cnt[v[j]],v[j]));
        }
        while((!my_q.empty())&&(my_q.getHead().first!=cnt[my_q.getHead().second])){
            my_q.deQueue();//ȥ���Ѿ���Ч��;
        }
        if(!my_q.empty()){
            ans = mmax(ans,my_q.getHead().first);
        }
        cnt[v[i]]--;//��˵�����һλ;
        if(cnt[v[i]]==0) now--;
        my_q.enQueue(mypair(cnt[v[i]],v[i]));
        i++;
    }
    cout<<ans;
}
int main()
{
    _init();
    _solve();
    return 0;
}

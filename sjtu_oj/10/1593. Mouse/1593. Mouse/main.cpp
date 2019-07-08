#include <iostream>

using namespace std;

struct _mouse{
    int p,s,num;
    _mouse(int pp=0,int ss=0,int nn=0){p=pp,s=ss,num=nn;}

    bool operator<(const _mouse& rhs){
        if (p<rhs.p) return true;
        else if (p==rhs.p && num>rhs.num) return true;
        else return false;
    }
    bool operator>(const _mouse& rhs){
        if (p>rhs.p) return true;
        else if (p==rhs.p && num<rhs.num) return true;
        else return false;
    }
};

const int maxn=2e5+7;
_mouse m[maxn];

template<class T>
void qsort(T* a,int l,int r){
    if (l>=r) return ;
    int i=l;
    T x=a[r];
    for (int j=l;j<r;j++){
        if (a[j]>x){
            swap(a[i],a[j]);
            i++;
        }
    }
    swap(a[i],a[r]);
    qsort(a,l,i-1);
    qsort(a,i+1,r);
}

int main()
{
    int N,R;cin>>N>>R;

    for (int i=1;i<=2*N;i++){
        cin>>m[i].p;
    }
    for (int i=1;i<=2*N;i++){
        cin>>m[i].s;
        m[i].num=i;
    }
    qsort<_mouse>(m,1,2*N);
//    for (int i=1;i<=2*N;i++) cout<<m[i].num<<' ';

    for (int q=0;q<R;q++){
        for (int i=1;i<=2*N;i+=2){
            _mouse& tmp1=m[i];
            _mouse& tmp2=m[i+1];
            if (tmp1.s>tmp2.s) tmp1.p+=2;
            else if (tmp1.s==tmp2.s) tmp1.p++,tmp2.p++;
            else tmp2.p+=2;

            if (tmp1<tmp2) swap(tmp1,tmp2);
            if (i!=1){
                if (m[i-1]<m[i]) swap(m[i],m[i-1]);
                if (m[i]<m[i+1]) swap(m[i],m[i+1]);
                if (m[i-2]<m[i-1]) swap(m[i-2],m[i-1]);
            }
        }
    }

    for (int i=1;i<=2*N;i++) cout<<m[i].num<<' ';

    return 0;
}

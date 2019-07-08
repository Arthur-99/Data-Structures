#include <iostream>
#include <cmath>

using namespace std;

long long max(long long a,long long b,long long c)
{
    if(b>a) a=b;
    if(c>a) a=c;
    return a;
}

int main() {
    long long NN;cin>>NN;
    const long long N=NN;

    long long X[N];
    for (long long i=0;i<N;i++) cin>>X[i];

    long long W1,T1,W2,T2;
    W1=T1=W2=T2=0;

    //T1
    long long W11,W12,W13;W11=W12=W13=0;
    for (long long i=0;i<N ;i+=3) W11+=X[i];
    for (long long i=1;i<N ;i+=3) W12+=X[i];
    for (long long i=2;i<N ;i+=3) W13+=X[i];
    T1=max(W11,W12,W13);

    //W1
    for (long long i=0;i<N ;i++) W1 += X[i] * ((N-i-1)/3);

    //T2
    long long p1,p2,p3; p1=p2=p3=0;//person
    long long i=0;//person index
    bool f=true;

    long long W21[N]={0},W22[N]={0},W23[N]={0};
    long long i1,i2,i3; i1=i2=i3=0;
    while (true){
        if (i==N) f=false;

        if (p1<=0 && f) {
            p1=X[i++];
            W21[i1++]=p1;
            continue;
        }
        if (p2<=0 && f) {
            p2=X[i++];
            W22[i2++]=p2;
            continue;
        }
        if (p3<=0 && f) {
            p3=X[i++];
            W23[i3++]=p3;
            continue;
        }
        if (p1<=0 && p2<=0 && p3<=0) break;

        T2++;
        p1--;p2--;p3--;
    }

    //W2
    for (long long i=0;i<i1;i++) W2 += W21[i] * (i1-i-1);
    for (long long i=0;i<i2;i++) W2 += W22[i] * (i2-i-1);
    for (long long i=0;i<i3;i++) W2 += W23[i] * (i3-i-1);

    cout<<W1<<' '<<T1<<endl;
    cout<<W2<<' '<<T2;

    return 0;
}
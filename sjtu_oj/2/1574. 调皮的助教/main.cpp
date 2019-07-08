#include <iostream>

using namespace std;

int pow(int x, int y, int mod)
{
    int res = 1;
    while(y)
    {
        if(y & 1) res =  res * x % mod;
        x = x * x % mod;
        y = y / 2;
    }
    return res;
}

int main() {
    int n,m,k,x;cin>>n>>m>>k>>x;

    //cout<<(pow(10,k)*m+x)%n;
/*
    int tenkmodn=1;
    int i=0;
    for (;i<k;i+=6) {
        tenkmodn *= (1000000 % n);
        if (tenkmodn > n) tenkmodn %= n;
    }
    for (;i<k;i++){
        tenkmodn *= 10 % n;
    }

    int res = m * tenkmodn +x;
    cout<<res%n;
*/
    //cout<<pow(10,k,n);

    cout<<(pow(10,k,n)*(m%n)+x)%n;
    return 0;
}
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int n,t;scanf("%d %d",&n,&t);
    const int N=n,T=t;

    int X[N],Y[T];
    for (int i=0;i<N;i++) scanf("%d",&X[i]);
    for (int i=0;i<T;i++) scanf("%d",&Y[i]);

    if (N==0){
        for (int i=0;i<T;i++) printf("0\n");
        return 0;
    }
    if (T==0){
        return 0;
    }

    for (int i=0;i<T;i++) {
        int left = 0, right = N - 1;

        while (left < right) {
            int mid = (right - left) / 2 + left;

            if (Y[i] < X[mid]) right = mid - 1;
            else left = mid + 1;
        }

        //Now left==right
        if (Y[i] >= X[left]) printf( "%d\n",N - left - 1);
        else printf( "%d\n",N - left );
    }

    return 0;
}
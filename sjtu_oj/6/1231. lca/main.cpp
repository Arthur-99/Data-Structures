#include <iostream>

using namespace std;


const int N=1e6+7;

int p[N]={0};

int pathX[N]={0};
int pathY[N]={0};

int main()
{
    int n,X,Y;cin>>n>>X>>Y;
    int l,r;
    for (int i=1;i<=n;i++){
        cin>>l>>r;
        p[l]=p[r]=i;
    }

    pathX[0]=X;
    int ix=1;
    int px=p[X];
    while (px){
        pathX[ix++]=px;
        px=p[px];
    }

    pathY[0]=Y;
    int iy=1;
    int py=p[Y];
    while (py){
        pathY[iy++]=py;
        py=p[py];
    }

    while (pathX[--ix]==pathY[--iy]);
    cout<<pathX[ix+1];

    return 0;
}

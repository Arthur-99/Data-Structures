#include <iostream>

using namespace std;

const int N = 1e5+7;
int a[N],L[2*N]={0},R[2*N]={0};

int main()
{
    int n,b;cin>>n>>b;
    for (int i=1;i<=n;i++) cin>>a[i];

    int index_b;
    for (int i=1;i<=n;i++) {
        if (a[i]>b) a[i]=1;
        else if (a[i]==b) a[i]=0,index_b=i;
        else a[i]=-1;
    }

    int l=n,r=n;
	for(int i=index_b;i>0;i--) l+=a[i],L[l]++;
	for(int i=index_b;i<=n;i++) r+=a[i],R[r]++;

	int ans=0;
	for(int i=0;i<=2*n;i++) ans+=(L[i]*R[2*n-i]);

    cout<<ans;

    return 0;
}

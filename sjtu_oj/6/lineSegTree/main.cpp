#include <iostream>

using namespace std;

#define lson l,m,root<<1
#define rson m+1,r,root<<1|1

const int N = 1e3+7;
int a[N];
int sum[4*N];
int tag[4*N]={0};

int n;

void pushUp(int root) {
	sum[root]=sum[root<<1]+sum[root<<1|1];
}

void build(int l=1,int r=n,int root=1) {
	if (l==r) {
		sum[root]=a[l];
		return;
	}

	int m=(l+r)/2;
	build(lson);
	build(rson);
	pushUp(root);
}

void pushDown(int l,int r,int root){
	if (tag[root]){
		int c=tag[root];
		tag[root*2]+=c;
		tag[root*2+1]+=c;
		sum[root]+=c*(r-l+1);
		tag[root]=0;
	}
}

int query(int L,int R,int l=1,int r=n,int root=1) {
	pushDown(l,r,root);
	
	if (L<=l && r<=R) return sum[root];
	
	int m = (r+l)/2;
	int ret=0;
	if (L<=m) ret+=query(L,R,lson);
	if (m<R) ret+=query(L,R,rson);
	return ret;
}

void add(int L,int R,int c,int l=1,int r=n,int root=1) {
	if (L<=l && r<=R) {
		tag[root]=c;
		return ;
	}
	
	int m=(l+r)/2;
	if (L<=m) add(L,R,c,lson);
	if (m<R) add(L,R,c,rson);
}

int main() {
	cin>>n;
	for (int i=1; i<=n; i++) cin>>a[i];

	build();
	cout<<query(2,4)<<endl;
	
	add(2,3,2);
	cout<<query(2,2)<<endl;
	cout<<query(2,3)<<endl;
	cout<<query(2,4)<<endl;
	
	return 0;
}

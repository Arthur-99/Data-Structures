#include <iostream>

using namespace std;

int first_larger(int* a,int n,int key){
	int l=0,r=n-1,mid;
	while(l<=r){
		mid = (l+r)/2;
		if (a[mid]>key) r=mid-1;
		else l=mid+1;
	}
	return l;
}

int last_smaller(int* a,int n,int key){
	int l=0,r=n-1,mid;
	while (l<=r){
		mid = (l+r)/2;
		if (a[mid]<key) l=mid+1;
		else r=mid-1;
	}
	return r;
}

const int N = 1e5+7;
int a[N];
int main() {
//	int x=33;
//	for (int i=0;i<1e8;i++) {
//		x*=2;
//		x/=2;
//	} 
//	2.823s
//	for (int i=0;i<1e8;i++){
//		x=x>>1;
//		x=x<<1;
//	}
//	0.6321s
	
	int n;
	cin>>n;
	for (int i=0;i<n;i++) cin>>a[i];
	
	cout<<"input t: ";
	int t;
	cin>>t;
	
	int fl=first_larger(a,n,t);
	int ls=last_smaller(a,n,t);
	
	cout<<fl<<'\t'<<a[fl]<<endl;
	cout<<ls<<'\t'<<a[ls]<<endl;

	return 0;
}

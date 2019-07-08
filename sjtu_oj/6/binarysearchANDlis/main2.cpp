#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

const int N = 2018;
int dp[N];
int DP[N];
int a[N];

void disp(int* arr,int n){
	for (int i=0;i<n;i++) cout<<arr[i]<<' ';
	cout<<endl;
}

int lower_bound(int* arr,int n,int key){
	int l=0,r=n-1;
	while(l<=r){
		int mid = (l+r)/2;
		if (arr[mid]>key) r=mid-1;
		else l=mid+1;
	}
	return l;
}

int main(int argc, char** argv) {
	srand(time(0));
	
	int n;
	cin>>n;
	
	for (int i=0;i<n;i++) a[i]=rand()%50;
	disp(a,n);
	
	//dp[i] : LIS 's length ended with a[i]
	for (int i=0;i<n;i++) dp[i]=1;
	
	for (int i=0;i<n;i++){
		for (int j=0;j<i;j++){
			if (a[i]>a[j]) dp[i]=max(dp[i],dp[j]+1); 
		}
	}
	disp(dp,n);
	
	//DP[i] : last element of LIS which length is i+1, DP is an increasing sequence
	DP[0]=a[0]; 
	int pos=0;
	for (int i=1;i<n;i++){
		if (a[i]>DP[pos]) DP[++pos]=a[i];
		else {
			//Find first element larger than a[i] in DP //and replace it with a[i]
			DP[lower_bound(DP,pos+1,a[i])]=a[i];
		}
	} 
	disp(DP,pos+1);
	
	return 0;
}

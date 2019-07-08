#include <iostream>

using namespace std;

#define ll long long

const int N = 2e5+7;

ll a[N];

int main() {
    int n,k;
    cin>>k>>n;

    for (int i=0;i<n;i++) cin>>a[i];


    ll max = a[0];
    int index = 0;
    for (int i=0;i<n-k+1;i++){
        if (i==0){
            for (int j=0;j<k;j++){
                if (a[j]>=max){
                    max = a[j];
                    index = j;
                }
            }
            cout<<max<<' ';
        } else {
            if (i<=index){
                if (a[i+k-1]>=max){
                    max = a[i+k-1];
                    index = i+k-1;
                }
                cout << max << ' ';
            } else {
                max = a[i];
                index = i;
                for (int j=i;j<i+k;j++){
                    if (a[j]>=max){
                        max = a[j];
                        index = j;
                    }
                }
                cout << max << ' ';
            }
        }
    }

    return 0;
}
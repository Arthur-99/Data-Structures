#include <iostream>
#include <cmath>

using namespace std;


int main() {
    const int N = 1007;

    int n,m;
    char x[N]={0},y[N]={0};

    int dp[N][N]={0};

    cin>>n>>m;
    cin>>x>>y;

    for (int i=0;i<=n;i++){
        for (int j=0;j<=m;j++){
            if (i==0 || j==0) dp[i][j]=0;
            else if (i>0 && j>0 && x[i-1]==y[j-1]) dp[i][j]=dp[i-1][j-1]+1;
            else if (i>0 && j>0 && x[i-1]!=y[j-1]) dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }

    cout<<dp[n][m];

    return 0;
}
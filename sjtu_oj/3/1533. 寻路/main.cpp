#include <iostream>

using namespace std;

int step=2;

void clockwise(int** b,int& i,int& j,int l){
    char direct;

    if (b[i][j-1]==step-2 && b[i][j+1]==0) b[i][++j]=step;
    else if (b[i-1][j]==step-2 && b[i+1][j]==0) b[++i][j]=step;
    else if (b[i][j+1]==step-2 && b[i][j-1]==0) b[i][--j]=step;
    else if (b[i+1][j]==step-2 && b[i-1][j]==0) b[--i][j]=step;

    else if (i==j+1) b[i][++j]=step;
    else if (i==j && i>=l/2) b[i][--j]=step;
    else if (i+j==l-1 && i<j) b[++i][j]=step;
    else if (i+j==l-1 && i>j) b[--i][j]=step;
}

int main() {
    int n,x,y;cin>>n>>x>>y;

    if (n==1) {
        cout<<0<<endl;
        return 0;
    }
    int** board=new int* [n+2];
    for (int i=0;i<n+2;i++) board[i]=new int[n+2];

    for (int i=0;i<n+2;i++){
        for (int j=0;j<n+2;j++){
            board[i][j]=0;
        }
    }

    for (int i=0;i<n+2;i++) board[0][i]=-5;
    for (int i=0;i<n+2;i++) board[i][0]=-5;
    for (int i=0;i<n+2;i++) board[n+1][i]=-5;
    for (int i=0;i<n+2;i++) board[i][n+1]=-5;

    int i=1,j=2;
    board[1][1]=1,board[1][2]=2;
    while(i!=x || j!=y){
        step++;
        clockwise(board,i,j,n+2);
/*
        for(int i=0;i<n+2;i++){
            for (int j=0;j<n+2;j++){
                cout<<board[i][j]<<'\t';
            }cout<<endl;
        }cout<<"\n\n\n";
        */
    }

    cout<<step-1;

    return 0;
}
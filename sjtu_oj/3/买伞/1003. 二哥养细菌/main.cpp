#include <iostream>

using namespace std;

bool full(int** b, int l){
    for (int i=0;i<l;i++){
        for (int j=0;j<l;j++){
            if(b[i][j]==0) return false;
        }
    }
    return true;
}

void reproduct(int** b,int i,int j){
    if (b[i-1][j]==0){b[i-1][j]=3;}
    if (b[i][j-1]==0){b[i][j-1]=3;}
    if (b[i+1][j]==0){b[i+1][j]=3;}
    if (b[i][j+1]==0){b[i][j+1]=3;}
}

void grow(int** b,int l){
    for (int i=0;i<l;i++){
        for (int j=0;j<l;j++){
            if (b[i][j]==3) b[i][j]=1;
        }
    }
}

int main() {
    int l;cin>>l;

    int** board = new int* [l+2];
    for (int i=0;i<l+2;i++) board[i]=new int[l+2];

    for(int i=0;i<l+2;i++)board[0][i]=2;
    for(int i=0;i<l+2;i++)board[i][0]=2;
    for(int i=0;i<l+2;i++)board[l+1][i]=2;
    for(int i=0;i<l+2;i++)board[i][l+1]=2;

    for (int i=1;i<l+1;i++){
        for (int j=1;j<l+1;j++){
            cin>>board[i][j];
        }
    }



    int m=0;
    while(!full(board,l+2)){
        for (int i=1;i<l+1;i++){
            for (int j=1;j<l+1;j++){
                if (board[i][j]==1){
                    if (board[i-1][j]==0){board[i-1][j]=3;}
                    if (board[i][j-1]==0){board[i][j-1]=3;}
                    if (board[i+1][j]==0){board[i+1][j]=3;}
                    if (board[i][j+1]==0){board[i][j+1]=3;}
                }
            }
        }
        for (int i=0;i<l+2;i++){
            for (int j=0;j<l+2;j++){
                if (board[i][j]==3) board[i][j]=1;
            }
        }

        m++;
    }

    cout<<m;

    for (int i=0;i<l+2;i++) delete []board[i];
    delete []board;

    return 0;
}
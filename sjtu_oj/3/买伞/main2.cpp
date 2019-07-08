#include <iostream>
 
using namespace std;
 
 
void disp(int map[][1050],int m,int n){
    for (int i=0;i<m+2;i++){
        for (int j=0;j<n+2;j++){
            cout<<map[i][j]<<'\t';
        }cout<<endl;
    }cout<<"\n\n\n";
}
 
void reproduct(int b[][1050],int i,int j,int grownup,int infant){
    if (b[i-1][j]!=1 && !(10<b[i-1][j] && b[i-1][j]<=grownup)) b[i-1][j]=infant;
    if (b[i][j-1]!=1 && !(10<b[i][j-1] && b[i][j-1]<=grownup)) b[i][j-1]=infant;
    if (b[i+1][j]!=1 && !(10<b[i+1][j] && b[i+1][j]<=grownup)) b[i+1][j]=infant;
    if (b[i][j+1]!=1 && !(10<b[i][j+1] && b[i][j+1]<=grownup)) b[i][j+1]=infant;
}
void grow(int b[][1050],int m,int n,int grownup,int infant,bool& flag){
    for (int i=0;i<m+2;i++){
        for (int j=0;j<n+2;j++){
            if (b[i][j]==infant) {
                b[i][j]=grownup;
                flag=true;
            }
        }
    }
}
void getd(int MAP[][1050],int m,int n,int x,int y){
    int step=10;
 
    step++;
    reproduct(MAP,x,y,step-1,-1);
 
    bool f=false; grow(MAP,m,n,step,-1,f);
 
    while (f){
        step++;
        for (int i=1;i<m+1;i++){
            for (int j=1;j<n+1;j++){
                if (MAP[i][j]==step-1 ) //reproduct(MAP,i,j,step-1,-1);
                {
                    if (MAP[i-1][j]!=1 && !(10<MAP[i-1][j] && MAP[i-1][j]<=step-1)) MAP[i-1][j]=-1;
                    if (MAP[i][j-1]!=1 && !(10<MAP[i][j-1] && MAP[i][j-1]<=step-1)) MAP[i][j-1]=-1;
                    if (MAP[i+1][j]!=1 && !(10<MAP[i+1][j] && MAP[i+1][j]<=step-1)) MAP[i+1][j]=-1;
                    if (MAP[i][j+1]!=1 && !(10<MAP[i][j+1] && MAP[i][j+1]<=step-1)) MAP[i][j+1]=-1;
                }
            }
        }
 
        f=false; //grow(MAP,m,n,step,-1,f);
        for (int i=0;i<m+2;i++){
            for (int j=0;j<n+2;j++){
                if (MAP[i][j]==-1) {
                    MAP[i][j]=step;
                    f=true;
                }
            }
        }
        //disp(MAP,m,n);
    }
 
    for (int i=1;i<m+1;i++){
        for (int j=1;j<n+1;j++){
            if (MAP[i][j]>10){
                MAP[i][j]-=10;
            }
            else if (MAP[i][j]==0 || MAP[i][j]==2 || MAP[i][j]==3 || MAP[i][j]==4)
                MAP[i][j]=50000;
        }
    }
    //disp(MAP,m,n);
}
 
int map[1050][1050]={{0}};
int MAP[1050][1050]={{0}};
 
int x4[1000000]={0},y4[1000000]={0};
 
int main() {
    ios::sync_with_stdio(false);
    //input
    int n,m;cin>>n>>m;
 
    //1 padding
    for (int i=0;i<n+2;i++) map[0][i]=map[m+1][i]=1;
    for (int i=0;i<m+2;i++) map[i][0]=map[i][n+1]=1;
    for (int i=0;i<n+2;i++) MAP[0][i]=MAP[m+1][i]=1;
    for (int i=0;i<m+2;i++) MAP[i][0]=MAP[i][n+1]=1;
 
    int x2,y2,x3,y3;
    int k=0;
 
    for (int i=1;i<m+1;i++){
        for (int j=1;j<n+1;j++){
            cin>>map[i][j];
            if (map[i][j]==2) { x2=i;y2=j; }
            else if (map[i][j]==3) { x3=i;y3=j; }
            else if (map[i][j]==4) { x4[k]=i;y4[k]=j;k++; }
            MAP[i][j]=map[i][j];
        }
    }
 
    //dp get d24,d34
 
    getd(MAP,m,n,x2,y2);
    getd(map,m,n,x3,y3);
 
    //output
    int min=100000;
    for (int i=0;i<k;i++){
        //cout<<MAP[x4[i]][y4[i]]<<'\t'<<map[x4[i]][y4[i]]<<endl;
        int d = MAP[x4[i]][y4[i]]+map[x4[i]][y4[i]];
        if (min>d) min=d;
    }
    cout<<min<<endl;
    return 0;
}

#include <iostream>

using namespace std;

int x[1001];

void read(int* xx,int n){
    char c;
    c=cin.get();
    while (c!='[') c=cin.get();
    int res;
    for (int i=0;i<n;i++){
        res=0;
        while ((c=cin.get())!=',' && c!=']'){
            res=res*10 + c-'0';
        }
        xx[i]=res;
    }
//    cin.get();
}

int main()
{
    int n;cin>>n;
    read(x,n);
//
//    for (int i=0;i<n;i++) cout<<x[i]<<' ';
//    return 0;

    int decreasing_stack[1001];
    int top_p=-1;
    int buttom=0;

    int save_water=0;

    decreasing_stack[++top_p]=x[0];

    for (int i=1;i<n;i++){
        // xi <= s.top
        if (x[i]<=decreasing_stack[top_p]){
            decreasing_stack[++top_p]=x[i];
        }
        // xi > s.top
        else if (x[i]>=decreasing_stack[buttom]){
            while (top_p!=-1){
                save_water += decreasing_stack[buttom] - decreasing_stack[top_p--];
            }
            decreasing_stack[++top_p]=x[i];
        }
        else {
            int p=top_p;
            while (decreasing_stack[p] < x[i]){
                save_water += x[i]-decreasing_stack[p];
                decreasing_stack[p]=x[i];
                p--;
            }
            decreasing_stack[++top_p]=x[i];
        }
    }

    cout<<save_water<<endl;

    return 0;
}

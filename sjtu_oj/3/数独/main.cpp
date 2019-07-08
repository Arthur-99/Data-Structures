#include <iostream>

using namespace std;


int main() {
    int nn;cin>>nn;
    const int n=nn;
    if (n<1 || n>20){
        cout<<"Wrong"<<endl;
        return 0;
    }
    int a[n][9][9]={0};

//input
    for (int i=0;i<n;i++){
        for (int j=0;j<9;j++){
            for (int k=0;k<9;k++){
                a[i][j][k]=0;
            }
        }
        for (int j=0;j<9;j++){
            for (int k=0;k<9;k++){
                cin>>a[i][j][k];
            }
        }
    }

//analysis
    for (int i=0;i<n;i++){
        //row
        bool Wrong=false;
        for (int q=0;q<9;q++){
            //same
            bool same = false;
            for (int w=0;w<9;w++){
                for (int e=w+1;e<9;e++){
                    if (a[i][q][w]==a[i][q][e]) {
                        same =true;
                        break;
                    }
                }if (same) break;
            }
            //range
            bool out=false;
            for (int w=0;w<9;w++){
                if (a[i][q][w]<1 || a[i][q][w]>9) {
                    out=true;
                    break;
                }
            }
            //sum
            int sum =0;
            for (int w=0;w<9;w++)sum+=a[i][q][w];

            //judge
            if (same || out || (sum!=45)) {
                Wrong=true;
                cout<<"Wrong"<<endl;
                break;
            }
        }

        //col
        if (Wrong) continue;
        for (int q=0;q<9;q++){
            //same
            bool same = false;
            for (int w=0;w<9;w++){
                for (int e=w+1;e<9;e++){
                    if (a[i][w][q]==a[i][e][q]) {
                        same =true;
                        break;
                    }
                }if (same) break;
            }
            //range
            bool out=false;
            for (int w=0;w<9;w++){
                if (a[i][w][q]<1 || a[i][w][q]>9) {
                    out=true;
                    break;
                }
            }
            //sum
            int sum =0;
            for (int w=0;w<9;w++)sum+=a[i][w][q];

            //judge
            if (same || out || (sum!=45)) {
                Wrong=true;
                cout<<"Wrong"<<endl;
                break;
            }
        }

        //3x3
        if (Wrong) continue;
        for (int q=0;q<9;q++){
            //same
            bool same = false;
            for (int w=0;w<9;w++){
                for (int e=w+1;e<9;e++){
                    int aqw = a[i][3*(q/3)+w/3][3*(q%3)+w%3];
                    int aqe = a[i][3*(q/3)+e/3][3*(q%3)+e%3];

                    if (aqw==aqe) {
                        same =true;
                        break;
                    }
                }if (same) break;
            }
            //range
            bool out=false;
            for (int w=0;w<9;w++){
                int aqw = a[i][3*(q/3)+w/3][3*(q%3)+w%3];
                if (aqw<1 || aqw>9) {
                    out=true;
                    break;
                }
            }
            //sum
            int sum =0;
            for (int w=0;w<9;w++){
                int aqw = a[i][3*(q/3)+w/3][3*(q%3)+w%3];
                sum+=aqw;
            }

            //judge
            if (same || out || (sum!=45)) {
                Wrong=true;
                cout<<"Wrong"<<endl;
                break;
            }
        }


        if (!Wrong) cout<<"Right"<<endl;
    }
    return 0;
}
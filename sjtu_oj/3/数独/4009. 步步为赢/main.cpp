#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int main() {
    char s1[101]={0},s2[101]={0};
    cin.getline(s1,101);cin.getline(s2,101);

    int len=strlen(s1),len2=strlen(s2);
    if(len!=len2){
        cout<<"No Solution"<<endl;
        return 0;
    }


    for (int a =2;a<=len;a++){
        if (len%a) continue;

        bool f= true;
        for (int i=0;i<len;i++) {
            if (s1[i]!=s2[(i%a)*(len/a)+i/a]) {
                f = false;
                break;
            }
        }

        if (f) {
            cout<<a<<endl;
            return 0;
        }

    }


    cout<<"No Solution"<<endl;
    return 0;
}
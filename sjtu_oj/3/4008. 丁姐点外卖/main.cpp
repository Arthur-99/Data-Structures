#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char c;

    char res[200]={0};int k=0;

    char a[101],b[101];cin.getline(a,101);cin.getline(b,101);
    int lena=strlen(a),lenb=strlen(b);

    int carry=0;
    int i=lena-1,j=lenb-1;
    for (;i>=0 && j>=0;i--,j--){
        res[k++]=(a[i]+b[j]+carry-'a'-'a')%26+'a';
        carry=(a[i]+b[j]+carry-'a'-'a')/26;

        //cout<<res<<endl;
    }
    while (i>=0){
        res[k++]=(a[i]+carry-'a')%26+'a';
        carry=(a[i]+carry-'a')/26;
        //cout<<res<<endl;
        i--;
    }
    while (j>=0){
        res[k++]=(b[j]+carry-'a')%26+'a';
        carry=(b[j]+carry-'a')/26;
        //cout<<res<<endl;
        j--;
    }
    //cout<<"carry="<<carry<<endl;
    if (carry!=0)res[k++]=carry+'a';

    //cout<<res<<endl;

    for (int i=strlen(res)-1;i>=0;i--) cout<<res[i];

    return 0;
}
#include <iostream>

using namespace std;

const int N1=1e6+3,N2=1e5+3;
char s1[N1];
char s2[N2];

int main()
{
    char c;
    int i=0;
    while ((c = cin.get()) != '\n'){
        s1[i++]=c;
    }
    int sizea=i;
    i=0;
    while ((c = cin.get()) != '\n'){
        s2[i++]=c;
    }

//    cout<<s1<<endl;
//    cout<<s2<<endl;
    int sizeb=i;
    int* p=new int[sizeb];
    int j;

    p[0]=-1;
    for(int i=1;i<sizeb;i++){
        j=i-1;
        while (j>=0 && s2[p[j]+1]!=s2[i]) j=p[j];
        if (j<0) p[i]=-1;
        else p[i]=p[j]+1;
    }

    i=j=0;
    while (i<sizea && j<sizeb){
        if (s2[j]==s1[i]){
            i++;j++;
        }
        else if (j==0) i++;
        else j=p[j-1]+1;
    }

    delete []p;
    if (j==sizeb) cout<<i-j;
    else cout<<-1;


    return 0;
}

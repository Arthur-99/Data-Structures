#include <iostream>

using namespace std;

void Qsort(int *A, int p, int r) {
    if (p >= r) return;
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    Qsort(A, p, i);
    Qsort(A, i + 2, r);
}


class set{
public:
    int data[10007];
    int len;

    void sort(){Qsort(data,0,len-1);}
    void disp(){sort();for (int i=0;i<len;i++) cout<<data[i]<<' '; cout<<'\n';}
    int find(int x){for (int i=0;i<len;i++) if(data[i]==x) return i; return -1;}

public:
    set(){len=0;}
    set(const set& s){
        len = s.len;
        for (int i=0;i<len;i++) data[i]=s.data[i];
    }
    set(int d[],int l){for (int i=0;i<l;i++) data[i] = d[i]; len = l;}

    void operator+(const set& s){
        for (int i=0;i<s.len;i++){
            if (find(s.data[i])==-1) data[len++]=s.data[i];
        }
    }
    void operator-(const set& s){
        for (int i=0;i<s.len;i++){
            int index = find(s.data[i]);
            if (index!=-1) {
                for (int i=index;i<len-1;i++){
                    data[i]=data[i+1];
                }
                len--;
            }
        }
    }
    set operator*(const set& s){
        set c;
        for (int i=0;i<s.len;i++){
            int index = find(s.data[i]);
            if (index!=-1) {
                c.data[c.len++]=s.data[i];
            }
        }
        return c;
    }
    set& operator=(const set& s){
        if (this == &s) return *this;

        len = s.len;
        for (int i=0;i<len;i++) data[i]=s.data[i];
        return *this;
    }
};

int main() {
    int n;
    cin>>n;

    set o;

    for (int i=0;i<n;i++){
        char operation;
        cin>>operation;

        switch (operation){
            case '+':{
                int m;
                cin>>m;
                int t[101];
                for (int i=0;i<m;i++){
                    cin>>t[i];
                }
                set tmp(t,m);

                o+tmp;
                o.disp();

                break;
            }
            case '-':{
                int m;
                cin>>m;
                int t[101];
                for (int i=0;i<m;i++){
                    cin>>t[i];
                }
                set tmp(t,m);

                o-tmp;
                o.disp();

                break;
            }
            case '*': {
                int m;
                cin >> m;
                int t[107];
                for (int i = 0; i < m; i++) {
                    cin >> t[i];
                }
                set tmp(t, m);

                o = o * tmp;
                o.disp();

                break;
            }
        }
    }

    return 0;
}
#include <iostream>
#include <cstring>

using namespace std;

int INT(char c){
    switch (c){
        case '+':return -1;
        case '-':return -2;
        case '*':return -3;
        case '/':return -4;
        case '(':return -5;
        case ')':return -6;
    }
}
char CHAR[7]={'\0','+','-','*','/','(',')'};

template<class T>
class stack {
    T *storage;
    int top_p;
    int maxSize;

    void dbSpace() {
        T *tmp = storage;
        storage = new T[maxSize *= 2];
        for (int i = 0; i <= top_p; i++) storage[i] = tmp[i];
        delete tmp;
    }
public:
    stack(int initSize = 1000) {
        maxSize = initSize;
        storage = new T[maxSize];
        top_p = -1;
    }
    ~stack() { delete[]storage; }

    void push(const T &x) {
        if (top_p == maxSize - 1) dbSpace();
        storage[++top_p] = x;
    }
    T pop() { return storage[top_p--]; }
    bool empty() { return top_p == -1; }
    T &top() { return storage[top_p]; }
    int Size(){return top_p+1;}

    void trav(){
        if (storage[top_p]>=0) cout<<storage[top_p];
        else cout<<CHAR[-storage[top_p]];

        for (int i=top_p-1;i>=0;i--){
            if (storage[i]>=0) cout<<' '<<storage[i];
            else cout<<' '<<CHAR[-storage[i]];
        }
        cout<<endl;
    }
};

int priority(char a){
    if (a=='+' || a=='-') return 1;
    if (a=='*' || a=='/') return 2;
    return 0;
}

int pow(int a,int b){
    int res=1;
    for (int i=0;i<b;i++) res*=a;
    return res;
}

int getNum(char* s,int& i){
    int i0=i;
    if (i==0) return s[i]-'0';
    else {
        int res=s[i]-'0';
        while (i>=1 && s[i-1]>='0' && s[i-1]<='9'){
            i--;
            res+=pow(10,i0-i)*(s[i]-'0');
        }
        return res;
    }
}


int main(){
    stack<int> S1,S2;
    char expression[1007];cin.getline(expression,1007);

    char c;
    for(int i=strlen(expression)-1;i>=0;i--){
        c=expression[i];
        if (c==' ') continue;
        if (c>='0' && c<='9'){
            int n=getNum(expression,i);
            S1.push(n);
        }

        else if (c==')') S2.push(INT(c));

        else if (c=='('){
            while(S2.top()!=INT(')')) S1.push(S2.pop());
            S2.pop();
        }

        else{
            while (!S2.empty() && priority(c) < priority(CHAR[-S2.top()])) S1.push(S2.pop());
            S2.push(INT(c));
        }

    }
    while(!S2.empty()) S1.push(S2.pop());

    if (S1.empty());
    else S1.trav();

    stack<int> S3;
    while (!S1.empty()) S3.push(S1.pop());

    stack<int> num;

    while (!S3.empty()){
        int tmp=S3.pop();
        if (tmp>=0) num.push(tmp);
        else {
            if (num.Size()>=2) {
                int a=num.pop(),b=num.pop();
                switch (tmp){
                    case -1:num.push(a+b);break;
                    case -2:num.push(a-b);break;
                    case -3:num.push(a*b);break;
                    case -4:num.push(a/b);
                }
            }
        }
    }
    if (num.empty());
    else cout<<num.top();

    return 0;
}

#include <iostream>
#include <assert.h>
#include <cstring>

using namespace std;


class error{};


template <class T>
class list {
    friend istream& operator>>(istream& is, list<T>& l){
        l.clear();
        int i;
        while ((i = is.get()) != '\n'){
            l.push_back(i);
        }
        return is;
    }
    friend ostream& operator<<(ostream& os, const list<T>& l){
        node* p =l.head->next;
        while (p->data==0) p=p->next;
        while (p!=l.tail){
            os<<p->data;
            p=p->next;
        }
        return os;
    }
    friend bool operator==(const list<T>& l1,const list<T>& l2){
        node* p1=l1.head->next;
        node* p2=l2.head->next;

        while(p1!=l1.tail && p2!=l2.tail){
            if (p1->data!= p2->data) return false;

            p1=p1->next;
            p2=p2->next;
        }
        return p1==l1.tail && p2==l2.tail;
    }
protected:
    struct node{
        T data;
        node* prev;
        node* next;

        node(){prev = next =nullptr;}
        node(const T& x, node* p= nullptr, node* n = nullptr){data = x; prev = p; next = n;}
    };

    node* head;
    node* tail;
    int current_size;

    node* move(int i) const{
        assert(i>=0 && i<= current_size); // 如果i=current_size 最后返回的p是tail结点的地址

        node* p=head->next;
        for (int j=0;j<i;j++) p=p->next;
        return p;
    }
public:
    list(){
        head = new node;
        tail = new node;
        head -> next = tail;
        tail -> prev = head;
        current_size = 0;
    }
    list(const list& l){
        list();

        node* p=l.head->next;
        while(p!=l.tail){
            push_back(p->data);
            p=p->next;
        }
    }
    list& operator=(const list& l){
        if (this==&l) return *this;

        clear();

        node* p=l.head->next;
        while(p!=l.tail){
            push_back(p->data);
            p=p->next;
        }
        return *this;
    }
    ~list(){clear();delete head;delete tail;}

    void clear(){
        node* p=head->next;
        node* q;
        while(p!=tail){
            q=p->next;
            delete p;
            p=q;
        }

        head->next=tail;
        tail->prev=head;
        current_size=0;
    }

    int length() const {return current_size;}

    void insert(int i, const T& x){
        assert(i>=0 && i<=current_size); //insert 里允许对current_size取等 方便了push_back的设计

        node* p=new node(x);
        node* q=move(i);
        node* r=q->prev;

        p->prev=r;
        p->next=q;

        q->prev=p;
        r->next=p;

        current_size++;
    }
    void remove(int i){
        assert(i>=0 && i<current_size);

        node* p=move(i);
        node* q=p->prev;
        node* r=p->next;

        delete p;

        q->next=r;
        r->prev=q;

        current_size--;
    }

    void push_back(const T& x){
        node* p=new node(x);
        node* q=tail->prev;

        p->prev=q;
        q->next=p;

        tail->prev=p;
        p->next=tail;

        current_size++;
    }
    void push_front(const T& x){
        node* p=new node(x);
        node* q=head->next;

        p->next=q;
        q->prev=p;

        head->next=p;
        p->prev=head;

        current_size++;
    }
    void pop_back(){
        node* p=tail->prev;
        node* o=p->prev;

        delete p;

        o->next=tail;
        tail->prev=o;

        current_size--;
    }
    void pop_front(){
        node* p = head->next;
        node* q = p->next;

        delete p;

        head->next=q;
        q->prev=head;

        current_size--;
    }

    int find(const T& x){
        node* p=head->next;
        for (int i=0;i<current_size;i++){
            if (p->data == x) return i;
            p = p->next;
        }
        return -1;
    }

    T& operator[](int i){
        assert(i>=0 && i<current_size);

        node* p=head->next;
        for (int j=0;j<i;j++) p = p->next; //进行了i次操作
        return p->data;
    }
};


typedef list<char> line;

class document : public list<list<char>> {
public:
    void input(){
        line l;
        line end; for (int i=0;i<6;i++) end.push_back('*');

        while (true){
            cin>>l;
            if (l==end) break;
            push_back(l);
        }
    }
    void quit() { list(1,length()); }
    void list(int n1,int n2){
        if (n1<1 ||n2<1 || n1>length() || n2>length() || n1>n2) { throw error{}; }

        for (int i=n1-1;i<n2;i++) cout<<(*this)[i]<<endl;
    }
    void ins(int i,int j,char* str){
        if (i<1 || i>length()) { throw error{}; }
        node* p =move(i-1);
        int J=j-1;
        if (J<0 || J> p->data.length()) { throw error{}; }

        while (*str){
            p->data.insert(J++,*str);
            str++;
        }
    }
    void del(int i,int j,int num){
        if (i<=0 || i>length() || num<0){ throw error{}; }
        node* p =move(i-1);
        int J=j-1;
        if (J<0 || J> p->data.length() - num || (J==0 && num==p->data.length())) { throw error{}; }

        for (int k=0;k<num;k++){
            p->data.remove(J);
        }
    }
};

int main() {
    document d;d.input();
    while (true){
        try{
            char input[2000];cin>>input;
            if (strcmp(input,"quit")==0) {
                d.quit();
                break;
            }
            else if (strcmp(input,"list")==0){
                int n1,n2;cin>>n1>>n2;
                d.list(n1,n2);
            }
            else if (strcmp(input,"ins")==0){
                int i,j;char str[101];cin>>i>>j; cin.get();cin.getline(str,101);
                d.ins(i,j,str);
            }
            else if (strcmp(input,"del")==0){
                int i,j,num;cin>>i>>j>>num;
                d.del(i,j,num);
            }
            else {
                throw error{};
            }
        }
        catch(...){
            cout<<"Error!"<<endl;
        }
    }
    return 0;
}
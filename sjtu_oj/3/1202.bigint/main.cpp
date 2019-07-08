#include <iostream>
#include <assert.h>


using namespace std;

template <class T>
class list {
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
            current_size++;
            push_back(p->data);
            p=p->next;
        }
    }
    list& operator=(const list& l){
        if (this==&l) return *this;

        clear();

        node* p=l.head->next;
        while(p!=l.tail){
            current_size++;
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
    void pop_back(){ remove(current_size-1); }
    void pop_front(){remove(0);}

    int search(const T& x){
        node* p=head->next;
        for (int i=0;i<current_size;i++){
            if (p->data == x) return i;
            p = p->next;
        }
        return -1;
    }

    T visit(int i) const{
        assert(i>=0 && i<current_size);

        node* p=head->next;
        for (int j=0;j<i;j++) p = p->next; //进行了i次操作
        return p->data;
    }

    void printall() const{
        node* p=head->next;
        for (int i=0;i<current_size;i++){
            cout<<p->data;
            p = p->next;
        }
        cout<<endl;
    }
};

class bigint : public list<int> {
    friend istream& operator>>(istream& is, bigint& b){
        b.clear();
        int i;
        while ((i = is.get() - '0') != ('\n' - '0')){
            assert(i>=0 && i<=9);
            b.push_back(i);
        }
        return is;
    }
    friend ostream& operator<<(ostream& os, const bigint& b){
        node* p =b.head->next;
        while (p->data==0) p=p->next;
        while (p!=b.tail){
            os<<p->data;
            p=p->next;
        }
        return os;
    }
    friend bigint operator+(const bigint& b1, const bigint& b2){
        bigint b;

        node* p1=b1.tail->prev;
        node* p2=b2.tail->prev;
        node* q1=b1.head;
        node* q2=b2.head;
        int carry =0;
        while (p1!=q1 && p2!=q2){
            int t = p1->data+p2->data+carry;
            if (t<10){
                carry=0;
                b.push_front(t);
            }else{
                b.push_front(t%10);
                carry = t/10;
            }

            p1=p1->prev;
            p2=p2->prev;
        }
        while (p1==q1 && p2!=q2){
            int t = p2->data+carry;
            if (t<10){
                b.push_front(t);
                carry =0;
            }else{
                b.push_front(t%10);
                carry = t/10;
            }
            p2=p2->prev;
        }
        while (p1!=q1 && p2==q2){
            int t = p1->data+carry;
            if (t<10){
                carry=0;
                b.push_front(t);
            }else{
                b.push_front(t%10);
                carry = t/10;
            }
            p1=p1->prev;
        }
        if (carry!=0) {
            b.push_front(carry);
        }
        return b;
    }
};

int main(){
    bigint b1,b2;
    cin>>b1>>b2;

    bigint b = b1 + b2;
    cout<<b;
    return 0;
}
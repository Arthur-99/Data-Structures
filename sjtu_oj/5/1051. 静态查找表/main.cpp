#include <iostream>

using namespace std;

template<class T>
class list {
private:
    struct node {
        T data;
        node *prev;
        node *next;

        node() { prev = next = nullptr; }

        node(T d, node *p = nullptr, node *n = nullptr) {
            data = d;
            prev = p;
            next = n;
        }
    };

    node *head;
    node *tail;
public:
    list() {
        head = new node;
        tail = new node;
        head->next = tail;
        tail->prev = head;
    }

    list(const list &l) {
        head = new node;
        tail = new node;
        head->next = tail;
        tail->prev = head;

        node *p = l.head->next;
        while (p != l.tail) {
            push_back(node(p->data));
            p = p->next;
        }
    }

    ~list() {
        node *p = head->next;
        node *q = p;
        while (p != tail) {
            q = p->next;
            delete p;
            p = q;
        }
        delete head;
        delete tail;
    }

    void push_back(const T &x) {
        node *p = tail->prev;
        node *q = new node(x);
        p->next = q;
        q->prev = p;
        tail->prev = q;
        q->next = tail;
    }

    T pop_back() {
        node *p = tail->prev;
        node *q = p->prev;
        q->next = tail;
        tail->prev = q;
        T ret = p->data;
        delete p;
        return ret;
    }

    void push_front(const T &x) {
        node *p = head->next;
        node *q = new node(x);
        p->prev = q;
        q->next = p;
        head->next = q;
        q->prev = head;
    }

    T pop_front() {
        node *p = head->next;
        node *q = p->next;
        head->next = q;
        q->prev = head;
        T ret = p->data;
        delete p;
        return ret;
    }

    int size() {
        int len = 0;
        node *p = head->next;
        while (p != tail) {
            len++;
            p = p->next;
        }
        return len;
    }

    void trav() {
        node *p = head->next;
        while (p != tail) {
            cout << p->data << ' ';
            p=p->next;
        }
        cout << endl;
    }

    int find(T& x){
        int total=0;
        node* p = head->next;
        while (p!=tail){
            total++;
            if (p->data == x) {
                push_front(p->data);

                node* q=p->prev;
                node* r=p->next;
                delete p;
                q->next=r;
                r->prev=q;

                return total;
            }
            p=p->next;
        }
        return total;
    }
};

int main() {
    int n;
    cin>>n;

    list<int> l;
    for (int i=0;i<n;i++) {
        int t;
        cin>>t;
        l.push_back(t);
    }

    int m;
    cin>>m;

    int times=0;
    for (int i=0;i<m;i++){
        int t;
        cin>>t;

        int lfindt = l.find(t);
        times+=lfindt;
    }

    cout<<times;

    return 0;
}
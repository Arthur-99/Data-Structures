#include <iostream>
#include <cstdio>

using namespace std;

template<class T>
class linkStack {
private:
    struct node {
        T data;
        node *prev;
        node *next;

        node(const T &x, node *p = nullptr, node *n = nullptr) {
            data = x;
            prev = p;
            next = n;
        }

        node() {
            prev = nullptr;
            next = nullptr;
        }
    };

    node *head;
    node *tail;

public:
    linkStack() {
        head = new node;
        tail = new node;

        head->next = tail;
        tail->prev = head;
    }

    linkStack(const linkStack<T> &s) {
        head = new node;
        tail = new node;

        head->next = tail;
        tail->prev = head;

        node *p = s.head->next;
        while (p != s.tail) {
            //push(p->data);
            node *r = new node(p->data);
            node *s = tail->prev;

            s->next = r;
            r->prev = s;
            tail->prev = r;
            r->next = tail;

            p = p->next;
        }
    }

    ~linkStack() {
        node *p = head;
        node *q;

        while (p != tail) {
            q = p->next;
            delete p;
            p = q;
        }
        delete tail;
    }

    void push(const T &x) {
        node *p = new node(x);
        node *q = tail->prev;

        q->next = p;
        p->prev = q;
        tail->prev = p;
        p->next = tail;
    }

    void push_front(const T &x) {
        node *p = new node(x);
        node *q = head->next;

        head->next = p;
        p->prev = head;
        q->prev = p;
        p->next = q;
    }

    bool isEmpty() { return head->next == tail; }

    T pop() {
        node *p = tail->prev;
        node *q = p->prev;

        T ret = p->data;

        delete p;
        q->next = tail;
        tail->prev = q;

        return ret;
    }

    T &top() { return tail->prev->data; }
};

template<class T>
class seqStack {
private:
    T *elem;
    int top_p;
    int maxSize;

    void doubleSpace() {
        maxSize *= 2;

        T *tmp = elem;
        elem = new T[maxSize];

        for (int i = 0; i <= top_p; i++) elem[i] = tmp[i];

        delete[]tmp;
    }

public:
    seqStack(int initSize = 1000) {
        elem = new T[initSize];
        maxSize = initSize;
        top_p = -1;
    }

    seqStack(const seqStack &s) {
        elem = new T[s.maxSize];
        for (int i = 0; i <= s.top_p; i++) elem[i] = s.elem[i];

        maxSize = s.maxSize;
        top_p = s.top_p;
    }

    ~seqStack() { delete[]elem; }

    bool isEmpty() { return top_p == -1; }

    void push(const T &x) {
        if (top_p == maxSize - 1) doubleSpace();
        top_p++;
        elem[top_p] = x;
    }

    T pop() { return elem[top_p--]; }

    T &top() { return elem[top_p]; }

    void trav() {
        int p = -1;
        while (p != top_p) {
            p++;
            cout << elem[p] << ' ';
        }
        cout << endl;
    }

    int get_top_p() { return top_p; }

    void set_top_p(int t) { top_p = t; }
};


bool match(char c1, char c2) {
    if ((c1 == '(' && c2 == ')')) return true;
    if ((c1 == '[' && c2 == ']')) return true;
    if ((c1 == '{' && c2 == '}')) return true;
    return false;
}

//'match' is for right brackets
struct bracket {
    char ch;
    bool match;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    seqStack<bracket> s, t; // save & tmp
    for (int i = 0; i < n; i++) {
        int operation;
        cin >> operation;
        switch (operation) {
            case 1://push
                char ch;
                cin >> ch;

                s.push({ch, 0});

                if (!t.isEmpty()) {
                    if (match(t.top().ch, ch)) {
                        t.pop();
                        s.top().match = 1;
                    } else t.push({ch, 0});
                } else t.push({ch, 0});

                break;
            case 2://pop
                bracket tmp;
                if (!s.isEmpty()) {
                    tmp = s.pop();

                    if (tmp.match) t.push({(char) (tmp.ch - 1), 0});
                    else t.pop();
                }
                break;
            case 3://top
                if (!s.isEmpty()) cout << s.top().ch << '\n';
                break;
            case 4://ifmatch
                if (t.isEmpty() || s.isEmpty()) cout << "YES\n";
                else cout << "NO\n";

                break;
        }
    }

    cout << flush;

    return 0;
}
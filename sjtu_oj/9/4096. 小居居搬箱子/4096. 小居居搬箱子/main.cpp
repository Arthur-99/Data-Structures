#include <iostream>
#include <cstring>

using namespace std;

struct _box{
    int num;
    int pos;
    _box* prev;
    _box* next;

    _box(int nu=-1,int po=0,_box* p=nullptr,_box* n=nullptr){num=nu;pos=po;prev=p;next=n;}
};

_box box[27];


class list {
public:
    _box* head;
    _box* tail;
public:
    list(){
        head=new _box;
        tail=new _box;
        head->next=tail;
        tail->prev=head;
    }
//    ~list(){clear();delete head;delete tail;}
    void clear(){
        _box* p=head->next;
        _box* q;
        while(p!=tail){
            q=p->next;
            delete p;
            p=q;
        }
        head->next=tail;
        tail->prev=head;
    }

    void push_back(_box* p){
        _box* q=tail->prev;
        p->prev=q;
        q->next=p;
        tail->prev=p;
        p->next=tail;
    }
    void push_back(_box* p1,_box* p2){
        _box* q=tail->prev;
        p1->prev=q;
        q->next=p1;
        tail->prev=p2;
        p2->next=tail;
    }
    void remove(_box* p){
        _box* o=p->prev;
        _box* q=p->next;
        o->next=q;
        q->prev=o;
    }

    bool empty(){return head->next==tail;}
};

list l[27];

void moveOver(int a,int b){
    int ptr_list = box[a].pos;
    _box* Tail = l[ptr_list].tail;
    _box* p = Tail->prev;

    while (p->num != a){
        _box* q=p->prev;
        l[a].remove(p);
        l[p->num].push_back(p);
        p->pos=p->num;
        p=q;
    }

    _box* top=p->prev;
    top->next=Tail;
    Tail->prev=top;

    l[box[b].pos].push_back(p);
    p->pos=box[b].pos;
}
void moveOnto(int a,int b){
    int a_ptr_list = box[a].pos;
    _box* a_Tail = l[a_ptr_list].tail;
    _box* a_p = a_Tail->prev;

    while (a_p->num != a){
        _box* q=a_p->prev;
        l[a].remove(a_p);
        l[a_p->num].push_back(a_p);
        a_p->pos=a_p->num;
        a_p=q;
    }

    _box* a_top=a_p->prev;
    a_top->next=a_Tail;
    a_Tail->prev=a_top;

    //b
    int b_ptr_list = box[b].pos;
    _box* b_Tail = l[b_ptr_list].tail;
    _box* b_p = b_Tail->prev;

    while (b_p->num != b){
        _box* q=b_p->prev;
        l[b].remove(b_p);
        l[b_p->num].push_back(b_p);
        b_p->pos=b_p->num;
        b_p=q;
    }

    _box* b_top=b_p;
    b_top->next=b_Tail;
    b_Tail->prev=b_top;

    l[b_ptr_list].push_back(a_p);
    a_p->pos=b_ptr_list;
}
void pileOver(int a,int b){
    int ptr_list = box[a].pos;
    _box* Tail = l[ptr_list].tail;
    _box* p = Tail->prev;

    while (p->num != a){
        p->pos=box[b].pos;
        p=p->prev;
    }
    p->pos=box[b].pos;

    _box* top=p->prev;

    l[box[b].pos].push_back(p,Tail->prev);

    top->next=Tail;
    Tail->prev=top;
}
void pileOnto(int a,int b){
    int b_ptr_list = box[b].pos;
    _box* b_Tail = l[b_ptr_list].tail;
    _box* b_p = b_Tail->prev;

    while (b_p->num != b){
        _box* q=b_p->prev;
        l[b].remove(b_p);
        l[b_p->num].push_back(b_p);
        b_p->pos=b_p->num;
        b_p=q;
    }

    _box* b_top=b_p;
    b_top->next=b_Tail;
    b_Tail->prev=b_top;

    //pile onto
    int ptr_list = box[a].pos;
    _box* Tail = l[ptr_list].tail;
    _box* p = Tail->prev;

    while (p->num != a){
        p->pos=box[b].pos;
        p=p->prev;
    }
    p->pos=box[b].pos;

    _box* top=p->prev;

    l[box[b].pos].push_back(p,Tail->prev);

    top->next=Tail;
    Tail->prev=top;
}

int n;

void disp(){
    for (int i=0;i<n;i++){
        cout<<i<<':';
        _box* p=l[i].head->next;
        while (p!=l[i].tail) {
            cout<<' '<<p->num;
            p=p->next;
        }
        cout<<endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for (int i=0;i<n;i++) {
        box[i].num=i;
        box[i].pos=i;
        l[i].push_back(&box[i]);
    }

    char op1[20],op2[20];
    int a,b;
    cin>>op1;
    while (strcmp(op1,"quit")!=0){
        cin>>a>>op2>>b;
        if (a!=b && box[a].pos!=box[b].pos && a>=0 && a<n && b>=0 && b<n){
            if (strcmp(op1,"move")==0){
                if (strcmp(op2,"over")==0) moveOver(a,b);
                else if (strcmp(op2,"onto")==0) moveOnto(a,b);
            }
            else if (strcmp(op1,"pile")==0){
                if (strcmp(op2,"over")==0) pileOver(a,b);
                else if (strcmp(op2,"onto")==0) pileOnto(a,b);
            }
        }
        cin>>op1;
    }

    disp();

    cout<<flush;

    return 0;
}

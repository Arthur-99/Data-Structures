#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

namespace sjtu {

template<class T>
class deque {
    class list {
    public:
        struct listNode{
            T data;
            listNode* prev;
            listNode* next;

            listNode(){prev = next =nullptr;}
            listNode(const T& x, listNode* p= nullptr, listNode* n = nullptr){data = x; prev = p; next = n;}
        };

        listNode* head;
        listNode* tail;
        int current_size;

        listNode* move(int i) const{
            listNode* p=head->next;
            for (int j=0;j<i;j++) p=p->next;
            return p;
        }
    public:
        list(){
            head = new listNode;
            tail = new listNode;
            head -> next = tail;
            tail -> prev = head;
            current_size = 0;
        }
        list(const list& l){
            head = new listNode;
            tail = new listNode;
            head -> next = tail;
            tail -> prev = head;
            current_size = 0;

            listNode* p=l.head->next;
            while(p!=l.tail){
                push_back(p->data);
                p=p->next;
            }
        }
        list& operator=(const list& l){
            if (this==&l) return *this;

            clear();

            listNode* p=l.head->next;
            while(p!=l.tail){
                push_back(p->data);
                p=p->next;
            }
            return *this;
        }
        ~list(){clear();delete head;delete tail;}

        void clear(){
            listNode* p=head->next;
            listNode* q;
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
            listNode* p=new listNode(x);
            listNode* q=move(i);
            listNode* r=q->prev;

            p->prev=r;
            p->next=q;

            q->prev=p;
            r->next=p;

            current_size++;
        }
        void remove(int i){
            listNode* p=move(i);
            listNode* q=p->prev;
            listNode* r=p->next;

            delete p;

            q->next=r;
            r->prev=q;

            current_size--;
        }

        void push_back(const T& x){
            listNode* p=new listNode(x);
            listNode* q=tail->prev;

            p->prev=q;
            q->next=p;

            tail->prev=p;
            p->next=tail;

            current_size++;
        }
        void push_front(const T& x){
            listNode* p=new listNode(x);
            listNode* q=head->next;

            p->next=q;
            q->prev=p;

            head->next=p;
            p->prev=head;

            current_size++;
        }
        void pop_back(){
            listNode* p=tail->prev;
            listNode* o=p->prev;

            delete p;

            o->next=tail;
            tail->prev=o;

            current_size--;
        }
        void pop_front(){
            listNode* p = head->next;
            listNode* q = p->next;

            delete p;

            head->next=q;
            q->prev=head;

            current_size--;
        }

        int id(const T& x){
            listNode* p=head->next;
            for (int i=0;i<current_size;i++){
                if (p->data == x) return i;
                p = p->next;
            }
            return -1;
        }
        int id(listNode* x){
            listNode* p=head->next;
            for (int i=0;i<current_size;i++){
                if (p == x) return i;
                p = p->next;
            }
            return -1;
        }

        T& operator[](int i){
            listNode* p=head->next;
            for (int j=0;j<i;j++) p = p->next; //进行了i次操作
            return p->data;
        }
    };


    size_t deque_sz;

    struct node{
        node* prev;
        node* next;

        list l;
        size_t node_sz;

        node(){
            prev=next=nullptr;
            l=list();
            node_sz=0;
        }
        node(const node& n){
            prev=next=nullptr;
            node_sz=n.node_sz;
            l=n.l;
        }
        node(const node* p){
            prev=next=nullptr;
            node_sz=p->node_sz;
            l=p->l;
        }
    };

    node* head;
    node* tail;
public:
	class const_iterator;
	class iterator {
            friend class deque;//
        private:
            node* node_p;
            listNode* elem_p;
        public:
            iterator() {
                node_p=nullptr;
                elem_p=nullptr;
            }
            iterator(node* n,T* e){
                node_p=n;
                elem_p=e;
            }
            iterator(const const_iterator &other) {
                node_p=other.node_p;
                elem_p=other.elem_p;
            }
            iterator(const iterator &other) {
                node_p=other.node_p;
                elem_p=other.elem_p;
            }

            iterator operator+(int n) const {
                //n>0?
                if (n<0) {return operator-(-n);}

                iterator tmp=*this;

                n+=node_p->id(elem_p);

                while (n>=tmp.node_p->node_sz && tmp.node_p!=tail){
                    n-=tmp.node_p->node_sz;
                    tmp.node_p=tmp.node_p->next;
                }

                return iterator(tmp.node_p,tmp.node_p->move(n));
            }
            iterator operator-(int n) const {
                if (n<0) {return operator+(-n);}

                iterator tmp=*this;

                n+=node_p->currentSize - node_p->id(elem_p) - 1;

                while (n>=tmp.node_p->node_sz && tmp.node_p!=head){
                    n-=tmp.node_p->node_sz;
                    tmp.node_p=tmp.node_p->prev;
                }

                return iterator(tmp.node_p,tmp.node_p->move(tmp.node_p->node_sz - n - 1));
            }
            // return th distance between two iterator,
            // if these two iterators points to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const {
                //find the bigger one
                bool flag=false;
                iterator big=*this,small=rhs;
                iterator tmp1=*this,tmp2=rhs;

                int num1=0;
                while (tmp1.node_p->node_sz/*!=0*/){ // 0 : head
                    tmp1.node_p=tmp1.node_p->prev;
                    num1++;
                }
                int num2=0;
                while (tmp2.node_p->node_sz/*!=0*/){ // 0 : head
                    tmp2.node_p=tmp2.node_p->prev;
                    num2++;
                }
                if (tmp1.node_p != tmp2.node_p) throw invalid_iterator{};
                else if (num1==num2){
                    return tmp1.node_p->id(tmp1->elem_p)-tmp2.node_p->id(tmp2->elem_p);
                } else if (num1>num2){
                    //pass
                } else if (num1<num2){
                    std::swap(big,small);
                    flag=true;
                }


                //----------------------------------------------------------------------------------
                int res=0;
                if (big.elem_p==nullptr){
                    big.node_p=big.node_p->prev;
                    big.elem_p=big.node_p->storage
                                +big.node_p->node_sz
                                -1;
                    res++;
                }
                res+=(big.elem_p - big.node_p->storage) - (small.elem_p - small.node_p->storage);//
                big.node_p=big.node_p->prev;
                small.node_p=small.node_p->prev;


                big.elem_p=big.node_p->storage
                            +(big.node_p->storage
                            +big.node_p->node_sz
                            -big.elem_p-1);

                while (big.node_p!=small.node_p){
                    res+=big.node_p->node_sz;
                    big.node_p=big.node_p->prev;
                }

                if (flag) return -res;
                else return res;

            }
            iterator operator+=(int n) {
                if (n<0) return *this=*this-(-n);
                return *this=*this+n;
            }
            iterator operator-=(int n) {
                if (n<0) return *this=*this+(-n);
                return *this=*this-n;
            }

            iterator operator++(int) {
                iterator tmp=*this;
                if (elem_p==node_p->tail->prev){
                    node_p=node_p->next;
                    elem_p=node_p->head->next;
                } else elem_p=elem_p->next;
                return tmp;
            }
            iterator& operator++() {
                if (elem_p==node_p->tail->prev){
                    node_p=node_p->next;
                    elem_p=node_p->head->next;
                } else elem_p=elem_p->next;
                return *this;
            }
            iterator operator--(int) {
                iterator tmp=*this;
                if (elem_p==node_p->head->next){
                    node_p=node_p->prev;
                    elem_p=node_p->tail->prev;
                } else elem_p=elem_p->prev;
                return tmp;
            }
            iterator& operator--() {
                if (elem_p==node_p->head->next){
                    node_p=node_p->prev;
                    elem_p=node_p->tail->prev;
                } else elem_p=elem_p->prev;
                return *this;
            }

            T& operator*() const {return *elem_p;}
            T* operator->() const noexcept {return elem_p;}

            bool operator==(const iterator &rhs) const {
                return node_p==rhs.node_p && elem_p==rhs.elem_p;
            }
            bool operator==(const const_iterator &rhs) const {
                return node_p==rhs.node_p && elem_p==rhs.elem_p;
            }
            bool operator!=(const iterator &rhs) const {
                return node_p!=rhs.node_p || elem_p!=rhs.elem_p;
            }
            bool operator!=(const const_iterator &rhs) const {
            return node_p!=rhs.node_p || elem_p!=rhs.elem_p;
		}
	};
	class const_iterator {
		private:
            node* node_p;
            T* elem_p;
		public:
            const_iterator(node* n,T* e){
                node_p=n;
                elem_p=e;
            }
            const_iterator(const const_iterator &other) {
                node_p=other.node_p;
                elem_p=other.elem_p;
            }
            const_iterator(const iterator &other) {
                node_p=other.node_p;
                elem_p=other.elem_p;
            }

            const_iterator operator+(int n) const {
                //n>0?
                if (n<0) {return operator-(-n);}

                iterator tmp=*this;

                n+=elem_p-node_p->storage;

                tmp.elem_p=tmp.node_p->storage;

                while (n>=tmp.node_p->node_sz && tmp.node_p->node_sz /*!= -1*/){// -1 : tail
                    n-=tmp.node_p->node_sz;
                    tmp.node_p=tmp.node_p->next;
                }

                return const_iterator(tmp.node_p,tmp.node_p->storage+n);
            }
            const_iterator operator-(int n) const {
                if (n<0) {return operator+(-n);}

                iterator tmp=*this;

                if (tmp.elem_p==nullptr){
                    tmp.node_p=tmp.node_p->prev;
                    tmp.elem_p=tmp.node_p->storage
                                +tmp.node_p->node_sz
                                -1;
                }

                n+=node_p->storage
                    +node_p->node_sz
                    -elem_p-1;

                tmp.elem_p=tmp.node_p->storage
                            +(tmp.node_p->storage
                            +tmp.node_p->node_sz
                            -tmp.elem_p-1);

                while (n>=tmp.node_p->node_sz && tmp.node_p->node_sz /*!= 0*/){ // 0 : head
                    n-=tmp.node_p->node_sz;
                    tmp.node_p=tmp.node_p->prev;
                }

                return const_iterator(
                                tmp.node_p,
                                tmp.node_p->storage + tmp.node_p->node_sz - n - 1
                                );
            }
            // return th distance between two iterator,
            // if these two iterators points to different vectors, throw invaild_iterator.
            int operator-(const const_iterator &rhs) const {
                //find the bigger one
                bool flag=false;
                iterator big=*this,small=rhs;
                iterator tmp1=*this,tmp2=rhs;

                int num1=0;
                while (tmp1.node_p->node_sz/*!=0*/){ // 0 : head
                    tmp1.node_p=tmp1.node_p->prev;
                    num1++;
                }
                int num2=0;
                while (tmp2.node_p->node_sz/*!=0*/){ // 0 : head
                    tmp2.node_p=tmp2.node_p->prev;
                    num2++;
                }
                if (tmp1.node_p != tmp2.node_p) throw invalid_iterator{};
                else if (num1==num2){
                    return tmp1.elem_p-tmp2.elem_p;
                } else if (num1>num2){
                    //pass
                } else if (num1<num2){
                    std::swap(big,small);
                    flag=true;
                }


                //----------------------------------------------------------------------------------
                int res=0;
                if (big.elem_p==nullptr){
                    big.node_p=big.node_p->prev;
                    big.elem_p=big.node_p->storage
                                +big.node_p->node_sz
                                -1;
                    res++;
                }
                res+=(big.elem_p - big.node_p->storage) - (small.elem_p - small.node_p->storage);//
                big.node_p=big.node_p->prev;
                small.node_p=small.node_p->prev;


                big.elem_p=big.node_p->storage
                            +(big.node_p->storage
                            +big.node_p->node_sz
                            -big.elem_p-1);

                while (big.node_p!=small.node_p){
                    res+=big.node_p->node_sz;
                    big.node_p=big.node_p->prev;
                }

                if (flag) return -res;
                else return res;

            }

            T& operator*() const {return *elem_p;}
            T* operator->() const noexcept {return elem_p;}

            bool operator==(const iterator &rhs) const {
                return node_p==rhs.node_p && elem_p==rhs.elem_p;
            }
            bool operator==(const const_iterator &rhs) const {
                return node_p==rhs.node_p && elem_p==rhs.elem_p;
            }
            bool operator!=(const iterator &rhs) const {
                return node_p!=rhs.node_p || elem_p!=rhs.elem_p;
            }
            bool operator!=(const const_iterator &rhs) const {
		    return node_p!=rhs.node_p || elem_p!=rhs.elem_p;
		}
	};

	deque() {
	    srand(time(0));//
	    deque_sz=0;

        head=new node;
        tail=new node;

//        head->node_sz=0;
//        tail->node_sz=-1;

        link(head,tail);
	}
	deque(const deque &other) {
        deque_sz=other.deque_sz;

        head=new node;
        tail=new node;

//        head->node_sz=0;
//        tail->node_sz=-1;

        link(head,tail);

        node* p=other.head->next;
        while (p!=other.tail){
            node* q=new node(p);
            link(tail->prev,q,tail);
            p=p->next;
        }
	}
	~deque() {
        clear();
        delete head;
        delete tail;
	}
	deque &operator=(const deque &other) {
        if (this==&other) return *this;

        clear();

        deque_sz=other.deque_sz;

        node* p=other.head->next;
        while (p!=other.tail){
            node* q=new node(p);
            link(tail->prev,q,tail);
            p=p->next;
        }
	}

	T & at(size_t pos) {
	    if (pos>=deque_sz || pos<0) throw index_out_of_bound{};

        node* p=head->next;
        while (p->next!=tail && pos>=p->node_sz){
            pos-=p->node_sz;
            p=p->next;
        }

        return p->storage[pos];
	}
	const T & at(size_t pos) const {
        if (pos>=deque_sz || pos<0) throw index_out_of_bound{};

        node* p=head->next;
        while (p!=tail && pos>=p->node_sz){
            pos-=p->node_sz;
            p=p->next;
        }

        return p->storage[pos];
	}
	T & operator[](size_t pos) {
        if (pos>=deque_sz || pos<0) throw index_out_of_bound{};

        node* p=head->next;
        while (p!=tail && pos>=p->node_sz){
            pos-=p->node_sz;
            p=p->next;
        }

        return p->storage[pos];
	}
	const T & operator[](size_t pos) const {
        if (pos>=deque_sz || pos<0) throw index_out_of_bound{};

        node* p=head->next;
        while (p!=tail && pos>=p->node_sz){
            pos-=p->node_sz;
            p=p->next;
        }

        return p->storage[pos];
	}

	const T & front() const {
        if (deque_sz==0) throw container_is_empty{};
        return head->next->storage[0];
	}
	const T & back() const {
        if (deque_sz==0) throw container_is_empty{};
        return tail->prev->storage[tail->prev->node_sz-1];
	}

	iterator begin() {return iterator(head->next,head->next->storage);}
	const_iterator cbegin() const {return const_iterator(head->next,head->next->storage);}
	iterator end() {return iterator(tail,tail->storage);}
	const_iterator cend() const {return const_iterator(tail,tail->storage);}

	bool empty() const {return head->next==tail;}
	size_t size() const {return deque_sz;}
	void clear() {
        node* p=head->next;
        while (p!=tail){
            node* q=p->next;

            delete []p->storage;
            delete p;

            p=q;
        }

        deque_sz=0;
	}

	iterator insert(iterator pos, const T &value) {
        if (wrong_place(pos)) throw invalid_iterator{};

        deque_sz++;

        node* p=pos.node_p;
        int index=pos.elem_p-p->storage;

        if (p->node_sz > 2*sqrt(deque_sz)){
            //divide
            int sz=p->node_sz+1;

            node* q=new node; // sz/2
            node* r=new node; // sz - sz/2
            q->node_sz=sz/2;
            r->node_sz=sz-sz/2;
            q->storage=new T[q->node_sz];
            r->storage=new T[r->node_sz];

            if (index < sz/2){
                //q : insert
                for (int i=0;i<index;i++) q->storage[i]=p->storage[i];
                q->storage[index]=value;
                for (int i=index+1;i<sz/2;i++) q->storage[i]=p->storage[i-1];

                //r : just copy
                for (int i=0;i<sz-sz/2;i++) r->storage[i]=p->storage[sz/2 + i];
            } else {
                //r : insert
                for (int i=0;i<index - sz/2;i++) r->storage[i]=p->storage[i + sz/2];
                r->storage[index - sz/2]=value;
                for (int i=index - sz/2 + 1;i<sz-sz/2;i++) r->storage[i]=p->storage[i + sz/2 -1];

                //q : just copy
                for (int i=0;i<sz/2;i++) q->storage[i]=p->storage[i];
            }

            link(p->prev,q,r,p->next);

            delete []p->storage;
            delete p;

            return iterator(r,r->storage+index);
        } else {
            T* tmp=p->storage;
            p->storage=new T[++p->node_sz];
            for (int i=0;i<index;i++) p->storage[i]=tmp[i];
            p->storage[index]=value;
            for (int i=index+1;i<p->node_sz;i++) p->storage[i]=tmp[i-1];
            delete []tmp;

            return iterator(p,p->storage+index);
        }
	}

	iterator erase(iterator pos) {
        if (deque_sz==0) throw container_is_empty{};
        if (wrong_place(pos)) throw invalid_iterator{};

        deque_sz--;

        node* p=pos.node_p;
        if (p->node_sz - 1 < sqrt(deque_sz)/2 /* && !(p==tail->prev && p==head->next)*/) {
            //merge
            int dir=rand()%2;

            //spacial cases
            if (p==head->next && p!=tail->prev){
                node* q=p->next;

                node* r=new node;//merge result

                int index=pos.elem_p-pos.node_p->storage;

                size_t r_sz=--p->node_sz + q->node_sz;
                r->storage=new T[r_sz];
                r->node_sz=r_sz;

                int i;
                for (i=0;i<index;i++) r->storage[i]=p->storage[i];
                for (i=index;i<p->node_sz;i++) r->storage[i]=p->storage[i+1];
                for (i=p->node_sz;i<r_sz;i++) r->storage[i]=q->storage[i-p->node_sz];


                link(head,r,q->next);//

                delete []p->storage;
                delete p;
                delete []q->storage;
                delete q;

                return iterator(r,r->storage+index);//end??
            }
            if (p==tail->prev && p!=head->next){
                node* q=p->prev;
                node* r=new node;//merge result

                int index=pos.elem_p-pos.node_p->storage
                            + q->node_sz;

                size_t r_sz=--p->node_sz + q->node_sz;
                r->node_sz=r_sz;
                r->storage=new T[r_sz];
                for (int i=0;i<q->node_sz;i++) r->storage[i]=q->storage[i];
                for (int i=q->node_sz;i<index;i++) r->storage[i]=p->storage[i-q->node_sz];
                for (int i=index;i<r_sz;i++) r->storage[i]=q->storage[i+1-q->node_sz];

                link(q->prev,r,tail);

                delete []p->storage;
                delete p;
                delete []q->storage;
                delete q;

                return iterator(r,r->storage+index);//end??
            }

            if (dir==0){
                //merge with left block
                node* q=p->prev;
                node* r=new node;//merge result

                int index=pos.elem_p-pos.node_p->storage
                            + q->node_sz;

                size_t r_sz=--p->node_sz + q->node_sz;
                r->storage=new T[r_sz];
                r->node_sz=r_sz;

                for (int i=0;i<q->node_sz;i++) r->storage[i]=q->storage[i];
                for (int i=q->node_sz;i<index;i++) r->storage[i]=p->storage[i-q->node_sz];
                for (int i=index;i<r_sz;i++) r->storage[i]=q->storage[i+1-q->node_sz];

                link(q->prev,r,p->next);

                delete []p->storage;
                delete p;
                delete []q->storage;
                delete q;

                return iterator(r,r->storage+index);//end??
            }
            else {
                //merge with right block
                node* q=p->next;

                node* r=new node;//merge result

                int index=pos.elem_p-pos.node_p->storage;

                size_t r_sz=--p->node_sz + q->node_sz;
                r->node_sz=r_sz;
                r->storage=new T[r_sz];
                for (int i=0;i<index;i++) r->storage[i]=p->storage[i];
                for (int i=index;i<p->node_sz;i++) r->storage[i]=p->storage[i+1];
                for (int i=p->node_sz;i<r_sz;i++) r->storage[i]=q->storage[i-p->node_sz];


                link(p->prev,r,q->next);

                delete []p->storage;
                delete p;
                delete []q->storage;
                delete q;

                return iterator(r,r->storage+index);//end??
            }
        }
        else {
            int index=pos.elem_p-pos.node_p->storage;

            T* tmp=p->storage;
            p->storage=new T[--p->node_sz];
            for (int i=0;i<index;i++) p->storage[i]=tmp[i];
            for (int i=index;i<p->node_sz;i++) p->storage[i]=tmp[i+1];
            delete []tmp;

            return iterator(p,p->storage+index);
        }
	}


	void push_back(const T &value) {
	    deque_sz++;

        node* p=tail->prev;

        if (p==head){
            node* q=new node;

            link(head,q,tail);

            q->node_sz=1;
            q->storage = new T[q->node_sz];
            q->storage[0]=value;
        } else {
            if (p->node_sz > 2*sqrt(deque_sz)){
                //divide
                size_t tmp_sz=p->node_sz/2;

                node* q=new node;
                node* r=new node;

                q->node_sz=tmp_sz;
                r->node_sz=p->node_sz-tmp_sz+1;

                q->storage=new T[q->node_sz];
                r->storage=new T[r->node_sz];

                for (int i=0;i<q->node_sz;i++) q->storage[i]=p->storage[i];
                for (int i=0;i<r->node_sz-1;i++) r->storage[i]=p->storage[q->node_sz+i];

                r->storage[r->node_sz-1]=value;

                link(p->prev,q,r,tail);

                delete []p->storage;
                delete p;

            } else {
                T* tmp=p->storage;
                p->storage=new T[++(p->node_sz)];
                for (int i=0;i<p->node_sz-1;i++) p->storage[i]=tmp[i];
                delete []tmp;
                p->storage[p->node_sz-1]=value;
            }
        }
	}
	void pop_back() {
        if (deque_sz==0) throw container_is_empty{};

        deque_sz--;

        node* p=tail->prev;

        if (p->node_sz < sqrt(deque_sz) / 2){
            //merge
            node* o=p->prev;

            size_t sz=p->node_sz+o->node_sz-1;

            node* q=new node;
            q->node_sz=sz;
            q->storage=new T[q->node_sz];

            for (int i=0;i<o->node_sz;i++) q->storage[i]=o->storage[i];
            for (int i=o->node_sz;i<sz;i++) q->storage[i]=p->storage[i-o->node_sz];

            link(o->prev,q,tail);

            delete []o->storage;
            delete o;
            delete []p->storage;
            delete p;
        } else {
            if (--(p->node_sz)){
                T* tmp=p->storage;
                p->storage=new T[p->node_sz];
                for (int i=0;i<p->node_sz;i++) p->storage[i]=tmp[i];
                delete []tmp;
            } else {
                delete []p->storage;
                delete p;
                link(head,tail);
            }
        }
	}
	void push_front(const T &value) {
        deque_sz++;

        node* p=head->next;

        if (p==tail){
            node* q=new node;

            link(head,q,tail);

            q->node_sz=1;
            q->storage = new T[q->node_sz];
            q->storage[0]=value;
        } else {
            if (p->node_sz > 2*sqrt(deque_sz)){
                //divide
                size_t tmp_sz=p->node_sz/2;

                node* q=new node;
                node* r=new node;

                q->node_sz=tmp_sz+1;
                r->node_sz=p->node_sz-tmp_sz;

                q->storage=new T[q->node_sz];
                r->storage=new T[r->node_sz];

                q->storage[0]=value;
                for (int i=1;i<q->node_sz;i++) q->storage[i]=p->storage[i-1];
                for (int i=0;i<r->node_sz;i++) r->storage[i]=p->storage[q->node_sz+i-1];

                link(head,q,r,p->next);

                delete []p->storage;
                delete p;

            } else {
                T* tmp=p->storage;
                p->storage=new T[++(p->node_sz)];
                p->storage[0]=value;
                for (int i=1;i<p->node_sz;i++) p->storage[i]=tmp[i-1];
                delete []tmp;
            }
        }
	}
	void pop_front() {
        if (deque_sz==0) throw container_is_empty{};

        deque_sz--;

        node* p=head->next;

        if (p->node_sz < sqrt(deque_sz) / 2){
            //merge
            node* o=p->next;

            size_t sz=p->node_sz+o->node_sz-1;

            node* q=new node;
            q->node_sz=sz;
            q->storage=new T[q->node_sz];

            for (int i=0;i<p->node_sz-1;i++) q->storage[i]=p->storage[i+1];
            for (int i=p->node_sz-1;i<sz;i++) q->storage[i]=o->storage[i-p->node_sz+1];

            link(head,q,o->next);

            delete []o->storage;
            delete o;
            delete []p->storage;
            delete p;
        } else {
            if (--(p->node_sz)){
                T* tmp=p->storage;
                p->storage=new T[p->node_sz];
                for (int i=0;i<p->node_sz;i++) p->storage[i]=tmp[i+1];
                delete []tmp;
            } else {
                delete []p->storage;
                delete p;
                link(head,tail);
            }
        }
	}

	void trav(){
        node* p=head->next;
        while (p!=tail){
            std::cout<<"# ";
            for (int i=0;i<p->node_sz;i++) std::cout<<p->storage[i]<<' ';
            std::cout<<"\t\t size: "<<p->node_sz;
            std::cout<<"\n";
            p=p->next;
        }

        std::cout<<"\n\n\n";
	}
private:
    bool wrong_place(const iterator& itr){
        node* p=head->next;
        while (p!=tail){
            if (itr.node_p == p) return false;
            p=p->next;
        }
        return true;
    }
    bool wrong_place(const const_iterator& itr){
        node* p=head->next;
        while (p!=tail){
            if (itr.node_p == p) return false;
            p=p->next;
        }
        return true;
    }
    void link(node*& p,node*& q){
        p->next=q;q->prev=p;
    }
    void link(node*& p,node*& q,node*& r){
        if (q){
            p->next=q;q->prev=p;
            q->next=r;r->prev=q;
        } else link(p,r);
    }
    void link(node*& p,node*& q,node*& r,node*& s){
        p->next=q;q->prev=p;
        q->next=r;r->prev=q;
        r->next=s;s->prev=r;
    }
};

}

#endif

using namespace std;
using namespace sjtu;

int main(){

    int n=16;

    deque<int> d;
    for (int i=1;i<=n;i++) d.push_front(i);
    d.trav();

    for (deque<int>::iterator p=d.begin();p!=d.end();p=d.begin()){
        d.insert(p,0);
        d.trav();
    }

    cout<<"\nn: "<<n<<endl;
    return 0;
}

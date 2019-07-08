#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>

#include <iostream>
#include <cmath>

namespace sjtu {

template<class T>
class deque {
//node
    struct node {
        T* data;//
        node* prev;
        node* next;

        node(){data=nullptr;prev=next=nullptr;}
        node(const T& x, node* p= nullptr, node* n = nullptr){
            data = new T(x);
            prev = p;
            next = n;
        }
        ~node(){if (data) delete data;}
    };

//block : a list with 5 member variables ---- left right blockHead blockTail blockSize
    struct block {
        block* left;
        block* right;

        node* blockHead;
        node* blockTail;
        size_t blockSize;

        //move to the i-th elem of the block
        node* move(int i) const{
            node* p=blockHead->next;
            if (i>=0 ) for (int j=0;j<i && p;j++) p=p->next;
            else if (i==-1) {
                return blockHead;
            }
            return p;
        }

        block(){
            left=right=nullptr;

            blockHead = new node;
            blockTail = new node;
            link(blockHead,blockTail);

            blockSize = 0;
        }
        block(const block& l){
            left=right=nullptr;

            blockHead = new node;
            blockTail = new node;
            link(blockHead,blockTail);

            blockSize = 0;

            node* p=l.blockHead->next;
            while(p!=l.blockTail){
                push_back(*p->data); // blockSize++ simultaneously
                p=p->next;
            }
        }
        block(const block* l){
            left=right=nullptr;

            blockHead = new node;
            blockTail = new node;
            link(blockHead,blockTail);

            blockSize = 0;

            node* p=l->blockHead->next;
            while(p!=l->blockTail){
                push_back(*p->data); //blockSize++ simultaneously
                p=p->next;
            }
        }

        //Given l's head and tail, defines a block, this function is designed for function divide()
        block(node* h,node* t){
            blockHead=h;blockTail=t;
        }

        ~block(){
            clear();
            delete blockHead;
            delete blockTail;
        }

        bool empty(){return blockSize==0;}

        void link(node*& p,node*& q){
            p->next=q;q->prev=p;
        }
        void link(node*& p,node*& q,node*& r){
            p->next=q;q->prev=p;
            q->next=r;r->prev=q;
        }
        void clear(){
            node* p=blockHead->next;
            node* q;
            while(p!=blockTail){
                q=p->next;
                delete p;
                p=q;
            }

            link(blockHead,blockTail);
            blockSize=0;
        }

        /*
            inserts value before q
            returns a pointer of the inserted node(value)
        */
        node* insert(node* q, const T& value){
            node* p=new node(value);
            link(q->prev,p,q);
            blockSize++;
            return p;
        }

        /*
            returns a pointer of the node saving the following element, if q points to
            the last element of deque, the node pointer of end() will be returned

            PS: iterator is constructed with 2 pointers,
                one points to the block in which it is located and
                the other points to the very node containing the 'T* data'
        */
        node* remove(block*& p,node* q){
            link(q->prev,q->next);
            node* ret=q->next;//next不一定什么东西

            if (ret==blockTail){
                if (right->blockSize) {
                    ret=right->blockHead->next;
                    p=p->right;
                }
            }

            blockSize--;
            delete q;
            return ret;
        }

        void push_back(const T& x){insert(blockTail,x);}
        void push_front(const T& x){insert(blockHead->next,x);}

        /*
            returns the index in the block,
            if it doesn't exist in the block at all, returns -1
        */
        int id(const T& x){
            node* p=blockHead->next;
            for (int i=0;i<blockSize+1;i++){
                if (*(p->data) == x) return i;//bug *(p->data)
                p = p->next;
            }
            return -1;
        }
        int id(node* x){
            node* p=blockHead->next;
            for (int i=0;i<blockSize+1;i++){
                if (p == x) return i;
                p = p->next;
            }
            return -1;
        }

        /*
            merges this block with the smaller one of the left or right block,
            redefines this block,
            returns a pointer to the new block
        */
        block* merge(){
            // TODO : merges with the smaller one
            if (left->blockSize) {
                block* this_l=left->left;
                block* this_r=right;

                block* P=left;

                //add P to this then delete P
                node* w=P->blockHead->next;
                node* ww=P->blockTail->prev;

                link(ww,blockHead->next);
                link(blockHead,w);

                blockSize+=P->blockSize;

                link(P->blockHead,P->blockTail);
                delete P;

                this_l->right=this;
                this_r->left=this;
                left=this_l;
                right=this_r;

            } else if (right->blockSize){
                block* this_l=left;
                block* this_r=right->right;

                block* Q=right;

                //add Q to this then delete Q
                node* w=Q->blockHead->next;
                node* ww=Q->blockTail->prev;

                link(blockTail->prev,w);
                link(ww,blockTail);

                blockSize+=Q->blockSize;

                link(Q->blockHead,Q->blockTail);
                delete Q;

                this_l->right=this;
                this_r->left=this;
                left=this_l;
                right=this_r;

            }

            return this;
        }

        /*
            divides this block into 2 parts 'equally',
            redefines this block,
            returns a pointer to the block containing node* x
        */
         block* divide(node* x){
            block* this_l=left;
            block* this_r=right;

            //divides this block into 2 parts
            node* p=move(blockSize/2);
            node* q=p->next;

            node* p_n=new node;
            node* q_p=new node;
            link(p,p_n);
            link(q_p,q);

            block* Q=new block(q->prev,blockTail);
            //block* P=new block(blockHead,p->next);
            blockTail=p->next;

            //sets the 2 parts
            Q->blockSize=blockSize-blockSize/2 - 1;
            blockSize=blockSize/2 + 1;

            right=Q;

            Q->left=this;
            Q->right=this_r;


            this_r->left=Q;

            //returns the pointer to block containing x
            if (Q->id(x)==-1) return this;
            else return Q;
        }
    };

// d e q u e
    size_t dequeSize;

    block* head;
    block* tmp;
    block* tail;
public:
    class const_iterator;
    class iterator {
            friend class deque;
            friend class const_iterator;
        private:
            block* deque_p;
            block* list_p;
            node* node_p;
        public:
            iterator() {list_p=nullptr;node_p=nullptr;deque_p=nullptr;}
            iterator(block* l,node* n,block* d){list_p=l;node_p=n;deque_p=d;}
            iterator(const const_iterator &other) {list_p=other.list_p;node_p=other.node_p;deque_p=other.deque_p;}
            iterator(const iterator &other) {list_p=other.list_p;node_p=other.node_p;deque_p=other.deque_p;}

            iterator operator+(int n) const {
                //n>0?
                if (n<0) {return operator-(-n);}

                iterator tmp=*this;

                n+=list_p->id(node_p);

                while (n>=tmp.list_p->blockSize && tmp.list_p->blockSize){
                    if (tmp.list_p->right->blockSize==0) break;///end()
                    n-=tmp.list_p->blockSize;
                    tmp.list_p=tmp.list_p->right;
                }

                return iterator(tmp.list_p,tmp.list_p->move(n),deque_p);
            }
            iterator operator-(int n) const {
                //bug : end() - 0 , 把它变成end() + 0
                if (n<=0) {return operator+(-n);}

                iterator tmp=*this;

                n+=list_p->blockSize - list_p->id(node_p) - 1;

                while (n>=tmp.list_p->blockSize && tmp.list_p->blockSize){
                    if (tmp.list_p->left->blockSize==0) break;///begin()
                    n-=tmp.list_p->blockSize;
                    tmp.list_p=tmp.list_p->left;
                }

                return iterator(tmp.list_p,tmp.list_p->move(tmp.list_p->blockSize - n - 1),deque_p);
            }

            int operator-(const iterator &rhs) const {
                //find the bigger one
                bool flag=false;
                iterator big=*this,small=rhs;
                iterator tmp1=*this,tmp2=rhs;

                int num1=0;
                while (tmp1.list_p->blockSize/*!=0*/){ // 0 : head
                    tmp1.list_p=tmp1.list_p->left;
                    num1++;
                }
                int num2=0;
                while (tmp2.list_p->blockSize/*!=0*/){ // 0 : head
                    tmp2.list_p=tmp2.list_p->left;
                    num2++;
                }
                if (tmp1.list_p != tmp2.list_p) throw invalid_iterator{};
                else if (num1==num2){
                    return big.list_p->id(big.node_p)-small.list_p->id(small.node_p);
                } else if (num1<num2){
                    std::swap(big,small);
                    flag=true;
                }

                //----------------------------------------------------------------------------------
                int res=0;

                res+=(big.list_p->id(big.node_p)) - (small.list_p->id(small.node_p));//

                big.list_p=big.list_p->left;
                small.list_p=small.list_p->left;

                while (big.list_p!=small.list_p){
                    res+=big.list_p->blockSize;
                    big.list_p=big.list_p->left;
                }

                if (flag) return -res;
                else return res;

            }

            iterator operator+=(int n) {
                if (n<0) return *this=*this-(-n);
                return *this=*this+n;
            }
            iterator operator-=(int n) {
                if (n<=0) return *this=*this+(-n);
                return *this=*this-n;
            }

            iterator operator++(int) {
                //end throw
                if (node_p->data==nullptr && list_p->right->blockSize==0) throw invalid_iterator{};

                iterator tmp=*this;
                if (node_p==list_p->blockTail->prev && list_p->right->blockSize==0){
                    //last elem
                    node_p=node_p->next;
                } else if (node_p==list_p->blockTail->prev){
                    list_p=list_p->right;
                    node_p=list_p->blockHead->next;
                } else {
                    try{node_p=node_p->next;} catch(...) {throw invalid_iterator{};}
                }
                return tmp;
            }
            iterator& operator++() {
                //end throw
                if (node_p->data==nullptr && list_p->right->blockSize==0) throw invalid_iterator{};

                if (node_p==list_p->blockTail->prev && list_p->right->blockSize==0){
                    //last elem
                    node_p=node_p->next;
                } else if (node_p==list_p->blockTail->prev){
                    list_p=list_p->right;
                    node_p=list_p->blockHead->next;
                } else {
                    try{node_p=node_p->next;} catch(...) {throw invalid_iterator{};}
                }
                return *this;
            }
            iterator operator--(int) {
                //begin throw
                if (node_p->prev->data==nullptr && list_p->left->blockSize==0) throw invalid_iterator{};

                iterator tmp=*this;
                if (node_p==list_p->blockHead->next){
                    list_p=list_p->left;
                    node_p=list_p->blockTail->prev;
                } else node_p=node_p->prev;
                return tmp;
            }
            iterator& operator--() {
                //begin throw
                if (node_p->prev->data==nullptr && list_p->left->blockSize==0) throw invalid_iterator{};

                if (node_p==list_p->blockHead->next){
                    list_p=list_p->left;
                    node_p=list_p->blockTail->prev;
                } else node_p=node_p->prev;
                return *this;
            }

            T& operator*() const {
                if (node_p->data) {
                    return *node_p->data;
                } else {
                    throw invalid_iterator{};
                }
            }
            T* operator->() const noexcept {return node_p->data;}

            bool operator==(const iterator &rhs) const {return node_p==rhs.node_p  && deque_p==rhs.deque_p;}
            bool operator==(const const_iterator &rhs) const {return node_p==rhs.node_p && deque_p==rhs.deque_p;}
            bool operator!=(const iterator &rhs) const {return !(*this==rhs);}
            bool operator!=(const const_iterator &rhs) const {return !(*this==rhs);}
    };
    class const_iterator {
        friend class iterator;
        private:
            block* deque_p;
            block* list_p;
            node* node_p;
        public:
            const_iterator(){list_p=nullptr;node_p=nullptr;deque_p=nullptr;}
            const_iterator(block* l,node* n,block* d):list_p(l),node_p(n),deque_p(d){}
            const_iterator(const const_iterator &other):list_p(other.list_p),node_p(other.node_p),deque_p(other.deque_p){}
            const_iterator(const iterator &other):list_p(other.list_p),node_p(other.node_p),deque_p(other.deque_p){}

            const_iterator operator+(int n) const {
                //n>0?
                if (n<0) {return operator-(-n);}
                iterator tmp=*this;
                return const_iterator(tmp+n);
            }
            const_iterator operator-(int n) const {
                if (n<=0) {return operator+(-n);}
                iterator tmp=*this;
                return const_iterator(tmp-n);
            }

            int operator-(const const_iterator &rhs) const {
                iterator lhs_tmp=*this,rhs_tmp=rhs;
                return lhs_tmp-rhs_tmp;
            }

            const_iterator operator+=(int n) {
                if (n<0) return *this=*this-(-n);
                return *this=*this+n;
            }
            const_iterator operator-=(int n) {
                if (n<=0) return *this=*this+(-n);
                return *this=*this-n;
            }

            const_iterator operator++(int) {
                iterator tmp=*this;
                return const_iterator(tmp++);
            }
            const_iterator& operator++() {
                iterator tmp=*this;
                return *this=const_iterator(++tmp);
            }
            const_iterator operator--(int) {
                iterator tmp=*this;
                return const_iterator(tmp--);
            }
            const_iterator& operator--() {
                iterator tmp=*this;
                return *this=const_iterator(--tmp);
            }

            T operator*() const {
                if (node_p->data) {
                    return *node_p->data;
                } else {
                    throw invalid_iterator{};
                }
            }
            T* operator->() const noexcept {return node_p->data;}

            bool operator==(const iterator &rhs) const {return node_p==rhs.node_p  && deque_p==rhs.deque_p;}
            bool operator==(const const_iterator &rhs) const {return node_p==rhs.node_p && deque_p==rhs.deque_p;}
            bool operator!=(const iterator &rhs) const {return !(*this==rhs);}
            bool operator!=(const const_iterator &rhs) const {return !(*this==rhs);}
    };

    deque() {
        dequeSize=0;

        head=new block;
        tmp=new block;
        tail=new block;

        link(head,tmp,tail);
    }
    deque(const deque &other) {
        dequeSize=other.dequeSize;

        head=new block;
        tail=new block;

        link(head,tail);

        block* p=other.head->right;
        while (p!=other.tail){
            block* q=new block(p);
            link(tail->left,q,tail);
            p=p->right;
        }
    }
    ~deque() {
        clear();
        delete tmp;//clear
        delete head;
        delete tail;
    }
    deque &operator=(const deque &other) {
        if (this==&other) return *this;

        clear();
        delete tmp;//clear
        link(head,tail);

        dequeSize=other.dequeSize;

        block* p=other.head->right;
        while (p!=other.tail){
            block* q=new block(p);
            link(tail->left,q,tail);
            p=p->right;
        }
        return *this;
    }

    T & at(size_t pos) {
        if (pos>=dequeSize || pos<0) throw index_out_of_bound{};

        block* p=head->right;
        while (p!=tail && pos>=p->blockSize){
            pos-=p->blockSize;
            p=p->right;
        }

        return *(p->move(pos))->data;
    }
    const T & at(size_t pos) const {
        if (pos>=dequeSize || pos<0) throw index_out_of_bound{};

        block* p=head->right;
        while (p!=tail && pos>=p->blockSize){
            pos-=p->blockSize;
            p=p->right;
        }

        return *(p->move(pos))->data;
    }
    T & operator[](size_t pos) {
        if (pos>=dequeSize || pos<0) throw index_out_of_bound{};

        block* p=head->right;
        while (p!=tail && pos>=p->blockSize){
            pos-=p->blockSize;
            p=p->right;
        }

        return *(p->move(pos))->data;
    }
    const T & operator[](size_t pos) const {
        if (pos>=dequeSize || pos<0) throw index_out_of_bound{};

        block* p=head->right;
        while (p!=tail && pos>=p->blockSize){
            pos-=p->blockSize;
            p=p->right;
        }

        return *(p->move(pos))->data;
    }

    const T & front() const {
        if (dequeSize==0) throw container_is_empty{};
        return *head->right->blockHead->next->data;
    }
    const T & back() const {
        if (dequeSize==0) throw container_is_empty{};
        return *tail->left->blockTail->prev->data;
    }

    iterator begin() {return iterator(head->right,head->right->blockHead->next,head);}
    const_iterator cbegin() const {return const_iterator(head->right,head->right->blockHead->next,head);}
    iterator end() {return iterator(tail->left,tail->left->blockTail,head);}
    const_iterator cend() const {return const_iterator(tail->left,tail->left->blockTail,head);}

    bool empty() const {return dequeSize==0;}
    size_t size() const {return dequeSize;}
    void clear() {
        block* p=head->right;
        while (p!=tail){
            block* q=p->right;
            delete p;
            p=q;
        }
        dequeSize=0;

        tmp=new block;
        link(head,tmp,tail);
    }

    iterator insert(iterator pos, const T &value) {
        if (insert_wrong_place(pos)) throw invalid_iterator{};

        dequeSize++;
        block* p=pos.list_p;
        node* q=p->insert(pos.node_p,value);
        if (p->blockSize > 2 * bufferSize) p = p->divide(q);//
        return iterator(p,q,head);
    }

    iterator erase(iterator pos) {
        if (dequeSize==0) throw container_is_empty{};
        if (erase_wrong_place(pos)) throw invalid_iterator{};

        dequeSize--;
        block* p=pos.list_p;
        node* q=p->remove(p,pos.node_p);//remove 需要改p
        if (p->blockSize < bufferSize / 2) p = p->merge();
        return iterator(p,q,head);
    }

    void push_back(const T &value){insert(end(),value);}
    void push_front(const T &value){insert(begin(),value);}
    void pop_back(){erase(end()-1);}
    void pop_front(){erase(begin());}

    void trav1(){
        block* p=head->right;
        while (p!=tail){
            node* q=p->blockHead->next;
            while (q!=p->blockTail) {//
                std::cout<<*(q->data)<<' ';
                q=q->next;
            }
            std::cout<<"#  \t\t size = "<<p->blockSize<<"\n\n";
            p=p->right;
        }
        std::cout<<"\n\n\n\n";
    }

private:
    bool insert_wrong_place(const iterator& itr){
        if ((itr.node_p->data || itr==end()) && itr.deque_p==head) return false;
        else return true;
    }
    bool erase_wrong_place(const iterator& itr){
        if (itr.node_p->data && itr.deque_p==head) return false;
        else return true;
    }
    bool insert_wrong_place(const const_iterator& itr){
        if ((itr.node_p->data || itr==end()) && itr.deque_p==head) return false;
        else return true;
    }
    bool erase_wrong_place(const const_iterator& itr){
        if (itr.node_p->data && itr.deque_p==head) return false;
        else return true;
    }
    void link(block*& p,block*& q){
        p->right=q;q->left=p;
    }
    void link(block*& p,block*& q,block*& r){
        p->right=q;q->left=p;
        q->right=r;r->left=q;
    }

    static const int bufferSize = 100;
};

}

#endif
int N=10000;
#define Int int
#include <deque>
#include <vector>

bool isEqual(std::deque<Int> &a, sjtu::deque<Int> &b) {
	static std::vector<Int> resultA, resultB;
	resultA.clear();
	resultB.clear();
	for (auto x : a) resultA.push_back(x);
	for (auto x : b) resultB.push_back(x);
	if (resultA.size() != resultB.size()) return false;
	for (int i = 0; i < (int)resultA.size(); i++) {
		if (resultA[i] != resultB[i]) return false;
	}
	return true;
}
#include <ctime>
class Timer{
private:
	long dfnStart, dfnEnd;

public:
	void init() {
		dfnEnd = dfnStart = clock();
	}
	void stop() {
		dfnEnd = clock();
	}
	double getTime() {
		return 1.0 * (dfnEnd - dfnStart) / CLOCKS_PER_SEC;
	}

};

Timer timer;

std::pair<bool, double> synthesisChecker() {
	std::deque<Int> a, tA(a), ttA(tA);
	sjtu::deque<Int> b, tB(b), ttB(tB);

	timer.init();
	for (int i = 0; i < N; i++) {
		int tmp = 0;
		a.push_back(tmp);
		b.push_back(tmp);
	}
	if (!isEqual(tA, tB)) {
		return std::make_pair(false, 0);
	}
	tA = ttA; tB = ttB;
	if (!isEqual(tA, tB)) {
		return std::make_pair(false, 0);
	}
	tA = a = a; tB = b = b;
	if (!isEqual(tA, tB)) {
		return std::make_pair(false, 0);
	}
	a.clear();
	b.clear();
	if (!isEqual(tA, tB)) {
		return std::make_pair(false, 0);
	}
	tA = a = tA = tA;
	tB = b = tB = tB;
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	}




	const std::deque<Int> cA = a;
	const sjtu::deque<Int> cB = b;

	std::deque<Int>::iterator itA;
	sjtu::deque<Int>::iterator itB;
	itA = a.end();
	itB = b.end();
	for (int i = 0, delta; i < N; i++) {
		int tmp = rand();
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			return std::make_pair(false, 1);
		}
		if (rand() % 2) {
			if (itA != a.begin()) {
				int offset = rand() % (itA - a.begin());
				itA -= offset;
				itB -= offset;
			}
		} else {
			if (itA != a.end()) {
				int offset = rand() % (a.end() - itA);
				itA += offset;
				itB += offset;
			}
		}
		delta = itA - a.begin();

		sjtu::deque<Int>::iterator TMP1 = b.begin() + delta;

		if (b.begin() + delta != itB) {
            printf("%d %d %d ",i,*TMP1,*itB);
            printf("fuck22222222\n");
		}


		if (b.begin() + delta != itB) {
			//return std::make_pair(false, 2);
		}
		itA = a.insert(itA, tmp);
		itB = b.insert(itB, tmp);
		delta = itA - a.begin();

		sjtu::deque<Int>::iterator TMP2 = b.begin() + delta;

		if (b.begin() + delta != itB) {
            printf("%d %d %d ",i,*TMP2,*itB);
            printf("fuck33333333\n");
		}

		if (b.begin() + delta != itB) {
            printf("%d %d %d\n",i,*(b.begin() + delta),*itB);
//			return std::make_pair(false, 3);
		}
		if (*itA != *itB) {
			return std::make_pair(false, 4);
		}
	}




	tA = a = a = a;
	tB = b = b = b;
	a.clear();
	b.clear();
	ttA = a = a = a;
	ttB = b = b = b;
	std::deque<Int> tttA(tA);
	sjtu::deque<Int> tttB(tB);
	if (!isEqual(a, b)) {
		return std::make_pair(false, 5);
	}
	if (!isEqual(tA, tB)) {
		return std::make_pair(false, 6);
	}
	if (!isEqual(ttA, ttB)) {
		return std::make_pair(false, 7);
	}
	if (!isEqual(tttA, tttB)) {
		return std::make_pair(false, 8);
	}

	for (int i = 0; i < N; i++) {
		int tmp = rand();
		a.push_back(tmp);
		b.push_back(tmp);
	}
	itA = a.end();
	itB = b.end();
	for (int i = 0, delta; i < N; i++) {
		int tmp = rand();
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			return std::make_pair(false, 0);
		}
		if (rand() % 2) {
			if (itA != a.begin()) {
				int offset = rand() % (itA - a.begin());
				itA -= offset;
				itB -= offset;
			}
		} else {
			if (itA != a.end()) {
				int offset = rand() % (a.end() - itA);
				itA += offset;
				itB += offset;
			}
		}
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			return std::make_pair(false, 0);
		}
		if (itA == a.end()) {
			itA--;
			itB--;
		}
		itA = a.erase(itA);
		itB = b.erase(itB);
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
			return std::make_pair(false, 0);
		}
	}
	if (!isEqual(a, b)) {
		return std::make_pair(false, 0);
	}
	if (!isEqual(tA, tB)) {
		return std::make_pair(false, 0);
	}
	if (!isEqual(ttA, ttB)) {
		return std::make_pair(false, 0);
	}

	auto citA = cA.cbegin();
	auto citB = cB.cbegin();
	for (; citA != cA.end(); citA++, citB) {
		if (*citA != *citB) {
			return std::make_pair(false, 0);
		}
	}

	ttA.clear();
	ttB.clear();
	a.clear();
	b.clear();
	ttA.clear();
	ttB.clear();

	timer.stop();
	return std::make_pair(true, timer.getTime());
}

int main(){
   // std::cout<<synthesisChecker().first << ' '<<synthesisChecker().second;


    std::deque<Int> a, tA(a), ttA(tA);
	sjtu::deque<Int> b, tB(b), ttB(tB);

	for (int i = 0; i < N; i++) {
		a.push_back(i);
		b.push_back(i);
	}

	const std::deque<Int> cA = a;
	const sjtu::deque<Int> cB = b;

    std::deque<Int>::iterator itA;
	sjtu::deque<Int>::iterator itB;
	itA = a.end();
	itB = b.end();
	for (int i = 0, delta; i < 2000; i++) {
        if (i==1796){
            printf("1796");
            1796;
        }

		int tmp = rand();
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
            printf(" ## 1 ## \t %d %d %d\n",i,*(b.begin() + delta),*itB);
			//return std::make_pair(false, 1);
		}
		if (rand() % 2) {
			if (itA != a.begin()) {
				int offset = rand() % (itA - a.begin());
				itA -= offset;
				itB -= offset;
			}
		} else {
			if (itA != a.end()) {
				int offset = rand() % (a.end() - itA);
				itA += offset;
				itB += offset;
			}
		}
		delta = itA - a.begin();
		if (b.begin() + delta != itB) {
            printf(" ## 2 ## \t %d %d %d\n",i,*(b.begin() + delta),*itB);
			//return std::make_pair(false, 2);
		}
//		itA = a.insert(itA, -1);
//		itB = b.insert(itB, -1);
		delta = itA - a.begin();

		sjtu::deque<Int>::iterator TMP2 = b.begin() + delta;

		if (b.begin() + delta != itB) {
            printf(" ## 3 ## \t %d %d %d\n",i,*(b.begin() + delta),*itB);
			//return std::make_pair(false, 3);
		}
		if (*itA != *itB) {
			printf(" ## 4 ## \t %d %d \n",i,*itA,*itB);
		}
	}

    return 0;
}

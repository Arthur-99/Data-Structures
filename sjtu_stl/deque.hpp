#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>

#include <cmath>
#include <iostream>

namespace sjtu {

template<class T>
class deque
{
    struct node;
    struct block;

    int dequeSize;
    static const int bufferSize = 50;

    block* head;
    block* tmp;
    block* tail;

  public:
    class iterator;
    class const_iterator;

    deque();
    deque(const deque& other);
    ~deque();
    deque& operator=(const deque& other);

    T& at(int pos);
    const T& at(int pos) const;
    T& operator[](int pos);
    const T& operator[](int pos) const;

    const T& front() const;
    const T& back() const;

    iterator begin();
    const_iterator cbegin() const;
    iterator end();
    const_iterator cend() const;

    bool empty() const { return dequeSize == 0; }
    int size() const { return dequeSize; }
    void clear();

    iterator insert(iterator pos, const T& value);
    iterator erase(iterator pos);

    void push_back(const T& value) { insert(end(), value); }
    void push_front(const T& value) { insert(begin(), value); }
    void pop_back() { erase(end() - 1); }
    void pop_front() { erase(begin()); }

    void trav1();

  private:
    bool insert_wrong_place(const iterator& itr);
    bool erase_wrong_place(const iterator& itr);
    bool insert_wrong_place(const const_iterator& itr);
    bool erase_wrong_place(const const_iterator& itr);

    void link(block*& p, block*& q);
    void link(block*& p, block*& q, block*& r);
};
}

/*
    implementation of deque's functions
 */
#pragma region
namespace sjtu {
template<class T>
deque<T>::deque()
{
    dequeSize = 0;

    head = new block;
    tmp = new block;
    tail = new block;

    link(head, tmp, tail);
}

template<class T>
deque<T>::deque(const deque& other)
{
    dequeSize = other.dequeSize;

    head = new block;
    tail = new block;

    link(head, tail);

    block* p = other.head->right;
    while (p != other.tail) {
        block* q = new block(p);
        link(tail->left, q, tail);
        p = p->right;
    }
}

template<class T>
deque<T>::~deque()
{
    clear();
    delete tmp; // clear
    delete head;
    delete tail;
}

template<class T>
deque<T>&
deque<T>::operator=(const deque& other)
{
    if (this == &other)
        return *this;

    clear();
    delete tmp; // clear
    link(head, tail);

    dequeSize = other.dequeSize;

    block* p = other.head->right;
    while (p != other.tail) {
        block* q = new block(p);
        link(tail->left, q, tail);
        p = p->right;
    }
    return *this;
}

template<class T>
T&
deque<T>::at(int pos)
{
    if (pos >= dequeSize || pos < 0)
        throw index_out_of_bound{};

    block* p = head->right;
    while (p != tail && pos >= p->blockSize) {
        pos -= p->blockSize;
        p = p->right;
    }

    return *(p->move(pos))->data;
}

template<class T>
const T&
deque<T>::at(int pos) const
{
    if (pos >= dequeSize || pos < 0)
        throw index_out_of_bound{};

    block* p = head->right;
    while (p != tail && pos >= p->blockSize) {
        pos -= p->blockSize;
        p = p->right;
    }

    return *(p->move(pos))->data;
}

template<class T>
T& deque<T>::operator[](int pos)
{
    if (pos >= dequeSize || pos < 0)
        throw index_out_of_bound{};

    block* p = head->right;
    while (p != tail && pos >= p->blockSize) {
        pos -= p->blockSize;
        p = p->right;
    }

    return *(p->move(pos))->data;
}

template<class T>
const T& deque<T>::operator[](int pos) const
{
    if (pos >= dequeSize || pos < 0)
        throw index_out_of_bound{};

    block* p = head->right;
    while (p != tail && pos >= p->blockSize) {
        pos -= p->blockSize;
        p = p->right;
    }

    return *(p->move(pos))->data;
}

template<class T>
const T&
deque<T>::front() const
{
    if (dequeSize == 0)
        throw container_is_empty{};
    return *head->right->blockHead->next->data;
}

template<class T>
const T&
deque<T>::back() const
{
    if (dequeSize == 0)
        throw container_is_empty{};
    return *tail->left->blockTail->prev->data;
}

template<class T>
typename deque<T>::iterator
deque<T>::begin()
{
    return iterator(head->right, head->right->blockHead->next, head);
}
template<class T>
typename deque<T>::const_iterator
deque<T>::cbegin() const
{
    return const_iterator(head->right, head->right->blockHead->next, head);
}
template<class T>
typename deque<T>::iterator
deque<T>::end()
{
    return iterator(tail->left, tail->left->blockTail, head);
}
template<class T>
typename deque<T>::const_iterator
deque<T>::cend() const
{
    return const_iterator(tail->left, tail->left->blockTail, head);
}

template<class T>
void
deque<T>::clear()
{
    block* p = head->right;
    while (p != tail) {
        block* q = p->right;
        delete p;
        p = q;
    }
    dequeSize = 0;

    tmp = new block;
    link(head, tmp, tail);
}
template<class T>
typename deque<T>::iterator
deque<T>::insert(iterator pos, const T& value)
{
    if (insert_wrong_place(pos))
        throw invalid_iterator{};

    dequeSize++;
    block* p = pos.list_p;
    node* q = p->insert(pos.node_p, value);
    if (p->blockSize > 2 * bufferSize)
        p = p->divide(q); //
    return iterator(p, q, head);
}
template<class T>
typename deque<T>::iterator
deque<T>::erase(iterator pos)
{
    if (dequeSize == 0)
        throw container_is_empty{};
    if (erase_wrong_place(pos))
        throw invalid_iterator{};

    dequeSize--;
    block* p = pos.list_p;
    node* q = p->remove(p, pos.node_p); // remove 需要改p
    if (p->blockSize < bufferSize / 2)
        p = p->merge();
    return iterator(p, q, head);
}

template<class T>
void
deque<T>::trav1()
{
    block* p = head->right;
    while (p != tail) {
        node* q = p->blockHead->next;
        while (q != p->blockTail) { //
            std::cout << *(q->data) << ' ';
            q = q->next;
        }
        std::cout << "#  \t\t size = " << p->blockSize << "\n\n";
        p = p->right;
    }
    std::cout << "\n\n\n\n";
}

template<class T>
bool
deque<T>::insert_wrong_place(const iterator& itr)
{
    if ((itr.node_p->data || itr == end()) && itr.deque_p == head)
        return false;
    else
        return true;
}
template<class T>
bool
deque<T>::erase_wrong_place(const iterator& itr)
{
    if (itr.node_p->data && itr.deque_p == head)
        return false;
    else
        return true;
}
template<class T>
bool
deque<T>::insert_wrong_place(const const_iterator& itr)
{
    if ((itr.node_p->data || itr == end()) && itr.deque_p == head)
        return false;
    else
        return true;
}
template<class T>
bool
deque<T>::erase_wrong_place(const const_iterator& itr)
{
    if (itr.node_p->data && itr.deque_p == head)
        return false;
    else
        return true;
}

template<class T>
void
deque<T>::link(block*& p, block*& q)
{
    p->right = q;
    q->left = p;
}
template<class T>
void
deque<T>::link(block*& p, block*& q, block*& r)
{
    p->right = q;
    q->left = p;
    q->right = r;
    r->left = q;
}
}
#pragma endregion

/*
    node
 */
#pragma region
namespace sjtu {
template<class T>
struct deque<T>::node
{
    T* data; //
    node* prev;
    node* next;

    node()
    {
        data = nullptr;
        prev = next = nullptr;
    }
    node(const T& x, node* p = nullptr, node* n = nullptr)
    {
        data = new T(x);
        prev = p;
        next = n;
    }
    ~node()
    {
        if (data)
            delete data;
    }
};
}
#pragma endregion

/*
    block
 */
#pragma region
namespace sjtu {
template<class T>
struct deque<T>::block
{
    block* left;
    block* right;

    node* blockHead;
    node* blockTail;
    int blockSize;

    node* move(int i) const
    {
        node* p = blockHead->next;
        if (i >= 0)
            for (int j = 0; j < i && p; j++)
                p = p->next;
        else if (i == -1) {
            return blockHead;
        }
        return p;
    }

    block()
    {
        left = right = nullptr;

        blockHead = new node;
        blockTail = new node;
        link(blockHead, blockTail);

        blockSize = 0;
    }
    block(const block& l)
    {
        left = right = nullptr;

        blockHead = new node;
        blockTail = new node;
        link(blockHead, blockTail);

        blockSize = 0;

        node* p = l.blockHead->next;
        while (p != l.blockTail) {
            push_back(*p->data); // blockSize++ simultaneously
            p = p->next;
        }
    }
    block(const block* l)
    {
        left = right = nullptr;

        blockHead = new node;
        blockTail = new node;
        link(blockHead, blockTail);

        blockSize = 0;

        node* p = l->blockHead->next;
        while (p != l->blockTail) {
            push_back(*p->data); // blockSize++ simultaneously
            p = p->next;
        }
    }

    // Given l's head and tail, defines a block, this function is designed
    // for function divide()
    block(node* h, node* t)
    {
        blockHead = h;
        blockTail = t;
    }

    ~block()
    {
        clear();
        delete blockHead;
        delete blockTail;
    }

    bool empty() { return blockSize == 0; }

    void link(node*& p, node*& q)
    {
        p->next = q;
        q->prev = p;
    }
    void link(node*& p, node*& q, node*& r)
    {
        p->next = q;
        q->prev = p;
        q->next = r;
        r->prev = q;
    }
    void clear()
    {
        node* p = blockHead->next;
        node* q;
        while (p != blockTail) {
            q = p->next;
            delete p;
            p = q;
        }

        link(blockHead, blockTail);
        blockSize = 0;
    }

    /*
        inserts value before q
        returns a pointer of the inserted node(value)
    */
    node* insert(node* q, const T& value)
    {
        node* p = new node(value);
        link(q->prev, p, q);
        blockSize++;
        return p;
    }

    /*
        returns a pointer of the node saving the following element, if q
       points to the last element of deque, the node pointer of end() will
       be returned PS: iterator is constructed with 2 pointers, one points
       to the block in which it is located and the other points to the very
       node containing the 'T* data'
    */
    node* remove(block*& p, node* q)
    {
        link(q->prev, q->next);
        node* ret = q->next; // next不一定什么东西

        if (ret == blockTail) {
            if (right->blockSize) {
                ret = right->blockHead->next;
                p = p->right;
            }
        }

        blockSize--;
        delete q;
        return ret;
    }

    void push_back(const T& x) { insert(blockTail, x); }
    void push_front(const T& x) { insert(blockHead->next, x); }

    /*
        returns the index in the block,
        if it doesn't exist in the block at all, returns -1
    */
    int id(const T& x)
    {
        node* p = blockHead->next;
        for (int i = 0; i < blockSize + 1; i++) {
            if (*(p->data) == x)
                return i; // bug *(p->data)
            p = p->next;
        }
        return -1;
    }
    int id(node* x)
    {
        node* p = blockHead->next;
        for (int i = 0; i < blockSize + 1; i++) {
            if (p == x)
                return i;
            p = p->next;
        }
        return -1;
    }

    /*
        merges this block with the smaller one of the left or right block,
        redefines this block,
        returns a pointer to the new block
    */
    block* merge()
    {
        // TODO : merges with the smaller one
        if (left->blockSize) {
            block* this_l = left->left;
            block* this_r = right;

            block* P = left;

            // add P to this then delete P
            node* w = P->blockHead->next;
            node* ww = P->blockTail->prev;

            link(ww, blockHead->next);
            link(blockHead, w);

            blockSize += P->blockSize;

            link(P->blockHead, P->blockTail);
            delete P;

            this_l->right = this;
            this_r->left = this;
            left = this_l;
            right = this_r;

        } else if (right->blockSize) {
            block* this_l = left;
            block* this_r = right->right;

            block* Q = right;

            // add Q to this then delete Q
            node* w = Q->blockHead->next;
            node* ww = Q->blockTail->prev;

            link(blockTail->prev, w);
            link(ww, blockTail);

            blockSize += Q->blockSize;

            link(Q->blockHead, Q->blockTail);
            delete Q;

            this_l->right = this;
            this_r->left = this;
            left = this_l;
            right = this_r;
        }

        return this;
    }

    /*
        divides this block into 2 parts 'equally',
        redefines this block,
        returns a pointer to the block containing node* x
    */
    block* divide(node* x)
    {
        block* this_l = left;
        block* this_r = right;

        // divides this block into 2 parts
        node* p = move(blockSize / 2);
        node* q = p->next;

        node* p_n = new node;
        node* q_p = new node;
        link(p, p_n);
        link(q_p, q);

        block* Q = new block(q->prev, blockTail);
        // block* P=new block(blockHead,p->next);
        blockTail = p->next;

        // sets the 2 parts
        Q->blockSize = blockSize - blockSize / 2 - 1;
        blockSize = blockSize / 2 + 1;

        right = Q;

        Q->left = this;
        Q->right = this_r;

        this_r->left = Q;

        // returns the pointer to block containing x
        if (Q->id(x) == -1)
            return this;
        else
            return Q;
    }
};
}
#pragma endregion

/*
    iterator & const_iterator
 */
#pragma region
namespace sjtu {
template<class T>
class deque<T>::iterator
{
    friend class deque;
    friend class const_iterator;

  private:
    block* deque_p;
    block* list_p;
    node* node_p;

  public:
    iterator()
    {
        list_p = nullptr;
        node_p = nullptr;
        deque_p = nullptr;
    }
    iterator(block* l, node* n, block* d)
    {
        list_p = l;
        node_p = n;
        deque_p = d;
    }
    iterator(const const_iterator& other)
    {
        list_p = other.list_p;
        node_p = other.node_p;
        deque_p = other.deque_p;
    }
    iterator(const iterator& other)
    {
        list_p = other.list_p;
        node_p = other.node_p;
        deque_p = other.deque_p;
    }

    iterator operator+(int n) const
    {
        // n>0?
        if (n < 0) {
            return operator-(-n);
        }

        iterator tmp = *this;

        n += list_p->id(node_p);

        while (n >= tmp.list_p->blockSize && tmp.list_p->blockSize) {
            if (tmp.list_p->right->blockSize == 0)
                break; /// end()
            n -= tmp.list_p->blockSize;
            tmp.list_p = tmp.list_p->right;
        }

        return iterator(tmp.list_p, tmp.list_p->move(n), deque_p);
    }
    iterator operator-(int n) const
    {
        // bug : end() - 0 , 把它变成end() + 0
        if (n <= 0) {
            return operator+(-n);
        }

        iterator tmp = *this;

        n += list_p->blockSize - list_p->id(node_p) - 1;

        while (n >= tmp.list_p->blockSize && tmp.list_p->blockSize) {
            if (tmp.list_p->left->blockSize == 0)
                break; /// begin()
            n -= tmp.list_p->blockSize;
            tmp.list_p = tmp.list_p->left;
        }

        return iterator(
          tmp.list_p, tmp.list_p->move(tmp.list_p->blockSize - n - 1), deque_p);
    }

    int operator-(const iterator& rhs) const
    {
        // find the bigger one
        bool flag = false;
        iterator big = *this, small = rhs;
        iterator tmp1 = *this, tmp2 = rhs;

        int num1 = 0;
        while (tmp1.list_p->blockSize /*!=0*/) { // 0 : head
            tmp1.list_p = tmp1.list_p->left;
            num1++;
        }
        int num2 = 0;
        while (tmp2.list_p->blockSize /*!=0*/) { // 0 : head
            tmp2.list_p = tmp2.list_p->left;
            num2++;
        }
        if (tmp1.list_p != tmp2.list_p)
            throw invalid_iterator{};
        else if (num1 == num2) {
            return big.list_p->id(big.node_p) - small.list_p->id(small.node_p);
        } else if (num1 < num2) {
            std::swap(big, small);
            flag = true;
        }

        // get the result
        int res = 0;

        res +=
          (big.list_p->id(big.node_p)) - (small.list_p->id(small.node_p)); //

        big.list_p = big.list_p->left;
        small.list_p = small.list_p->left;

        while (big.list_p != small.list_p) {
            res += big.list_p->blockSize;
            big.list_p = big.list_p->left;
        }

        if (flag)
            return -res;
        else
            return res;
    }

    iterator operator+=(int n)
    {
        if (n < 0)
            return *this = *this - (-n);
        return *this = *this + n;
    }
    iterator operator-=(int n)
    {
        if (n <= 0)
            return *this = *this + (-n);
        return *this = *this - n;
    }

    iterator operator++(int)
    {
        // end throw
        if (node_p->data == nullptr && list_p->right->blockSize == 0)
            throw invalid_iterator{};

        iterator tmp = *this;
        if (node_p == list_p->blockTail->prev &&
            list_p->right->blockSize == 0) {
            // last elem
            node_p = node_p->next;
        } else if (node_p == list_p->blockTail->prev) {
            list_p = list_p->right;
            node_p = list_p->blockHead->next;
        } else {
            try {
                node_p = node_p->next;
            } catch (...) {
                throw invalid_iterator{};
            }
        }
        return tmp;
    }
    iterator& operator++()
    {
        // end throw
        if (node_p->data == nullptr && list_p->right->blockSize == 0)
            throw invalid_iterator{};

        if (node_p == list_p->blockTail->prev &&
            list_p->right->blockSize == 0) {
            // last elem
            node_p = node_p->next;
        } else if (node_p == list_p->blockTail->prev) {
            list_p = list_p->right;
            node_p = list_p->blockHead->next;
        } else {
            try {
                node_p = node_p->next;
            } catch (...) {
                throw invalid_iterator{};
            }
        }
        return *this;
    }
    iterator operator--(int)
    {
        // begin throw
        if (node_p->prev->data == nullptr && list_p->left->blockSize == 0)
            throw invalid_iterator{};

        iterator tmp = *this;
        if (node_p == list_p->blockHead->next) {
            list_p = list_p->left;
            node_p = list_p->blockTail->prev;
        } else
            node_p = node_p->prev;
        return tmp;
    }
    iterator& operator--()
    {
        // begin throw
        if (node_p->prev->data == nullptr && list_p->left->blockSize == 0)
            throw invalid_iterator{};

        if (node_p == list_p->blockHead->next) {
            list_p = list_p->left;
            node_p = list_p->blockTail->prev;
        } else
            node_p = node_p->prev;
        return *this;
    }

    T& operator*() const
    {
        if (node_p->data) {
            return *node_p->data;
        } else {
            throw invalid_iterator{};
        }
    }
    T* operator->() const noexcept { return node_p->data; }

    bool operator==(const iterator& rhs) const
    {
        return node_p == rhs.node_p && deque_p == rhs.deque_p;
    }
    bool operator==(const const_iterator& rhs) const
    {
        return node_p == rhs.node_p && deque_p == rhs.deque_p;
    }
    bool operator!=(const iterator& rhs) const { return !(*this == rhs); }
    bool operator!=(const const_iterator& rhs) const { return !(*this == rhs); }
};

template<class T>
class deque<T>::const_iterator
{
    friend class iterator;

  private:
    block* deque_p;
    block* list_p;
    node* node_p;

  public:
    const_iterator()
    {
        list_p = nullptr;
        node_p = nullptr;
        deque_p = nullptr;
    }
    const_iterator(block* l, node* n, block* d)
      : list_p(l)
      , node_p(n)
      , deque_p(d)
    {}
    const_iterator(const const_iterator& other)
      : list_p(other.list_p)
      , node_p(other.node_p)
      , deque_p(other.deque_p)
    {}
    const_iterator(const iterator& other)
      : list_p(other.list_p)
      , node_p(other.node_p)
      , deque_p(other.deque_p)
    {}

    const_iterator operator+(int n) const
    {
        // n>0?
        if (n < 0) {
            return operator-(-n);
        }
        iterator tmp = *this;
        return const_iterator(tmp + n);
    }
    const_iterator operator-(int n) const
    {
        if (n <= 0) {
            return operator+(-n);
        }
        iterator tmp = *this;
        return const_iterator(tmp - n);
    }

    int operator-(const const_iterator& rhs) const
    {
        iterator lhs_tmp = *this, rhs_tmp = rhs;
        return lhs_tmp - rhs_tmp;
    }

    const_iterator operator+=(int n)
    {
        if (n < 0)
            return *this = *this - (-n);
        return *this = *this + n;
    }
    const_iterator operator-=(int n)
    {
        if (n <= 0)
            return *this = *this + (-n);
        return *this = *this - n;
    }

    const_iterator operator++(int)
    {
        iterator tmp = *this;
        *this = const_iterator(++tmp);
        return const_iterator(tmp);
    }
    const_iterator& operator++()
    {
        iterator tmp = *this;
        return *this = const_iterator(++tmp);
    }
    const_iterator operator--(int)
    {
        iterator tmp = *this;
        *this = const_iterator(--tmp);
        return const_iterator(tmp);
    }
    const_iterator& operator--()
    {
        iterator tmp = *this;
        return *this = const_iterator(--tmp);
    }

    T operator*() const
    {
        if (node_p->data) {
            return *node_p->data;
        } else {
            throw invalid_iterator{};
        }
    }
    T* operator->() const noexcept { return node_p->data; }

    bool operator==(const iterator& rhs) const
    {
        return node_p == rhs.node_p && deque_p == rhs.deque_p;
    }
    bool operator==(const const_iterator& rhs) const
    {
        return node_p == rhs.node_p && deque_p == rhs.deque_p;
    }
    bool operator!=(const iterator& rhs) const { return !(*this == rhs); }
    bool operator!=(const const_iterator& rhs) const { return !(*this == rhs); }
};
}
#pragma endregion
#endif
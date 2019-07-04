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
    // node
    struct node
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
        node& operator=(const node& n)
        {
            if (n.data)
                data = new T(*n.data);
            prev = n.prev;
            next = n.next;
        }
        ~node()
        {
            if (data)
                delete data;
        }
    };

    // list : l_head l_tail l_size l_prev l_next
    struct list
    {
        list* l_prev;
        list* l_next;

        node* l_head;
        node* l_tail;
        size_t l_size;

        node* move(int i) const
        {
            node* p = l_head->next;
            if (i >= 0)
                for (int j = 0; j < i; j++)
                    p = p->next;
            else if (i == -1)
                return l_head;
            return p;
        }

        list()
        {
            l_prev = l_next = nullptr;

            l_head = new node;
            l_tail = new node;
            n_link(l_head, l_tail);

            l_size = 0;
        }
        list(const list& l)
        {
            l_prev = l_next = nullptr;

            l_head = new node;
            l_tail = new node;
            n_link(l_head, l_tail);

            l_size = 0;

            node* p = l.l_head->next;
            while (p != l.l_tail) {
                push_back(*p->data); // l_size++
                p = p->next;
            }
        }
        list(const list* l)
        {
            l_prev = l_next = nullptr;

            l_head = new node;
            l_tail = new node;
            n_link(l_head, l_tail);

            l_size = 0;

            node* p = l->l_head->next;
            while (p != l->l_tail) {
                push_back(*p->data); // l_size++
                p = p->next;
            }
        }

        // for divide()
        list(node* h, node* t)
        {
            l_head = h;
            l_tail = t;
        }

        list& operator=(const list& l)
        {
            if (this == &l)
                return *this;

            clear();

            node* p = l.l_head->next;
            while (p != l.l_tail) {
                push_back(*p->data);
                p = p->next;
            }
            return *this;
        }
        ~list()
        {
            if (l_size != 0)
                clear();
            delete l_head;
            delete l_tail;
        }

        bool empty() { return l_size == 0; }

        void n_link(node*& p, node*& q)
        {
            p->next = q;
            q->prev = p;
        }
        void n_link(node*& p, node*& q, node*& r)
        {
            p->next = q;
            q->prev = p;
            q->next = r;
            r->prev = q;
        }
        void clear()
        {
            node* p = l_head->next;
            node* q;
            while (p != l_tail) {
                q = p->next;
                delete p;
                p = q;
            }

            n_link(l_head, l_tail);
            l_size = 0;
        }

        node* insert(node* q, const T& x)
        {
            node* p = new node(x); //??
            n_link(q->prev, p, q);
            l_size++;
            return p;
        }
        node* remove(node* q)
        {
            n_link(q->prev, q->next);
            node* ret = q->next; // next不一定什么东西

            if (ret == l_tail) {
                if (l_next->l_size)
                    ret = l_next->l_head->next;
            }

            l_size--;
            delete q;
            return ret;
        }

        void push_back(const T& x) { insert(l_tail, x); }

        int id(const T& x)
        {
            node* p = l_head->next;
            for (int i = 0; i < l_size + 1; i++) {
                if (p->data == x)
                    return i;
                p = p->next;
            }
            return -1;
        }
        int id(node* x)
        {
            node* p = l_head->next;
            for (int i = 0; i < l_size + 1; i++) {
                if (p == x)
                    return i;
                p = p->next;
            }
            return -1;
        }

        list* merge1()
        {
            if (l_prev->l_size) { // merge with left block
                list* this_p = l_prev->l_prev;
                list* this_n = l_next;

                list* P = l_prev;
                list* Q = this;

                n_link(P->l_tail->prev, Q->l_head->next);

                delete P->l_tail;
                delete Q->l_head;

                // this = PQ
                l_next = Q->l_next;
                l_prev = P->l_prev;
                l_size = P->l_size + Q->l_size;
                l_head = P->l_head;
                l_tail = Q->l_tail;

                this_p->l_next = this;
                this_n->l_prev = this;

            } else if (l_next->l_size) { // merge with right block
                list* this_p = l_prev;
                list* this_n = l_next->l_next;

                list* P = this;
                list* Q = l_next;

                n_link(P->l_tail->prev, Q->l_head->next);

                delete P->l_tail;
                delete Q->l_head;

                // this = PQ
                l_next = Q->l_next;
                l_prev = P->l_prev;
                l_size = P->l_size + Q->l_size;
                l_head = P->l_head;
                l_tail = Q->l_tail;

                this_p->l_next = this;
                this_n->l_prev = this;
            }
            return this;
        }
        list* divide(node* x)
        {
            //
            list* this_p = l_prev;
            list* this_n = l_next;

            node* p = move(l_size / 2);
            node* q = p->next;

            node* p_n = new node;
            node* q_p = new node;
            n_link(p, p_n);
            n_link(q_p, q);

            //            list* Q=new list(P,l_next,q->prev,l_tail);
            //            list* P=new list(l_prev,Q,l_head,p->next);
            //            this=P;

            list* Q = new list(q->prev, l_tail);
            list* P = new list(l_head, p->next);

            Q->l_size = l_size - l_size / 2 - 1;
            P->l_size = l_size / 2 + 1;

            P->l_next = Q;
            P->l_prev = l_prev;
            Q->l_prev = P;
            Q->l_next = l_next;

            // this=P
            l_next = P->l_next;
            l_prev = P->l_prev;
            l_size = P->l_size;
            l_head = P->l_head;
            l_tail = P->l_tail;

            this_p->l_next = P;
            this_n->l_prev = Q;

            // x in P or Q?
            if (P->id(x) == -1)
                return Q;
            else
                return P;
        }
    };

    // d e q u e
    size_t d_size;

    list* head;
    list* tmp;
    list* tail;

  public:
    class const_iterator;
    class iterator
    {
        friend class deque;

      private:
        list* list_p;
        node* node_p;

      public:
        iterator()
        {
            list_p = nullptr;
            node_p = nullptr;
        }
        iterator(list* l, node* n)
        {
            list_p = l;
            node_p = n;
        }
        iterator(const const_iterator& other)
        {
            list_p = other.list_p;
            node_p = other.node_p;
        }
        iterator(const iterator& other)
        {
            list_p = other.list_p;
            node_p = other.node_p;
        }

        iterator operator+(int n) const
        {
            // n>0?
            if (n < 0) {
                return operator-(-n);
            }

            iterator tmp = *this;

            n += list_p->id(node_p);

            while (n >= tmp.list_p->l_size && tmp.list_p->l_size) {
                if (tmp.list_p->l_next->l_size == 0)
                    break; /// end()
                n -= tmp.list_p->l_size;
                tmp.list_p = tmp.list_p->l_next;
            }

            return iterator(tmp.list_p, tmp.list_p->move(n));
        }
        iterator operator-(int n) const
        {
            // bug : end() - 0 , 把它变成end() + 0
            if (n <= 0) {
                return operator+(-n);
            }

            iterator tmp = *this;

            n += list_p->l_size - list_p->id(node_p) - 1;

            while (n >= tmp.list_p->l_size && tmp.list_p->l_size) {
                if (tmp.list_p->l_prev->l_size == 0)
                    break; /// begin()
                n -= tmp.list_p->l_size;
                tmp.list_p = tmp.list_p->l_prev;
            }

            return iterator(tmp.list_p,
                            tmp.list_p->move(tmp.list_p->l_size - n - 1));
        }

        int operator-(const iterator& rhs) const
        {
            // find the bigger one
            bool flag = false;
            iterator big = *this, small = rhs;
            iterator tmp1 = *this, tmp2 = rhs;

            int num1 = 0;
            while (tmp1.list_p->l_size /*!=0*/) { // 0 : head
                tmp1.list_p = tmp1.list_p->l_prev;
                num1++;
            }
            int num2 = 0;
            while (tmp2.list_p->l_size /*!=0*/) { // 0 : head
                tmp2.list_p = tmp2.list_p->l_prev;
                num2++;
            }
            if (tmp1.list_p != tmp2.list_p)
                throw invalid_iterator{};
            else if (num1 == num2) {
                return big.list_p->id(big.node_p) -
                       small.list_p->id(small.node_p);
            } else if (num1 < num2) {
                std::swap(big, small);
                flag = true;
            }

            //----------------------------------------------------------------------------------
            int res = 0;

            res += (big.list_p->id(big.node_p)) -
                   (small.list_p->id(small.node_p)); //

            big.list_p = big.list_p->l_prev;
            small.list_p = small.list_p->l_prev;

            while (big.list_p != small.list_p) {
                res += big.list_p->l_size;
                big.list_p = big.list_p->l_prev;
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
            if (node_p->data == nullptr && list_p->l_next->l_size == 0)
                throw invalid_iterator{};

            iterator tmp = *this;
            if (node_p == list_p->l_tail->prev && list_p->l_next->l_size == 0) {
                // last elem
                node_p = node_p->next;
            } else if (node_p == list_p->l_tail->prev) {
                list_p = list_p->l_next;
                node_p = list_p->l_head->next;
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
            if (node_p->data == nullptr && list_p->l_next->l_size == 0)
                throw invalid_iterator{};

            if (node_p == list_p->l_tail->prev && list_p->l_next->l_size == 0) {
                // last elem
                node_p = node_p->next;
            } else if (node_p == list_p->l_tail->prev) {
                list_p = list_p->l_next;
                node_p = list_p->l_head->next;
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
            if (node_p->prev->data == nullptr && list_p->l_prev->l_size == 0)
                throw invalid_iterator{};

            iterator tmp = *this;
            if (node_p == list_p->l_head->next) {
                list_p = list_p->l_prev;
                node_p = list_p->l_tail->prev;
            } else
                node_p = node_p->prev;
            return tmp;
        }
        iterator& operator--()
        {
            // begin throw
            if (node_p->prev->data == nullptr && list_p->l_prev->l_size == 0)
                throw invalid_iterator{};

            if (node_p == list_p->l_head->next) {
                list_p = list_p->l_prev;
                node_p = list_p->l_tail->prev;
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
            return (list_p == rhs.list_p && node_p == rhs.node_p) ||
                   (*this - rhs == 0);
        }
        bool operator==(const const_iterator& rhs) const
        {
            return (list_p == rhs.list_p && node_p == rhs.node_p) ||
                   (*this - rhs == 0);
        }
        bool operator!=(const iterator& rhs) const { return !(*this == rhs); }
        bool operator!=(const const_iterator& rhs) const
        {
            return !(*this == rhs);
        }
    };
    class const_iterator
    {
      private:
        list* list_p;
        node* node_p;

      public:
        const_iterator(list* l, node* n)
        {
            list_p = l;
            node_p = n;
        }
        const_iterator(const const_iterator& other) { list_p = other.list_p; }
        const_iterator(const iterator& other) { list_p = other.list_p; }

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
            return (list_p == rhs.list_p && node_p == rhs.node_p) ||
                   (*this - rhs == 0);
        }
        bool operator==(const const_iterator& rhs) const
        {
            return (list_p == rhs.list_p && node_p == rhs.node_p) ||
                   (*this - rhs == 0);
        }
        bool operator!=(const iterator& rhs) const { return !(*this == rhs); }
        bool operator!=(const const_iterator& rhs) const
        {
            return !(*this == rhs);
        }
    };

    deque()
    {
        d_size = 0;

        head = new list;
        tmp = new list;
        tail = new list;

        link(head, tmp, tail);
    }
    deque(const deque& other)
    {
        d_size = other.d_size;

        head = new list;
        tail = new list;

        link(head, tail);

        list* p = other.head->l_next;
        while (p != other.tail) {
            list* q = new list(p);
            link(tail->l_prev, q, tail);
            p = p->l_next;
        }
    }
    ~deque()
    {
        clear();
        delete tmp; // clear
        delete head;
        delete tail;
    }
    deque& operator=(const deque& other)
    {
        if (this == &other)
            return *this;

        clear();
        delete tmp; // clear
        link(head, tail);

        d_size = other.d_size;

        list* p = other.head->l_next;
        while (p != other.tail) {
            list* q = new list(p);
            link(tail->l_prev, q, tail);
            p = p->l_next;
        }
        return *this;
    }

    T& at(size_t pos)
    {
        if (pos >= d_size || pos < 0)
            throw index_out_of_bound{};

        list* p = head->l_next;
        while (p != tail && pos >= p->l_size) {
            pos -= p->l_size;
            p = p->l_next;
        }

        return *(p->move(pos))->data;
    }
    const T& at(size_t pos) const
    {
        if (pos >= d_size || pos < 0)
            throw index_out_of_bound{};

        list* p = head->l_next;
        while (p != tail && pos >= p->l_size) {
            pos -= p->l_size;
            p = p->l_next;
        }

        return *(p->move(pos))->data;
    }
    T& operator[](size_t pos)
    {
        if (pos >= d_size || pos < 0)
            throw index_out_of_bound{};

        list* p = head->l_next;
        while (p != tail && pos >= p->l_size) {
            pos -= p->l_size;
            p = p->l_next;
        }

        return *(p->move(pos))->data;
    }
    const T& operator[](size_t pos) const
    {
        if (pos >= d_size || pos < 0)
            throw index_out_of_bound{};

        list* p = head->l_next;
        while (p != tail && pos >= p->l_size) {
            pos -= p->l_size;
            p = p->l_next;
        }

        return *(p->move(pos))->data;
    }

    const T& front() const
    {
        if (d_size == 0)
            throw container_is_empty{};
        return *head->l_next->l_head->next->data;
    }
    const T& back() const
    {
        if (d_size == 0)
            throw container_is_empty{};
        return *tail->l_prev->l_tail->prev->data;
    }

    iterator begin()
    {
        return iterator(head->l_next, head->l_next->l_head->next);
    }
    const_iterator cbegin() const
    {
        return const_iterator(head->l_next, head->l_next->l_head->next);
    }
    iterator end() { return iterator(tail->l_prev, tail->l_prev->l_tail); }
    const_iterator cend() const
    {
        return const_iterator(tail->l_prev, tail->l_prev->l_tail);
    }

    bool empty() const { return d_size == 0; }
    size_t size() const { return d_size; }
    void clear()
    {
        list* p = head->l_next;
        while (p != tail) {
            list* q = p->l_next;
            delete p;
            p = q;
        }
        d_size = 0;

        tmp = new list;
        link(head, tmp, tail);

        // link(head,tail);
    }

    iterator insert(iterator pos, const T& value)
    {
        if (insert_wrong_place(pos))
            throw invalid_iterator{};

        d_size++;
        list* p = pos.list_p;
        node* q = p->insert(pos.node_p, value);
        if (p->l_size > 2 * sqrt(d_size))
            p = p->divide(q); //
        return iterator(p, q);
    }

    iterator erase(iterator pos)
    {
        if (d_size == 0)
            throw container_is_empty{};
        if (erase_wrong_place(pos))
            throw invalid_iterator{};

        d_size--;
        list* p = pos.list_p;
        node* q = p->remove(pos.node_p);
        if (p->l_size < sqrt(d_size) / 2)
            p = p->merge1(); //
        return iterator(p, q);
    }

    void push_back(const T& value) { insert(end(), value); }
    void push_front(const T& value) { insert(begin(), value); }
    void pop_back() { erase(end() - 1); }
    void pop_front() { erase(begin()); }

    void trav1()
    {
        list* p = head->l_next;
        while (p != tail) {
            node* q = p->l_head->next;
            while (q != p->l_tail) { //
                std::cout << *(q->data) << ' ';
                q = q->next;
            }
            std::cout << "#  \t\t size = " << p->l_size << std::endl;
            p = p->l_next;
        }
        std::cout << "\n\n" << std::endl;
    }
    void trav()
    {
        list* p = tail->l_prev;
        while (p != head) {
            node* q = p->l_tail->prev;
            while (q != p->l_head) { //
                std::cout << (q->data) << ' ';
                q = q->prev;
            }
            p = p->l_prev;
            std::cout << "# \n";
        }
        std::cout << "\n\n" << std::endl;
    }

  private:
    bool insert_wrong_place(const iterator& itr)
    {
        list* p = head->l_next;
        while (p != tail) {
            if (itr.list_p == p || itr.node_p == p->l_tail)
                return false;
            p = p->l_next;
        }
        return true;
    }
    bool erase_wrong_place(const iterator& itr)
    {
        list* p = head->l_next;
        while (p != tail) {
            if (itr.list_p == p && itr.node_p->data)
                return false;
            p = p->l_next;
        }
        return true;
    }
    void link(list*& p, list*& q)
    {
        p->l_next = q;
        q->l_prev = p;
    }
    void link(list*& p, list*& q, list*& r)
    {
        p->l_next = q;
        q->l_prev = p;
        q->l_next = r;
        r->l_prev = q;
    }
};
}

#endif
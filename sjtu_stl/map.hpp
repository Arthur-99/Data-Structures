#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include "exceptions.hpp"
#include "utility.hpp"
#include <cstddef>
#include <functional>

namespace sjtu {

template<class Key, class T, class Compare = std::less<Key>>
class map
{
  public:
    typedef pair<const Key, T> value_type;

  private:
  public:
    struct node
    {
        value_type* value;
        size_t height;

        node* parent;
        node* left;
        node* right;

        node()
        {
            value = nullptr;
            height = 0;
            parent = left = right = nullptr;
        }

        node(const value_type& v,
             int h = 0,
             node* p = nullptr,
             node* l = nullptr,
             node* r = nullptr)
          : height(h)
          , parent(p)
          , left(l)
          , right(r)
        {
            value = new value_type(v);
        }

        ~node()
        {
            if (value)
                delete value;
        }
    };

    typedef node* Nptr;

    node* root;

    node* zero;

    int Size;

  public:
    class const_iterator;
    class iterator
    {
        friend class const_iterator;
        friend class map;

      private:
      public:
        node* n;
        map* m;

      public:
        iterator() = default;
        iterator(node* nn, map* mm)
          : n(nn)
          , m(mm)
        {}
        iterator(const iterator& other)
          : n(other.n)
          , m(other.m)
        {}
        iterator(const const_iterator& other)
          : n(other.n)
          , m(other.m)
        {}

        iterator operator++(int)
        {
            if (m->empty())
                throw invalid_iterator{};

            iterator ret = *this;
            increment(n);
            return ret;
        }
        iterator& operator++()
        {
            if (m->empty())
                throw invalid_iterator{};

            increment(n);
            return *this;
        }
        iterator operator--(int)
        {
            if (m->empty())
                throw invalid_iterator{};

            iterator ret = *this;
            if (n == nullptr)
                n = m->getMax(); // if end
            else
                decrement(n);
            return ret;
        }
        iterator& operator--()
        {
            if (m->empty())
                throw invalid_iterator{};

            if (n == nullptr)
                n = m->getMax(); // if end
            else
                decrement(n);
            return *this;
        }

        value_type& operator*() const { return *(n->value); }
        value_type* operator->() const noexcept { return n->value; }

        bool operator==(const iterator& rhs) const
        {
            return n == rhs.n && m == rhs.m;
        }
        bool operator==(const const_iterator& rhs) const
        {
            return n == rhs.n && m == rhs.m;
        }
        bool operator!=(const iterator& rhs) const
        {
            return n != rhs.n || m != rhs.m;
        }
        bool operator!=(const const_iterator& rhs) const
        {
            return n != rhs.n || m != rhs.m;
        }

      private:
        // end increment && begin decrement
        void increment(node*& n)
        {
            if (n == nullptr)
                throw invalid_iterator{}; // end

            if (n->right) {
                n = n->right;
                while (n->left)
                    n = n->left;
            } else {
                if (n == m->root) {
                    n = nullptr;
                    return;
                }
                while (n->parent->right == n) {
                    n = n->parent;
                    if (n == m->root) {
                        n = nullptr;
                        return;
                    }
                }
                n = n->parent;
            }
        }
        void decrement(node*& n)
        {
            if (n == nullptr)
                return;

            if (n->left) {
                n = n->left;
                while (n->right)
                    n = n->right;
            } else {
                if (n == m->root) {
                    throw invalid_iterator{};
                }
                while (n->parent->left == n) {
                    n = n->parent;
                    if (n == m->root) {
                        throw invalid_iterator{};
                    }
                }
                n = n->parent;
            }
        }
    };
    class const_iterator
    {
        friend class iterator;
        friend class map;

      private:
        node* n;
        map* m;

      public:
        const_iterator() = default;
        const_iterator(node* nn, map* mm)
          : n(nn)
        {
            m = mm;
        }
        const_iterator(const iterator& other)
          : n(other.n)
          , m(other.m)
        {}
        const_iterator(const const_iterator& other)
          : n(other.n)
          , m(other.m)
        {}

        const_iterator operator++(int)
        {
            if (m->empty())
                throw invalid_iterator{};

            const_iterator ret = *this;
            increment(n);
            return ret;
        }
        const_iterator& operator++()
        {
            if (m->empty())
                throw invalid_iterator{};

            increment(n);
            return *this;
        }
        const_iterator operator--(int)
        {
            if (m->empty())
                throw invalid_iterator{};

            const_iterator ret = *this;
            if (n == nullptr)
                n = m->getMax(); // if end
            else
                decrement(n);
            return ret;
        }
        const_iterator& operator--()
        {
            if (m->empty())
                throw invalid_iterator{};

            if (n == nullptr)
                n = m->getMax(); // if end
            else
                decrement(n);
            return *this;
        }

        const value_type& operator*() const { return *(n->value); }
        value_type* operator->() const noexcept { return n->value; }

        bool operator==(const iterator& rhs) const
        {
            return n == rhs.n && m == rhs.m;
        }
        bool operator==(const const_iterator& rhs) const
        {
            return n == rhs.n && m == rhs.m;
        }
        bool operator!=(const iterator& rhs) const
        {
            return n != rhs.n || m != rhs.m;
        }
        bool operator!=(const const_iterator& rhs) const
        {
            return n != rhs.n || m != rhs.m;
        }

      private:
        void increment(node*& n)
        {
            if (n == nullptr)
                return;

            if (n->right) {
                n = n->right;
                while (n->left)
                    n = n->left;
            } else {
                if (n == m->root) {
                    n = nullptr;
                    return;
                }
                while (n->parent->right == n) {
                    n = n->parent;
                    if (n == m->root) {
                        n = nullptr;
                        return;
                    }
                }
                n = n->parent;
            }
        }
        void decrement(node*& n)
        {
            if (n == nullptr)
                return;

            if (n->left) {
                n = n->left;
                while (n->right)
                    n = n->right;
            } else {
                if (n == m->root) {
                    throw invalid_iterator{};
                }
                while (n->parent->left == n) {
                    n = n->parent;
                    if (n == m->root) {
                        throw invalid_iterator{};
                    }
                }
                n = n->parent;
            }
        }
    };

    map()
    {
        root = nullptr;
        zero = nullptr;
        Size = 0;
    }
    map(const map& other)
    {
        root = copy(other.root);
        zero = nullptr;
        Size = other.Size;
    }
    map& operator=(const map& other)
    {
        if (this == &other)
            return *this;

        clear();
        root = copy(other.root);
        Size = other.Size;
        return *this;
    }
    ~map() { clear(root); }

    T& at(const Key& key)
    {
        node* f = find(key, root);
        if (f)
            return f->value->second;
        else
            throw index_out_of_bound{};
    }
    const T& at(const Key& key) const
    {
        node* f = find(key, root);
        if (f)
            return f->value->second;
        else
            throw index_out_of_bound{};
    }
    T& operator[](const Key& key)
    {
        iterator itr = insert(value_type(key, T())).first;
        return itr->second;
    }
    const T& operator[](const Key& key) const
    {
        node* f = find(key, root);
        if (f)
            return f->value->second;
        else
            throw index_out_of_bound{};
    }

    iterator begin() { return iterator(getMin(), const_cast<map*>(this)); }
    const_iterator cbegin() const
    {
        return const_iterator(getMin(), const_cast<map*>(this));
    }
    iterator end() { return iterator(nullptr, const_cast<map*>(this)); }
    const_iterator cend() const
    {
        return const_iterator(nullptr, const_cast<map*>(this));
    }

    bool empty() const { return root == nullptr; }
    size_t size() const { return Size; }
    void clear()
    {
        clear(root);
        root = nullptr;
        Size = 0;
    }

    pair<iterator, bool> insert(const value_type& value)
    {
        node* res = nullptr;
        bool flag = false;
        insert(value, root, zero, res, flag);
        if (flag)
            ++Size;
        return pair<iterator, bool>(iterator(res, this), flag);
    }

    void erase(iterator pos)
    {
        if (pos == end() || pos.m != this)
            throw index_out_of_bound{};
        remove(pos.n->value->first, root, zero);
        --Size;
    }

    size_t count(const Key& key) const
    {
        return (find(key, root) == nullptr) ? 0 : 1;
    }
    iterator find(const Key& key)
    {
        return iterator(find(key, root), const_cast<map*>(this));
    }
    const_iterator find(const Key& key) const
    {
        return const_iterator(find(key, root), const_cast<map*>(this));
    }

  private: // helper functions
    // use it when p is valid
    void link_pl(node* p, node* l)
    {
        p->left = l;
        if (l)
            l->parent = p;
    }
    void link_pr(node* p, node* r)
    {
        p->right = r;
        if (r)
            r->parent = p;
    }

    // if empty return nullptr
    node* getMin() const
    {
        node* t = root;
        if (t)
            while (t->left)
                t = t->left;
        return t;
    }
    node* getMax() const
    {
        node* t = root;
        if (t)
            while (t->right)
                t = t->right;
        return t;
    }

    node* copy(node* t)
    {
        if (t) {
            node* copy_t = new node(*t->value, t->height);

            node* cl = copy(t->left);
            node* cr = copy(t->right);

            link_pl(copy_t, cl);
            link_pr(copy_t, cr);

            return copy_t;
        } else
            return nullptr;
    }
    void clear(node* t)
    {
        if (t) {
            clear(t->left);
            clear(t->right);
            delete t;
        }
    }

    int height(node* t) { return (t) ? t->height : -1; }
    int max(int a, int b) { return (a > b) ? a : b; }

    void LL(node*& t)
    {
        node* tl = t->left;
        link_pl(t, tl->right);
        tl->parent = t->parent;
        //        if (tl->parent==nullptr) root=tl;
        link_pr(tl, t);

        t->height = max(height(t->left), height(t->right)) + 1;
        tl->height = max(height(tl->left), height(t)) + 1;

        t = tl; //?
    }
    void RR(node*& t)
    {
        node* tr = t->right;
        link_pr(t, tr->left);
        tr->parent = t->parent;
        //        if (tr->parent==nullptr) root=tr;
        link_pl(tr, t);

        t->height = max(height(t->right), height(t->left)) + 1;
        tr->height = max(height(tr->right), height(t)) + 1;

        t = tr;
    }
    void LR(node*& t)
    {
        RR(t->left);
        LL(t);
    }
    void RL(node*& t)
    {
        LL(t->right);
        RR(t);
    }

    // insert remove find
    node* find(const Key& key, node* rt, Compare comp = Compare()) const
    {
        if (rt) {
            if (comp(key, rt->value->first))
                return find(key, rt->left);
            else if (comp(rt->value->first, key))
                return find(key, rt->right);
            else
                return rt;
        } else
            return nullptr;
    }
    void remove(const Key& key,
                node*& rt,
                node*& rt_p,
                Compare comp = Compare())
    {
        if (rt == nullptr)
            return;
        else if (comp(rt->value->first, key)) {
            remove(key, rt->right, rt);
            if (height(rt->left) - height(rt->right) >= 2) {
                if (height(rt->left->left) > height(rt->left->right))
                    LL(rt);
                else
                    LR(rt);
            }
        } else if (comp(key, rt->value->first)) {
            remove(key, rt->left, rt);
            if (height(rt->right) - height(rt->left) >= 2) {
                if (height(rt->right->right) > height(rt->right->left))
                    RR(rt);
                else
                    RL(rt);
            }
        }
        // rt->value->first == key
        else if (rt->left && rt->right) {
            node* tmp = rt->left;
            while (tmp->right)
                tmp = tmp->right;

            mySwap(rt, tmp);
            remove(key, tmp->left, tmp);

            //            std::swap(rt->value,tmp->value);
            //            remove(key,rt->left,rt);
        } else {
            node* tmp = (rt->left) ? (rt->left) : rt->right;
            delete rt;
            rt = tmp;
            if (rt)
                rt->parent = rt_p;
        }
        if (rt)
            rt->height = max(height(rt->left), height(rt->right)) + 1;
    }

    // flag : if an insertion is successful
    // res : address of the new node
    void insert(const value_type& v,
                node*& rt,
                node*& rt_p,
                node*& res,
                bool& flag,
                Compare comp = Compare())
    {
        Key key = v.first;

        if (rt == nullptr) {
            rt = new node(v);
            rt->parent = rt_p;
            res = rt;
            flag = true;
        } else if (comp(key, rt->value->first)) {
            insert(v, rt->left, rt, res, flag);
            // LL or LR
            if (height(rt->left) - height(rt->right) == 2) {
                if (comp(key, rt->left->value->first))
                    LL(rt);
                else if (comp(rt->left->value->first, key))
                    LR(rt);
            }
        } else if (comp(rt->value->first, key)) {
            insert(v, rt->right, rt, res, flag);
            // RL or RR
            if (height(rt->right) - height(rt->left) == 2) {
                if (comp(key, rt->right->value->first))
                    RL(rt);
                else if (comp(rt->right->value->first, key))
                    RR(rt);
            }
        }
        // ==
        else {
            res = rt;
            flag = false;
        }
        rt->height = max(height(rt->left), height(rt->right)) + 1;
    }

    void mySwap(node* r, node* t)
    {
        Nptr r_p = r->parent, r_l = r->left, r_r = r->right;
        Nptr t_p = t->parent, t_l = t->left, t_r = t->right;
        int r_h = r->height, t_h = t->height;

        t->height = r_h;
        r->height = t_h;

        if (t->parent != r) {
            if (r_p) {
                if (r_p->left == r)
                    link_pl(r_p, t);
                else
                    link_pr(r_p, t);
            } else {
                t->parent = nullptr;
                root = t;
            }
            link_pl(t, r_l);
            link_pr(t, r_r);

            link_pr(t_p, r);
            link_pl(r, t_l);
            link_pr(r, t_r);

        } else {
            if (r_p) {
                if (r_p->left == r)
                    link_pl(r_p, t);
                else
                    link_pr(r_p, t);
            } else {
                t->parent = nullptr;
                root = t;
            }
            link_pr(t, r_r);

            link_pl(t, r);

            link_pl(r, t_l);
            link_pr(r, t_r);
        }
    }
};
}

#endif
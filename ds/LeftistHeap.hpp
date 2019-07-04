// a kind of priority queue, faster than binary heap

#ifndef SJTU_CS358_LHEAP
#define SJTU_CS358_LHEAP

namespace SJTU_CS358 {

template<class T>
class LeftistHeap
{
  private:
    struct node
    {
        T data;
        node* l;
        node* r;
        int npl; // null path length

        node(const T& d)
          : data(d)
        {
            l = r = nullptr;
            npl = 0;
        }
    };
    node* root;

    void clear(node* rt);
    int npl(node* rt) { return (rt) ? rt->npl : -1; }
    node* merge(node* h1, node* h2);

  public:
    LeftistHeap(node* rt = nullptr) { root = rt; }
    ~LeftistHeap() { clear(root); }

    T& top() { return root->data; }
    void push(const T& x);
    T pop();
};

// implementation

template<class T>
void
LeftistHeap<T>::push(const T& x)
{
    node* p = new node(x);
    root = merge(root, p);
}

template<class T>
T
LeftistHeap<T>::pop()
{
    T ret = root->data;
    node* rl = root->l;
    node* rr = root->r;
    delete root;
    root = merge(rl, rr);
    return ret;
}

template<class T>
void
LeftistHeap<T>::clear(node* rt)
{
    if (rt) {
        clear(rt->l);
        clear(rt->r);
        delete rt;
    }
}

template<class T>
typename LeftistHeap<T>::node*
LeftistHeap<T>::merge(node* h1, node* h2)
{
    if (h1 == nullptr)
        return h2;
    if (h2 == nullptr)
        return h1;

    if (h1->data > h2->data)
        std::swap(h1, h2);
    h1->r = merge(h1->r, h2);

    if (npl(h1->r) > npl(h1->l))
        std::swap(h1->r, h1->l);
    h1->npl = npl(h1->l) + 1;

    return h1;
}
}
#endif
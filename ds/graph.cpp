
struct nodeE
{
    int end;
    int w;
    nodeE* next;
    nodeE(int e = 0, int ww = 0, nodeE* n = nullptr)
    {
        end = e;
        w = ww;
        next = n;
    }
};
struct nodeV
{
    nodeE* head;
    int ver;
    nodeV(nodeE* h = nullptr, int v = 0)
    {
        head = h;
        ver = v;
    }
};

class graph
{
    int Vers;

  public:
    nodeV* listV;
    graph(int sz = 10)
    {
        listV = new nodeV[sz];
        Vers = sz;
        for (int i = 1; i < sz; i++) {
            listV[i].ver = i;
        }
    }
    ~graph()
    {
        for (int i = 0; i < Vers; i++) {
            nodeE* p = listV[i].head;
            nodeE* q;
            while (p) {
                q = p->next;
                delete p;
                p = q;
            }
        }
        delete[] listV;
    }
    void insert(int u, int v, int w)
    {
        nodeE* p = listV[u].head;
        listV[u].head = new nodeE(v, w, p);
    }
    bool exist(int u, int v)
    {
        nodeE* p = listV[u].head;
        while (p) {
            if (p->end == v)
                return true;
            p = p->next;
        }
        return false;
    }

    struct edge
    {
        int beg, end;
        int w;
        bool operator<(const edge& rp) const { return w < rp.w; }
    };

    int kruskal()
    {
        int edgeAccepted = 0, u, v;
        nodeE* p;
        edge e;
        ds djs(Vers);
        lheap<edge> lh;

        for (int i = 0; i < Vers; i++) {
            for (p = listV[i].head; p != 0; p = p->next) {
                if (i < p->end) {
                    e.beg = i;
                    e.end = p->end;
                    e.w = p->w;
                    lh.enQueue(e);
                }
            }
        }

        int ans = 0;
        while (edgeAccepted < Vers - 1) {
            e = lh.deQueue();
            u = djs.Find(e.beg);
            v = djs.Find(e.end);
            if (u != v) {
                edgeAccepted++;
                djs.Union(u, v);
                cout << '(' << listV[u].ver << ',' << listV[v].ver << ')'
                     << endl;
                ans += e.w;
            }
        }

        return ans;
    }
};

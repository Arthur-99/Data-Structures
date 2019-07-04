#ifndef SJTU_CS358_DJS
#define SJTU_CS358_DJS

namespace SJTU_CS358 {

class DisjointSet
{
  private:
    int* parent;

  public:
    DisjointSet(int sz);
    ~DisjointSet();

    void Union(int p, int q);
    int Find(int x);
};

// implementation

DisjointSet::DisjointSet(int sz)
{
    parent = new int[sz];
    for (int i = 0; i < sz; i++)
        parent[i] = -1;
}

DisjointSet::~DisjointSet()
{
    delete[] parent;
}

void
DisjointSet::Union(int p, int q)
{
    int rt1 = Find(p), rt2 = Find(q);
    if (rt1 == rt2)
        return;
    if (parent[rt1] > parent[rt2]) {
        parent[rt2] += parent[rt1];
        parent[rt1] = rt2;
    } else {
        parent[rt1] += parent[rt2];
        parent[rt2] = rt1;
    }
}

int
DisjointSet::Find(int x)
{
    return (parent[x] < 0) ? x : (parent[x] = Find(parent[x]));
}
}

#endif
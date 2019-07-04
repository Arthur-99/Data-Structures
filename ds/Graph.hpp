#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int dep_city, arr_city;
    double dep_time, arr_time, cost;
    int type;
    edge() {}
    edge(int depc, int arrc, double dept, double arrt, double co, int ty)
      : dep_city(depc)
      , arr_city(arrc)
      , dep_time(dept)
      , arr_time(arrt)
      , cost(co)
      , type(ty)
    {}

    friend ostream& operator<<(ostream& os, const edge& e)
    {
        os << e.dep_city << "\t\t" << e.dep_time << " " << e.arr_time << " "
           << e.type << "\t\t" << e.arr_city;
        return os;
    }
};

struct node
{
    unordered_multimap<int, edge> um;
    auto operator[](int i) { return um.equal_range(i); }

    void insert(const pair<int, edge>& p) { um.insert(p); }
    auto begin() { return um.begin(); }
    auto end() { return um.end(); }
};

class MultiDiGraph
{
  private:
    // using node = unordered_multimap<int, edge>;
    vector<node> nodes;

  public:
    MultiDiGraph(int nodes_num = 0) { nodes.resize(nodes_num); }

    void add_edge(int dep_city, int arr_city, const edge& e)
    {
        nodes[dep_city].insert(pair<int, edge>(arr_city, e));
    }

    node& operator[](int i) { return nodes[i]; }

    int size() { return nodes.size(); }
};

#endif
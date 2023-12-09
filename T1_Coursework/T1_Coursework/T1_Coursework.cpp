#include <iostream>
#include "dsu.h"
#include "graph.h"

int main()
{
    auto edges = readGraph("input.txt");
    DSU dsu(edges.size());

    unsigned n = 0;
    std::vector<Edge> mst;
    for (Edge e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            n += e.weight;
            mst.push_back(e);
            dsu.unite(e.u, e.v);
        }
    }

    for (Edge e : mst) {
        std::cout << e.a << ' ' << e.b << std::endl;
    }
    std::cout << n;
}
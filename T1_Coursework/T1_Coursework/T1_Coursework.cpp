#include <iostream>
#include "dsu.h"
#include "graph.h"

int main()
{
    auto edges = Graph::fromFile("input.txt");

    auto mst = edges.mst();
    for (Edge e : mst.get_edges()) {
        std::cout << e.a << ' ' << e.b << std::endl;
    }
    std::cout << mst.get_mass();
}
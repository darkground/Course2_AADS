#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "dsu.h"

// Edge Structure
struct Edge {
    std::string a, b;
    int u, v, weight;
    
    // Простой конструктор
    Edge(std::string x, std::string y, int w = 0) {
        a = x;
        b = y;
        weight = w;
    }

    // Именованный конструктор
    Edge(std::vector<std::string>& named, int x, int y, int w = 0) : Edge(named[x], named[y], w) {
        u = x;
        v = y;
    }

    bool operator< (Edge const& other) {
        return weight < other.weight;
    }
};

class Graph {
    std::vector<Edge> edges;
    unsigned mass;

public:
    Graph();
    Graph(std::vector<Edge>);

    static Graph fromFile(std::string);
    Graph mst() const;
    const std::vector<Edge> get_edges() const;
    unsigned get_mass() const;
};

Graph::Graph() {
    mass = 0;
}

Graph::Graph(std::vector<Edge> e) {
    edges = e;
    mass = 0;
    for (Edge edge : edges) {
        mass += edge.weight;
    }
}

// Создать граф из файла
Graph Graph::fromFile(std::string path) {
    std::vector<std::string> names;
    std::string next;

    std::ifstream ifs(path);
    if (!ifs.is_open()) throw std::runtime_error("File not found");

    std::string line;
    getline(ifs, line);
    std::istringstream ss(line);

    while (ss >> next) {
        names.push_back(next);
    }

    unsigned m = 0;
    std::vector<Edge> edges;
    for (unsigned i = 0; i < names.size(); i++) {
        for (unsigned j = 0; j < names.size(); j++) {
            int w;
            ifs >> w;
            if (i < j) {
                if (w <= 0) throw std::runtime_error("Invalid weights in file");
                Edge e(names, i, j, w);
                m += w;
                edges.push_back(e);
            }
        }
    }

    std::sort(edges.begin(), edges.end());

    return Graph(edges);
}

// Поиск минимального остового дерева текущего графа
Graph Graph::mst() const {
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

    return Graph(mst);
}

// Получить вершины графа
const std::vector<Edge> Graph::get_edges() const
{
    return edges;
}

// Получить массу графа
unsigned Graph::get_mass() const
{
    return mass;
}

#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stack>
#include <unordered_set>
#include <queue>
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

    std::string first();
    Graph mst() const;
    std::vector<std::string> dfs(const std::string&);
    std::vector<std::string> bfs(const std::string&);
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
    if (!ifs.is_open()) throw std::runtime_error("File not found: " + path);

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
                if (w < 0) throw std::runtime_error("Invalid weights in file: " + std::to_string(w));
                else if (w > 0) {
                    Edge e(names, i, j, w);
                    m += w;
                    edges.push_back(e);
                }
            }
        }
    }

    return Graph(edges);
}

std::string Graph::first() {
    return edges.empty() ? "" : edges.front().a;
}

std::vector<std::string> Graph::dfs(const std::string& start) {
    std::stack<std::string> stack;
    std::unordered_set<std::string> visited;
    std::vector<std::string> out;

    stack.push(start);
    while (!stack.empty()) {
        std::string current = stack.top();
        stack.pop();

        if (visited.find(current) == visited.end()) {
            out.push_back(current);
            visited.insert(current);

            for (const Edge& edge : edges) {
                if (edge.a == current && visited.find(edge.b) == visited.end()) {
                    stack.push(edge.b);
                }
            }
        }
    }

    return out;
}

std::vector<std::string> Graph::bfs(const std::string& start) {
    std::queue<std::string> queue;
    std::unordered_set<std::string> visited;
    std::vector<std::string> out;

    queue.push(start);
    while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();

        if (visited.find(current) == visited.end()) {
            std::cout << current << " ";
            visited.insert(current);

            for (const Edge& edge : edges) {
                if (edge.a == current && visited.find(edge.b) == visited.end()) {
                    queue.push(edge.b);
                }
            }
        }
    }

    return out;
}

// Поиск минимального остового дерева текущего графа
Graph Graph::mst() const {
    DSU dsu(edges.size());

    unsigned n = 0;
    std::vector<Edge> mst;
    std::vector<Edge> edges_sorted(edges);
    std::sort(edges_sorted.begin(), edges_sorted.end()); 
    for (Edge e : edges_sorted) {
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

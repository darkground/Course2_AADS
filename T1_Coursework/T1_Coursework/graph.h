#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

// Edge Structure
struct Edge {
    std::string a, b;
    int weight;
    
    Edge(std::string a_, std::string b_, int w = 0) : a(a_), b(b_), weight(w) {}

    bool operator< (Edge const& other) {
        return weight < other.weight;
    }
};


// Read a graph from given file
std::vector<Edge> readGraph(std::string path) {
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

    std::vector<Edge> edges;
    for (unsigned i = 0; i < names.size(); i++) {
        for (unsigned j = 0; j < names.size(); j++) {
            int w;
            ifs >> w;
            if (i < j) {
                if (w <= 0) throw std::runtime_error("Invalid weights in file");
                Edge e(names[i], names[j], w);
                edges.push_back(e);
            }
        }
    }

    std::sort(edges.begin(), edges.end());
    return edges;
}
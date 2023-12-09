#pragma once
#include <vector>

// Disjoint-Set-Union Structure
class DSU {
	std::vector<size_t> parent, rank;
public:
	DSU(size_t n) : parent(n, 0), rank(n, 1) {
		for (size_t i = 0; i < n; i++)
			make(i);
	}

	size_t find(size_t v) {
		return (v == parent[v]) ? v : (parent[v] = find(parent[v]));
	}

	void make(size_t v) {
		parent[v] = v;
		rank[v] = 1;
	}

	void unite(size_t a, size_t b) {
		a = find(a);
		b = find(b);
		if (a != b) {
			if (rank[a] < rank[b])
				std::swap(a, b);
			parent[b] = a;
			rank[a] += rank[b];
		}
	}
};
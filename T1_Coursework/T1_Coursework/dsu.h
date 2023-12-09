#pragma once
#include <vector>

// Disjoint-Set-Union Structure
class DSU {
	std::vector<int> parent, rank;
public:
	DSU(unsigned n) : parent(n, 0), rank(n, 1) {
		for (unsigned i = 0; i < n; i++)
			make(i);
	}

	unsigned find(unsigned v) {
		return (v == parent[v]) ? v : (parent[v] = find(parent[v]));
	}

	void make(unsigned v) {
		parent[v] = v;
		rank[v] = 1;
	}

	void unite(unsigned a, unsigned b) {
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
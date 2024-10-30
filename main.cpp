#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge with its source, destination, and weight
struct Edge {
    int src, dest, weight;
};

// Comparator function to sort edges by weight in ascending order
bool compareEdge(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Structure to represent a disjoint set for Union-Find
struct DisjointSet {
    vector<int> parent, rank;

    // Initialize disjoint set with n elements
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // Find the root of the set containing element x with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union of two sets by rank
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Function to find the MST using Kruskal's algorithm
vector<Edge> kruskalMST(vector<Edge>& edges, int V) {
    // Sort edges by weight
    sort(edges.begin(), edges.end(), compareEdge);

    DisjointSet ds(V);
    vector<Edge> mst;

    for (const auto& edge : edges) {
        int u = edge.src;
        int v = edge.dest;

        // Check if the current edge forms a cycle
        if (ds.find(u) != ds.find(v)) {
            mst.push_back(edge);  // Include the edge in the MST
            ds.unionSets(u, v);   // Union the sets of u and v
        }

        // Stop if we've added enough edges for an MST
        if ((int) mst.size() == V - 1) {
            break;
        }
    }
    return mst;
}

// Function to print the MST
void printMST(const vector<Edge>& mst) {
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto& edge : mst) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
    }
}

int main() {
    int V = 4;  // Number of vertices
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    // Find MST using Kruskal's algorithm
    vector<Edge> mst = kruskalMST(edges, V);

    // Print the MST
    printMST(mst);

    return 0;
}

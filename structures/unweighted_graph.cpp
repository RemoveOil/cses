#include <iostream>
#include <vector>
#include "../_utils.cpp"

using namespace std;

struct UWGraph {
    vector<vector<int>> adj;
    int N, M;
    bool directed, one_indexed;

    UWGraph(istream &stream,
            bool directed = false,
            bool one_indexed = false) : directed(directed), one_indexed(one_indexed) {

        stream >> N >> M;
        if (one_indexed) ++N;
        adj.resize(N);
        for (int i = 0, src, dst; i < M; ++i) {
            stream >> src >> dst; 
            adj[src].push_back(dst);
            if (!directed)  adj[dst].push_back(src);
        }
    }
    
    void add_edge(int src, int dst) {
        adj[src].push_back(dst);
        if (!directed)  adj[dst].push_back(src);
        ++M;
    }

    friend ostream& operator<<(ostream& os, const UWGraph& graph) {
        for (int i = graph.one_indexed; i < graph.adj.size(); ++i) {
            os << i << ": ";
            os << graph.adj[i];
        }
        return os;
    }
};

// WGraph
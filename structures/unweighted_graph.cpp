#include <iostream>
#include <vector>


using namespace std;


struct UWGraph {
    vector<vector<int>> adj;
    int N, M;
    bool directed;

    UWGraph(istream &stream, bool _directed = false) {

        // vector<T> values;
        directed = _directed;
        stream >> N >> M;
        adj.resize(N+1); // N or N + 1
        // adj.size()  <--- bu guvenilir bi sey degil
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
};

// WGraph
#include <iostream>
#include <vector>
#include <queue>

// #include "../_utils.cpp"
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



vector<int> parent;
queue<int> Q;

// arg order bakmalisin
void BFS(const UWGraph &graph, int start, int target) {
    Q.push(start);
    parent[start] = start;
    while (!Q.empty()) {
        int cur = Q.front(); Q.pop();
        for(auto dst : graph.adj[cur]) {
            if (!parent[dst]) {
                parent[dst] = cur;
                Q.push(dst);
            }
        }

    }

    if (parent[target]) {
        vector<int> res;
        int cur = target;
        while (parent[cur] != cur) {
            res.push_back(cur);
            cur = parent[cur];
        }
        res.push_back(cur);

        cout << res.size() << endl;
        for (int i = res.size() - 1; i > 0; --i)
            cout << res[i] << " ";
        cout << res[0] << endl;
    }
    else {
        cout << "IMPOSSIBLE" << endl;
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    UWGraph graph(cin); // 1 indexed
    parent = vector<int>(graph.N + 1, 0);
    BFS(graph, 1, graph.N);
    return 0;
}

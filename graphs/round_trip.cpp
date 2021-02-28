#include <iostream>
#include <vector>
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


vector<int> S;
vector<bool> mark;
int found;

void dfs(const UWGraph& graph, int cur, int parent) {
    if (found) return;
    S.push_back(cur);
    for(auto neighbor : graph.adj[cur]) {
        if (neighbor != parent) {
            if (mark[neighbor] && !found) {
                found = neighbor; return;
            }
            mark[neighbor] = true;
            dfs(graph, neighbor, cur);
        }
    }
    if (found) return;
    S.pop_back();
}


int main() {
    ios_base::sync_with_stdio(false);
    UWGraph graph(cin);
    mark = vector<bool>(graph.N + 1, false);

    for (int i = graph.N; i > 0; --i) {
        if (!mark[i]) {
            mark[i] = true;
            dfs(graph, i, i);
        }
    }

    if (found) {
        vector<int> res;
        res.push_back(found);
        while (S.back() != found) {
            res.push_back(S.back());
            S.pop_back();
        }
        res.push_back(found);
        cout << res.size() << endl;
        for (int node : res)    cout << node << " ";
    }
    else { cout << "IMPOSSIBLE" ; }
    cout << endl;
    return 0;
}

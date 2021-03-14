#include <iostream>
#include <vector>
// #include "../_utils.cpp"

using namespace std;

using ulli = unsigned long long int;
using lli = long long int;

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

vector<int> el_colors;
bool sictik = false;

// mesajlarin arg order
void dfs (const UWGraph &graph, int cur_node, int cur_color) {
    if (sictik)
        return;

    int next_color = 3 - cur_color;
    for (int neighbor : graph.adj[cur_node]) {
        if (el_colors[neighbor] && el_colors[neighbor] != next_color)
            sictik = true;

        if (!el_colors[neighbor]) {
            el_colors[neighbor] = next_color;
            dfs(graph, neighbor, next_color);
        }
    }

}
 
int main() {
    ios_base::sync_with_stdio(false);
    UWGraph graph(cin);
    el_colors = vector<int>(graph.N + 1, 0);
    
    // loop..
    for(int i=1;i<=graph.N;i++) {
        if (!el_colors[i]) {
            el_colors[i] = 1;
            dfs(graph, i, 1);
        }
    }

    if (sictik) cout << "IMPOSSIBLE";
    else for(int i = 1; i < el_colors.size(); ++i) cout << el_colors[i] << " ";
    cout << endl;

    return 0;
}

#include <iostream>
#include <queue>
#include <set>
#include <vector>

// #include "../_utils.cpp"

using namespace std;

using ulli = unsigned long long int;
using lli = long long int;
using ii = pair<lli, int>;

// edge is direction agnostic.
struct WeightedEdge {
    const int p, q, w;
    WeightedEdge(int _p, int _q, int _w): p(_p), q(_q), w(_w) {}

    // gerizekali bi sey gelirse throwlamayi dusun.
    int other(int end) { return end == p? q : p; }

    bool operator<(const WeightedEdge& other) const {
        if (p != other.p)   return p < other.p;
        if (q != other.q)   return q < other.q;
        return w < other.w;
    }

    friend ostream& operator<<(ostream& os, const WeightedEdge& edge) {
        os << "(" << edge.p << ", " << edge.q << ", " << edge.w << ")";
        return os;
    }
};


// consider using hash sets if performance becomes a concern.
struct WGraph {
    vector<set<WeightedEdge>> adj;
    int N, M;
    bool directed;

    WGraph(istream &stream, bool _directed = false) {

        // vector<T> values;
        directed = _directed;
        stream >> N >> M;
        adj.resize(N+1); // N or N + 1
        // adj.size()  <--- bu guvenilir bi sey degil
        for (int i = 0, src, dst, weight; i < M; ++i) {
            stream >> src >> dst >> weight; 
            __add_edge(src, dst, weight);
        }
    }

    void add_edge(int src, int dst, int weight) {
        __add_edge(src, dst, weight);
        ++M;
    }

    void __add_edge(int src, int dst, int weight) {
        WeightedEdge cur_edge(src, dst, weight);
        adj[src].insert(cur_edge);
        if (!directed)  adj[dst].insert(cur_edge);
    }

    const vector<WeightedEdge> neighbors(int p) { return vector<WeightedEdge>(adj[p].begin(), adj[p].end()); }
};


priority_queue<ii, vector<ii>, greater<ii>> q;



void dijkstra(WGraph g) {
    vector<bool> mark(g.adj.size(), 0);
    vector<lli> distances(g.adj.size(), 0);
    q.push({0, 1});

    while (!q.empty()) {
        auto [dist, node] = q.top(); q.pop();
        if (mark[node]) continue;
        mark[node] = true;
        distances[node] = dist;
        for(auto e : g.neighbors(node))
            q.push({dist + e.w, e.other(node)});
    }

    for(int i = 1; i < g.adj.size(); ++i)
        cout << distances[i] << " ";
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    WGraph g(cin, true);
    dijkstra(g);
    // cout << g.neighbors(2);
    return 0;
}

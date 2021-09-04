#include <iostream>
#include <queue>
// #include "../_utils.cpp"
 
#include <iostream>
#include <vector>
#include <set>
 
using namespace std;
 
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
    vector<set<WeightedEdge>> adj; // adj.size()  <--- bu guvenilir bi sey degil
    int N, M;
    bool directed;
 
    WGraph(int _N, bool _directed = false): directed(_directed), N(_N) {
        adj.resize(N + 1);
    }
 
    WGraph(istream &stream, bool _directed = false) {
 
        // vector<T> values;
        directed = _directed;
        stream >> N >> M;
        adj.resize(N+1); // N or N + 1
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
 
    const vector<WeightedEdge> neighbors(int p) const { return vector<WeightedEdge>(adj[p].begin(), adj[p].end()); }
 
    // friend ostream& operator<<(ostream& os, const WGraph& graph) {
    //     for (int i = 1; i < graph.adj.size(); ++i) {
    //         os << i << ": ";
    //         os << graph.neighbors(i);
    //     }
    //     return os;
    // }
};
 
 
#define COMP_MAX_INT (1e17)
#define MAXN 100010
 
using namespace std;
 
using ulli = unsigned long long int;
using lli = long long int;
 
struct Node {
    int node;
    lli distance;
    bool coupon_used;
    const bool operator<(const Node& other) const { return distance > other.distance; }
};
 
priority_queue<Node> Q;
lli distances[MAXN][2];
 
void init() { fill(distances[0], distances[MAXN], COMP_MAX_INT); }
 
void eval(const WGraph& graph) {
    Q.push(Node{1, 0, false});
    while (!Q.empty()) {
        auto [cur_node, cur_distance, cur_coupon_used]  = Q.top(); Q.pop();
        for(auto adj : graph.neighbors(cur_node)) {
            auto [p, q, w] = adj; // q == dst;
            if (distances[q][cur_coupon_used] > cur_distance + w) {
                distances[q][cur_coupon_used] = cur_distance + w;
                Q.push(Node{q, distances[q][cur_coupon_used], cur_coupon_used});
            }
            if (cur_coupon_used == false) {
                if (distances[q][1] > cur_distance + w/2) {
                    distances[q][1] = cur_distance + w/2;
                    Q.push(Node{q, distances[q][1], true});
                }
            }
        }
    }
    cout << distances[graph.N][1] << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    WGraph graph(cin, true); // read;
    init();
    eval(graph);
    return 0;
}

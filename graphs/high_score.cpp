#include <iostream>
#include "../_utils.cpp"
#include "../structures/weighted_graph.cpp"

#define COMP_MAX_INT (1e17)


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

    friend ostream& operator<<(ostream& os, const WGraph& graph) {
        for (int i = 1; i < graph.adj.size(); ++i) {
            os << i << ": ";
            os << graph.neighbors(i);
        }
        return os;
    }
};

using namespace std;

using ulli = unsigned long long int;
using lli = long long int;

vector<lli> distances;

WGraph read_graph() {
    int N, M;
    cin >> N >> M;
    WGraph graph(N, true);
    for (int i, src, dst, w = 0; i < M; ++i) {
        cin >> src >> dst >> w;
        graph.add_edge(src, dst, -w);
    }

    return graph;
}


lli bellman_ford(const WGraph &g) {
    distances = vector<lli>(g.N + 1, COMP_MAX_INT);
    vector<bool> goesToM(g.N + 1, false);
    goesToM[g.N] = true;
    distances[1] = 0;
    for (int k=0; k < g.N-1; k++)
        for(int i=1; i <= g.N; i++)
            for (auto u : g.neighbors(i)) {
                auto other = u.other(i);
                if (distances[i] != COMP_MAX_INT)
                    distances[other] = min(distances[other], distances[i] + u.w);
                if (goesToM[other]) goesToM[i] = true;
            }

    // DEBUGN(goesToM);
    // DEBUGN(distances);
    for (int i = 1; i <= g.N; i++)
        for (auto u : g.neighbors(i)) {
            auto [src, dst, weight] = u;
            if (
                distances[src] != COMP_MAX_INT &&
                goesToM[dst] &&
                distances[src] + weight < distances[dst]) {
                return -1;
            }
        }
    return -distances[g.N];
}

int main() {
    ios_base::sync_with_stdio(false);
    WGraph g = read_graph();
    // cout << g;
    cout << bellman_ford(g) << endl;
    return 0;
}

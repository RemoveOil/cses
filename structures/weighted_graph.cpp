#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <sstream>

#include "../_utils.cpp"

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
    vector<int> extras;

    WGraph(int _N, bool _directed = false): directed(_directed), N(_N) {
        adj.resize(N + 1);
    }

    WGraph(istream &stream, bool _directed = false) {

        // vector<T> values;
        directed = _directed;
        stream >> N >> M;///
        read_extras(stream);
        adj.resize(N + 1); // N or N + 1
        for (int i = 0, src, dst, weight; i < M; ++i) {
            stream >> src >> dst >> weight; 
            __add_edge(src, dst, weight);
        }
    }

    void read_extras(istream &stream) {
        string rest_of_first_line;
        getline(stream, rest_of_first_line);
        stringstream cocuk(rest_of_first_line);
        extras = vector<int>(
            istream_iterator<int>(cocuk),
            istream_iterator<int>());
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

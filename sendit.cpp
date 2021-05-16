#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <set>
#include <type_traits>
#include <queue>
#ifndef __UTILS__
#define __UTILS__

using namespace std;

#define DEBUG(name) print(#name, name)
#define DEBUGN(name) print(#name, name, true)

template<typename>
struct is_std_vector : std::false_type {};

template<typename T, typename A>
struct is_std_vector<std::vector<T,A>> : std::true_type {};

template<class T>
ostream& operator<<(ostream& os, const vector<T> &v) {
    if (!v.size())
        return os;

    char sep = ' ';
    typename vector<T>::const_iterator it = v.begin(), end = prev(v.end());
    while (it != end) {
        os << *it;
        if (!is_std_vector<T>::value)
            os << sep;
        ++it;
    }

    os << *it << endl;
    return os;
    
}

template<class T>
void print(string var_name, T var, bool newline=false) {
    cout << var_name << ':' << (newline ? '\n' : ' ') << var; 
}

#endif

using namespace std;
struct WeightedEdge {
    const int p, q, w;
    WeightedEdge(int _p, int _q, int _w): p(_p), q(_q), w(_w) {}
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
struct WGraph {
    vector<set<WeightedEdge>> adj;
    int N, M;
    bool directed;
    vector<int> extras;

    WGraph(int _N, bool _directed = false): directed(_directed), N(_N) {
        adj.resize(N + 1);
    }

    WGraph(istream &stream, bool _directed = false) {
        directed = _directed;
        stream >> N >> M;
        read_extras(stream);
        adj.resize(N + 1);
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

#define COMP_MAX_INT (1e17)

using namespace std;

using ulli = unsigned long long int;
using lli = long long int;

struct Item {
    int node;
    lli dist;
    bool operator<(const Item& other) const { return dist > other.dist; }
};

priority_queue<Item> cur_mainQ;
void eval(WGraph& graph, int K) {
    vector<int> visited_counts(graph.N + 1, 0);
    int cn = 0;
    cur_mainQ.push({1, 0});
    while(!cur_mainQ.empty()) {
        auto [node, dist] = cur_mainQ.top(); cur_mainQ.pop();
        if (visited_counts[node] > K + 1)
            continue;
        visited_counts[node]++;
        if (node == graph.N) {
            cout << dist << " ";
            cn++;
            if (cn == K) return;
        }
        for(auto& neigh : graph.neighbors(node)) {
            auto [src, dst, w] = neigh;
            if (visited_counts[node] <= K )
                cur_mainQ.push({dst, dist + w});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    WGraph graph(cin, true);
    int k = graph.extras[0];

    eval(graph, k);
    return 0;
}

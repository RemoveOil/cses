#include <iostream>
#include <queue>
#include "../_utils.cpp"
#include "../structures/weighted_graph.cpp"

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
    cur_mainQ.push({1, 0}); // initial...
    while(!cur_mainQ.empty()) {
        auto [node, dist] = cur_mainQ.top(); cur_mainQ.pop();
        if (visited_counts[node] > K)
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

// 10s 13136541002025 13136541009480 13136541098393 13136541105848 13136541130800 13136541138255 13136541144220 13136541151675 13136541227168 13136541234623 
// jevap 13136541002025 13136541009480 13136541098393 13136541105848 13136541130800 13136541138255 13136541144220 13136541151675 13136541227168 13136541234623 
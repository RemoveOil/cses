#include <iostream>
#include <queue>
// #include "../structures/unweighted_graph.cpp"

using namespace std;

struct QItem { int parent, id, dist; };

// distance, node_id
pair<int, int> pulse(const UWGraph& graph, int source) {
    queue<QItem> Q;
    Q.push({-1, source, 0});
    QItem last_out;

    while (!Q.empty()) {
        last_out = Q.front(); Q.pop();
        auto [parent_id, cur_id, cur_dist] = last_out;
        for (auto child_id : graph.adj[cur_id]) {
            if (parent_id != child_id)
                Q.push({cur_id, child_id, cur_dist + 1});
        }
    }
    return {last_out.dist, last_out.id};
}


UWGraph make_graph() {
    int N, src, dst;
    cin >> N;
    UWGraph graph(N, false, true);
    for (int i = 0; i < N-1; ++i) {
        cin >> src >> dst;
        graph.add_edge(src, dst);
    }
    return graph;
}

int main() {
    auto graph = make_graph();
    auto [height, id] = pulse(graph, 1);
    auto [res, res_id] = pulse(graph, id);
    cout << res << endl;
    return 0;
}

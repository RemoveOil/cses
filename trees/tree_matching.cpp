#include <iostream>
#include <queue>
#include "../_utils.cpp"
#include "../structures/unweighted_graph.cpp"

using namespace std;

vector<int> degree;
UWGraph graph;
queue<int> starters;
vector<bool> mark;
int res, N;
// outdegree 0 olani al
// parenti isaretli mi bak
// isaretli degilse parenti pair olarak al
// parentin parentinin outdegreesini dusur
// outdegree 0 ise onu leaf olarak al ve queue ya at

void read() {
    cin >> N;
    graph = UWGraph(N, false, true);
    degree = vector<int>(N + 1);
    mark = vector<bool>(N + 1);
    int src, dst;
    for (int i = 1; i < N; i++) {
        cin >> src >> dst;
        graph.add_edge(src, dst);
        degree[src]++;
        degree[dst]++;
    }
}


void eval() {
    for (int i = 1; i <= N; i++)
        if (degree[i] == 1)
            starters.push(i);

    while (!starters.empty()) {
        int cur_node = starters.front(); starters.pop();
        for (auto neighbor : graph.adj[cur_node]) {
            // select this node secicez??   edge(cur_node ⇄ neighbor)
            if (!mark[neighbor]) {
                res ++;
                mark[neighbor] = mark[cur_node] = true;
                for(auto n_neighbor : graph.adj[neighbor]) {
                    degree[n_neighbor]--;
                    if (!mark[n_neighbor] && degree[n_neighbor] == 1) starters.push(n_neighbor);
                }           
            }
        }
    }
    cout << res << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    read();
    eval();
    return 0;
}

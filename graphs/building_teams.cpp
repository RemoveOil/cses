#include <iostream>
#include <vector>
#include "../_utils.cpp"
#include "../structures/unweighted_graph.cpp"

using namespace std;

using ulli = unsigned long long int;
using lli = long long int;

vector<int> el_colors;
bool kutabatta = false;

// mesajlarin arg order
void dfs (const UWGraph &graph, int cur_node, int cur_color) {
    if (kutabatta)
        return;

    int next_color = 3 - cur_color;
    for (int neighbor : graph.adj[cur_node]) {
        if (el_colors[neighbor] && el_colors[neighbor] != next_color)
            kutabatta = true;

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

    if (kutabatta) cout << "IMPOSSIBLE";
    else for(int i = 1; i < el_colors.size(); ++i) cout << el_colors[i] << " ";
    cout << endl;

    return 0;
}

#include <iostream>
#include <iterator>
#include "../_utils.cpp"
#include "../structures/unweighted_graph.cpp"

#define COMP_MAX_INT (1e17)

using namespace std;

using ulli = unsigned long long int;
using lli = long long int;

// call'da girdigimiz cocuklar

bool DFS(int cur, UWGraph &graph, vector<bool> &call_mark, vector<bool> &mark, vector<int> &call_stack) {
    call_stack.push_back(cur);
    if (call_mark[cur])   return true;
    if (mark[cur]) {
        call_stack.pop_back();
        return call_mark[cur] = false;
    }
    call_mark[cur] = mark[cur] = true;
    for (auto neigh : graph.adj[cur])
        if (DFS(neigh, graph, call_mark, mark, call_stack))
            return true;
    call_stack.pop_back();
    return call_mark[cur] = false;
}
// 0 --> 1 --> 2 -- >3 -- >1


// 4 -> 5 -> ... loop varsa buluyosun
// 7 -> 5
void print_solution(vector<int> &call_stack) {
    // DEBUG(call_stack); cout << endl;

    auto i_stack = call_stack.end() - 1;
    auto i_end = call_stack.end() - 1;
    while (*(--i_stack) != *i_end);
    cout << i_end - i_stack + 1 << endl;
    copy(i_stack, i_end + 1, ostream_iterator<int>(cout, " "));
}

int main() {
    ios_base::sync_with_stdio(false);
    UWGraph graph(cin, true, true);
    vector<bool> mark(graph.N), call_mark(graph.N);
    vector<int> call_stack;

    for (int i = graph.one_indexed; i < graph.N; ++i) {
        if (DFS(i, graph, call_mark, mark, call_stack)) {
            print_solution(call_stack);
            return 0;
        }
    }
    cout << "IMPOSSIBLE" << endl;

    return 0;
}

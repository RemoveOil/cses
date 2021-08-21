#include <iostream>
#include <vector>
#include <queue>
#include "../unweighted_graph.cpp"
#include "../tree.cpp"

using namespace std;


size_t size_of_tree(TreeNode* root) {
    int res = 1;
    for (auto* child : root->children) res += size_of_tree(child);
    return res;
}

TreeNode* bfs_tree_from(const UWGraph& graph, int source) {
    TreeNode* root = new TreeNode(source);
    queue<pair<int, TreeNode*>> Q;
    Q.push({-1, root});

    while (!Q.empty()) {
        auto [parent, current_node] = Q.front(); Q.pop();
        for (auto child : graph.adj[current_node->id]) {
            if (parent != child) {
                TreeNode* child_node = new TreeNode(child);
                current_node->children.push_back(child_node);
                Q.push({current_node->id, child_node});
            }
        }
    }
    return root;
}


UWGraph bfs_graph_from(TreeNode* root, bool one_indexed = false) {
    UWGraph g;
    size_t size_tree = size_of_tree(root);
    g.adj.resize(size_tree + one_indexed);
    g.directed = false;

    queue<TreeNode*> Q;
    Q.push(root);

    while(!Q.empty()) {
        auto cur = Q.front(); Q.pop();
        for (auto* child : cur->children) {
            g.adj[cur->id].push_back(child->id);
            g.adj[child->id].push_back(cur->id);
            Q.push(child);            
        }
    }
    
    return g;
} 


void bfs_tree_travel(TreeNode* root) {
    queue<pair<int, TreeNode*>> Q;
    Q.push({0, root});
    while(!Q.empty()) {
        auto [level, cur] = Q.front(); Q.pop();
        for(int i = 0; i < level; i++) cout << " ";
        cout << cur->id << endl;
        for(auto* child : cur->children) Q.push({level+1, child});        
    }
}



// int main () {
//     UWGraph graph(cin, false, true);
//     cout << graph;
//     TreeNode* encoded = bfs_tree_from(graph, 1);
//     bfs_tree_travel(encoded);
//     cout << endl;
// 
//     UWGraph decoded = bfs_graph_from(encoded, true);
//     cout << decoded << endl;
// }
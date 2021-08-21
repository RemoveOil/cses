#include <vector>

using namespace std;

struct TreeNode {
    int id;
    vector<TreeNode*> children; 
    TreeNode (int id): id(id) { }
};

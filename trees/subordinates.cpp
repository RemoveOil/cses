#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

vector<vector<int>> children;
vector<int> subordinates;
int N;

int count_children(int root) {
    int res = children[root].size();
    for (int child : children[root])
        res += count_children(child);
    return subordinates[root] = res;
}
// 5
// 1 1 2 3

// 0  1  2  3  4
// 1  3  4
// 2

void read() {
    cin >> N;
    int a;
    children = vector<vector<int>>(N, vector<int>());
    subordinates = vector<int>(N);
    for (int i = 1; i < N; i++) {
        cin >> a;
        children[a-1].push_back(i);
    }
    
}

int main() {
    ios_base::sync_with_stdio(false);
    read();
    count_children(0);
    copy(subordinates.begin(), subordinates.end(), ostream_iterator<int>(cout, " "));

    return 0;
}

#include <iostream>
#include <queue>
#include <vector>

#define START_NODE ('A')
#define TARGET_NODE ('B')
#define EMPTY ('.')
#define WALL ('#')


using namespace std;

using ulli = unsigned long long int;
using lli = long long int;

struct Node {
    char move; // ULDR or space char
    int i, j;
    Node *parent;
    Node(char _move, int _i, int _j, Node* _parent) {
        move = _move;
        i = _i;
        j = _j;
        parent = _parent;
    }
};

int N, M;
vector<string> labyrinth;
queue<Node*> Q;
vector< vector<Node*> > map(N, vector<Node*>(M, new Node(' ', -1, -1 ,nullptr))); // -> parenti point et, ve urld yazsin

vector<Node*> nope(5, nullptr);

void init_Nope() {
    for (int i = 0; i < N; ++i)
        nope[i] = new Node(' ', 0, i, nullptr);
    cout << nope.size() << endl;
    cout << nope[1]->j << endl;
}

void init_map() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j)
            map[i][j] = new Node(' ', i, j, nullptr);
    }
    cout << "scitkds" << endl;
    // cout << map[0].size() << endl;
}

void oku_bakalim() {
    cin >> N >> M;
    for(int i=0;i<N;i++) {
        string ss;
        cin >> ss;
        labyrinth.push_back(ss);
    }
}

bool valid(unsigned i, unsigned j) {
    return i < N && j < M;
}

Node* BFS(int start_i, int start_j) {
    int dir[4][2] = {{1,0}, {-1,0}, {0, 1}, {0, -1}};
    char dir_char[] = "DURL";


    map[start_i][start_j]->parent = map[start_i][start_j];
    Q.push(map[start_i][start_j]);
    while (!Q.empty()) {
        Node* current = Q.front();
        Q.pop();

        for (int i=0;i<4;i++) {
            int next_i = dir[i][0] + current->i;
            int next_j = dir[i][1] + current->j;
            if (valid(next_i, next_j) && labyrinth[next_i][next_j] != WALL && map[next_i][next_j]->parent == nullptr) {
                map[next_i][next_j]->parent = current;
                map[next_i][next_j]->move = dir_char[i];
                if (labyrinth[next_i][next_j] == TARGET_NODE)
                    return map[next_i][next_j];
                Q.push(map[next_i][next_j]);
            }
        }
    }
    return NULL; 
}

void find_node(int &start_i, int &start_j, char node_key) {
    int found = 0;
    for (int i = 0; i < N && !found; ++i) {
        for (int j = 0; j < M && !found; ++j) {
            if (labyrinth[i][j] == node_key) {
                start_i = i;
                start_j = j;
                found = 1;
            }
        }
    }
}


void solve() {
    int start_i, start_j;
    find_node(start_i, start_j, START_NODE);
    Node* target = BFS(start_i, start_j);

    if (!target) cout << "NO" << endl;
    else {
        string path_reversed;
        Node* cur = target;
        while(cur->parent != cur) {
            path_reversed.push_back(cur->move);
            cur = cur->parent;
        }
        
        cout << "YES" << endl;
        cout << path_reversed.length() << endl;
        cout << string(path_reversed.rbegin(), path_reversed.rend()) << endl;
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    oku_bakalim(); // labyrinth
    init_Nope();
    // init_map(); // map
    // solve();
    return 0;
}

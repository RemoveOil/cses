#include <iostream>
#include <queue>
// #include "../_utils.cpp"

using namespace std;

#define MAXN 1000
#define MONSTERS ('M')
#define FLOOR ('.')
#define EXIT ('.')
#define DUDE ('A')
#define FATALITY ('@')

int dir[4][2] = {{1,0}, {0, 1}, {-1,0}, {0, -1}};
int linear_offset[4] = {MAXN, 1, -MAXN, -1};
char dir_char[] = "DRUL";

vector<string> maze;
int I, J, exit_index = 0, dude_linear_index;
queue<pair<int, char>> Q; // linear_index, 'M'/'A'


bool valid(unsigned i, unsigned j) { return i < I && j < J; }
bool is_boundry(unsigned i, unsigned j) {
    return (
        ((i == 0 || i == I - 1)) ||
        ((j == 0 || j == J - 1))
    );
}

int find_dir_index(char x) {
    for (int i=0; i<4; i++)
        if (dir_char[i] == x)
            return (i + 2) % 4;
    return -1;
}

void init_globals() {
    cin >> I >> J;
    string line;
    for (int i = 0; i < I; ++i) {
        cin >> line;
        for (int j = 0; j < J; ++j) {
            int linear_index = i * MAXN + j;
            if (is_boundry(i, j) && line[j] == EXIT)
                line[j] = FATALITY;
            if (line[j] == MONSTERS)
                Q.push({linear_index, 'M'});
            if (line[j] == DUDE)
                dude_linear_index = linear_index;
        }
        maze.push_back(line);
    }
    Q.push({dude_linear_index, 'A'});
}

pair<int, int> BFS() {
    auto [dude_i, dude_j] = make_pair(dude_linear_index / MAXN, dude_linear_index % MAXN);
    if (is_boundry(dude_i, dude_j))
        return {dude_i, dude_j};

    while (Q.size()) {
        auto [cur_linear_index, node_type] = Q.front(); Q.pop();
        int cur_i = cur_linear_index / MAXN;
        int cur_j = cur_linear_index % MAXN;

        for(int d = 0; d < 4; ++d) {
            int next_i = dir[d][0] + cur_i;
            int next_j = dir[d][1] + cur_j;
            int next_linear_index = cur_linear_index + linear_offset[d];
            if (valid(next_i, next_j)) {
                if (node_type == DUDE && maze[next_i][next_j] == FATALITY) {
                    maze[next_i][next_j] = dir_char[d];
                    return {next_i, next_j};
                }
                if (maze[next_i][next_j] == FLOOR || maze[next_i][next_j] == FATALITY) {
                    Q.push({next_linear_index, node_type});
                    char printer = 'M';
                    if (node_type == DUDE) 
                        printer = dir_char[d];
                    maze[next_i][next_j] = printer;
                }
            }
        }
    }
    return {-1, -1};
}


void print_result(pair<int, int> &node) {
    string path = "";
    auto [i, j] = node;
    while (maze[i][j] != DUDE) {
        int d_index = find_dir_index(maze[i][j]);
        path.push_back(maze[i][j]);
        i += dir[d_index][0];
        j += dir[d_index][1];
    }
    cout << path.length() << endl;
    cout << string(path.rbegin(), path.rend()) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    init_globals();
    auto res = BFS();
    if (res.first == -1) cout << "NO" << endl;
    else { 
        cout << "YES" << endl;
        print_result(res);
    }
    // cout << maze << endl;
    return 0;
}

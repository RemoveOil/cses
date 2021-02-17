/*
You are given a map of a building, and your task is to count the number of its rooms. The size of the map is n×m squares, and each square is either floor or wall. You can walk left, right, up, and down through the floor squares.

Input

The first input line has two integers n and m: the height and width of the map.

Then there are n lines of m characters describing the map. Each character is either . (floor) or # (wall).

Output

Print one integer: the number of rooms.

Constraints
1≤n,m≤1000
Example

Input:
5 8
########
#..#...#
####.#.#
#..#...#
########

Output:
3
Graph Algorithms
Counting Rooms
Labyrinth
Building Roads
Message Route
Building Teams
Round Trip
Monsters
Shortest Routes I
...

*/
#include <iostream>
#include <vector>

#define EMPTY ('.')
#define WALL ('#')

using namespace std;

using ulli = unsigned long long int;
using lli = long long int;

int deltaI[4] = {-1, 1, 0 ,0};
int deltaJ[4] = {0, 0, 1 ,-1};

vector<string> map;
int N, M, res;

void read_input() {
    cin >> N >> M;
    for(int i=0;i<N;i++) {
        string ss;
        cin >> ss;
        map.push_back(ss);
    }
}

bool valid(unsigned i, unsigned j) {
    return i < N && j < M;
}

void kaptir(unsigned i, unsigned j) {
    if (!valid(i, j) || map[i][j] == WALL)
        return;
    map[i][j] = WALL;
    for (int index = 0; index < 4; ++index)
        kaptir(i + deltaI[index], j + deltaJ[index]);
}

int main() {
    ios_base::sync_with_stdio(false);
    read_input();
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++) {
            if (map[i][j] == EMPTY) {
                res ++;
                kaptir(i, j);
            }
        }

    cout << res << endl;
    return 0;
}



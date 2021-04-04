#include <iostream>
// #include "../_utils.cpp"

using namespace std;

using ulli = unsigned long long int;
using lli = long long int;

#define MAXN 502

lli matrix[MAXN][MAXN];
int N, M, NUM_QUERIES;

void read() {
    cin >> N >> M >> NUM_QUERIES;
    for (int i = 0, p, q, w; i < M; ++i) {
        cin >> p >> q >> w;
        if (w < matrix[p][q])
            matrix[p][q] = matrix[q][p] = w;
    }
}

void queries() {
    while (NUM_QUERIES--) {
        int a, b;
        cin >> a >> b;
        lli res = matrix[a][b] == INT64_MAX ? -1 : matrix[a][b];
        cout << res << endl;
    }
}

void init() {
    for(int i = 0; i < MAXN; i++) {
        for(int j = 0; j < MAXN; j++)
            matrix[i][j] = INT64_MAX;
        matrix[i][i] = 0;
    }
}

void eval() {
    for(int k = 1; k <= N; k++)
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= N; j++)
                if (matrix[k][j] != INT64_MAX && matrix[i][k] != INT64_MAX)
                    matrix[i][j] = min(
                        matrix[i][j],
                        matrix[i][k] + matrix[k][j]);
}

int main() {
    ios_base::sync_with_stdio(false);
    init();
    read();
    eval();
    queries();
    return 0;
}

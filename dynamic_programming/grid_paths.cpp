#include <iostream>
#include <vector>

using namespace std;

#define BOK '*'

const int MAXN = 1001;

const int MOD = 1e9 + 7;
int n;

vector<vector<int>> dp = vector<vector<int>>(2, vector<int>(MAXN, 0));

void populate_first_line() {
    string line;
    cin >> line;
    int index = line.find(BOK);
    if (index == -1)
        index = dp[0].size();
    fill(begin(dp[0]), begin(dp[0]) + index, 1);
}

void eval() {
    string line;
    cin >> n;
    populate_first_line();
    for (int i=1; i < n; i++) {
        cin >> line;
        for (int j=0;j<n;j++)
            dp[i % 2][j] = (line[j] != BOK) ? ((dp[(i+1) % 2][j] + ((j!=0) ? dp[i % 2][j-1] : 0)) % MOD) : 0;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    eval();
    cout << dp[(n-1) % 2][n-1] << endl;
    return 0;
}

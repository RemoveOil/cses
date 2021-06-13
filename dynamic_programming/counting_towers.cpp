#include <iostream>
#include <vector>


#define COMP_MAX_INT (1e17)
#define MAX 1'000'000

using namespace std;

const int64_t MOD = 1e9+7;//  + 9

vector<vector<int64_t>> dp;

void init() {
    dp = vector<vector<int64_t>>(MAX + 1, vector<int64_t>(2, 0));
    fill(begin(dp[1]), end(dp[1]), 1);
    for (int i = 1; i < MAX; ++i) {
       dp[i+1][0] = ((dp[i][0] << 1)+ 1 * dp[i][1]) % MOD;
       dp[i+1][1] = (1 * dp[i][0] + (dp[i][1] << 2)) % MOD;
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    init();
    int n, t;    
    cin >> t;
    while(t--) {
        cin >> n;
        cout << (dp[n][0] + dp[n][1]) % MOD << endl;
    }
    return 0;
}

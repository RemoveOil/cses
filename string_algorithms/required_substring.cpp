#include <iostream>
#include <vector>

using namespace std;
using lli = long long int;

const int MOD = 1e9 + 7;


int n;
string Q;
vector<vector<int>> dp;
vector<vector<int>> bucket_addresses; // bucket_addresses[i][j]  i. buckettaki bi seye j karakteri eklenince

lli exp(int a, int b) {
    lli res = 1;
    lli x = a;
    while(b) {
        if (b & 1) res = (res * x) % MOD;
        b >>= 1; x = (x * x) % MOD;
    }
    return res;
}

int match_length(const string& Q, const string test) {
    int offset = 0;
    while (offset < test.size()) {
        if (test.substr(offset) == Q.substr(0, test.size() - offset))
            return test.size() - offset;
        ++offset;
    }
    return 0;
}

void init() {
    cin >> n >> Q;
    dp = vector<vector<int>>(n + 1, vector<int>(Q.size() + 1));
    dp[0][0] = 1;
    bucket_addresses = vector<vector<int>>(Q.size(), vector<int>(26));
    for (int i = 0; i < Q.size(); ++i)
        for (int j = 0; j < 26; ++j)
            bucket_addresses[i][j] = match_length(Q, Q.substr(0, i) + (char)('A' + j));
}
6
B[BABA]C
26 -> 676*3 = 2028 -3/5
1800 + 210 + 18
int solve() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < Q.size(); ++j)
            for (int c = 0; c < 26; ++c)
                dp[i + 1][bucket_addresses[j][c]] = (dp[i + 1][bucket_addresses[j][c]] + dp[i][j]) % MOD;

    lli res = exp(26, n);
    for(int i = 0; i < Q.size(); i++) 
        res = (res - dp[n][i] + MOD) % MOD;
    return res;
}


int main() {
    init();
    cout << solve() << endl;
    return 0;
}

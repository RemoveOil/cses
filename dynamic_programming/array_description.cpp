#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
// #include "../_utils.cpp"


using namespace std;


const int MOD = 1e9+7;

int n, m;
vector<int> arr;
vector<vector<int64_t>> dp;

void read() {
    cin >> n >> m;
    copy_n(istream_iterator<int>(cin), n, back_inserter(arr));
    dp = vector<vector<int64_t>>(n + 1, vector<int64_t>(m + 1, -1));
    auto last_element = arr.back();
    if (last_element) {
        fill(begin(dp[n - 1]), end(dp[n - 1]), 0);
        dp[n - 1][last_element] = 1;
    }
    else
        fill(begin(dp[n - 1]), end(dp[n - 1]), 1); 
}

int64_t say(int index, int k) {
    if (k <= 0 || k > m) return 0;
    if (dp[index][k] != -1)
        return dp[index][k];

    if (
        (arr[index] != 0 && arr[index] != k) ||
        (index != 0 && abs(arr[index - 1] - k) > 1))
        return dp[index][k] = 0;


    int64_t res = 0;
    if (arr[index] == 0) {
        for(int i = 1; i <= m; i++) {
            arr[index] = i;
            dp[index][i] = (
                say(index + 1, i + 1) +
                say(index + 1, i) +
                say(index + 1, i - 1)) % MOD;
        }
        arr[index] = 0;
    } else 
        dp[index][k] = (
            say(index + 1, k + 1) +
            say(index + 1, k) +
            say(index + 1, k - 1)) % MOD;
    return dp[index][k];
}

int main() {
    read();
    int64_t res = 0;
    for (int k = 1; k <= m; ++k) {
        res += say(0, k);
        res %= MOD;
    }
    cout << res << endl;
    return 0;
}

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

#define BOK '*'

const int MAXN = 1001;

int n_books, budget;

vector<vector<int>> dp;
vector<int> prices = {0}, pages = {0};


void read() {
    cin >> n_books >> budget;
    dp = vector<vector<int>>(n_books + 1, vector<int>(budget + 1, 0));
    copy_n(istream_iterator<int>(cin), n_books, back_inserter(prices));
    copy_n(istream_iterator<int>(cin), n_books, back_inserter(pages));
}

void eval() {
    for (int i = 1; i <= n_books; i++) {
        for (int j=0; j<=budget; j++) {
            if(j < prices[i]) dp[i][j] = dp[i-1][j];
            else dp[i][j] = max(
                dp[i-1][j],
                dp[i-1][j-prices[i]] + pages[i]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    read();
    eval();
    cout << dp[n_books][budget] << endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

const int OVERFLOW_SAFE_MAX = 1e8;
int num_coins, n;
vector<int> values(1'000'001, OVERFLOW_SAFE_MAX), coins;

void init() {
    values[0] = 0;
    for (int coin : coins) {
        for (int i = coin; i <= n; ++i)
            values[i] = min(values[i], values[i-coin] + 1);
    }
}

void read_input() {
    cin >> num_coins >> n;
    copy_n(istream_iterator<int>(cin), num_coins, back_inserter(coins));
}

int main() {
    read_input();
    init();
    cout << ((values[n] == OVERFLOW_SAFE_MAX) ? -1 : values[n]) << endl;
    return 0;
}

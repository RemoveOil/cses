#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

const int64_t MOD = 1e9 + 7;
int n, num_coins;
vector<int> coins;
vector<int64_t> values(1'000'001);


void init() {
    values[0] = 1;
    for (int coin : coins) {
        for (size_t i = coin; i < values.size(); ++i) {
            values[i] +=  values[i - coin];
            values[i] %= MOD;
        }
    }
}

void read_input() {
    cin >> num_coins >> n;
    copy_n(istream_iterator<int>(cin), num_coins, back_inserter(coins));
}


int main() {
    read_input();
    init();
    cout << values[n];
    return 0;
}

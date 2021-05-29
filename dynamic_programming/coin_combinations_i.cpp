#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
 
using namespace std;
 
const int64_t MOD = 1e9 + 7;
int n, num_coins;
vector<int> coins;
vector<int64_t> values(1'000'001);
 
void fill_index(int index) {
    for (int coin : coins)
        if (index >= coin)
            values[index] +=  values[index - coin];
    values[index] %= MOD;
}
 
void init() {
    values[0] = 1;
    for (size_t i = 1; i < values.size(); ++i)
        fill_index(i);
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
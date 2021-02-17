#include <iostream>
#include <vector>

using namespace std;

using ulli = unsigned long long int;
using lli = long long int;

int main() {
    ios_base::sync_with_stdio(false);
    vector<ulli> table = {0, 0, 6, 28, 96, 252};
    unsigned n; cin >> n;
    ulli last_n = table.size() - 1;

    ulli last_n_sq;
    while (last_n < n) {
        last_n_sq = last_n * last_n;
        table.push_back(
            table[last_n]
            + (5LL*(last_n_sq - 2) + 4LL*(last_n_sq - 3) + (2LL * last_n - 8)*(last_n_sq - 4))
            + (2LL * last_n_sq + last_n - 2));
        last_n++;
    }

    for (unsigned i = 1; i <= n; ++i)
        cout << table[i] << endl;

    return 0;
}

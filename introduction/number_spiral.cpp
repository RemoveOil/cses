#include <iostream>

using namespace std;

using lli = long long int;

// normally i'd write a nicer function: lli solve(unsigned row, unsigned col);
void solve() {
    lli row, col;
    cin >> row >> col;

    lli sq_size = max(row, col);
    lli offset = sq_size + col - row - 1;
    lli coeff = (sq_size % 2) ? 1 : -1;
    lli btm_left = (sq_size / 2 * 2) * (sq_size / 2 * 2) + (sq_size % 2);

    cout << btm_left + coeff * offset << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    while (T--)
        solve();
    return 0;
}

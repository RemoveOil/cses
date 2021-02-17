#include <iostream>

using namespace std;


void solve(unsigned n) {
    if (1 < n && n < 4) {
        cout << "NO SOLUTION" << endl;
        return;
    }

    unsigned i;
    for (i = 2; i <= n; i += 2)
        cout << i << " ";
    for (i = 1; i < n - 1; i += 2)
        cout << i << " ";
    cout << i << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    unsigned n;
    cin >> n;
    solve(n);

    return 0;
}

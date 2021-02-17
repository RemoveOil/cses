#include <iostream>

using namespace std;

using ulli = unsigned long long int;
using lli = long long int;

int main() {
    ios_base::sync_with_stdio(false);
    unsigned t; cin >> t;
    unsigned p, q;

    while (t--) {
        cin >> p >> q;
        if ((p + q) % 3 == 0 && p <= 2*q && q <= 2*p)
            cout << "YES" << endl;
        else 
            cout << "NO" << endl;
    }
    return 0;
}

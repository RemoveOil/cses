#include <iostream>

#define MOD_BASE 1000000007

using namespace std;

using ulli = unsigned long long int;

ulli powar(ulli btm, unsigned top) {
    if (!top)
        return 1;

    btm %= MOD_BASE;
    ulli coef = top % 2 ? btm : 1;
    return (coef * powar(btm * btm, top / 2)) % MOD_BASE;
}


int main() {
    unsigned n; cin >> n;
    cout << powar(2, n) << endl;
    return 0;
}

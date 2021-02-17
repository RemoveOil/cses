#include <iostream>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    unsigned n, res = 0;
    cin >> n;
    while (n) {
        res += n/=5;
    }
    cout << res << endl;

    return 0;
}

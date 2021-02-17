#include <iostream>

using namespace std;



int main() {
    ios_base::sync_with_stdio(false);

    unsigned n, max_so_far, tmp;
    unsigned long long int res = 0;

    cin >> n;
    cin >> max_so_far;
    for (unsigned int i = 1; i < n; ++i) {
        cin >> tmp;
        if (tmp < max_so_far)
            res += max_so_far - tmp;
        else
            max_so_far = tmp;
    }
    cout << res << endl;

    return 0;
}

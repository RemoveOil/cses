#include <iostream>

using namespace std;



int main() {
    ios_base::sync_with_stdio(false);

    unsigned long long int N, sum = 0, tmp;
    cin >> N;
    for (int i = 1; i < N; ++i) {
        cin >> tmp;
        sum += tmp;
    }
    cout << N * (N + 1) / 2 - sum << endl;

    return 0;
}

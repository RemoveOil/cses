#include <iostream>
#include <vector>

using namespace std;

const int OVERFLOW_SAFE_MAX = 1e8;
int n;
vector<int> values(1'000'001, OVERFLOW_SAFE_MAX);

vector<int> split_digits(int i) {
    vector<int> digits;
    while(i) {digits.push_back(i%10); i/=10;}
    return digits;
}

void init() {
    values[0] = 0;
    for (int i = 1; i <= n; ++i) {
        vector<int> digits = split_digits(i);
        for (const auto digit : digits)
            values[i] = min(values[i], values[i - digit] + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    init();
    cout << values[n] << endl;
    return 0;
}

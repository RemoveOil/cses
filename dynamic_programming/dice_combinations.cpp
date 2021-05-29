#include <iostream>
#include <vector>

using namespace std;

const int64_t MOD = 1e9 + 7;
int64_t N, res = 0;
int K_BACK = 6;
vector<int64_t> values(1'000'001);
    
void fill_index(int index) {
    for (int q = index; q >= max(0, index - K_BACK); --q)
        values[index] += values[q];
    values[index] %= MOD;
}

void init() {
    values[0] = 1;
    for (size_t i = 1; i < values.size(); ++i)
        fill_index(i);
}

int main() {
    init();
    cin >> N;
    cout << values[N];
    return 0;
}

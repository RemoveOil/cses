#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>

using namespace std;

using ulli = unsigned long long int;

unsigned two_to_nth(unsigned n) {
    unsigned res = 1;
    while (n--)
        res <<= 1;
    return res;
}

vector<ulli>* read_input() {
    vector<ulli>* numbers = new vector<ulli>();
    unsigned n;
    ulli tmp;
    cin >> n;
    for (unsigned i = 0; i < n; ++i) {
        cin >> tmp;
        numbers->push_back(tmp);
    }

    return numbers;
}

ulli calc_diff(const vector<ulli>& numbers, unsigned encoding, ulli sum) {
    ulli group_sum = 0;
    for (unsigned i = 0, size = numbers.size(), test = 1; i < size; ++i) {
        if (encoding & test)
            group_sum += numbers[i];
        test <<= 1;
    }
    ulli rest = sum - group_sum;
    return rest > group_sum ? rest - group_sum : group_sum - rest;
}

int main() {
    ios_base::sync_with_stdio(false);

    vector<ulli>& numbers = *read_input();
    ulli sum = accumulate(numbers.begin(),numbers.end(),0LL);

    ulli res = 1e12;
    for (unsigned i = 0, num_subsets = two_to_nth(numbers.size()); i < num_subsets; ++i)
        res = min(res, calc_diff(numbers, i, sum));

    cout << res << endl;

    return 0;
}

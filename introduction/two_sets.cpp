#include <iostream>
#include <vector>

using namespace std;

// declaring unsigned int?
void print_set(const vector<bool> &reference_set, bool side) {
    unsigned int last_match_index = 0, num_matches = 0, i;
    unsigned int size = reference_set.size();
    for (i = 1; i < size; ++i) {
        if (reference_set[i] == side) {
            last_match_index = i;
            num_matches++;
        }
    }

    cout << num_matches << endl;
    for (i = 1; i < last_match_index; ++i)
        if (reference_set[i] == side)
            cout << i << " ";
    cout << i << endl;

}

// learn some typedef or using?

void solve(unsigned long long int n) {
    if ((n * n + n) % 4) {
        cout << "NO" << endl;
        return;
    }

    vector<bool> reference_set(n + 1, false);
    unsigned long long int required = (n * n + n) / 4;
    unsigned i = n;
    while (required >= i) {
        reference_set[i] = true;
        required -= i--;
    }
    if (required)
        reference_set[required] = true;

    cout << "YES" << endl;
    print_set(reference_set, true);
    print_set(reference_set, false);
}

int main() {
    unsigned long long int n;cin >> n;
    solve(n);
    return 0;
}

#include <iostream>
#include <vector>
// #include "../_utils.cpp"

using namespace std;

// needs to explain even indices

// When even == ture
//    radii[i]'s symmetrical center is between the indices i and i - 1, filling radii in indice i.
void manacher_helper(const string& s, vector<size_t> &radii, bool even = true) {
    int l = 0, r = -1;
    for (auto i = 0; i < s.size(); ++i) {
        radii[i] = (i > r) ? (size_t) !even : min(radii[r - i + l + even], (size_t)(r - i + 1));
        while(0 <= i - radii[i] - even && i + radii[i] < s.size()
                && s[i - radii[i] - even] == s[i + radii[i]]) {
            l = i - radii[i] - even;
            r = i + radii[i];
            radii[i]++;
        }
    }
}

vector<vector<size_t>> manacher(const string& s) {
    vector<vector<size_t>> res(2, vector<size_t>(s.size()));
    manacher_helper(s, res[0], false); // res[0][i] == k -> length == 2k - 1
    manacher_helper(s, res[1]); // res[1][i] == k -> length == 2k
    return res;
}

vector<size_t> calculate_z(const string& s) {
    vector<size_t> z(s.size());
    size_t l = 0, r = 0;
    for (auto i = 1; i < s.size(); ++i) {
        z[i] = max((size_t)0, min(z[i - l], r - i + 1));
        while(i + z[i] < s.size() && s[z[i]] == s[i+z[i]]) {
            l = i; r = i + z[i]; z[i]++;
        }
    }
    return z;
}

#include <iostream>
#include <numeric>
#include <iterator>
// #include "../_utils.cpp"
#include "../structures/string_utils.cpp"

using namespace std;

pair<size_t, size_t> get_window(const vector<size_t> &radii, bool odd = true) {
    size_t l = 1, r = 0;
    for (int i = 0; i < radii.size(); ++i) {
        if (r - l + 1 < radii[i] * 2 - odd) {
            l = i - radii[i] + odd;
            r = i + radii[i] - 1;
        }
    }
    return {l, r};
}

string eval(const string& s) {

    auto radii = manacher(s);
    auto [l0, r0] = get_window(radii[0]);
    auto [l1, r1] = get_window(radii[1], false);

    string res;
    if (r0 - l0 > r1 - l1) res = s.substr(l0, r0 - l0 + 1);
    else res = s.substr(l1, r1 - l1 + 1);

    return res;
}



int main() {
    ios_base::sync_with_stdio(false);
    string s; cin >> s;

    
    cout << eval(s) << endl;

    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

vector<size_t> calculate_z(const string& s) {
    vector<size_t> z(s.size());
    size_t x = 0, y = 0;
    for (auto i = 1; i < s.size(); ++i) {
        z[i] = max((size_t)0, min(z[i - x], y - i + 1));
        while(i + z[i] < s.size() && s[z[i]] == s[i+z[i]]) {
            x = i; y = i + z[i]; z[i]++;
        }
    }
    return z;
}

int main() {
    string text; cin >> text;
    auto z = calculate_z(text);
    for (int i = text.size() - 1; i >= 0; --i)
        if (z[i] + i == text.size()) cout << z[i] << " ";

    return 0;
}

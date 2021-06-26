#include <iostream>
#include <vector>

using namespace std;
// aad == 1
// aacaacaa
vector<size_t> compute_prefix(const string& pattern) {
    vector<size_t> pi(pattern.length());
    size_t k = 0;
    for (auto i = 1; i < pi.size(); ++i) { // i + 1 matches
        while (k > 0 && pattern[k] != pattern[i])
            k = pi[k-1];
        if (pattern[k] == pattern[i])
            k++;
        pi[i] = k;
    }
    return pi;
}

vector<size_t> kmp_matcher(const string& text, const string& pattern) {
    auto n = text.length();
    auto m = pattern.length();

    auto pi = compute_prefix(pattern);
    vector<size_t> matches;

    size_t q = 0;
    for (size_t i = 0; i < n; i++) {
        while (q > 0 && pattern[q] != text[i]) q = pi[q - 1];
        if (pattern[q] == text[i]) q++;
        if (q == m) {
            matches.push_back(i - m + 1);
            q = pi[q - 1];
        }
    }

    return matches;
}
// aabcaabc

int main() {
    string text, pattern;
    cin >> text >> pattern;
    cout << kmp_matcher(text, pattern).size() << endl;
    return 0;
}

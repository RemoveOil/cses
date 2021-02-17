#include <iostream>
#include <vector>

using namespace std;

using ulli = unsigned long long int;
using lli = long long int;

void solve(const string &n) {
    string palindrome;
    int freqs[26] = {0};
    for (char c: n)
        freqs[c - 'A']++;

    int num_odd = 0;
    for (int i = 0; i < 26; ++i)
        num_odd += freqs[i] % 2;

    if (num_odd > 1) {
        cout << "NO SOLUTION" << endl;
        return;
    }

    char odd_char = '\0', tmp_char;
    int odd_freqs = 0;
    for (int i = 0; i < 26; ++i) {
        char tmp_char = i + 'A';
        if (freqs[i] % 2) {
            odd_char = tmp_char;
            odd_freqs = freqs[i];
        }
        else {
            int r = freqs[i] / 2;
            while (r--)
                palindrome.push_back(tmp_char);
        }
    }

    cout << (
        palindrome +
        string(odd_freqs, odd_char) +
        string(palindrome.rbegin(), palindrome.rend())) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    string n; cin >> n;
    solve(n);
    return 0;
}

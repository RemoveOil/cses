#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

using ulli = unsigned long long int;
using lli = long long int;


vector<pair<char, int>>* create_unique_letters_with_freqs(const string &str) {
    vector<int>* _freqs = new vector<int>(26, 0);
    vector<int>& freqs = *_freqs;
    for (char c : str)
        freqs[c - 'a']++;


    vector<pair<char, int>>* unique_letters_with_freqs = new vector<pair<char, int>>();
    for (int i = 0; i < 26; ++ i)
        if (freqs[i])
            unique_letters_with_freqs->push_back(make_pair(i + 'a', freqs[i]));

    return unique_letters_with_freqs;
}

int calc_num_perms(const vector<pair<char, int>> &unique_letters, int str_length) {
    int factorials[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};

    int res = factorials[str_length];
    for (const auto &letter : unique_letters)
        res /= factorials[letter.second];

    return res;
}


void generate_permutations(vector<pair<char, int>> &unique_letters, string &buffer, int n_left) {
    if (!n_left) {
        cout << buffer << endl;
        return;
    }

    for (auto &letter : unique_letters) {
        if (letter.second) {
            letter.second--;
            buffer.push_back(letter.first);
            generate_permutations(unique_letters, buffer, n_left - 1);
            letter.second++;
            buffer.pop_back();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    string str, buffer = "";
    cin >> str;

    vector<pair<char, int>>* unique_letters_with_freqs = create_unique_letters_with_freqs(str);
    cout << calc_num_perms(*unique_letters_with_freqs, str.length()) << endl;
    generate_permutations(*unique_letters_with_freqs, buffer, str.length());
    return 0;
}

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
// #include "../_utils.cpp"


using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode> children;
    bool word;
};

vector<int64_t> dp;
TrieNode root;
string target;

const int64_t MOD = 1e9 + 7;

void insert_word(TrieNode& root, const string& word) {
    TrieNode* it = &root;
    for (char letter : word) {
        if (it->children.find(letter) == it->children.end())
            it->children[letter] = TrieNode{};
        it = &it->children[letter];
    }
    it->word = true;
}

// void traverse_from_index(int start_index) {
//     TrieNode* it = root;
//     for (int i = start_index; i < target.size(); ++i) {
//         char letter = target[i];
//         if (it->children.find(letter) == it->children.end())
//             return;
//         it = it->children[letter];
//         if (it->word)
//             dp[i+1] = (dp[i+1] + dp[start_index]) % MOD;
//     }
// }

void read() {
    string s;
    cin >> target;

    int k;
    cin >> k;
    while(k--) {
        cin >> s;
        insert_word(root, s);
    }
    dp = vector<int64_t>(target.size() + 1);
    dp[0] = 1;
}

// "abc" "ab" "qwe"
void print_all(TrieNode& root, string& buffer) {
    if (root.word) cout << buffer << endl;
    for (auto [character, cocuk] : root.children) {
        buffer.push_back(character);
        print_all(cocuk, buffer);
        buffer.pop_back();
    }
}

// void eval() {
//     for(int i=0;i<target.size();i++)    
//         traverse_from_index(i);
//     cout << dp[target.size()] << endl;
// }

int main() {
    read();
    // eval();
    string s;
    print_all(root, s);
    return 0;
}

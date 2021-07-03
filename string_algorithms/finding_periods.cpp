#include <iostream>
#include <iterator>
#include "../structures/string_utils.cpp"
// #include "../_utils.cpp"

using namespace std;

string s;


vector<int> find_everything() {
    vector<size_t> z = calculate_z(s);
    vector<int> res;
    for(int i = 1; i < z.size(); i++)
        if (z[i] + i == z.size())
            res.push_back(i);
    res.push_back(s.size());
    return res;
}

// alias g++17='g++ -std=c++17'
int main() {
    ios_base::sync_with_stdio(false);
    cin >> s;
    vector<int> res = find_everything();
    copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
    return 0;
}

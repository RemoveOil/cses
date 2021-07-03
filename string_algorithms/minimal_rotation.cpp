#include <iostream>
// #include "../_utils.cpp"
#include "../structures/string_utils.cpp"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    string s;
    cin >> s;
    auto p = sort_cyclic_shifts(s);
    cout << s.substr(p[0]) + s.substr(0, p[0]) << endl;
    return 0;
}

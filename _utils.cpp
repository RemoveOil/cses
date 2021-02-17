#include <iostream>
#include <vector>

using namespace std;

using ulli = unsigned long long int;
using lli = long long int;

template <class T>
void print_vector(const vector<T> &v, bool one_item_per_line=false) {
    if (!v.size())
        return;

    char sep = one_item_per_line ? '\n' : ' ';
    typename vector<T>::const_iterator it = v.begin(), end = prev(v.end());
    while (it != end) {
        cout << *it << sep;
        ++it;
    }
    cout << *it << endl;
}

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "../structures/geometry.cpp"

using namespace std;
using lli = long long int;

lli pol_area(const vector<Point> &points) {
    lli res = 0;
    for(int i = 0, n = points.size(); i < n; i++) {
        res += points[i].x * points[(i+1) % n].y;
        res -= points[i].y * points[(i+1) % n].x;
    }
    return res;
}


int main() {
    int n; cin >> n;
    vector<Point> points;
    copy_n(istream_iterator<Point>(cin), n, back_inserter(points));
    cout << pol_area(points);
    return 0;
}
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
    return abs(res);
}

lli gcd(lli p, lli q) {
    if (!q)
        return p;
    return gcd(q, p % q);
}

lli boundary_points(const vector<Point>& points) {
    lli res = points.size();
    for(int i = 0, n = points.size(); i < n; i++) {
        lli dx = abs(points[i].x - points[(i + 1)%n].x);
        lli dy = abs(points[i].y - points[(i + 1)%n].y);
        res += gcd(dx, dy) - 1;
    }
    return res; 
}

lli interior_points(const vector<Point>& points, lli b) {
    lli pol = pol_area(points);
    return (pol + 2 - b) / 2;
}

int main() {
    int n; cin >> n;
    vector<Point> points;
    copy_n(istream_iterator<Point>(cin), n, back_inserter(points));
    lli b = boundary_points(points);
    lli i = interior_points(points, b);
    cout << i << " " << b << endl;
    return 0;
}
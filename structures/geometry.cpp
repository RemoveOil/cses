#include <iostream>
#include <cmath>

using namespace std;

using lli = long long int;

struct Point {
    lli x, y;
    Point(lli _x, lli _y): x(_x), y(_y) {}
    Point(): x(0), y(0) {}


    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }

    friend istream& operator>>(istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }

    double dist_to_origin() {
        return sqrt(x * x + y * y);
    }
};
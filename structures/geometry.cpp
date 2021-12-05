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

    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    lli operator*(const Point& other) const {
        return x*other.x + y*other.y;
    }

    Point operator*(const lli c) const {
        return Point(c*x, c*y);
    }

    friend ostream& operator << (ostream& os, const Point& p) {
        return os << p.x << " " << p.y;
    }

    friend istream& operator>>(istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }

    auto dist_to_origin() -> double { return sqrt(dist_e2()); }
    auto dist_e2() -> lli { return (x * x + y * y); }
};

constexpr lli calc_det(const Point& x, const Point& y) { return (x.x * y.y - x.y * y.x); }
int orientation(const Point& x, const Point& y, const Point& z) {
    lli det = calc_det(y - x, z - x);
    if (det > 0)    return 1;
    if (det < 0)    return -1;
    return 0;
}

// True iff w1 is on [q1, q2]
bool in_between(const Point& q1, const Point& q2, const Point& w1) {
    double dst1 = (q2-q1).dist_to_origin();
    double dst2 = (w1-q1).dist_to_origin();
    double dst3 = (w1-q2).dist_to_origin();
    return !(dst2 + dst3 > dst1);
}

bool segments_intersect(const Point& q1, const Point& q2, const Point& w1, const Point& w2) {
    int o_q1q2w1 = orientation(q1, q2, w1);
    int o_q1q2w2 = orientation(q1, q2, w2);
    int o_w1w2q1 = orientation(w1, w2, q1);
    int o_w1w2q2 = orientation(w1, w2, q2);

    // double oh
    if (!o_q1q2w1 and !o_q1q2w2)
        return (
            in_between(q1, q2, w1)
            or in_between(q1, q2, w2)
            or in_between(w1, w2, q1)
            or in_between(w1, w2, q2));
    // LL/RR
    if ((o_q1q2w1 == o_q1q2w2) or (o_w1w2q1 == o_w1w2q2))
        return false;

    // YUKSEK TESTOSTERON BI NOTASYON.
    return true;
}

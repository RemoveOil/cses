#include <iostream>
#include "../_utils.cpp"

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
};

lli calc_det(Point x, Point y) {
    return (x.x * y.y - x.y * y.x);
}

string run_test() {
    Point q, w, e;
    cin >> q >> w >> e;
    lli det = calc_det(w - q, e - q); 

    if (det > 0)    return "LEFT";
    if (det < 0)    return "RIGHT";
    return "TOUCH";
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) cout << run_test() << endl;
    return 0;
}


#include<algorithm>
#include<iostream>
#include<iterator>
#include<vector>
#include<set>
#include<list>
#include "../structures/geometry.cpp"

using namespace std;

vector<Point> points, hull;

void prep_points() {
    int n; cin >> n;
    copy_n(istream_iterator<Point>(cin), n, back_inserter(points));
    sort(begin(points), end(points), [](const Point& q, const Point& p) {
        return (q.x == p.x) ? (q.y < p.y) : (q.x < p.x);
    });
}

void place_point_on_hull(int i) {
    while(hull.size() > 1 && orientation(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) == 1)
        hull.pop_back();
    hull.push_back(points[i]);
}

void convex_hull() {
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    for(int i = 2, size = points.size(); i < size; ++i)
        place_point_on_hull(i);
    for(int i = points.size() - 2; i > -1; --i)
        place_point_on_hull(i);
    hull.pop_back();
}

int main() {
    prep_points();
    convex_hull();
    cout << hull.size() << endl;
    copy(begin(hull), end(hull), ostream_iterator<Point>(cout, "\n"));
}

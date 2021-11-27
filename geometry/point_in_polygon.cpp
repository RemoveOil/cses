#include<iostream>
#include<algorithm>
#include<iterator>
#include<vector>
#include "../structures/geometry.cpp"
using namespace std;


string eval_point(const vector<Point>& polygon, const Point& w) {
    int cnt = 0; 
    Point dallas = Point(1e9+7, 1e9-17);
    for(int i = 0, n = polygon.size(); i < n; i++) {
        if (in_between(polygon[i], polygon[(i+1) % n], w))
            return "BOUNDARY";
        if (segments_intersect(polygon[i], polygon[(i+1) % n], w, dallas))
            ++cnt;
    }
    return cnt % 2 ? "INSIDE" : "OUTSIDE";
}


int main() {
    int n, m;
    vector<Point> polygon;
    Point query;
    cin >> n >> m;
    copy_n(istream_iterator<Point>(cin), n, back_inserter(polygon));
    while(m--) {
        cin >> query;
        cout << eval_point(polygon, query) << endl;
    }
}
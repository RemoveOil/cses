#include<algorithm>
#include<iostream>
#include<iterator>
#include<vector>
#include<set>
#include<list>
#include "../structures/geometry.cpp"

using namespace std;


auto cmp = [](const Point& q, const Point& p) { return (q.y == p.y) ? (q.x < p.x) : (q.y < p.y);};
set<Point, decltype(cmp)> candidates(cmp);
vector<Point> points;
list<set<Point>::iterator> schindlers_list;
// int iLeft = 0; candidates.erase(points[iLeft++]);

void put_schindlers_list(const Point& p) {
    auto address = candidates.insert(p);
    schindlers_list.push_back(address.first);
}

void soldakileri_cikar(const Point& p, lli query_d) {
    while(query_d < p.x - schindlers_list.front()->x) {
        candidates.erase(schindlers_list.front()); 
        schindlers_list.pop_front();
    }
}


lli check_dist(const Point& p, lli query_d) {
    lli dist = 9e18+1;
    auto it = candidates.lower_bound({0, p.y - query_d});
    while (it != end(candidates) and (it->y <= p.y + query_d)) {
        dist = min(dist, (p - *(it++)).dist_e2());
    }
    return dist;
}

lli sweep_line() {
    lli d = (points[1] - points[0]).dist_e2();
    lli query_d = sqrt(d) + 1;
    put_schindlers_list(points[0]);

    for (int i = 1, size = points.size(); i < size; ++i) {
        soldakileri_cikar(points[i], query_d);
        d = min(check_dist(points[i], query_d), d); // bakarken itaretor kullanabiliriz.
        query_d = sqrt(d) + 1;
        put_schindlers_list(points[i]);
    }
    return d;
}

int main() {
    int n; cin >> n;
    copy_n(istream_iterator<Point>(cin), n, back_inserter(points));
    sort(begin(points), end(points), [](const Point& q, const Point& p) {
        return (q.x == p.x) ? (q.y < p.y) : (q.x < p.x);
    });
    cout << sweep_line() << endl;
}

#include <iostream>
#include <vector>

using namespace std;

vector<int> nodes, cnt;
int N, M;

int find_parent(int q) {
    while (nodes[q] != q) {
        nodes[q] = nodes[nodes[q]];
        q = nodes[q];
    }
    return q;
}

void unionz(int p, int q) {
    int pp = find_parent(p);
    int pq = find_parent(q);
    if (pp == pq) return;
    if (cnt[pp] < cnt[pq]) swap(pp, pq);
    cnt[pp] += cnt[pq];
    nodes[pq] = pp;
}

void solve () {
    cin >> N >> M;
    nodes.resize(N+1);
    cnt.resize(N+1);
    fill(cnt.begin(), cnt.end(), 1);
    for(int i=1;i<=N;i++) nodes[i] = i;
    int a, b;
    for(int i=0;i<M;i++) {
        cin >> a >> b;
        unionz(a,b);
    }

    vector<int> res;
    for(int i=1;i<=N;i++)
        if (i == nodes[i])
            res.push_back(i);

    cout << res.size() - 1 << endl;
    for(auto i=0 ; i < res.size()-1; i++)
        cout << res[i] << " " << res[i+1] << endl;
}



int main() {
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}

#include <iostream>
#include <vector>
#include <functional>
#include <climits>

#include "../_utils.cpp"
using namespace std;



template<class T>
struct segment {
    using BinaryOperation = function<T(T,T)>;
    vector<T> vals;
    vector<T> tree;
    BinaryOperation _agg;
    int N;
    T _id_elem;

    void init(const vector<T> values, T id_elem, BinaryOperation agg) {
        _agg = agg;
        _id_elem = id_elem;
        vals = values;
        N = values.size() - 1;
        tree.resize(2*N + 1);
        _init_tree(1);
    }

    segment(istream &stream, T id_elem, BinaryOperation agg) {
        vector<T> values;
        stream >> N;
        values.resize(N + 1);
        for (int i = 1; i <= N; i++) stream >> values[i];
        init(values, id_elem, agg);
    }

    // values[0] must be a dummy element.
    segment(const vector<T> values, T id_elem, BinaryOperation agg) { init(values, id_elem, agg); }

    T _init_tree(int k) {
        if (k == N) return tree[k] = tree[2*k] = vals[N];
        if (k > N) return tree[k] = vals[k - N];
        return tree[k] = _agg(_init_tree(2*k), _init_tree(2*k+1));
    }

    void update(int k, int x) {
        k += N;
        tree[k] = x;
        for (k >>= 1; k >= 1; k >>= 1)
            tree[k] = _agg(tree[2*k], tree[2*k+1]);
    }

    void add(int k, int x) {
        k += N;
        tree[k] += x;
        for(k >>= 1; k >= 1; k >>= 1)
            tree[k] = _agg(tree[2*k], tree[2*k+1]);
    }

    T query(int a, int b) {
        a += N; b += N;
        T res = _id_elem;
        while (a <= b) {
            if (a % 2) res = _agg(res, tree[a++]);
            if (!(b % 2)) res = _agg(res, tree[b--]);
            a >>= 1; b >>= 1;
        }
        return res;
    }

    friend ostream& operator<<(ostream& os, const segment<T>& sg) {
        os << sg.vals;
        os << sg.tree;
        return os;
    }
};




int main(int argc, char const *argv[]) {
    

    segment<int> S(
        cin,
        INT_MIN,
        [&](int p, int q) { return max(p , q);});
    // segment<int> S(minn<>{});
    // segment<int> S(maxx<>{});
    cout << S << "naber"<< endl;
    // cout << S.query(1, 8) << endl;
    vector<vector<int>> nope {{1,2,3,4}, {2,4,5,2}, {10,3,1,2}};
    vector<int> dope {1,2,3,4};
    cout << ' ' << nope;


    
    return 0;

}

/*
In file included from segment.cpp:6:
./_utils.cpp:20:12: error: invalid operands to binary expression ('std::__1::ostream' (aka 'basic_ostream<char>') and
      'const std::__1::vector<int, std::__1::allocator<int> >')
        os << *it << endl;
        ~~ ^  ~~~

*/
#include <bits/stdc++.h>
using namespace std;

template<class T>
struct segment{
    using BinaryOperation = function<T(T,T)>;
    segment(BinaryOperation agg) : _agg(agg) {}
    vector<T> vals;
    vector<T> tree;
    BinaryOperation _agg;
    int N;


    void array_init() {
        cin >> N;
        vals.resize(N+1);
        tree.resize(2*N+1);
        for(int i=1;i<=N;i++) cin >> vals[i];
        init(1);
    }
    
    T init(int k) {
        if (k == N) return tree[k] = tree[2*k] = vals[N];
        if (k > N) return tree[k] = vals[k - N];
        return tree[k] = _agg(init(2*k), init(2*k+1));
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
        T res = 0;
        while (a <= b) {
            if (a % 2) res = _agg(res, tree[a++]);
            if (!(b % 2)) res = _agg(res, tree[b--]);
            a >>= 1; b >>= 1;
        }
        return res;
    }
    
    void print() {
        for(auto elem : vals) cout << elem << " ";
        cout << endl;
        for(auto elem : tree) cout << elem << " ";
        cout << endl;
    }
};

template<typename T=void>
struct minn;

template<>
struct minn<void> {
    template<typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    -> decltype(min(std::forward<T>(lhs), std::forward<U>(rhs))) {
        return min(std::forward<T>(lhs), std::forward<U>(rhs));
    }
};

template<typename T=void>
struct maxx;


template<>
struct maxx<void> {
    template<typename T, typename U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
    -> decltype(max(std::forward<T>(lhs), std::forward<U>(rhs))) {
        return max(std::forward<T>(lhs), std::forward<U>(rhs));
    }
};



// range updates with difference array is enough [a, b] by k is diff[a] + k and diff[b+1] - k


int main(int argc, char const *argv[]) {


    segment<int> S(plus<>{});
    // segment<int> S(minn<>{});
    // segment<int> S(maxx<>{});
    S.array_init();
    cout << S.query(1, 8) << endl;


    
    return 0;

}

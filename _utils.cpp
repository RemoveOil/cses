#include <iostream>
#include <vector>
#include <type_traits>

using namespace std;

#define DEBUG(name) print(#name, name)
#define DEBUGN(name) print(#name, name, true)

template<typename>
struct is_std_vector : std::false_type {};

template<typename T, typename A>
struct is_std_vector<std::vector<T,A>> : std::true_type {};
// typedef integral_constant<bool,false> false_type;

template<class T>// T = vector<int>
ostream& operator<<(ostream& os, const vector<T> &v) {
    if (!v.size())
        return os;

    char sep = ' ';
    typename vector<T>::const_iterator it = v.begin(), end = prev(v.end());
    while (it != end) {
        os << *it;
        if (!is_std_vector<T>::value)
            os << sep;
        ++it;
    }

    os << *it << endl;
    return os;
    
}

template<class T>
void print(string var_name, T var, bool newline=false) {
    cout << var_name << ':' << (newline ? '\n' : ' ') << var; 
}

/*
int main() {

    vector<vector<int>> nope {{1,2,3,4}, {2,4,5,2}, {10,3,1,2}};
    // vector<int> nope {1,2,3,4};
    typedef int not_vec;
    std::cout << is_std_vector<decltype(nope)>::value << is_std_vector<not_vec>::value << endl;
    // cout << nope;
    DEBUGN(nope);
    cout <<"burdayiz?";
}*/



// void __possible_experiments(const vector<int> &vec_of_nums) {
//     std::copy(  vec_of_nums.begin(),
//                     vec_of_nums.end(),
//                     std::ostream_iterator<int>(std::cout," "));

// }

// namespace utils { }

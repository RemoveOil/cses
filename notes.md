# Structures

## Graph
Utilities to consider:
- construct new graph with all edges reversed(i.e directions)
- take negative of all edges and construct a new graph from it


## Segment Tree Binary Operation

It helps you implement new binary operations for segment tree. The main feature of these functions is that it can automatically deduce type of the binary function from its parameter types.
```c++
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
```


## Misc.
- template typename vs class
- template constraints?
- false type / true type -> singletons?
- makefile bundling local libs.
  - Write a script that doest this. gcc doesn't like picking fav libs (:
- Implement? Interesting Algs
  -  traveling salesman
  -  euler circuit(this is a loop)
- Git submodules - for registerign repos as dependencies.


# "Ft__containers"

C++ containers, tout simplement!

## Summary:
C++ containers each have a specific use.
To ensure that you understand them, you will implement them!

## Chapter I Objectives

In this project, you will implement a few C++ containers from the Standard Template Library (STL).
You must base your implementation on the structure of the original containers. If a part of the canonical form of Coplien is not present, do not include it.
Remember, you must adhere to the C++98 standard. Therefore, any newer features should NOT be implemented, but any C++98 functionality (even obsolete) is expected.


## Chapter II Mandatory Part

Implement the following containers and make corresponding `<container>.hpp` files:
- vector
  You do not have to specialize ([`vector<bool>`](https://cplusplus.com/reference/vector/vector-bool/?kw=vector%3Cbool%3E#google_vignette)).
- map
- stack
  It will use your vector class as the default underlying container. However, it will remain compatible with other containers, including those in the STL.
  
You must also implement:
- ([`iterator_traits`](https://legacy.cplusplus.com/reference/iterator/iterator_traits/))
- ([`reverse_iterator`](https://en.cppreference.com/w/cpp/iterator/reverse_iterator))
- ([`enable_if`](https://en.cppreference.com/w/cpp/types/enable_if))
  Yes, this involves C++11, but you should be able to redo it in C++98. The goal is to introduce you to SFINAE.
- ([`is_integral`](https://www.cplusplus.com/reference/type_traits/is_integral/))
- ([`equal`](https://en.cppreference.com/w/cpp/algorithm/equal)) and/or ([`lexicographical_compare`](https://cplusplus.com/reference/algorithm/lexicographical_compare/))
- ([`std::pair`](https://cplusplus.com/reference/utility/pair/pair/))
-([`std::make_pair`](https://cplusplus.com/reference/utility/make_pair/))


### Prerequisites
- The namespace must be `ft`.
- The internal data structure used for each of your containers must be consistent and justifiable (using just an array for map is not accepted).
- You cannot implement more public functions than standard containers have. Any additional functions must be private or protected. Each public function and variable must be justified.
- All member functions, non-member functions, and overloads of a container are expected.
- You must adhere to the original naming. Pay attention to details.
- If the container has an iterator system, you must implement it.
- You must use `std::allocator`.
- For non-member overloads, the `friend` keyword is allowed. Each use of `friend` must be justified and will be checked during evaluation.
- Of course, to implement `map::value_compare`, the `friend` keyword is allowed.

### Testing
- You must also provide your own tests, at least one `main.cpp`, for your evaluation. You must go beyond the example main given!
- You must create two binaries running the same tests: one with your containers and the other with standard containers.
- Compare outputs and performance/timing (your containers can be up to 20 times slower than the originals).
- To test your containers: `ft::<container>`.


## Bonus Part

You will receive bonus points if you implement one more container:

set
However, this time, a ([red-black tree](https://www.programiz.com/dsa/red-black-tree))is mandatory. 

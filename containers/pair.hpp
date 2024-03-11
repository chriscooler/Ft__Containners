#ifndef PAIR_HPP
# define PAIR_HPP

//https://legacy.cplusplus.com/reference/utility/pair/
namespace ft 
{
	template <class T1, class T2> struct pair 
    {
        typedef T1	first_type;
        typedef T2	second_type;

        first_type		first;
        second_type		second;

        //Default constructor
        pair(void) : first(), second() { };

        //Copy constructor:
        template < class U, class V >
            pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) { };

        //Fill constructor:
        pair(const first_type &a, const second_type &b) : first(a), second(b){ };
        
        pair& operator= (const pair& pr)  
        {
            if (this != &pr) 
            {
                this->first = pr.first;
                this->second = pr.second;
            }
            return (*this);
        }
    };

    template <class T1, class T2>
    bool operator== (pair<T1, T2> const &rhs, pair<T1, T2> const &lhs) 
    {
        return (rhs.first == lhs.first && rhs.second == lhs.second);
    }

    template <class T1, class T2>
    bool operator!= (pair<T1, T2> const &rhs, pair<T1, T2> const &lhs) 
    {
        return (!(rhs == lhs));
    }
    
    template <class T1, class T2>
    bool operator< (pair<T1, T2> const &rhs, pair<T1, T2> const &lhs)
    {
        return (rhs.first < lhs.first || (!(lhs.first < rhs.first) && rhs.second < lhs.second));
    }

    template <class T1, class T2>
    bool operator<= (pair<T1, T2> const &rhs, pair<T1, T2> const &lhs)
    {
        return (!(lhs < rhs));
    }
	
	template <class T1, class T2>
    bool operator> (pair<T1, T2> const &rhs, pair<T1, T2> const &lhs)
    {
        return (lhs < rhs);
    }

	template <class T1, class T2>
    bool operator>= (pair<T1, T2> const &rhs, pair<T1, T2> const &lhs)
    {
        return (!(rhs < lhs));
    }

    // make pair
	template <class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y) 
    { 
        return ( pair<T1, T2>(x, y) ); 
    }
}

#endif

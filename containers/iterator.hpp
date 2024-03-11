#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>

//  -----------------------------------------------------------------------
    // ### `iterator`:
    // 1. **Purpose**: Represents a means of iterating over a sequence of elements in C++ containers.
    // 2. **Interface**: Provides operations for accessing and manipulating elements in a container, including dereferencing (`*`), incrementing (`++`), and decrementing (`--`).
    // 3. **Abstraction**: Abstracts the process of traversal, enabling uniform access to container elements regardless of the underlying container type.
    // 4. **Categories**: Iterators can belong to different categories such as input, output, forward, bidirectional, random access, etc., depending on the capabilities they offer.
    // 5. **Usage**: Used extensively with standard library containers like vectors, lists, and maps, as well as algorithms like `std::find`, `std::sort`, etc.
    
    // ### `iterator_traits`:
    // 1. **Purpose**: Provides a uniform interface to obtain information about iterators, such as iterator category and value type.
    // 2. **Template Meta-Programming**: Utilizes template meta-programming techniques to extract traits from iterator types.
    // 3. **Member Types**: Defines member types like `iterator_category`, `value_type`, `difference_type`, `pointer`, and `reference`, which help algorithms operate efficiently with different iterator types.
    // 4. **Specialization**: Allows customization for user-defined iterator types by specializing `iterator_traits`.
    // 5. **Example**: Used internally by standard library algorithms to adapt their behavior according to the properties of iterators passed to them.
    
    //  https://legacy.cplusplus.com/reference/iterator/
    //  https://legacy.cplusplus.com/reference/iterator/iterator_traits/
//  -----------------------------------------------------------------------
namespace ft
{
    // Iterator bass class
    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    class iterator 
    {
        public:
            typedef T			    value_type;
            typedef Distance	    difference_type;
            typedef Pointer		    pointer;
            typedef Reference	    reference;
            typedef Category	    iterator_category;
            
        protected:
            pointer				    _ptr;
    };

    // Iterator category tag
    class input_iterator_tag {};
	class output_iterator_tag {};
	class forward_iterator_tag {};
	class bidirectional_iterator_tag {};
	class random_access_iterator_tag {};

    // struct iterator traits
    template <class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::value_type			value_type;
        typedef typename Iterator::difference_type		difference_type;
        typedef typename Iterator::pointer				pointer;
        typedef typename Iterator::reference			reference;
        typedef typename Iterator::iterator_category	iterator_category;
    };

	template<class T> 
    struct iterator_traits<T*>
    {
        typedef T						        value_type;
        typedef ptrdiff_t				        difference_type;
        typedef T*						        pointer;
        typedef T&						        reference;
        typedef random_access_iterator_tag		iterator_category;		
    };
	
	template<class T> 
    struct iterator_traits<const T*> 
    {
        typedef T						        value_type;
        typedef ptrdiff_t						difference_type;
        typedef const T*					    pointer;
        typedef const T&					    reference;
        typedef random_access_iterator_tag	    iterator_category;		
    };

    
    template<class InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    distance (InputIterator first, InputIterator last) 
    {
        typename iterator_traits<InputIterator>::difference_type size = 0;
        while (first != last)
        {
            first++;
            size += 1;
        }
        return (size);
    };
}



#endif
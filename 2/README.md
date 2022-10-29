# Assignment

A.

Create a hash class, whose instances will serve as a functors for calcullation of hash values of class std::tuple
The hash should be calculated using a combination of hash values of each of its items' values
The hash of a value should be retrieved by applying the std::hash functor
For the combination of items hashes use the XOR operation
You can use C++17 including the if constexpr

B.

Given a code template, create a meta function TupleElement<I, T> which will evaluate the type of the "I"th element of class Tuple passed as template argument T
The class TupleElement has to be a friend class of Tuple (see template)
Examples:
TupleElement<1, Tuple<int, double, bool> >::type has to be evaluated as double
TupleElement<0, Tuple<const long&> >::type has to be evaluated as const long&

C.

Function get, which returns a reference to "I"th element of Tuple can look like this in C++17:

<code>
template <size_t I, typename T>
auto& get(T& tuple)
{
   if constexpr (I == 0)   
      return tuple.t_;      
   else   
      return get<I - 1>(tuple.ts_);      
}
</code>


In C++11 or C++14 we cannot use if constexpr and this easy implementation cannot be used.
Implement the get function in C++11 or C++14.

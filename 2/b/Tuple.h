#ifndef TUPLE_H
#define TUPLE_H

#include <cstddef>

template <typename T, typename... Ts>
class Tuple 
{
   using value_type = T;
   using nested_type = Tuple<Ts...>;
   value_type t_;
   nested_type ts_;
   
   template <size_t, typename> friend struct TupleElement;
   
public:
   Tuple(const T& t, const Ts&... ts) : t_(t), ts_(ts...) { }
};

template <typename T>
class Tuple<T>
{
   using value_type = T;
   T t_;
   
   template <size_t, typename> friend struct TupleElement;
   
public:
   Tuple(const T& t) : t_(t) { }
};

template <size_t I, typename T>
struct TupleElement
{ 
   using type = typename TupleElement<I - 1, typename T::nested_type>::type;
};

template <typename T>
struct TupleElement<0, T>
{ 
   using type = typename T::value_type;
};

#endif
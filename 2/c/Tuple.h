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
   
// template <size_t, typename> friend struct TupleElement;

#if __cplusplus >= 201703L
   template <size_t, typename U> friend auto& get(U&);
#else
   template <size_t, typename> friend struct TupleGetHelper;
#endif
   
public:
   Tuple(const T& t, const Ts&... ts) : t_(t), ts_(ts...) { }
};

template <typename T>
class Tuple<T>
{
   using value_type = T;
   T t_;
   
// template <size_t, typename> friend struct TupleElement;

#if __cplusplus >= 201703L
   template <size_t, typename U> friend auto& get(U&);
#else
   template <size_t, typename> friend struct TupleGetHelper;
#endif
   
public:
   Tuple(const T& t) : t_(t) { }
};

#if __cplusplus >= 201703L
// C++17 version:

template <size_t I, typename T>
auto& get(T& tuple)
{
   if constexpr (I == 0)
      return tuple.t_;
   else
      return get<I - 1>(tuple.ts_);
}

#else
// prior-C++17 version:

template <size_t I, typename T>
struct TupleGetHelper
{
   static auto& get(T& tuple)
   {
      return TupleGetHelper<I-1, typename T::nested_type>::get(tuple.ts_);
   }
};

template <typename T>
struct TupleGetHelper<0, T>
{
   static auto& get(T& tuple)
   {
      return tuple.t_;
   }
};

template <size_t I, typename T>
auto& get(T& tuple)
{
    return TupleGetHelper<I, T>::get(tuple);
}

#endif

#endif
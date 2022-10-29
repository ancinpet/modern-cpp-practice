#include <iostream>
#include "Tuple.h"

int main()
{
   int i = 2;
   using T = Tuple<int&, double, bool>;
   T t(i, 3.5, false);
   
   std::cout << get<0>(t) << std::endl;
   std::cout << get<1>(t) << std::endl;
   std::cout << get<2>(t) << std::endl;
   
   get<0>(t) = -1;
   std::cout << i << std::endl;
}
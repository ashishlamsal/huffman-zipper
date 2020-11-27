#include <iostream>
#include<vector>
#include<string>
#include <cstdarg> // header for variadic function

template<class T>
std::vector<T> vectorify(int count, T...)
/*
 *   Takes any number of arguments and return  vector containing the arguments
 *   arguments: (int noOfArguments , T argument1[,T argument2,[T argument3...]]]
 *   return: std::vector<T>
*/
{
    std::va_list args;
    va_start(args, count);
    std::vector<T> vectorInstance;
    for (int i = 0; i < count; ++i) {
        vectorInstance.push_back(va_arg(args, T));
    }
    va_end(args);
    return vectorInstance;
}
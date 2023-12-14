#pragma once

#include <stdexcept>
namespace Math::inline Operations  {

//TODO add type-constrait for template parametr
template<typename T>
T greatestCommonDivisor(T first, T second){
    if(second == 0) throw std::logic_error{"divide by zero is ilegal"};
    if(first % second == 0) return second;
    
    return greatestCommonDivisor(second, first % second); 
}
}
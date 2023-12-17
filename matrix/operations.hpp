#pragma once

#include <stdexcept>
#include "matrix.hpp"
namespace Math::inline Operations  {
/***
 * 
 * 
 * 
*/
//TODO add type-constrait for template parametr

template<typename T>
T greatestCommonDivisor(T first, T second) noexcept {
    if(second == 0) return first;
    if(first % second == 0) return second;
    
    return greatestCommonDivisor(second, first % second); 
}


//fast pow with integer degree
template<typename T>
//todo add type constraint
auto binaryPow( T mult, std::size_t degree = 0) noexcept{
  auto res { T{1} };
 
  while(degree > 0){
    if(degree % 2 ==1){
      res *=mult;
    }
    mult *= mult;
    degree /= 2;
  }
  return res;
}
//overload for matrices
template<typename T>
auto binaryPow(Matrix<T> ob , std::size_t degree = 0){
  if(ob.getHeight() != ob.getWidth() ) throw std::invalid_argument{"square matrix only :("};
  auto result { initWithIdentityMatrix<T>(ob.getWidth()) };
  while(degree > 0){
    if(degree % 2 ==1){
      result = result * ob;
      //result *= ob;
    }
    ob = ob * ob;
    //ob *=ob;
    degree /= 2;
  }
  return result;
  
}

//Fibonachi numbers
auto fibNumber(std::size_t number = 0) noexcept {
  Matrix<std::size_t> result {2,2};
  result(0,0) = result(0,1) = result(1,0) = 1;
  
  /*if(number % 2 == 0){
  result =  binPow(binPow(result, number / 2) , 2 );
  }
  else{
    result = result * binPow(result, (number - 1) / 2 )
  }*/
  return binaryPow(result, number)(0,0);
  //return result(0,0);
}

}
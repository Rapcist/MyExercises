
#pragma once

#include "Structs.hpp"
#include <string>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <stdexcept>
namespace Intersection {
	
template <typename T>
using Func = const T & (*) (const T &, const T &);

//BINARYFORCUBE func-obj for std::accumulate
//throws: logic_error("Emptyset") from check(...), invalid_argument 
template <typename Type>
class Intersect{
    public:
    auto operator()(const Cube<Type> & lhs,const Cube<Type> & rhs) const;
};

//func for cheking correctness of the intersection
//throws: logic_error("Emptyset") , invalid_argument
template<typename Type>
void check(const Point<Type> & lhs, const Point<Type> & rhs); 

//func for perfomring axial intersection using std::max and std::min
//throws: logic_error("Emptyset") from check(...), invalid_argument  
template<typename T>
auto axial_intersection(const Point<T> & lhs,const Point<T> &rhs, Func<T> Foo); 

template<typename T>
void app(const std::string & s);

//IMPLEMENTATION

//Used in std::accumulate 
template <typename Type>
auto Intersect<Type>::operator()(const Cube<Type> & lhs,const Cube<Type> & rhs) const{
    auto one {axial_intersection<Type>(lhs.getFirstPoint(),rhs.getFirstPoint(),std::max)};
    auto two {axial_intersection<Type>(lhs.getSecondPoint(),rhs.getSecondPoint(),std::min)};

    check(one,two);
	
    return Cube<Type>(one,two);
}

//Check if lhs and rhs can't constitute Cube
template<typename Type>
void check(const Point<Type> & lhs, const Point<Type> & rhs) {
    if(lhs.size() != rhs.size()) throw std::invalid_argument{"Different sizes(number of dimensions). check()"};
    
    for(std::size_t x{0}; x < lhs.size(); ++x){
        if (lhs[x] > rhs[x]) throw std::logic_error{"Emptyset"} ;
    }
}

//return: Point that can represent Cube
template<typename T>
auto axial_intersection(const Point<T> & lhs,const Point<T> &rhs, Func<T> Foo){
    if(lhs.size() != rhs.size()) throw std::invalid_argument{"Different sizes(number of dimensions).ax_int()"};
    
    Point<T> tmp;
	
    for(std::size_t x{0}; x < lhs.size(); ++x){
        tmp.addCoordinate(Foo(lhs[x],rhs[x]));
    }
    return tmp;
}
//FORMAT:
//DIMENSIONS
//P1 P2 //CUBE 1 
//...
//USER MUST PROVIDE APPROPRIATE INPUT FORMAT: P1(x(i)) <= P2(x(i)) ; x(i) - coordinate
//OTHERWISE BEHAVIOR IS UNDEFINED
template<typename T>
void app(const std::string & s){
    std::ifstream fin(s); 
    std::size_t dimensions{0};
    fin>>dimensions;

   
    std::vector<Cube<T>> arrayOfDomains;
    Point<T> tmp_point1(dimensions),tmp_point2(dimensions);
	
    fin>>tmp_point1>>tmp_point2;
	
    Cube<T> initC(tmp_point1, tmp_point2);

    while(!fin.eof()){
        fin>>tmp_point1>>tmp_point2;
        arrayOfDomains.push_back(Cube<T>(tmp_point1,tmp_point2));
    }
    try{
		auto res {std::accumulate(arrayOfDomains.begin(),arrayOfDomains.end(), initC, Intersect<T>())};
		res.getFirstPoint().printPoint();
		res.getSecondPoint().printPoint();
    }catch(const std::invalid_argument & er){
        std::cout<<er.what();
    }
    catch(const std::logic_error & emptyset){
        std::cout<<emptyset.what();
    }
}
}
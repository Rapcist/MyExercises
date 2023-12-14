#ifndef METHODSFORINTERSECTIONS
#define METHODSFORINTERSECTIONS

#include "Structs.hpp"
#include <string>
#include <fstream>

namespace Intersection {
	
//template <typename T>
//using Func = const T & (*) (const T &, const T &);

//BINARYFORCUBE func-obj for std::accumulate
//throws: logic_error("Emptyset") from check(...)
template <typename Type>
class BinForCube{
    public:
    auto operator()(const Cube<Type> & lhs,const Cube<Type> & rhs) const;
};

//func for cheking correctness of the intersection
//throws: logic_error("Emptyset")
template<typename Type>
void check(const Point<Type> & lhs, const Point<Type> & rhs); 

//func for perfomring axial intersection using std::max and std::min
//throws: logic_error("Emptyset") from check(...)
template<typename T,typename Func>
auto axial_intersection(const Point<T> & lhs,const Point<T> &rhs, Func Foo); 

template<typename T>
void app(const std::string & s);

//IMPLEMENTATION

//Used in std::accumulate 
template <typename Type>
auto BinForCube<Type>::operator()(const Cube<Type> & lhs,const Cube<Type> & rhs) const{
    auto one {axial_intersection(lhs.getFirstPoint(),rhs.getFirstPoint(),std::max<Point<Type>>)};
    auto two {axial_intersection(lhs.getSecondPoint(),rhs.getSecondPoint(),std::min<Point<Type>>)};

    check(one,two);
	
    return Cube<Type>(one,two);
}

//Check if lhs and rhs can't constitute Cube
template<typename Type>
void check(const Point<Type> & lhs, const Point<Type> & rhs) {
    auto iter1{lhs.getData().begin()}, iter2{rhs.getData().begin()};
	
    while(iter1 != lhs.getData().end() && iter2 != rhs.getData().end()) if(*iter1++ > *iter2++ ) throw logic_error{"Emptyset"} ;
}

//return: Point that can represent Cube
template<typename T,typename Func>
auto axial_intersection(const Point<T> & lhs,const Point<T> &rhs, Func Foo){
    Point<T> tmp;
    auto iter1{lhs.getData().begin()}, iter2{rhs.getData().begin()}; 
	
    while(iter1 != lhs.getData().end()) tmp.getData().push_back(Foo(*iter1++,*iter2++));
	
    return tmp;
}
//FORMAT 
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
		auto res {std::accumulate(arrayOfDomains.begin(),arrayOfDomains.end(), initC, BinForCube<T>())};
		res.getFirstPoint().printPoint();
		res.getSecondPoint().printPoint();
    }catch(const std::logic_error & emptyset){
        cout<<emptyset.what();
    }
}
}
#endif
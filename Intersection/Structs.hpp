#pragma once

#include <iostream>
#include <vector>


namespace Intersection{
    
template<typename Type>
class Point;

template<typename Type>
std::istream & operator>>(std::istream & stream, Point<Type>& ob);

//CLASSES
template <typename Type>
class Point{
    std::vector<Type> m_coordinates;
    public:
    explicit Point(std::size_t N = 0);

    const auto & getData() const; 
    auto & getData();

    
    friend std::istream & operator>> <Type>(std::istream & stream, Point<Type>& ob);
    void printPoint() const;
};

template <typename Type>
class Cube{
    Point<Type> m_first, m_second;     
    public:
    Cube(const Point<Type> & first , const Point<Type> & second );
    //Cube(Point<Type>&& first,Point<Type>&& second);
    //auto & operator=(Cube<Point<Type>>&& rhs);

    auto & getFirstPoint();
    auto & getSecondPoint();
    const auto & getFirstPoint() const;
    const auto & getSecondPoint() const;

};


//implementation
#pragma region
//POINT
template <typename Type>
Point<Type>::Point(size_t N) : m_coordinates{std::vector<Type>(N)} {}


template <typename Type>
auto & Point<Type>::getData()  { return m_coordinates;}

template <typename Type>
const auto & Point<Type>::getData()  const { return m_coordinates;}


template <typename Type>
std::istream & operator>>(std::istream & stream, Point<Type> & ob){
    for(auto & coord: ob.m_coordinates){
        stream>>coord;
    }
    return stream;
}
template <typename Type>
void Point<Type>::printPoint() const{
    for(const auto & ob: m_coordinates ) std::cout<<ob<<' ';
    std::cout<<std::endl;
}
//CUBE		
template <typename Type>
Cube<Type>::Cube(const Point<Type> & first ,const Point<Type> & second ) : m_first {first}, m_second {second} {
 /*   try{
        check(first,second);
    }catch(...){
        m_first = second;
        m_second = first;
    }*/
}
 

template <typename Type>
auto & Cube<Type>::getFirstPoint(){
    return m_first; 
}
template <typename Type>
auto & Cube<Type>::getSecondPoint(){
    return m_second; 
}
template <typename Type>
const auto & Cube<Type>::getFirstPoint() const{
    return m_first; 
}
template <typename Type>
const auto & Cube<Type>::getSecondPoint() const{
    return m_second; 
}


#pragma endregion


}
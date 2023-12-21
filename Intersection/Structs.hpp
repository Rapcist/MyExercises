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

    Type & operator[](std::size_t x);
    const Type & operator[](std::size_t x) const;
    void setCoordinate(Type coord, std::size_t x);
    void addCoordinate(Type coord);
    std::size_t size() const;
    //const auto & getData() const; 
    //auto & getData();

    
    friend std::istream & operator>> <Type>(std::istream & stream, Point<Type>& ob);
    void printPoint() const;
};

template <typename Type>
class Cube{
    Point<Type> m_first, m_second;     
    public:
    Cube(Point<Type> first , Point<Type> second );

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


//template <typename Type>
//auto & Point<Type>::getData()  { return m_coordinates;}

//template <typename Type>
//const auto & Point<Type>::getData()  const { return m_coordinates;}


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
template <typename Type>
void Point<Type>::addCoordinate(Type coord) {
    m_coordinates.push_back(coord);
}
template <typename Type>
void Point<Type>::setCoordinate(Type coord, std::size_t x){
    m_coordinates.at(x) = coord;
}
template <typename Type>
inline std::size_t Point<Type>::size() const{
    return m_coordinates.size();
}
template <typename Type>
inline Type & Point<Type>::operator[](std::size_t x){
    return m_coordinates[x];
}
template <typename Type>
inline const Type & Point<Type>::operator[](std::size_t x) const{
    return m_coordinates[x];
}
//CUBE		
template <typename Type>
Cube<Type>::Cube(Point<Type> first ,Point<Type>  second ) :
 m_first {std::move(first)}, m_second {std::move(second)} 
{
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
#include "rational.hpp"
#include <compare>
#include "operations.hpp"
using namespace std;
using namespace Math;

namespace Math::inline Numeric {

//Ctor;


Rational::Rational(type num , type den ) : m_numerator{num / greatestCommonDivisor( num,den == 0 ? 1 : den )},
 m_denominator{den / greatestCommonDivisor( num, den == 0 ? 1 : den)}
{
    if(den == 0) m_numerator = 0;
}
//GETTERs
inline auto Rational::getNumerator() const {
    return m_numerator;
}
inline auto Rational::getDenominator() const {
    return m_denominator;
}

//MISC.
strong_ordering Rational::operator<=>(const Rational & rhs) const {
    return (m_numerator * rhs.getDenominator()) <=> (m_denominator * rhs.getNumerator());
}
bool Rational::operator==(const Rational & rhs) const{
    return(m_numerator * rhs.getDenominator()) == (m_denominator * rhs.getNumerator());
}
//OPERTATIONS
auto Rational::operator+( const Rational & rhs) const{
    return Rational{getNumerator()*rhs.getDenominator() + rhs.getNumerator() * getDenominator(),
     getDenominator()*rhs.getDenominator()};
}
auto Rational::operator*( const Rational & rhs) const{
    return Rational{getNumerator()*rhs.getNumerator(), getDenominator()*rhs.getDenominator()};
    }
auto Rational::operator-( const Rational & rhs) const{
    return Rational{getNumerator()*rhs.getDenominator() - rhs.getNumerator() * getDenominator(),
     getDenominator()*rhs.getDenominator()};
}
auto Rational::operator/(const Rational & rhs) const{
    return Rational{getNumerator()*rhs.getDenominator(), getDenominator()*rhs.getNumerator()};
}
Rational & Rational::operator+=( const Rational & rhs) &{
    *this = *this + rhs; 
    return *this;
}

Rational & Rational::operator*=( const Rational & rhs) &{
    *this = *this * rhs; 
    return *this;

}
Rational & Rational::operator-=( const Rational & rhs) & {
    *this = *this - rhs; 
    return *this;

}
Rational & Rational::operator/=( const Rational & rhs) &{
    *this = *this * rhs; 
    return *this;

}




istream & operator>>(istream & stream, Rational & rhs){
    stream>>rhs.m_numerator;
    //TODO check for spaces???
    if(stream.get() != '/') return stream;
    stream>>rhs.m_denominator;
    return stream;
}
ostream & operator<<(ostream & stream, const Rational & rhs){
    if(rhs.getNumerator() == 0) {stream<<0; return stream;}
    if(rhs.getDenominator() == 1) {stream<<rhs.getNumerator(); return stream;}
    stream<<rhs.getNumerator()<<'/'<<rhs.getDenominator();
    return stream;
}

auto reduction(const Rational & srs){
    auto GCD { greatestCommonDivisor( srs.getNumerator(), srs.getDenominator())};
    return Rational{srs.getNumerator() / GCD, srs.getDenominator() / GCD};
}
}
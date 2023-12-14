#pragma once

#include <compare>
#include <iostream>

namespace Math::inline Numeric {


class Rational{
    using type = int;

    public:
    //Rational() = default;
    Rational(type num = 0 , type den = 1);

    [[nodiscard]] bool operator==(const Rational & rhs) const;
    [[nodiscard]] std::strong_ordering operator<=>(const Rational & rhs) const;

    auto operator+( const Rational & rhs) const;
    auto operator*( const Rational & rhs) const;
    auto operator-( const Rational & rhs) const;
    auto operator/(const Rational & rhs) const;

    Rational & operator+=( const Rational & rhs) &;
    Rational & operator*=( const Rational & rhs) &;
    Rational & operator-=( const Rational & rhs) &;
    Rational & operator/=( const Rational & rhs) &;

   
   
    friend std::istream & operator>>(std::istream & stream, Rational & rhs);

    auto getNumerator() const;
    auto getDenominator() const;

    private:

    type m_numerator{0},m_denominator{1};

};



std::ostream & operator<<(std::ostream & stream, const Rational & rhs);
auto reduction(const Rational & srs);
}
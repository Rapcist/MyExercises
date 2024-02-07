#pragma once

#include<iostream>

namespace meta {
	//-------------------------------------------
	template<unsigned N> struct factorial {
		static constexpr long unsigned value { N * factorial<N-1>::value };
	};

	template<> struct factorial<0>{
		static constexpr long unsigned value { 1 };
	};
	//------------------------------------------
	template<int first, int second>
	struct GCD {
		static constexpr int value { GCD<second,first % second>::value };
	};
	template<int first>
	struct GCD<first,0> {
		static constexpr int value { first };
	};
	template<int second>
	struct GCD<0,second> {
		static constexpr int value { second };
	};
	//------------------------------------------
	template<int base,unsigned N> struct Power{
		static constexpr int value {base * Power<base, N-1>::value };
	};
	template<int base> struct Power<base,1>{
		static constexpr int value {base};
	};
	template<int base> struct Power<base,0> {
		static constexpr int value {1};
	};
	//-------------------------------------------
	//Fraction is needed for Sum(see below)
	template<int N, int D> struct Fraction;
	
	template<int N, int D> 
	consteval auto normalize() {
		constexpr int delta {GCD<N,D>::value};
		return Fraction<N/delta, D/delta>{};
	}
	
	template<int N, int D> struct Fraction {
		int m_num{N}, m_den{D};
		
		constexpr Fraction() = default;
		template <int N1, int D1>
		constexpr Fraction(Fraction<N1,D1> src) : m_num{N1}, m_den {D1} {}
		
	};
	

	template<int N1,int D1,int N2,int D2>
	consteval auto addFraction([[maybe_unused]]const Fraction<N1,D1>& rhs,[[maybe_unused]] const Fraction<N2,D2>& lhs){
		return normalize<N1*D2 + N2 *D1, D1 * D2>();
	}

	//-------------------------------------------
}

namespace meta::inline Tests{

	//(b+1)*(b+2)*...*(b+g+2) analog of (b+g+2)! / b!
	/*template<unsigned beta,unsigned gamma>
	struct Sigma{
		static constexpr long unsigned value { factorial<beta+gamma+2>::value / factorial<beta>::value};	
	};*/
	template<unsigned beta,unsigned gamma>
	struct Sigma{
		static constexpr long unsigned value { Sigma<beta,gamma -1>::value * (beta + gamma + 2)};	
	};
	template<unsigned beta>
	struct Sigma<beta,0>{
		static constexpr long unsigned value { (beta + 1) * (beta +2 )};	
	};
	

	template<unsigned beta,unsigned gamma, unsigned i >
	struct Sum {
		static constexpr Fraction value {
			addFraction(Fraction<Power<-1, i>::value , factorial<i>::value * factorial<gamma + 1 - i>::value * (beta + i + 1)>{}, Sum<beta,gamma, i - 1 >::value)
		};
	};
	template<unsigned beta,unsigned gamma>
	struct Sum<beta,gamma,0> {
		static constexpr Fraction value {Fraction<1 , factorial<gamma+1>::value * (beta + 1)>{} };
	};
}

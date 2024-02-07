#include<iostream>
#include "meta.hpp"

using namespace std;
using namespace meta;


//struct factorial<10>;

int main() {
	
	/*cout<<factorial<3>::value<<'\n';
	cout<<factorial<5>::value<<'\n';
	cout<<factorial<7>::value<<'\n';

	cout<<Sigma<3,4>::value;*/
	int a =  Sum<7,4,5>::value.m_num ;
	int b = Sum<7,4,5>::value.m_den;
	cout<<a<<'/'<<b<<endl;
	cout<<Sigma<7,4>::value;
	// equals :) => how to prove :(

	
}


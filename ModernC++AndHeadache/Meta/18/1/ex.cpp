#include<iostream>
#include<vector>

namespace ex18 {
	void print(auto & range) {
		for(auto & val : range) {
			std::cout<<val<<' ';
		}	
		std::cout<<std::endl;
	}
	void one(){
		using namespace std;
		vector<int> values {2,5}; //not (2,5);
		values.insert(++begin(values),{3,4});
		
		vector second {0,1};
		values.insert(begin(values), cbegin(second), cend(second));

		vector<int> third;
		third.reserve(values.size());
		for(auto it{ crbegin(values) }; it != crend(values) ; ++it) {
			third.push_back(*it);
		}
		print(third);

	}
}//namespace ex18

#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <iterator>
using namespace std;



int main(){

	//auto res {views::iota(1) | views::take_while([](auto val){return val< 20;}) | views::common };
	auto res {ranges::iota_view(1,20)};// uhh common range )))
	vector<int> values{begin(res),end(res)};
	erase_if(values,[](int val){ return val%2 != 0 ;});	
	ranges::copy(values, ostream_iterator<int>(cout, "^"));
}

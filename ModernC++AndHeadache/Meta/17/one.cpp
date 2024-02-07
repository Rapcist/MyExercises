
#include <iostream>
#include <ranges>
#include <format>
#include <vector>
#include <utility>
#include <string>
#include <iterator>
#include <iomanip>
//abreviated function-template syntax
void printRange(auto & range) {
	for(const auto & ob : range) std::cout<<ob<<' ';
	std::cout<<std::endl;
}

namespace seventeen {
	template<typename T>
	concept Dereferenceable = requires(T a){*a;}; 
	
	template<typename T>
	concept PreIncrementable = requires(T a){++a;};

	template<typename T>
	concept	weakForwardIterator = Dereferenceable<T> && PreIncrementable<T>;
	
	
	
	void one() {
		using namespace std;
		ranges::iota_view range{10};
		
		auto  result1 {range |
		views::take_while([](int i){return i < 30;}) };
		
		vector<int> tmp;
		tmp.reserve(20);
		for(auto value : result1) {tmp.push_back(value);}
		
		/*auto  result {range | views::filter([](int i){return i % 3 != 0;}) |
		views::take_while([](int i){return i < 30;}) | views::transform([](int i){ return std::format(R"('{}')", i);} ) };*/
		auto  result2 {tmp | views::filter([](int i){return i % 3 != 0;}) };
		
		for(auto & value : result2) {value *=2;}
	
		printRange(tmp);
	}	
	//---------------------------------------
	template <typename InputIter> requires weakForwardIterator<InputIter>
	auto sum(InputIter begin, InputIter end)
	{
		auto sum{ *begin };
		for (auto iter{ ++begin }; iter != end; ++iter) {
			sum += *iter;
		}
		return sum;
	}
	//template arguments can be rewritten like this:
	//template<weakForwardIterator T, weakForwardIterator E>
	template <typename InputIter,typename OutputIter> requires weakForwardIterator<InputIter> && weakForwardIterator<OutputIter>
	void myCopy(InputIter begin, InputIter end, OutputIter out) {
		for(auto iter{begin}; iter != end; ++iter,++out)  {
			*out = *iter;
		}
	}
	struct Person {
		std::string firstname,lastname;
	};
	std::ostream & operator<<(std::ostream & out, const Person & person){
		out<<std::quoted(person.firstname)<<std::quoted(person.lastname);
		return out;
	}
	void two(){
		using namespace std;
		vector<pair<Person,int>> arr {{{"a","b"}, 13},{{"c","d"}, 43},{{"e","f"}, 3},{{"g","o"}, 73},{{"t","s"}, 63}};

		auto result {views::common(arr | views::values | views::filter([](const auto & age){return (age >=12) && (age <=65);})) };
		
		auto count { distance(begin(result),end(result))};
		//auto count {ranges::size(result)};		

		auto average { sum(begin(result), end(result)) / static_cast<double>(count) };
		
		cout<<average;
		
	}
	void three() {
		using namespace std;
		vector<pair<Person,int>> arr {{{"a","b"}, 13},{{"c","d"}, 43},{{"e","f"}, 3},{{"g","o"}, 73},{{"t","s"}, 63}};
		
		auto onlyFour { views::common(arr | views::keys | views::take(4)) };
		
		myCopy( begin(onlyFour), end(onlyFour), ostream_iterator<Person> {cout,"\n"} );
		
		//projection : only lastname
		auto onlyLastName { onlyFour | views::transform([](const auto & person){return person.lastname;}) };
		
		cout<<endl;
		myCopy( begin(onlyLastName), end(onlyLastName), ostream_iterator<std::string> {cout,"\n"} );
	}
	void four1() {
		using namespace std;
		vector<int> bank;
		for(int value : ranges::istream_view<int>(cin) | views::take_while([](const auto & num) {return num != -1;} ) ) {
			bank.push_back(value);
		}
		cout<<"--->\n";
		printRange(bank);
		
	}
	//doesn't compile on gcc13.2, i dont know why:| maybe bug:D
/*	void four2(){
		using namespace std;
		//auto r { ranges::istream_view<int>(cin) | views::take_while([](const auto & num) {return num != -1;} ) | views::common };
		auto r1{ ranges::istream_view<int>(cin)
			| views::take_while([](const auto& v) {return v != -1; })
		};
		auto r { ranges::common_view{ r1 } };
		vector<int> values{ begin(r), end(r)};
		
		cout<<"--->\n";
		//printRange(values);
	}*/
	void four3() {
		using namespace std;
		vector<int> bank;
		ranges::copy(
			ranges::istream_view<int>(cin) | views::take_while([](const auto & num) {return num != -1;} ),
			back_inserter(bank)
		);
		
		myCopy(begin(bank), end(bank), std::ostream_iterator<int>(cout, "...") );
	
	}
}

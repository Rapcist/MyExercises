#include <iostream>
#include <span>
#include <vector>
#include <type_traits>
using namespace std;

double average(span<const double> seq){
	cout<<"\nfirst\n";
	double sum{0};
	for(double val : seq) sum +=val;
	return sum/seq.size();
}

template<typename T>
concept Arithmetic = is_arithmetic_v<T>;

/*//works fine
template<Arithmetic T>
double average(span<const T> seq){
	cout<<"\nsecond\n";
	T sum{0};
	for(const auto val : seq ) sum += val;
	return sum / static_cast<double>(seq.size());
}*/

// experiment #sqrt(2214144)
// result : works fine heehehe
				\_0_
				  | \
				 / \	
double average(span<const Arithmetic auto> seq){
	cout<<"\nsecond\n";
	double sum{0};
	for(const auto val : seq ) sum += val;
	return sum / static_cast<double>(seq.size());
}

int main() {
	vector values1{ 1.1, 2.2, 3.3, 4.4 };

	//// The parameter of the function template is span<const T>.
	//// This cannot be automatically deduced from the function arguments.
	//// So, we need to specify the template type argument explicitly.
	//// NOTE : with first overload(not template) we can :D
	//cout << average<double>(values1) << endl;
	cout << average(values1) << endl;

	array<int, 4> values2{ 1, 2, 3, 4 };
	cout << average<int>(values2) << endl;
	cout << average<int>({ values2.data() + 2, 2 }) << endl;
}

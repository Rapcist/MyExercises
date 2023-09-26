#include <iostream>
#include <string>
#include <format>
#include <string_view>
#include <algorithm>
using namespace std;


string func1(string const &  hays, string_view  needle, string_view  repl);


int main() {
	string haystack,needle,replstr;

	getline(cin,haystack);
	getline(cin,needle);
	getline(cin,replstr);

	cout<<format("\nInit: {} \n", haystack);

	haystack = func1(haystack,needle,replstr);

	cout<<format("\nRes: {} \n", haystack);
	return 0;
}

string func1(string const& hays, string_view  needle, string_view  repl){
	string tmp;
	for(size_t i {0}; i < hays.length();++i) {
		if(hays[i] == needle[0]) {
			size_t j {1}; 
			for(; j < needle.length() && i+j<hays.length() && hays[i+j]==needle[j]; ++j);
			if(j == needle.length()) { // replacement
				tmp += repl.data();
				i += j ;
				continue;
			}
		}
		tmp.push_back(hays[i]);
	}
	return tmp;
}


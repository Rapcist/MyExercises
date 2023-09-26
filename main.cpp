#include <iostream>
#include <string>
#include <format>
#include <string_view>
using namespace std;


string func1(string_view  hays, string_view  needle, string_view  repl);

int main() {
	string haystack,needle,replstr;

	getline(cin,haystack);
	getline(cin,needle);
	getline(cin,replstr);

	cout<<format("\nInit: {} {} \n", haystack,& haystack);

	haystack = func1(haystack,needle,replstr);

	cout<<format("\nRes: {} {} \n", haystack,& haystack);
	return 0;
}

string func1(string_view  hays, string_view  needle, string_view  repl){
	string tmp;
	for(size_t i {0}; i < hays.length();++i) {

		if(hays[i] == needle[0]) {
			size_t j {1}; 
			for(; j < needle.length() && hays[i+j]==needle[j]; ++j);
			++j;
			if(j == needle.length()) { // replacement

			}
		}
	}
}

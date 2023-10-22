#include "SSS.hpp"

using namespace std;
using namespace MyStr;
int main() { 
	StrType s1("A sample session using string objects.\n");
	StrType s2(s1);
	StrType s3;
	char s[80];
	cout << s1 << s2;
	s3 = s1;
	cout << s1;
	s3.makestr(s);
	cout << "Convert to a string: " << s;
	s2 = "This is a new string.";
	cout << s2 << endl;
	StrType s4(" So is this.");
	s1 = s2+s4;
	cout << s1 << endl;
	if(s2==s3) cout << "Strings are equal.\n";
	if(s2!=s3) cout << "Strings are not equal.\n";
	if(s1<s4) cout << "s1 less than s4\n";
	if(s1>s4) cout << "s1 greater than s4\n";
	if(s1<=s4) cout << "s1 less than or equals s4\n";	
	if(s1>=s4) cout << "s1 greater than or equals s4\n";
	if(s2 > "ABC") cout << "s2 greater than ABC\n\n";
	s1 = "one two three one two three\n";
	s2 = "two";
	cout << "Initial string: " << s1;
	cout << "String after subtracting two: ";
	s3 = s1 - s2;
	cout << s3;
	cout << endl;
	s4 = "Hi there!";
	s3 = s4 + " C++ strings are fun\n";
	cout << s3;
	s3 = s3 - "Hi there!";
	s3 = "Aren't " + s3;
	cout << s3;
	s1 = s3 - "are";
	cout << s1;
	s3 = s1;
	cout << "Enter a string: ";
	cin >> s1;
	cout << s1 << endl;
	cout << "s1 is " << s1.strsize() << " characters long.\n";
	puts(s1); // convert to char * s1 = s2 = s3;
	cout << s1 << s2 << s3;
	s1 = s2 = s3 = "Bye ";
	cout << s1 << s2 << s3;
	
	cin.get();
	cin.get();
	return 0;
}
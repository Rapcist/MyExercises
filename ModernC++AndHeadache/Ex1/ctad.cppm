module;
#include <string>
#include<concepts>
export module ex1:ctad;

import :def;

namespace Ex{

template<typename T> //Doesn't work from another partion;
KeyValuePair(T , const char *) -> KeyValuePair<T, std::string>;

template<typename T>
KeyValuePair(const char * , T ) -> KeyValuePair<std::string, T>;

KeyValuePair(const char *,const char *) -> KeyValuePair<std::string, std::string>;
KeyValuePair(int, int) -> KeyValuePair<long,long>;

int foo() {return 2<<4;}

}
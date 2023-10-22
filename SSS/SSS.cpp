#include "SSS.hpp"
using namespace std;
namespace MyStr{ 
//CharPtr
CharPtr & CharPtr::operator=(CharPtr & ob){
	m_ptr = ob.m_ptr;
	ob.m_ptr = nullptr;
	return *this;
}
size_t CharPtr::length () const {
	size_t len{0};
	while(myPos >= len && m_ptr[len]) ++len;
	return len;
}
char & CharPtr::operator[](size_t pos) {
	if(pos<=length()) return m_ptr[pos];
	throw logic_error {"Overrun array bounds"};
}
const char CharPtr::operator[](size_t pos) const{
	if(pos<=length()) return m_ptr[pos];
	throw logic_error{"Overrun array bounds"};
}

//StrType
StrType::StrType(const char *cs){
    for(size_t i{0};cs[i];++i){ 
		m_str.push_back(cs[i]); 
	} 
} 
istream & operator>>(istream & stream, StrType & ob){ 
    char tmp_ch[myPos]; 
    StrType::cont_t tmp;
    stream>>tmp_ch;
    // stream.read(&tmp_ch,myPos-1); 
    for(size_t i=0;tmp_ch[i];++i){ 
		tmp.push_back(tmp_ch[i]); 
    } 
    ob.m_str = tmp;
    return stream; 
} 
ostream & operator<<(ostream &stream, const StrType & ob){ 
    auto p {ob.m_str.begin()}; 
    while(p!=ob.m_str.end()){ 
		stream<<*p++; 
    } 
    return stream; 
} 
StrType & StrType::operator=(const StrType &ob){ 
    m_str.assign(ob.m_str.begin(),ob.m_str.end()); 
    return *this; 
} 
StrType & StrType::operator=(const char * cs){ 
    size_t i{0}; 
    for(;cs[i];++i); 
    m_str.assign(cs,cs+i); 
    return *this; 
}  
const StrType StrType::operator+(const StrType &ob) const{ 
    auto tmp {*this};
    auto p {ob.m_str.begin()}; 
    while(p!=ob.m_str.end()){ 
		tmp.m_str.push_back(*p++); 
    } 
    return tmp; 
} 
const StrType StrType::operator+(const char* cs) const{ 
    auto tmp {*this}; 
    for(size_t i{0};cs[i];++i){ 
		tmp.m_str.push_back(cs[i]); 
    } 
    return tmp; 
} 
const StrType operator+(const char* cs,const StrType &ob) {    
    StrType tmp {cs}; 
    tmp.m_str.insert(tmp.m_str.end(),ob.m_str.begin(),ob.m_str.end()); 
    return tmp; 
} 
  
 //SUBTRACTING ALL SUBSTINRGS
const StrType StrType::operator-(const StrType &ob) const{ 
    size_t i {0}; 
    StrType tmp; 
    auto p { m_str.begin()}; 
    while(p!=m_str.end()){ 
		if(ob.m_str[0]!=*p) tmp.m_str.push_back(*p++); 
		else{ 
		for( i = 0; p+i != m_str.end() && p[i] == ob.m_str[i]; ++i); 
		if(i == ob.m_str.size()) p+=i; 
		else tmp.m_str.push_back(*p++); 
    } 
    } 
    return tmp; 
} 
const StrType StrType::operator-(const char* cs) const{ 
    return (*this)-StrType(cs); 
} 

//MISC. METHODS
void StrType::makestr(char *str) const {
	auto p { m_str.begin()} ; 
	while(str && p!=m_str.end()){ 
		*str++ = *p++; 
	} 
} 
  
StrType::operator const char *(){ 
	if(m_ptr.isEmpty()){ 
		size_t len { m_str.size()}; 
		m_ptr = new char[len+1]; 
		auto p { m_str.begin()}; 
		for(size_t i{0};p != m_str.end();++i){ 
			m_ptr[i]=*p++; 
		}	
		m_ptr[len]='\0'; 
	} 
	return m_ptr.get(); 
}

}
//|=========================================|
//|END OF THE SCOPE OF THE NAMESPACE "MyStr"|
//|=========================================|

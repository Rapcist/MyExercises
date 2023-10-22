#ifndef SSS
#define SSS

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>


namespace MyStr {
	
const int myPos {255};

//simple analog unique_ptr<char> (smart pointer)
class CharPtr{
	
	char *m_ptr {nullptr};
	
public:
	//CONSTRUCTORS DESTRUCTORS COPYes 
	constexpr CharPtr() = default ;
	CharPtr(char *ob );
	CharPtr (const CharPtr & ob) = delete;
	void operator=(char *ob);
	CharPtr & operator=(CharPtr & ob);
	~CharPtr();

	//METHODS
	std::size_t length () const;
	bool isEmpty() const;

	char & operator*();
	const char & operator*() const;
	char & operator[](std::size_t pos);
	const char operator[](std::size_t pos) const;
	char * get();
};

class StrType{
	//CONTAINER
    using cont_t = std::vector<char>; 
	
    cont_t m_str; 
    CharPtr m_ptr;
 public: 
 
    //CONSTRUCTORS DESTRUCTORS COPYes
    StrType() = default; 
    StrType(const StrType &ob) : m_str{ob.m_str} {}
    StrType(const char *cs); 
    ~StrType() = default;
   
    //OPERATORS
    friend std::istream & operator>>(std::istream &stream, StrType & ob); 
    friend std::ostream & operator<<(std::ostream &stream, const StrType & ob); 
  
    StrType & operator=(const StrType &ob); 
    StrType & operator=(const char * cs); 
  
    const StrType operator+(const StrType &ob) const; 
    const StrType operator+(const char* cs) const; 
    friend const StrType operator+(const char* cs,const StrType &ob); 
  
    const StrType operator-(const StrType &ob) const; 
    const StrType operator-(const char* cs) const; 
  
    //RELATIONAL WITH StrType 
    bool operator ==(const StrType & ob) const;
    bool operator <(const StrType & ob) const;
   
    bool operator !=(const StrType & ob) const;
    bool operator >=(const StrType & ob) const;
    bool operator >(const StrType & ob) const;
    bool operator <=(const StrType & ob) const;
  
    //RELATIONAL WITH Char * 
    bool operator ==(const char * cs) const;
    bool operator <(const char * cs) const;
  
    bool operator !=(const char * cs) const;
    bool operator >=(const char * cs) const;
    bool operator >(const char * cs) const;
    bool operator <=(const char * cs) const;
	
    //MISC. METHODS
    std::size_t strsize() const;
    void makestr(char *str) const; 
    operator const char *();
}; 
//|=============================|
//|END OF THE SCOPE OF THE CLASS|
//|=============================|
 
//CharPtr
inline CharPtr::CharPtr(char *ob )  : m_ptr{ob}  {} 
inline void CharPtr::operator=(char *ob) {m_ptr = ob;}
inline CharPtr::~CharPtr()  { delete [] m_ptr;}

inline bool CharPtr::isEmpty() const {return m_ptr == nullptr;}

inline char & CharPtr::operator*() {return *m_ptr;}
inline const char & CharPtr::operator*() const {return *m_ptr;}
inline char * CharPtr::get() {return m_ptr;}
 
//StrType
//relational with StrType 
inline bool StrType::operator ==(const StrType & ob) const{ 
	return equal(m_str.begin(),m_str.end(),ob.m_str.begin()); 
} 
inline bool StrType::operator <(const StrType & ob) const{ 
	return lexicographical_compare(m_str.begin(),m_str.end(),ob.m_str.begin(),ob.m_str.end()); 
} 

inline bool StrType::operator !=(const StrType & ob) const {return !(*this == ob);} 
inline bool StrType::operator >=(const StrType & ob) const {return !(*this < ob);} 
inline bool StrType::operator >(const StrType & ob) const {return !(*this < ob && !(*this == ob));} 
inline bool StrType::operator <=(const StrType & ob) const {return !(*this > ob);} 

//relational with Char * 
inline bool StrType::operator ==(const char * cs) const { 
	return equal(m_str.begin(),m_str.end(),StrType(cs).m_str.begin()); 
} 
inline bool StrType::operator <(const char * cs) const { 
	size_t i{0}; 
	for(;cs[i];++i); 
	return lexicographical_compare(m_str.begin(),m_str.end(),cs,cs+i); 
} 
  
inline bool StrType::operator !=(const char * cs) const {return !(*this==StrType(cs));} 
inline bool StrType::operator >=(const char * cs) const {return !(*this<StrType(cs));} 
inline bool StrType::operator >(const char * cs) const {return !(*this<StrType(cs) && *this!=StrType(cs));} 
inline bool StrType::operator <=(const char * cs) const {return !(*this>StrType(cs));}

//MISC. METHODS
inline size_t StrType::strsize() const {return m_str.size();} 


}
//|=========================================|
//|END OF THE SCOPE OF THE NAMESPACE "MyStr"|
//|=========================================|

#endif

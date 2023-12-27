module;
#include<concepts>
#include<string>

export module ex1:def;

namespace Ex{

export template<typename Key, typename Value> 
requires std::movable<Key> && std::movable<Value>
class KeyValuePair final{
    private:
    Key m_first;
    Value m_second;
    public:
    KeyValuePair(Key first , Value second) : m_first {std::move(first)}, m_second{std::move(second)}
    {}
    void setKey(Key src){
        m_first = std::move(src);
    }
    void setValue(Value src){
        m_second = std::move(src);
    }
    inline const Key getKey() const{
        return m_first;
    }
    inline const Value getValue() const{
        return m_second;
    }

   };

   export int foo(); 
//Working only if uddg is here
/*
template<typename T>
KeyValuePair(T , const char ) -> KeyValuePair<T, std::string>;

template<typename T>
KeyValuePair(const char * , T ) -> KeyValuePair<std::string, T>;

KeyValuePair(const char *,const char *) -> KeyValuePair<std::string, std::string>;
*/

}
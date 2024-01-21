module;
#include <vector>
#include <forward_list>
#include <stdexcept>
#include <iostream>
#include <utility>
//#include <format>
export module hash;



export namespace HASHI {

    template<typename Key> 
    class foo {
        public:
        size_t operator()(Key key){
            size_t N {static_cast<int>(key) / sizeof(Key)};
            ///...
            return N;
        }
    };
    
    //todo : add check for capisity and other misc.
    template<typename Key, typename Type,typename HashFunc = foo<Key>>
    class Hash_table final{
        public:
        //CTORS DESTS COPYES MOVES
        Hash_table() = default;


        //INTERACTION
        void insert(Key key, Type data){
            auto pos {HashFunc{}(key)};
            m_table.resize(pos+1);
            for(const auto & ob_pair : m_table[pos]){
                if(ob_pair.second == data){
                    throw std::invalid_argument {"Data must be unique"};
                }     
            }
            m_table[pos].emplace_front(std::move(key),std::move(data));
        }
        const std::pair<Key,Type> & search(const Key & key) const {
            auto pos {HashFunc{}(key)};
            if(pos >= size()) throw std::invalid_argument{"There is no created object with this Key"};

            for(const auto & ob_pair : m_table[pos]){
                if(ob_pair.first == key ) return ob_pair;
            }
            throw std::invalid_argument{"There is no matches"};
        }

        inline const Type getByKey(const Key & key) const{
            return search(key).second;
        }

        //MISC.
        void print() const{
            for(const auto & list: m_table){
                for(const auto & ob : list) {
                    const auto & [x,y] {ob};
                    std::cout<<x<<' '<<y<<'\n';
                }
                std::cout<<std::endl;
            }
        }
        inline bool isEmpty() const {
            return m_table.size() == 0;
        }

        size_t size() const{
            size_t N{};
            for(const auto & list: m_table){
                for(const auto & ob_pair : list){
                    ++N;
                }
            }
            return N;
        }
        //size_t size() {return m_table.size(}

        private:

        //метод-цепочек
        std::vector<std::forward_list<std::pair<Key,Type>>> m_table;
        size_t m_capasity {500};
    };
}
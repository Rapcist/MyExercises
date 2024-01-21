module;
#include <iostream>
#include <vector>
#include <typeinfo>

export module def;


using namespace std;

export namespace Solutions {
    //Не судите строго я впервые тесты пишу с помощью классов и template pattern
    class Test {
        public:
        Test() = default;
        Test(vector<vector<int>> ob) : m_tests {std::move(ob)} {}


        const vector<vector<int>> & getTests() const{
            return m_tests;
        }
        private:
        vector<vector<int>> m_tests;
    };

    class Solution {
        protected:
        static inline Test m_tests;

        private:

        virtual size_t getResult(const vector<int> & test) const = 0;
        virtual void initTests() = 0;
        
        public:

        virtual ~Solution() = default;

        void solution() {

            initTests();

            for(const auto & test : m_tests.getTests()){
                cout<<getResult(test)<<endl;
            }
        }
    };
    class First : public Solution {

        private:

        size_t getResult(const vector<int> & test) const override{
            size_t N { test.size()+2};
            for(size_t i {}; i< test.size(); ++i){
                for(size_t j {}; j< test.size(); ++j){
                    if(test[i] + test[j] == N) break;
                    if( j == test.size() - 1 ) return N-test[i];
                }
            }
            return {};
        }
        //not cool anyway
        void initTests() override {
            m_tests = std::move( Test{ {{1,2,3,5},{7,8,1,3,4,5,6},{6,1,3,2,4}} }) ;
        }
    };

    class Second : public Solution {
        static inline vector<vector<int>> tests ;
        public:
        size_t getResult(const vector<int> & test) const override{
            size_t N {};
            for(size_t i{1} ; i < test.size(); ++i) {
                if(test[i]>test[i-1]) ++N;
            }
            return N;
        }
        void initTests() override {
            m_tests = std::move( Test{ {{1,2,3,5},{7,8,1,3,4,5,6},{6,1,3,2,4},{5,523,623,32,3,6,3,22}} }) ;
        }
    };
    class Third : public Solution {
        public:
        size_t getResult(const vector<int> & test) const override {
            int nummax {0},secondmax{0};
            for(size_t i{0} ; i < test.size(); ++i){
                if(test[i] >= nummax){
                    secondmax = nummax;
                    nummax = test[i];
                }
            }
            return secondmax;

        }
        void initTests() override {
            m_tests = std::move( Test{ {{1,2,3,5},{7,8,1,3,4,5,6},{6,1,6,3,2,4},{5,523,623,32,3,6,3,22}} }) ;
        }
    };
   // class Forth : public 
}
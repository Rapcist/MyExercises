#include <iostream>
#include <memory>
import def;


using namespace Solutions;
using namespace std;

int main(int, char**){
    int s{-1};
    do{
        cout<<"Choose the Test: 1 2 3...(enter the number)\n";
        cin >> s;
        if(cin.bad()){
            cerr<<"Error 1";
        }
        unique_ptr<Solution> test {};
        
        if(s == 1) {
            test = make_unique<First>();
        }
        if( s == 2){
            test = make_unique<Second>();
        }
        if( s == 3) {
            test = make_unique<Third>();
        }
        if(test != nullptr) test->solution();
    } while( s != 0);
}

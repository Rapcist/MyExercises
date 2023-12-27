#include <iostream>
#include<format>
#include<typeinfo>
#include <string>
import ex1;
using namespace std;
using namespace Ex;
int main(){
    KeyValuePair ob {1, "str"s}; //CTAD is working fine :D
    ob.setKey(1487);
    ob.setValue(ob.getValue() + " c++");
    cout<<ob.getKey() + 1<< ' ' << ob.getValue();

    KeyValuePair ob2{"Zig","Hiel"};
    cout<<std::format("{} {}!",ob2.getKey(),ob2.getValue());
    //cout<<ob2.getKey()+ob2.getValue();
    cout<<typeid(ob2.getKey()).name()<<' '<<foo();

    KeyValuePair two{1,1};
    cout<<endl<<typeid(ob.getKey()).name();
    

}

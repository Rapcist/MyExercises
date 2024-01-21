import hash;
#include <iostream>


using namespace std;
using namespace HASHI;
int main(){
    Hash_table<int, char> test1;
    test1.insert(5, 'a');
    test1.insert(7,'b');
    test1.insert(9,'c');
    test1.insert(16, '3');
    test1.insert(17,'4');

    auto [x,y] {test1.search(17)};
    cout<<x<<y<<endl;
    test1.print();
}
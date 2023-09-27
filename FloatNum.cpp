#include <iostream>
#include <vector>
#include <format>
using namespace std;

int main() {
  vector<double> arr;
  //конечно можно и без дополнительной перем.,
  //но она у меня в массив попадает:((
  double tmp{1};
  while(cin>>tmp){
    arr.push_back(tmp);
  }
  cout<<"Res:\n";
  for(auto db : arr){
    auto s {format("\n|{0:<8.3e}|{0:#>+12.5f}|{0:?^16.7g}|\n",db)};
    cout<<s;
    for(auto ch: s) cout<<"=";
  }
}

#include <iostream>
#include <vector>
#include <format>
using namespace std;

int main() {
  vector<double> arr;
  double tmp{1};
  cin>>tmp;
  while(tmp){
    arr.push_back(tmp);
    cin>>tmp;
  }
  cout<<"Res:\n";
  for(int i{0};i< 50;++i) cout<<"=";
  for(auto db : arr){
    auto s {format("\n|{0:.<16.3e}|{0:#>+12.5f}|{0:?^16.7g}|\n",db)};
    cout<<s;
    for(auto ch: s) cout<<"=";
  }
}
//std::vector<basic_string<char>> s;
//auto s {f()}
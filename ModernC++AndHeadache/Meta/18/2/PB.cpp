module;
#include <vector>
#include <map>
#include <stdexcept>
#include <iterator>
module phone_book;

using namespace std;

void PhoneBook::addPhoneNumber(const Person& person, string_view phoneNumber){
	/*
	auto [begin, end]{ m_phoneBook.equal_range(person) };
	for (auto iter{ begin }; iter != end; ++iter) {
		if(iter->second == phoneNumber ) throw invalid_argument{"Why do we need duplicate numbers?"};
	}
	*/
	m_phoneBook.insert(make_pair(person,phoneNumber)};
} 

void PhoneBook::removePhoneNumber(const Person& person, string_view phoneNumber){
	auto [begin, end]{ m_phoneBook.equal_range(person) };
	for (auto iter{ begin }; iter != end; ++iter) {
		if (iter->second == phoneNumber) {
			m_phoneBook.erase(iter);
			break;
		}
	}
	
}
vector<string> PhoneBook::getPhoneNumbers(const Person& person) const{
	/*
	auto view {
		views::common { m_phoheBook | views::transform([](const auto & p) {return p.second;} }
	};
	*/
	auto [begin, end]{ m_phoneBook.equal_range(person) };
	
	vector<string> result;
	result.reserve(distance(it,endit));
	
	for(auto iter{begin};iter != end; ++iter) {
		result.push_back(iter->second);
	}
	return result;
}
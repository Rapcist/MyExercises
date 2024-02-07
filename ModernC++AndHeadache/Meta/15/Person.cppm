export module person;

import <string>;
import <format>;
import <compare>;
import <ostream>;

export class Person
{
public:
	// Two-parameter constructor automatically creates initials and
	// delegates the work to the three-parameter constructor.
	Person(std::string firstName, std::string lastName)
		: Person{ std::move(firstName), std::move(lastName),
		std::format("{}{}", firstName[0], lastName[0]) }
	{
	}

	Person() = default;

	Person(std::string firstName, std::string lastName, std::string initials)
		: m_firstName{ std::move(firstName) }
		, m_lastName{ std::move(lastName) }
		, m_initials{ std::move(initials) }
	{
	}

	const std::string& getFirstName() const { return m_firstName; }
	void setFirstName(std::string firstName) { m_firstName = std::move(firstName); }

	const std::string& getLastName() const { return m_lastName; }
	void setLastName(std::string lastName) { m_lastName = std::move(lastName); }

	const std::string& getInitials() const { return m_initials; }
	void setInitials(std::string initials) { m_initials = std::move(initials); }

	void output(std::ostream& output) const
	{
		output << std::format("{} {} ({})",
			getFirstName(), getLastName(), getInitials()) << std::endl;
	}

	// Only this single line of code is needed to add support
	// for all six comparison operators.
	[[nodiscard]] auto operator<=>(const Person&) const = default;
	operator std::string() const {
		return std::format("{} {}",getFirstName(),getLastName());
	}
private:
	std::string m_firstName;
	std::string m_lastName;
	std::string m_initials;
};

std::istream & operator>>(std::istream & in , Person & ob) {
	std::string fName,lName;
	
	in>>std::quoted(fName)>>std::quoted(nName);
	if(in.bad()) throw std::runtine_error {"error while reading person"};
	
	ob.setFirstName(std::move(fName));
	ob.setLastName(std::move(lName));
	ob.setInitials(std::(std::format("{}{}",fName[0],lName[0])));
	return in;
}
std::ostream & operator<<(std::ostream & out, const Person & ob) {
	out<<std::quoted(ob.getFirstName())<<std::quoted(ob.getLastName());
	if(out.bad()) throw std::runtine_error {"error while writing person"};
	return out;
}

Person operator"" _p(const char *ptr, size_t len){
	std::stringstream input{ptr};
	
	std::string firstname,lastname;
	input>>firstname;
	
	input>>std::ws;
	
	//reading 'odd'(to support lastnames with more than one words) last name : "Van der tick"
	std::getline(input, lastname);
	
	return Person{std::move(firstname),std::move(lastname)};
}
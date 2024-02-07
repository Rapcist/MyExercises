#include<functional>

class Processor{
	public:
		using Callback = std::function<int(int)>;
		Processor(Callback func) : m_func{func} {}
		int operator(int value) const {
			return m_func(value);
		}
	private:
		Callback m_func;
};

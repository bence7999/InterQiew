#include "Excercices.h"
#include <list>
#include <vector>
#include <algorithm>

namespace Ex10 {

	class Int
	{
	public:
		Int(int i = 0) : m_i(i) { }

	public:
		bool operator<(const Int& a) const { return this->m_i < a.m_i; }

		Int& operator=(const Int &a)
		{
			this->m_i = a.m_i;
			++m_assignments;
			return *this;
		}

		static int get_assignments() { return m_assignments; }

	private:
		int m_i;
		static int m_assignments;
	};

	int Int::m_assignments = 0;

	// std::sort vs list::sort

	void Excercise_10()
	{
		std::list<Int> l({ Int(3), Int(1) });
		l.sort(); // nins = opertor
		std::cout << (Int::get_assignments() > 0 ? 1 : 0);

		std::vector<Int> v({ Int(2), Int() });
		std::sort(v.begin(), v.end()); // van = operator
		std::cout << (Int::get_assignments() > 0 ? 2 : 0) << std::endl;
	}
}
#include "Excercices.h"

namespace Ex20 {
	class A
	{
	public:
		A(int n = 0) : m_i(n) { std::cout << m_i; }

	protected:
		int m_i;
	};

	class B
		: public A
	{
	public:
		B(int n) : m_j(n), m_a(--m_j), m_b() { std::cout << m_j; } // az m_j 1-é decrementálódik

	private:
		int m_j;
		A m_a;
		A m_b;
		static A m_c;
	};

	void Excercise_20()
	{
		B b(2);

		std::cout << std::endl;

	}

	//A B::m_c(3); // ez fut le legelőször - még a Excercise_20() meghívása előtt
}
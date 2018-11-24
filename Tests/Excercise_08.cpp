#include "Excercices.h"

namespace Ex08 {
	class A
	{
	public:
		A(int n = 0)
			: m_i(n)
		{
			std::cout << m_i;
			++m_i;
		}

	protected:
		int m_i;
	};

	class B
		: public A
	{
	public:
		B(int n = 5) : 
			m_a(new A[2]),  // végül m_a, mert ő az utolsó
			m_x(++m_i)      // m_x a 2., mivel ő szerepel hamarabb a deklarációban
		{					// legelőször az Ős hívódik fel (A)
				std::cout << m_i; 
		}

		~B() { delete[] m_a; }

	private:
		A m_x;  //
		A *m_a; // 
	};

	void Excercise_08()
	{
		B b;

		std::cout << std::endl;

	}

	class W {
	public:
		W(int a = 0) {
			std::cout << a << std::endl;
		}
	};

	void Extra01() {
		W *pw = new W[2];
	}
}
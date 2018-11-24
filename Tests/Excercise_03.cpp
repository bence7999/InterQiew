#include "Excercices.h"

namespace Ex03 {
	class A
	{
	public:
		A(int n = 2) : m_i(n) { }

		~A() { std::cout << m_i; }

	protected:
		int m_i;
	};

	class B
		: public A
	{
	public:
		B(int n) : m_a1(m_i + 1), m_a2(n) { }

	public:
		~B()
		{
			std::cout << m_i;
			--m_i;
		}

	private:
		A m_a1;
		A m_a2;
	};

	void Excercise_03()
	{
		{ 
			B b(5); // 1. B destructor; Máosdjára konstruált A(5) destruktor-a; Elsőre kontruált A(m_i+1) destructora; B ősének a A(2) destrukctora 
		}			// a felépített fában megy visszafelé, elégen az ős-ig

		std::cout << std::endl;
	}

	class C {
	public:
		C(int n = 10) : v(n) { }
		~C() { std::cout << v; }
	protected:
		int v;
	};

	class D : public C {
	public:
		D(int m) : w(m) { }
		~D() { std::cout << w; }
	protected:
		int w;
	};

	void Extra01() {

		{ D d(1); }

	}

}
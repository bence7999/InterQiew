#include "Excercices.h"

namespace Ex12 {

	class A
	{
	public:
		A(int n) : m_n(n) { std::cout << m_n; }

		~A() { std::cout << m_n; }

	private:
		int m_n;
	};

	int f(int n)
	{
		if (1 == n) {
			throw std::logic_error("0"); //megszakad a fut�s, de a destru�l�s megt�rt�nik
		}
		A l(n);
		return f(n - 1) * n / (n - 1);
	}

	void Excercise_12()
	{
		try {
			int r = f(3);
			A a(r);
		}
		catch (const std::exception &e) { // csak a destru�l�s ut�n fut bele a catch-�gba!
			std::cout << e.what() << std::endl;
		}
	}
}
#include "Excercices.h"

namespace Ex04 {
	class A
	{
	public:
		A() : m_i(0) { }

	protected:
		int m_i;
	};

	class B
	{
	public:
		B() : m_d(0.0) { }

	protected:
		double m_d;
	};

	class C
		: public A
		, public B
	{
	public:
		C() : m_c('a') { }

	private:
		char m_c;
	};

	void Excercise_04()
	{
		C c;
		A *pa = &c; // A t�pusu pointer c c�m�re
		B *pb = &c; // B t�pusu pointer c c�m�re

		const int x = (pa == &c) ? 1 : 2; // the two address is equal
		const int y = (pb == &c) ? 3 : 4; // the two address is equal

		const int z = (reinterpret_cast<char*>(pa) == reinterpret_cast<char*>(pb)) ? 5 : 6; // mivel m�s t�pus� pointerek, �gy nem fog megegyezni a reinterpret_cast-juk

		std::cout << x << y << z << std::endl;

	}
}
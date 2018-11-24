#include "Excercices.h"

namespace Ex06 {

	class A
	{
	public:
		A() : m_x(0) { }

	public:
		static ptrdiff_t member_offset(const A &a)
		{
			const char *p = reinterpret_cast<const char*>(&a);
			const char *q = reinterpret_cast<const char*>(&a);

			return q - p;
		}

	private:
		int m_x;
	};

	class B
		: public A
	{
	public:
		B() : m_x('a') { }

	public:
		static int m_n;

	public:
		static ptrdiff_t member_offset(const B &b)
		{
			const char *p = reinterpret_cast<const char*>(&b);
			const char *q = reinterpret_cast<const char*>(&b.m_x);

			return q - p;
		}

	private:
		char m_x;
	};

	int B::m_n = 1;

	class C
	{
	public:
		C() : m_x(0) { }
		virtual ~C() { }

	public:
		static ptrdiff_t member_offset(const C &c)
		{
			const char *p = reinterpret_cast<const char*>(&c);
			const char *q = reinterpret_cast<const char*>(&c.m_x);

			return q - p;
		}

	private:
		int m_x;
	};

	void Excercise_06()
	{
		A a;
		B b;
		C c;
		std::cout << ((A::member_offset(a) == 0) ? 0 : 1); // A-nak csak egy változója van m_x, szóval valójában a változó címe maga a példány címe
		std::cout << ((B::member_offset(b) == 0) ? 0 : 2); // B-nek van egy static változója is m_x mellett, valamit leszármazott, így nem az m_x címe mutat a példányra
		std::cout << ((A::member_offset(b) == 0) ? 0 : 3); // A-nak és B-nek is van m_x változója, mikor A fv-ét meghívjuk b-re, mivel leszármazott inplicit castolodik A-ra, aminke meg van m_x-je, arra nézni az egyenlőséget
		std::cout << ((C::member_offset(c) == 0) ? 0 : 4); // C-nek val virtual method-ja, így nem az m_x mutat a címére
		std::cout << std::endl;

	}
}
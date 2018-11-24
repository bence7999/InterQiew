#include "Excercices.h"

#include <vector>

namespace Ex02 {

	class A
	{
	public:
		A(int n = 0) : m_n(n) { }

	public:
		virtual int f() const { return m_n; }
		virtual ~A() { }

	protected:
		int m_n;
	};

	class B
		: public A
	{
	public:
		B(int n = 0) : A(n) { }

	public:
		virtual int f() const { return m_n + 1; }
	};

	void Excercise_02()
	{
		const A a(1);
		const B b(3);
		const A *x[2] = { &a, &b }; // A typusu pointer ->
		typedef std::vector<A> V; // A típusu a cevtor
		V y({ a, b }); // A és B típusu elemek -> vector<A> miatt -> A
		V::const_iterator i = y.begin();

		std::cout << x[0]->f() << x[1]->f() // A::f() & B::f() -> virtual az f()
			<< i->f() << (i + 1)->f() << std::endl; // 

	}

	void Extra01() {
		const A a(1);
		const B b(3);

		A* aa = new A(4); // A::f()
		B* bb = new B(6); // B::f()

		std::cout << aa->f() << " " << bb->f() << std::endl;

		A *c = new B(2); // B::f()
		std::cout << c->f() << std::endl; // mivel virtual az f(), bár a A* típusi, a B hívódik fel

		std::vector<A> v{ a, b };
		std::vector<A>::iterator i = v.begin();
		std::cout << i->f() << " " << (i+1)->f() << std::endl; // A tious miatt -> A::f(), A::f()
		
	}
}
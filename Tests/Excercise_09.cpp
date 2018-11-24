#include "Excercices.h"

namespace Ex09 {

	class A
	{
	public:
		A() {}

	public:
		virtual void f(int n) { std::cout << n << 1; }
		virtual ~A() { }

		void f(int n) const { std::cout << n; }
	};

	class B
		: public A
	{
	public:
		void f(int n) { std::cout << (n << 1); }

		void f(int n) const { std::cout << n + 1; }
	};

	void Excercise_09()
	{
		const A a;
		B b;
		A &c = b;
		const A *d = &b;

		a.f(2); // mivel const A típusi, a const f() fv-e fut le
		b.f(2); // nem const, és van a B-nek is  f() vf-e, az fut le
		c.f(1); // A tipusu referencia B::b-re, nem const, és mivel A nem cost f() fv-e virtual, B::f() hívodik meg
		d->f(1); // const A típusú pointer mutat B::b címére, mivel const A::f() nem virtual, A virtual f() fv fut le   

		std::cout << std::endl;

	}

	void Extra01() {
		const B b;
		const A &b1 = b;
		b1.f(1);
		const A *b2 = &b;
		b2->f(1);
	}

}
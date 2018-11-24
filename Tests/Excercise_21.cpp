#include "Excercices.h"

namespace Ex21 {
	class A
	{
	public:
		A() { f(); }

		virtual ~A() { }

	public:
		virtual void f() const { std::cout << 1; }
	};

	class B
		: public A
	{
	public:
		B() { f(); }

	private:
		virtual void f() const { std::cout << 2; }
	};

	void Excercise_21()
	{
		const A *a = new B; // B először meghívja A()-t, majd azután fut le B()
		delete a;

		std::cout << std::endl;
	}

	class C
	{
	public:
		C() { f(); }

		virtual ~C() { }

	public:
		virtual void f(int i = 3) const { std::cout << 1 << " " << i << std::endl; }
	};

	class D
		: public C
	{
	public:
		D() { f(); }

	private:
		virtual void f(int i = 4) const { std::cout << 2 << " " << i << std::endl; }
	};

	void Extra01() {
		const C *c = new D;  // 13 -> lefut C() constructor-a, 24 -> lefut D() constructor-a
		c->f(); // 23 -> run time polymorph
		delete c;

		std::cout << std::endl;
	}
}
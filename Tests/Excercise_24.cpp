#include "Excercices.h"

namespace Ex24 {
	class A
	{
	public:
		virtual ~A() { f(); }

	public:
		virtual void f() const { std::cout << 1; }
	};

	class B
		: public A
	{
	public:
		~B() { f(); }

	private:
		virtual void f() const { std::cout << 2; }
	};

	void Excercise_24()
	{
		const A *a = new B;
		delete a; // a destruálás fordított sorrendben történk mint a construálás
				  // először hívódik meg a ~B(), majd az ~A()

		std::cout << std::endl;
	}

	class C {
	public:
		virtual ~C() { f(); }
	public:
		void f() { std::cout << 1; }
	};

	class D : public C {
	public:
		~D() { f(); }
	private:
		void f() { std::cout << 2; }
	};

	void Extra01() {
		C *c = new D;
		delete c; // ha nem virtual a C destructor-a csak 1 íródik ki, mert nem kapja meg a D 
				  // ha virtual a C destructor-a, akkor 21 íródik ki, mert előbb lebut a D-é, aztán a C-é
	}
}
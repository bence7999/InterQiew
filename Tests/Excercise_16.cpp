#include "Excercices.h"

namespace Ex16 {
	class B
	{
	public:
		virtual int shift(int n = 2) const {
			return n << 2; 
		}
	};

	class D
		: public B
	{
	public:
		D() {}

	public:
		int shift(int n = 3) const { 
			return n << 3; 
		}
	};

	void Excercise_16()
	{
		const D d;
		const B *b = &d;

		std::cout << b->shift() << std::endl;

	}

	void Extra01() {
		const B b;
		std::cout << b.shift() << std::endl; // általános működés: 8

		const D d;
		std::cout << d.shift() << std::endl; // általános működés: 24
	}

	class A {
	public:
		int shift(int n = 2) const {
			return n << 2;
		}
	};

	class C : public A {
	public:
		int shift(int n = 3) const {
			return n << 3;
		}
	};

	void Extra02() {
		const C c;
		const A *a = &c;

		std::cout << a->shift() << std::endl; // 8 -> nem virtual a shift, A::shift hívódik meg
	}

	//Polymorphism and virtual functions -> https://www.geeksforgeeks.org/virtual-functions-and-runtime-polymorphism-in-c-set-1-introduction/

	class Base
	{
	public:
		virtual void show(int i = 5) { std::cout << " In Base \n"; std::cout << i << std::endl; }
	};

	class Derived : public Base
	{
	public:
		void show(int i = 1) { std::cout << "In Derived \n"; std::cout << i << std::endl; }
	};

	void Extra03() {
		Base *bp = new Derived;
		bp->show();  // RUN-TIME POLYMORPHISM => In Derived  5
		bp->show(3); //  =>  In Derived  3
	}
}
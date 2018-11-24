#include "Excercices.h"

namespace Ex17 {
	class A
	{
	public:
		A(int n = 2) : m_n(n) {}

	public:
		int get_n() const { return m_n; }
		void set_n(int n) { m_n = n; }

	private:
		int m_n;
	};

	class B
	{
	public:
		B(char c = 'a') : m_c(c) {}

	public:
		char get_c() const { return m_c; }
		void set_c(char c) { m_c = c; }

	private:
		char m_c;
	};

	class C
		: virtual public A // csak egy példány lesz A-ból
		, public B
	{ };

	class D
		: virtual public A // csak egy példány lesz A-ból
		, public B
	{ };

	class E
		: public C
		, public D
	{ };

	void Excercise_17()
	{
		E e; // C -> A::m_n=3, B::m_c ='a'; D -> A::m_n=3, B::m_c='a' => mivel virtual public A -> A ból csak egy példány lesz
		C &c = e; // 
		D &d = e; // 
		std::cout << c.get_c() << d.get_n(); // 

		c.set_n(3); // c-n állítja be 3-t => mivel virtual bublic A => ez hat D-re is
		d.set_c('b'); // d-n állítja be a b-t => mivel nem virtual public B => ez nem hat C-ra
		std::cout << c.get_c() << d.get_n() << std::endl; // C-n kéri le a m_n-et (D-n írtuk át), D-n kéri le az m_n-et (C-n írtuk át) --> mivel A virtuaé public ez hatott D-re is
	}

	class Base1 {
	public:
		Base1(int n = 0) : m_n(n) {}
		void Print() {
			std::cout << m_n << std::endl;
		}
	private:
		int m_n;
	};

	class Drived1 : public Base1 {
	public:
		void Print2() {
			std::cout << "print" << std::endl;
		}
	};

	void Extra01() {
		Drived1 d1;
		d1.Print(); // print
		Base1 *b = &d1;
		b->Print(); // 0 -> mert nem virtual a base Print
	}

	class Drived2 : public Base1 {
	public:
		void Print2() {
			std::cout << "print2" << std::endl;
		}
	};

	class DrivedDrived1 : public Drived1, public Drived2 {

	};

	void Extra02() {
		DrivedDrived1 dd1;
		Drived1 *d1 = &dd1;
		d1->Print(); // 0
		d1->Print2(); // print
		Drived2 *d2 = &dd1;
		d2->Print(); // 0
		d2->Print2(); // print2

		//dd1.Print(); // ambigouos
	}

	class Base2 {
	public:
		Base2(char c = 'b') : n_n(c) {}
		void Print() {
			std::cout << n_n << std::endl;
		}
	private:
		char n_n;
	};

	class Drived3 : public virtual Base2 {
	public:
		void Print2() {
			std::cout << "drived print" << std::endl;
		}
	};

	class Drived4 : public virtual Base2 {
	public:
		void Print2() {
			std::cout << "drived print2" << std::endl;
		}
	};

	class DrivedDrived2 : public Drived3, public Drived4{

	};

	void Extra03() {
		DrivedDrived2 dd1;
		dd1.Print(); // b
		//dd1.Print2(); // ambigouos
	}

	class BaseA {
	public:
		BaseA(int n = 5) : m_n(n) {}
		void Print() {
			std::cout << "baseA" << std::endl;
		}
	private:
		int m_n;
	};

	class BaseB {
	public:
		BaseB(char c = 'w') : m_c(c) {}
		void Print() {
			std::cout << "baseB" << std::endl;
		}
	private:
		char m_c;
	};

	class DrivedAB : virtual public A, public B {

	};

	class DrivedBA : public B, virtual public A {

	};

	class DrivedA : virtual public BaseA, public BaseB {

	};

	class DrivedB : public BaseA, virtual public BaseB {

	};

	void Extra04() {
		DrivedA da;
		//da.Print(); // ambigouos
		BaseA *ba = &da;
		ba->Print(); // baseA 
		BaseB *b = &da;
		b->Print(); // baseB

		DrivedB db;
		//db.Print(); // ambigouos
		BaseB *bb = &db;
		bb->Print(); // baseB
		BaseA *a = &db;
		a->Print(); // baseA
	}

	class A2
	{
	public:
		A2(int n = 2) : m_n(n) {}

	public:
		int get_n() const { return m_n; }
		void set_n(int n) { m_n = n; }

	private:
		int m_n;
	};

	class C2 : public A2 {

	};

	class C2V : virtual public A2 {

	};

	void Extra05() {
		C2 c2;
		std::cout << c2.get_n() << std::endl; // 2
		c2.set_n(3);
		std::cout << c2.get_n() << std::endl; // 3
		A2 *a21 = &c2;
		std::cout << a21->get_n() << std::endl; // 3
		a21->set_n(4);
		std::cout << a21->get_n() << std::endl; // 4

		C2V c2v;
		std::cout << c2v.get_n() << std::endl; // 2
		c2v.set_n(3);
		std::cout << c2v.get_n() << std::endl; // 3
		A2 *a22 = &c2v;
		std::cout << a22->get_n() << std::endl; // 3
		a22->set_n(4);
		std::cout << a22->get_n() << std::endl; // 4

	}

	class E2CV : public C2V {

	};

	class E2V : public C2 {

	};

	void Extra06() {
		E2CV e2cv;
		std::cout << e2cv.get_n() << std::endl; // 2
		e2cv.set_n(3);
		std::cout << e2cv.get_n() << std::endl; // 3

		C2V *c2v = &e2cv;
		std::cout << c2v->get_n() << std::endl; // 3
		c2v->set_n(4);
		std::cout << c2v->get_n() << std::endl; // 4

		A2 *a21 = &e2cv;
		std::cout << a21->get_n() << std::endl; // 4
		a21->set_n(5);
		std::cout << a21->get_n() << std::endl; // 5

		E2V e2v;
		std::cout << e2v.get_n() << std::endl; // 2
		e2v.set_n(3);
		std::cout << e2v.get_n() << std::endl; // 3

		C2 *c2 = &e2v;
		std::cout << c2->get_n() << std::endl; // 3
		c2->set_n(4);
		std::cout << c2->get_n() << std::endl; // 4

		A2 *a22 = &e2v;
		std::cout << a22->get_n() << std::endl; // 4
		a22->set_n(5);
		std::cout << a22->get_n() << std::endl; // 5

	}

}
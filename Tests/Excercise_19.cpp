#include "Excercices.h"
#include <functional> 
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>

namespace Ex19 {

	class A
	{
	public:
		A() : m_size(sizeof(A)) { // 8 byte -> virtual table (4), variable (4)
			std::cout << "A: " << m_size << std::endl;
		}

	public:
		virtual void f() const { std::cout << 1; }
		virtual ~A() { }

	public:
		static bool compare(const A *a, const A *b)
		{
			assert(a != nullptr);
			assert(b != nullptr);
			return a->m_size < b->m_size;
		}

	protected:
		size_t m_size;
	};

	class B
		: public A
	{
	public:
		B() : m_b(nullptr) { 
			m_size = sizeof(B); // 12 byte -> A (8), +1 char* param(4)
			std::cout << "B: " << m_size << std::endl;
		}

	public:
		virtual void f() const { std::cout << 2; }

	private:
		char *m_b;
	};

	class C
		: public A
	{
	public:
		C() { 
			m_size = sizeof(C); // 8 byte -> A (8), static int* nem növeli a méretét
			std::cout << "C: " << m_size << std::endl;
		}

	public:
		virtual void f() const { std::cout << 3; }

	private:
		static int *m_c;
	};

	int *C::m_c = nullptr;

	void Excercise_19()
	{
		std::vector<A*> v({ new C, new B, new A });
		std::stable_sort(v.begin(), v.end(), A::compare);
		std::for_each(v.begin(), v.end(), std::mem_fn(&A::f));
		std::cout << std::endl;
		std::for_each(v.begin(), v.end(), std::default_delete<A>());

	}

	void Extra05() {
		A *a = new A(); // m_a = 8 -> maga a class 4b + virtual table 4b
		B *b = new B(); // m_b = 12 -> maga b class 4b + a class 4b + virtual table 4b
		C *c = new C(); // m_c = 8  ->  maga c class 1b (static miatt) + a class 4b + virtual table 4b
	}

	// std::mem_fn 

	struct int_holder {
		int value;
		int triple() { return value * 3; }
	};

	void Extra01() {
		int_holder five{ 5 };

		std::cout << five.triple() << '\n';

		auto triple = std::mem_fn(&int_holder::triple);
		std::cout << triple(five) << '\n';
	}

	struct Foo {
		void display_greeting() {
			std::cout << "Hello, world.\n";
		}
		void display_number(int i) {
			std::cout << "number: " << i << '\n';
		}
		int data = 7;
	};

	void Extra02(){
		Foo f;

		auto greet = std::mem_fn(&Foo::display_greeting);
		greet(f);

		auto print_num = std::mem_fn(&Foo::display_number);
		print_num(f, 42);

		auto access_data = std::mem_fn(&Foo::data);
		std::cout << "data: " << access_data(f) << '\n';
	}

	// std::stable_sort

	struct Employee {
		int age;
		std::string name;  // Does not participate in comparisons
	};

	bool operator<(const Employee &lhs, const Employee &rhs) {
		return lhs.age < rhs.age;
	}

	void Extra03() {
		std::vector<Employee> v = {
			{108, "Zaphod"},
			{32, "Arthur"},
			{108, "Ford"},
		};

		std::stable_sort(v.begin(), v.end());

		for (const Employee &e : v) {
			std::cout << e.age << ", " << e.name << '\n';
		}
	}

	bool compare_as_ints(double i, double j)
	{
		return (int(i) < int(j));
	}

	void Extra04() {
		double mydoubles[] = { 3.14, 1.41, 2.72, 4.67, 1.73, 1.32, 1.62, 2.58 };

		std::vector<double> myvector;

		myvector.assign(mydoubles, mydoubles + 8);

		std::cout << "using default comparison:";
		std::stable_sort(myvector.begin(), myvector.end());
		for (std::vector<double>::iterator it = myvector.begin(); it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		myvector.assign(mydoubles, mydoubles + 8);

		std::cout << "using 'compare_as_ints' :";
		std::stable_sort(myvector.begin(), myvector.end(), compare_as_ints);
		for (std::vector<double>::iterator it = myvector.begin(); it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// class sizes

	class SizeA {

	};

	class SizeB {
	public:
		SizeB() = default;
	};

	class SizeC {
		
	private:
		int m_n;
	};

	class SizeD {
	public:
		SizeD(int n = 1) : m_n(n) { }
	private:
		int m_n;
	};

	class SizeE {
	public:
		void print() { }
	};

	class SizeF {
	public:
		virtual void print() { }
	};

	class SizeG {
	public:
		SizeG(int n = 1) : m_n(n) { }
		virtual void print() {}
	private:
		int m_n;
	};

	void Extra06() {
		SizeA a;
		std::cout << "A: " << sizeof(SizeA) << std::endl; // 1
		std::cout << "a: " << sizeof(a) << std::endl; // 1

		SizeB b;
		std::cout << "B: " << sizeof(SizeB) << std::endl; // 1
		std::cout << "b: " << sizeof(b) << std::endl; // 1

		SizeC c;
		std::cout << "C: " << sizeof(SizeC) << std::endl; // 4
		std::cout << "c: " << sizeof(c) << std::endl; // 4

		SizeD d(0);
		std::cout << "D: " << sizeof(SizeD) << std::endl; // 4
		std::cout << "d: " << sizeof(d) << std::endl; // 4
		
		SizeE e;
		std::cout << "E: " << sizeof(SizeE) << std::endl; // 1
		std::cout << "e: " << sizeof(e) << std::endl; // 1

		SizeF f;
		std::cout << "F: " << sizeof(SizeF) << std::endl; // 4
		std::cout << "f: " << sizeof(f) << std::endl; // 4

		SizeG g(0);
		std::cout << "G: " << sizeof(SizeG) << std::endl; // 8
		std::cout << "g: " << sizeof(g) << std::endl; // 8
	}

	class DerivedA : public SizeA { };

	class DerivedVA : virtual public SizeA { };

	class DerivedC : public SizeC { };

	class DerivedVC : virtual public SizeC { };

	class DerivedF : public SizeF { };

	class DerivedVF : virtual public SizeF { };

	class DerivedG : public SizeG { };

	class DerivedVG : virtual public SizeG { };


	void Extra07() {

		DerivedA da;
		std::cout << "DerivedA: " << sizeof(DerivedA) << std::endl; // 1

		DerivedVA dva;
		std::cout << "DerivedVA: " << sizeof(DerivedVA) << std::endl; // 4

		DerivedC dc();
		std::cout << "DerivedC: " << sizeof(DerivedC) << std::endl; // 4

		DerivedVC dvc();
		std::cout << "DerivedVC: " << sizeof(DerivedVC) << std::endl; // 8

		DerivedF df;
		std::cout << "DerivedF: " << sizeof(DerivedF) << std::endl; // 4

		DerivedVF dvf;
		std::cout << "DerivedVF: " << sizeof(DerivedVF) << std::endl; // 8

		DerivedG dg;
		std::cout << "DerivedG: " << sizeof(DerivedG) << std::endl; // 8

		DerivedVG dvg;
		std::cout << "DerivedVG: " << sizeof(DerivedVG) << std::endl; // 12

	}

	class DerivedEA : public SizeA {
		// pareméter nélkül: 1
		char *m_b; // 1 paraméterrel: 4
		int m_n; // 2 paraméterrel: 8
		// plusz 2 param + 8 byte
		// char *m_c;
		// int m_m;

		// static
		static int s_n; // nem növeli DerivedEA méretét
		static int *sp_n; // nem növeli DerivedEA méretét
	};

	int DerivedEA::s_n = 0;
	int* DerivedEA::sp_n = new int(0);

	class DerivedEB : public SizeB {

	};

	class DerivedEC : public SizeC {

	};

	class DerivedED : public SizeD {

	};

	class DerivedEE : public SizeE {

	};

	class DerivedEF : public SizeF {

	};

	class DerivedEG : public SizeG {

	};

	void Extra08() {
		DerivedEA dea;
		std::cout << "DerivedEA: " << sizeof(DerivedEA) << std::endl; // 8

	}
}
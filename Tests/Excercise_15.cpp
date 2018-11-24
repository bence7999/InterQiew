#include "Excercices.h"
#include <typeinfo>

namespace Ex15 {
	class A
	{
	public:
		A(int n = 0) : m_n(n) { 
			std::cout << "create A" << std::endl; 
		}
		A(const A &a) : m_n(a.m_n) { 
			++m_copy_ctor_calls; 
			std::cout << "copy A" << std::endl; 
		}
		A& operator=(const A& a)
		{
			this->m_n = a.m_n;
			return *this;
		}
		~A() { 
			++m_dtor_calls; 
			std::cout << "kill A" << std::endl; 
		}

	private:
		int m_n;

	public:
		static int m_copy_ctor_calls;
		static int m_dtor_calls;
	};

	int A::m_copy_ctor_calls = 0;
	int A::m_dtor_calls = 0;

	void Excercise_15()
	{
		A *p = nullptr; // csak egy pointer keletkezik
		{
			const A a = 2; // simple constructor
			p = new A[3]; // 3 A létrejön -> 3 simple constructor
			p[0] = a; //  copy assignment operator
			//std::cout << typeid(a).name() << std::endl; // A
			//std::cout << typeid(p).name() << std::endl; // A*
			//std::cout << typeid(p[0]).name() << std::endl; // A
		} // itt meghal az eredeti a
		std::cout << A::m_copy_ctor_calls << A::m_dtor_calls;
		p[1] = A(1); // keletkezik és meghal egy A => copy assignment operator & destructor
		p[2] = 2; // keletkezik és meghal egy A => copy assignment operator & destructor
		delete[] p; // 3 destructor lefut
		std::cout << A::m_copy_ctor_calls << A::m_dtor_calls << std::endl;

	}

	class B {
	public:
		B(int n = 0) : m_n(n) { std::cout << "create B" << std::endl; }
		~B() { std::cout << "kill B" << std::endl; }
	private:
		int m_n;
		int m_m;
	};

	void Extra01() {
		A a = 2; //m_n = 2
		B b = 1; // m_n = 1, m_m = ?????
		A a1 = A(3); //m_n = 3

		{
			A a3 = a;
		}

	}

	void Extra02() {
		B *bp = nullptr;
		{
			const B b = 3;
		}
	}

	void Extra03() {
		B *bp = nullptr;
		{ 
			bp = new B[3]; // 3 B created
		}
		// 3 B még él
		delete[] bp; // 3 B killed
	}

	void Extra04() {
		B *bp = nullptr;
		{
			bp = new B[3];
		}
		bp[0] = B(1); // 
		B b = B(2);
		bp[1] = 2; // 
		B b2 = 1;
		delete[] bp;
	}

	// Copy assignment operator


}
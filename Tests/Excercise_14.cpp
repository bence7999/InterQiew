#include "Excercices.h"

namespace Ex14 {
	class A
	{
	public:
		explicit A(int n = 0) : m_n(n) { 
			++m_initialization_calls; 
		}
		// Copy constructor 
		A(const A &a) { 
			m_n = a.m_n; 
			++m_copyctor_calls; 
		}
	public:
		A& operator=(const A& a)
		{
			this->m_n = a.m_n;
			++m_assignment_calls;
			return *this;
		}

	public:
		static int m_assignment_calls;
		static int m_copyctor_calls;
		static int m_initialization_calls;

	private:
		int m_n;
	};

	int A::m_assignment_calls = 0;
	int A::m_copyctor_calls = 0;
	int A::m_initialization_calls = 0;

	A f(const A& a) // ha referenciát kap, csak 1 copy ctorhívódik meg
	{ 
		return a; 
	}

	A g(const A a)  // függvényhíváskor 2 copy ctor hívódik meg
	{ 
		return a; 
	}

	void Excercise_14()
	{
		A a(3); // initialization
		A b = a; // nem használja az értékadó operator-t -> default copy constructor-t hasznal // copy ctor nem referenciát használ
		std::cout << A::m_initialization_calls << " ";
		std::cout << A::m_assignment_calls << " ";
		std::cout << A::m_copyctor_calls << std::endl;

		b = g(a); // csak itt használja az értékadó operator-t és a default copy constructor-t is // 
		g(b);
		std::cout << A::m_initialization_calls << " ";
		std::cout << A::m_assignment_calls << " ";
		std::cout << A::m_copyctor_calls << std::endl;

		const A& c = f(b); // nem használja az értékadó operator-t -> default copy constructor-t hasznal // 
		std::cout << A::m_initialization_calls << " ";
		std::cout << A::m_assignment_calls << " ";
		std::cout << A::m_copyctor_calls << std::endl;
	}

	//explicit specifier
	struct C
	{
		C(int) { }      // converting constructor
		C(int, int) { } // converting constructor (C++11)
		operator bool() const { return true; }
	};

	struct D
	{
		explicit D(int) { }
		explicit D(int, int) { }
		explicit operator bool() const { return true; }
	};

	void Extra01() {
		C a1 = 1;      // OK: copy-initialization selects A::A(int)
		C a2(2);       // OK: direct-initialization selects A::A(int)
		C a3{ 4, 5 };   // OK: direct-list-initialization selects A::A(int, int)
		C a4 = { 4, 5 }; // OK: copy-list-initialization selects A::A(int, int)
		C a5 = (C)1;   // OK: explicit cast performs static_cast
		if (a1);      // OK: A::operator bool()
		bool na1 = a1; // OK: copy-initialization selects A::operator bool()
		bool na2 = static_cast<bool>(a1); // OK: static_cast performs direct-initialization

	//  D b1 = 1;      // error: copy-initialization does not consider B::B(int)
		D b2(2);       // OK: direct-initialization selects B::B(int)
		D b3{ 4, 5 };   // OK: direct-list-initialization selects B::B(int, int)
	//  D b4 = {4, 5}; // error: copy-list-initialization does not consider B::B(int,int)
		D b5 = (D)1;   // OK: explicit cast performs static_cast
		if (b2);      // OK: B::operator bool()
	//  bool nb1 = b2; // error: copy-initialization does not consider B::operator bool()
		bool nb2 = static_cast<bool>(b2); // OK: static_cast performs direct-initialization
	}

}
#include "Excercices.h"
#include <cstdint>
#include <cassert>

namespace Ex27 {
	class A
	{
	public:
		A() : m_n(++m_object_id) { /*std::cout << m_n;*/ }

		~A() { std::cout << m_n; }

	private:
		const int m_n;
		static int m_object_id;
	};

	int A::m_object_id = 0;

	void Excercise_27()
	{
		A * const p = new A[2]; // lista 2 db A-val, p az elsőre mutat
		A * const q = reinterpret_cast<A * const>(new char[2 * sizeof(A)]); // nem fut le constructor mivel csak típus válltozik, csak létrehozunk 2 db A* tipusu const pointert

		new (q) A; // létrejön ez úgy A, megnöveli m_object_id-t, majd meg is hal -> a reinterpretált q első elemét használja fel
		new (q + 1) A; // létrejön egy új A, megnöveli m_object_id-t, majd meg is hal -> a reinterpretált q másodig elemét használja fel
		q->~A(); // q egy lista első emelére mutat, amikben A-k vannak, ennek az első elemáre hívja meg a destruktort
		q[1].~A(); // q által mutatott lista második elemére hívja meg a destruktort
		delete[] reinterpret_cast<char *>(q);
		delete[] p;

		std::cout << std::endl;
	}

	// reinterpret_cast

	int f() { return 42; }

	void Extra01() {
		int i = 7;

		// pointer to integer and back
		std::uintptr_t v1 = reinterpret_cast<std::uintptr_t>(&i); // static_cast is an error
		std::cout << "The value of &i is 0x" << std::hex << v1 << '\n';
		int* p1 = reinterpret_cast<int*>(v1);
		assert(p1 == &i);

		// pointer to function to another and back
		void(*fp1)() = reinterpret_cast<void(*)()>(f);
		// fp1(); undefined behavior
		int(*fp2)() = reinterpret_cast<int(*)()>(fp1);
		std::cout << std::dec << fp2() << '\n'; // safe

		// type aliasing through pointer
		char* p2 = reinterpret_cast<char*>(&i);
		if (p2[0] == '\x7')
			std::cout << "This system is little-endian\n";
		else
			std::cout << "This system is big-endian\n";

		// type aliasing through reference
		reinterpret_cast<unsigned int&>(i) = 42;
		std::cout << i << '\n';

		[[maybe_unused]] const int &const_iref = i;
		//int &iref = reinterpret_cast<int&>(const_iref); //compiler error - can't get rid of const
		//Must use const_cast instead:  int &iref = const_cast<int&>(const_iref);
	}

	void Extra02() {
		int* p = new int(65);
		char* ch = reinterpret_cast<char*>(p);
		std::cout << *p << std::endl;
		std::cout << *ch << std::endl;
		std::cout << p << std::endl;
		std::cout << ch << std::endl;
	}

	struct mystruct {
		int x;
		int y;
		char c;
		bool b;
	};

	void Extra03() {
		mystruct s;

		// Assigning values 
		s.x = 5;
		s.y = 10;
		s.c = 'a';
		s.b = true;

		// data type must be same during casting 
		// as that of original 

		// converting the pointer of 's' to, 
		// pointer of int type in 'p'. 
		int* p = reinterpret_cast<int*>(&s);

		std::cout << sizeof(s) << std::endl;

		// printing the value currently pointed by *p 
		std::cout << *p << std::endl;

		// incrementing the pointer by 1 
		p++;

		// printing the next integer value 
		std::cout << *p << std::endl;

		p++;

		// we are casting back char * pointed 
		// by p using char *ch. 
		char* ch = reinterpret_cast<char*>(p);

		// printing the character value 
		// pointed by (*ch) 
		std::cout << *ch << std::endl;

		ch++;

		/* since, (*ch) now points to boolean value,
		so it is required to access the value using
		same type conversion.so, we have used
		data type of *n to be bool. */

		bool* n = reinterpret_cast<bool*>(ch);
		std::cout << *n << std::endl;

		// we can also use this line of code to 
		// print the value pointed by (*ch). 
		std::cout << *(reinterpret_cast<bool*>(ch));
	}

	class Ae {
	public:
		void fun_a()
		{
			std::cout << " In class A\n";
		}
	};

	class Be {
	public:
		void fun_b()
		{
			std::cout << " In class B\n";
		}
	};

	void Extra04() {
		// creating object of class B 
		Be* x = new Be();

		// converting the pointer to object 
		// referenced of class B to class A 
		Ae* new_a = reinterpret_cast<Ae*>(x);

		// accessing the function of class A 
		new_a->fun_a();
	}

	// operator new

	void Extra05() {
		A* a = new A();
		new (a) A;
	}

	struct MyClass {
		int data[100];
		MyClass() { std::cout << "constructed [" << this << "]\n"; }
	};

	void Extra06() {
		std::cout << "1: ";
		MyClass * p1 = new MyClass;
		// allocates memory by calling: operator new (sizeof(MyClass))
		// and then constructs an object at the newly allocated space

		std::cout << "2: ";
		MyClass * p2 = new (std::nothrow) MyClass;
		// allocates memory by calling: operator new (sizeof(MyClass),std::nothrow)
		// and then constructs an object at the newly allocated space

		std::cout << "3: ";
		new (p2) MyClass;
		// does not allocate memory -- calls: operator new (sizeof(MyClass),p2)
		// but constructs an object at p2

		// Notice though that calling this function directly does not construct an object:
		std::cout << "4: ";
		MyClass * p3 = (MyClass*) ::operator new (sizeof(MyClass));
		// allocates memory by calling: operator new (sizeof(MyClass))
		// but does not call MyClass's constructor

		delete p1;
		delete p2;
		delete p3;
	}

	void Extra07() {
		int i = 2 * sizeof(A);
		char *c = new char[2 * sizeof(A)];
		auto a = (new char[2 * sizeof(A)]);
	}

	void Extra08() {
		A * const p = new A[10]; // create: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
		std::cout << std::endl;
		delete[] p; // delete 10 -> 9 -> 8 -> 7 -> 6 -> 5 -> 4 -> 3 -> 2 -> 1
	}

	void Extra09() {
		//A * const q = reinterpret_cast<A * const>(new char[2 * sizeof(A)]);

		auto a = new char[2 * sizeof(A)];
		auto b = reinterpret_cast<A * const>(new char[2 * sizeof(A)]);

		std::cout << std::endl;
	}

	// difference between new char[10] and new char(10)

	void Extra10(){
		char c1[10];
		char c2(23);

		char* c3 = new char[10];
		char* c4 = new char(10);
	}

}
#include "Excercices.h"
#include <exception>
#include <vector>

namespace Ex25 {
	class A
	{
	public:
		virtual ~A() { }
	};

	class B
		: public A
	{
	};

	class C
		: public A
	{
	};

	void Excercise_25()
	{
		try {
			B b;
			C c;
			A *pa1 = &b, *pa2 = &c; // upcast, dynamic_cast

			std::cout << ((dynamic_cast<B*>(pa1) != nullptr) ? 1 : 0); // B tipusu referencia van pa1-ben, így szabályos a B* dynamic_cast és nem null lesz
			std::cout << ((dynamic_cast<B*>(pa2) != nullptr) ? 1 : 0); // C tipusu referencia van pa2-ben, bár szabályos a B* dynamic_cast, nullptr-lesz benne

			B &b1 = dynamic_cast<B&>(*pa2);
			pa1 = &b1;

			std::cout << ((static_cast<C*>(pa1) != nullptr) ? 1 : 0);
		}
		catch (const std::exception &) {
			std::cout << 2;
		}

		std::cout << std::endl;
	}

	// dynamic_cast

	struct V {
		virtual void f() {};  // must be polymorphic to use runtime-checked dynamic_cast
	};
	
	struct Av : virtual V {};
	
	struct Bv : virtual V {
		Bv(V* v, Av* a) {
			// casts during construction (see the call in the constructor of D below)
			dynamic_cast<Bv*>(v); // well-defined: v of type V*, V base of B, results in B*
			dynamic_cast<Bv*>(a); // undefined behavior: a has type A*, A not a base of B
		}
	};
	
	struct Dv : Av, Bv {
		Dv() : Bv(static_cast<Av*>(this), this) { }
	};

	struct Base {
		virtual ~Base() {}
	};

	struct Derived : Base {
		virtual void name() {}
	};

	void Extra01() {
		Dv d; // the most derived object
		Av& a = d; // upcast, dynamic_cast may be used, but unnecessary
		Dv& new_d = dynamic_cast<Dv&>(a); // downcast
		Bv& new_b = dynamic_cast<Bv&>(a); // sidecast


		Base* b1 = new Base;
		Derived* dd = dynamic_cast<Derived*>(b1); // null
		if (Derived* d = dynamic_cast<Derived*>(b1))
		{
			std::cout << "downcast from b1 to d successful\n";
			d->name(); // safe to call
		}

		Base* b2 = new Derived;
		if (Derived* d = dynamic_cast<Derived*>(b2))
		{
			std::cout << "downcast from b2 to d successful\n";
			d->name(); // safe to call
		}

		delete b1;
		delete b2;
	}

	// static_cast

	struct Bs {
		int m = 0;
		void hello() const {
			std::cout << "Hello world, this is B!\n";
		}
	};
	struct Ds : Bs {
		void hello() const {
			std::cout << "Hello world, this is D!\n";
		}
	};

	enum class E { ONE = 1, TWO, THREE };
	enum EU { ONE = 1, TWO, THREE };

	void Extra02() {
		// 1: initializing conversion
		int n = static_cast<int>(3.14);
		std::cout << "n = " << n << '\n';
		std::vector<int> v = static_cast<std::vector<int>>(10);
		std::cout << "v.size() = " << v.size() << '\n';

		// 2: static downcast
		Ds d;
		Bs& br = d; // upcast via implicit conversion
		br.hello();
		Ds& another_d = static_cast<Ds&>(br); // downcast
		another_d.hello();

		// 3: lvalue to xvalue
		std::vector<int> v2 = static_cast<std::vector<int>&&>(v);
		std::cout << "after move, v.size() = " << v.size() << '\n';

		// 4: discarded-value expression
		static_cast<void>(v2.size());

		// 5. inverse of implicit conversion
		void* nv = &n;
		int* ni = static_cast<int*>(nv);
		std::cout << "*ni = " << *ni << '\n';

		// 6. array-to-pointer followed by upcast
		Ds a[10];
		Bs* dp = static_cast<Bs*>(a);

		// 7. scoped enum to int or float
		E e = E::ONE;
		int one = static_cast<int>(e);
		std::cout << one << '\n';

		// 8. int to enum, enum to another enum
		E e2 = static_cast<E>(one);
		EU eu = static_cast<EU>(e2);

		// 9. pointer to member upcast
		int Ds::*pm = &Ds::m;
		std::cout << br.*static_cast<int Bs::*>(pm) << '\n';

		// 10. void* to any type
		void* voidp = &e;
		std::vector<int>* p = static_cast<std::vector<int>*>(voidp);
	}
}
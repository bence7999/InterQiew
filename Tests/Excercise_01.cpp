#include "Excercices.h"
#include <vector>

namespace Ex01
{
	class A
	{
	public:
		A(int n = 0)
			: m_n(n)
		{
			std::cout << 'd';
		}

		A(const A& a)
			: m_n(a.m_n)
		{
			std::cout << 'c';
		}

	private:
		int m_n;
	};

	void f(const A &a1, const A &a2 = A())
	{
	}

	void Excercise_01() {
		A a(2), b; // A(2), A(0)
		const A c(a), &d = c; // A(a) -> copy constructor A c(a) === A c = a, new reference
		const A e = b; // // conversion to A& and copy ctor
		b = d; // értékadás
		A *p = new A(c), *q = &a; // copy ctor, pointer to reference
		static_cast<void>(q); 
		delete p;
		f(3); // 2 alases of A(3), A(0)
		// const A &a1(3); // new alias of A (3)
		std::cout << std::endl;
	}

	// static_cast

	struct B {
		int m = 0;
		void hello() const {
			std::cout << "Hello world, this is B!\n";
		}
	};
	struct D : B {
		void hello() const {
			std::cout << "Hello world, this is D!\n";
		}
	};

	enum class E { ONE = 1, TWO, THREE };
	enum EU { ONE = 1, TWO, THREE };
	
	void Extra01() {
		// 1: initializing conversion
		int n = static_cast<int>(3.14);
		std::cout << "n = " << n << '\n';
		std::vector<int> v = static_cast<std::vector<int>>(10);
		std::cout << "v.size() = " << v.size() << '\n';

		// 2: static downcast
		D d;
		B& br = d; // upcast via implicit conversion
		br.hello();
		D& another_d = static_cast<D&>(br); // downcast
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
		D a[10];
		B* dp = static_cast<B*>(a);

		// 7. scoped enum to int or float
		E e = E::ONE;
		int one = static_cast<int>(e);
		std::cout << one << '\n';

		// 8. int to enum, enum to another enum
		E e2 = static_cast<E>(one);
		EU eu = static_cast<EU>(e2);

		// 9. pointer to member upcast
		int D::*pm = &D::m;
		std::cout << br.*static_cast<int B::*>(pm) << '\n';

		// 10. void* to any type
		void* voidp = &e;
		std::vector<int>* p = static_cast<std::vector<int>*>(voidp);
	}
}
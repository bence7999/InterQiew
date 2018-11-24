#include "Excercices.h"
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <fstream>
#include <functional>

namespace Ex22 {
	typedef std::unique_ptr<int> P;

	struct is_null
	{
		bool operator()(const P &p) const
		{
			return !bool(p);
		}
	};

	void Excercise_22() {
		P p[] = { P(new int(1)), P(new int(0)), P(nullptr), P(new int(2)), P() };
		auto b = std::begin(p);
		auto e = std::end(p);

		std::cout << std::count_if(b, e, is_null());

		P x = std::move(p[0]);
		P &y = p[1];
		static_cast<void>(y);
		p[2] = std::move(p[3]);

		std::cout << std::count_if(b, e, is_null()) << std::endl;
	}

	// std::count_if 

	bool IsOdd(int i) { return ((i % 2) == 1); }

	void Extra01() {
		std::vector<int> myvector;
		for (int i = 1; i < 10; i++) myvector.push_back(i); // myvector: 1 2 3 4 5 6 7 8 9

		int mycount = std::count_if(myvector.begin(), myvector.end(), IsOdd);
		std::cout << "myvector contains " << mycount << " odd values.\n";
	}

	//std::move

	void Extra02() {

		std::string str = "Hello";
		std::vector<std::string> v;

		v.push_back(str);
		std::cout << "After copy, str is \"" << str << "\"\n";
		
		v.push_back(std::move(str));
		std::cout << "After move, str is \"" << str << "\"\n";

		std::cout << "The contents of the vector are \"" << v[0]
				  << "\", \"" << v[1] << "\"\n";
	}

	// unique_ptr

	struct B {
		virtual void bar() { std::cout << "B::bar\n"; }
		virtual ~B() = default;
	};
	struct D : B
	{
		D() { std::cout << "D::D\n"; }
		~D() { std::cout << "D::~D\n"; }
		void bar() override { std::cout << "D::bar\n"; }
	};

	// a function consuming a unique_ptr can take it by value or by rvalue reference
	std::unique_ptr<D> pass_through(std::unique_ptr<D> p)
	{
		p->bar();
		return p;
	}

	void close_file(std::FILE* fp) { std::fclose(fp); }

	void Extra03() {
		std::cout << "unique ownership semantics demo\n";
		{
			auto p = std::make_unique<D>(); // p is a unique_ptr that owns a D
			auto q = pass_through(std::move(p));
			assert(!p); // now p owns nothing and holds a null pointer
			q->bar();   // and q owns the D object
		} // ~D called here
	}

	void Extra04() {
		std::cout << "Runtime polymorphism demo\n";
		{
			std::unique_ptr<B> p = std::make_unique<D>(); // p is a unique_ptr that owns a D
														  // as a pointer to base
			p->bar(); // virtual dispatch

			std::vector<std::unique_ptr<B>> v;  // unique_ptr can be stored in a container
			v.push_back(std::make_unique<D>());
			v.push_back(std::move(p));
			v.emplace_back(new D);
			for (auto& p : v) p->bar(); // virtual dispatch
		} // ~D called 3 times
	}

	void Extra05() {
		std::cout << "Custom deleter demo\n";
		std::ofstream("demo.txt") << 'x'; // prepare the file to read
		{
			std::unique_ptr<std::FILE, decltype(&close_file)> fp(std::fopen("demo.txt", "r"),
				&close_file);
			if (fp) // fopen could have failed; in which case fp holds a null pointer
				std::cout << (char)std::fgetc(fp.get()) << '\n';
		} // fclose() called here, but only if FILE* is not a null pointer
		  // (that is, if fopen succeeded)
	}

	void Extra06() {
		std::cout << "Custom lambda-expression deleter demo\n";
		{
			std::unique_ptr<D, std::function<void(D*)>> p(new D, [](D* ptr)
			{
				std::cout << "destroying from a custom deleter...\n";
				delete ptr;
			});  // p owns D
			p->bar();
		} // the lambda above is called and D is destroyed
	}

	void Extra07() {
		std::cout << "Array form of unique_ptr demo\n";
		{
			std::unique_ptr<D[]> p{ new D[3] };
		} // calls ~D 3 times
	}

}
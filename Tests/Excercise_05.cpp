#include "Excercices.h"
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <functional>

namespace Ex05 {
	
	void Excercise_05()
	{
		typedef std::list<int> L;
		L l(5);

		typedef L::const_iterator CI;
		CI cb = l.begin(), ce = l.end();
		typedef L::iterator I;
		I b = l.begin();

		std::transform(cb, --ce, ++b, [](CI::value_type n) { return ++n; }); // itt azért nő az n, mert két iterator van, az egyik +1-el megy, és mindig a növelthez képest kövel egyet
		std::copy(l.begin(), l.end(), std::ostream_iterator<CI::value_type>(std::cout));
		std::cout << std::endl;

	}

	// std::transform

	int op_increase(int i) { return ++i; }

	void Extra01() {
		std::vector<int> foo;
		std::vector<int> bar;

		for (int i = 1; i < 6; i++)
			foo.push_back(i * 10);

		bar.resize(foo.size());

		std::transform(foo.begin(), foo.end(), bar.begin(), op_increase);

		std::transform(foo.begin(), foo.end(), bar.begin(), foo.begin(), std::plus<int>());

		std::cout << "foo contains:";	
		for (std::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	void Extra02() {
		std::string str = "alma";
		std::string::iterator ib = str.begin();
		std::string::iterator ie = str.end();

		std::vector<int> v = { 0,1,2,3,4 };
		std::vector<int>::iterator vb = v.begin();
		std::vector<int>::iterator ve = v.end();
	}

	// anonymous function (lambda function)

	class AddressBook
	{
	public:
		// using a template allows us to ignore the differences between functors, function pointers 
		// and lambda
		template<typename Func>
		std::vector<std::string> findMatchingAddresses(Func func)
		{
			std::vector<std::string> results;
			for (auto itr = _addresses.begin(), end = _addresses.end(); itr != end; ++itr)
			{
				// call the function passed into findMatchingAddresses and see if it matches
				if (func(*itr))
				{
					results.push_back(*itr);
				}
			}
			return results;
		}

	private:
		std::vector<std::string> _addresses;
	};

	AddressBook global_address_book;

	std::vector<std::string> findAddressesFromOrgs()
	{
		return global_address_book.findMatchingAddresses(
			// we're declaring a lambda here; the [] signals the start
			[](const std::string& addr) { return addr.find(".org") != std::string::npos; }
		);
	}

	void Extra03() {
		auto func = []() { std::cout << "Hello world"; };
		func(); // now call the function

		auto address = findAddressesFromOrgs();
	}

	// Lambda expressions

	void Extra04() {
		std::vector<int> c = { 1, 2, 3, 4, 5, 6, 7 };
		int x = 5;
		c.erase(std::remove_if(c.begin(), c.end(), [x](int n) { return n < x; }), c.end());

		std::cout << "c: ";
		std::for_each(c.begin(), c.end(), [](int i) { std::cout << i << ' '; });
		std::cout << '\n';

		// the type of a closure cannot be named, but can be inferred with auto
		// since C++14, lambda could own default arguments
		auto func1 = [](int i = 6) { return i + 4; };
		std::cout << "func1: " << func1() << '\n';

		// like all callable objects, closures can be captured in std::function
		// (this may incur unnecessary overhead)
		std::function<int(int)> func2 = [](int i) { return i + 4; };
		std::cout << "func2: " << func2(6) << '\n';
	}

	// std::function


	
}
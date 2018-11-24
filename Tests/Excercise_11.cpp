#include "Excercices.h"
#include <list>
#include <algorithm>

namespace Ex11 {
	
	struct P
	{
		bool operator()(const int &n) const
		{
			return n % 3 == 0;
		}
	};

	void Excercise_11()
	{
		std::list<int> l({ 5, 2, 6, 1, 13, 9, 19 });
		std::cout << l.size(); 
		std::remove_if(l.begin(), l.end(), P()); // attól még hogy törli az elemeket, megtartja a végén, ami kiamaradna -> az iterátor vége előbbre mutat
		std::cout << l.size() << std::endl;

		for (auto i : l)
			std::cout << ' ' << i;

		std::cout << std::endl;

		auto b = l.begin(), e = l.end();

		for(auto it = b; it != e; ++it)
			std::cout << ' ' << *it;

	}

	// std::remove_if

	struct Q{
		bool operator()(const char &c) const {
			std::cout << c << std::endl;
			return c == 'a' ? true : false;
		}
	};

	void Extra01() {
		std::string str = "alma";
		std::string::iterator sb = str.begin();
		std::string::iterator se = str.end();
		std::remove_if(sb, se, Q());

		for (auto i : str)
			std::cout << ' ' << i;

		std::cout << std::endl;

		for (auto it = str.begin(); it != str.end(); ++it)
			std::cout << ' ' << *it;
	}

	bool IsOdd(int i) { return ((i % 2) == 1); }

	void Extra02() {
		int myints[] = { 1,2,3,4,5,6,7,8,9 };

		int* pbegin = myints;
		int* pend = myints + sizeof(myints) / sizeof(int);
		
		pend = std::remove_if(pbegin, pend, IsOdd);

		std::cout << "the range contains:";
		for (int* p = pbegin; p != pend; ++p)
			std::cout << ' ' << *p;
		std::cout << '\n';

		for (auto i : myints)
			std::cout << ' ' << i;
	}
}
#include "Excercices.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace Ex26 {
	bool compare(int a, int b)
	{
		return a % 2 == b % 2;
	}

	void Excercise_26()
	{
		int a[] = { 3, 1, 4, 6, 1, 3 };
		auto b = std::begin(a);
		auto e = std::end(a);

		e = std::unique(b, e, compare);
		std::copy(b, e, std::ostream_iterator<int>(std::cout));

		std::cout << std::endl;
	}

	// std::unique

	bool myfunction(int i, int j) {
		return (i == j);
	}

	void Extra01() {
		int myints[] = { 10,20,20,20,30,30,20,20,10 };           // 10 20 20 20 30 30 20 20 10
		std::vector<int> myvector(myints, myints + 9);

		// using default comparison:
		std::vector<int>::iterator it;
		it = std::unique(myvector.begin(), myvector.end());   // 10 20 30 20 10 ?  ?  ?  ?
															   //                ^

		myvector.resize(std::distance(myvector.begin(), it)); // 10 20 30 20 10

		// using predicate comparison:
		std::unique(myvector.begin(), myvector.end(), myfunction);   // (no changes)

		// print out content:
		std::cout << "myvector contains:";
		for (it = myvector.begin(); it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

	}

	void Extra02() {
		// remove duplicate elements
		std::vector<int> v{ 1,2,3,1,2,3,3,4,5,4,5,6,7 };
		std::sort(v.begin(), v.end()); // 1 1 2 2 3 3 3 4 4 5 5 6 7 
		auto last = std::unique(v.begin(), v.end());
		// v now holds {1 2 3 4 5 6 7 x x x x x x}, where 'x' is indeterminate
		v.erase(last, v.end());
		for (int i : v)
			std::cout << i << " ";
		std::cout << "\n";
	}
}
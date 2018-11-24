#include "Excercices.h"
#include <vector>
#include <algorithm>

namespace Ex30 {
	bool compare(int a, int b)
	{
		return a % 3 < b % 3;
	}

	void Excercise_30()
	{
		typedef std::vector<int> V;
		V v({ 7, 0, 8, 5, 2, 11 });

		std::sort(v.begin(), v.end());
		typedef V::const_reverse_iterator R;
		const R i = std::adjacent_find(v.rbegin(), v.rend(), compare);
		if (i == v.rend()) {
			std::cout << -1 << std::endl;
		}
		else {
			std::cout << *i << *(i + 1) << std::endl;
		}
	}

	// const_reverse_iterator

	void Extra01() {
		std::vector<int> myvector(5);  // 5 default-constructed ints

		int i = 0;

		std::vector<int>::reverse_iterator rit = myvector.rbegin();
		for (; rit != myvector.rend(); ++rit)
			*rit = ++i;

		std::cout << "myvector contains:";
		for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

	}

	// adjacent_find

	void Extra02() {
		std::vector<int> v1{ 0, 1, 2, 3, 40, 40, 41, 41, 5 };

		auto i1 = std::adjacent_find(v1.begin(), v1.end()); // alapjáraton az első ismétlés első elemét adja vissza

		if (i1 == v1.end()) {
			std::cout << "no matching adjacent elements\n";
		}
		else {
			std::cout << "the first adjacent pair of equal elements at: "
				<< std::distance(v1.begin(), i1) << '\n';
		}

		auto i2 = std::adjacent_find(v1.begin(), v1.end(), std::greater<int>()); // greater fv() ha az első nagyobb minta masodik, visszaadja az első true előfordulás első elemét (41) különben v.end()
		if (i2 == v1.end()) {
			std::cout << "The entire vector is sorted in ascending order\n";
		}
		else {
			std::cout << "The last element in the non-decreasing subsequence is at: "
				<< std::distance(v1.begin(), i2) << '\n';
		}
	}

	bool myfunction(int i, int j) {
		return (i == j);
	}

	void Extra03() {
		int myints[] = { 5,20,5,30,30,20,10,10,20 };
		std::vector<int> myvector(myints, myints + 8);
		std::vector<int>::iterator it;

		// using default comparison:
		it = std::adjacent_find(myvector.begin(), myvector.end()); // it = myints[4] = 30

		if (it != myvector.end())
			std::cout << "the first pair of repeated elements are: " << *it << '\n';

		//using predicate comparison:
		it = std::adjacent_find(++it, myvector.end(), myfunction); // ahol először true -> ++it = myints[4] = 30 -> először igaz: myints[7] == myints[8] = 10

		if (it != myvector.end())
			std::cout << "the second pair of repeated elements are: " << *it << '\n';
	}
}
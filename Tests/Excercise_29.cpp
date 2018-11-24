#include "Excercices.h"
#include <stdexcept>

namespace Ex29 {
	class A
	{
	public:
		A(int n)
		{
			if (0 == n) {
				throw std::logic_error("0");
			}
		}
	};

	void Excercise_29()
	{
		A *p0 = nullptr, *p1 = nullptr, *p2 = nullptr; // p0, p1, p2 = 0
		try {
			p1 = new A(1); // p1 uj A-ra mutat, n = 1
			p0 = new A(0); // construalas nem megy végig, mert n == 0, p0 = 0 -> throw exception
			p2 = new A(2); // el sem jutun idaig
		}
		catch (const std::exception &) {
			std::cout << 3;
		}

		std::cout << ((0 != p1) ? 1 : 0); // p1 = 1
		std::cout << ((0 != p0) ? 1 : 0); // p1 = 0
		std::cout << ((0 != p2) ? 1 : 0) << std::endl; // p2 = 0

		delete p1;
		delete p0;
		delete p2;
	}
}
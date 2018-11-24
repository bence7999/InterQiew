#include "Excercices.h"

namespace Ex23 {
	class A
	{
	public:
		A(int n)
			: m_n(n)
		{
			if (0 == n) {
				throw std::logic_error("0"); // mivel a constructor lefutása előtt dob error-t, nem fejeződik be a konstruálás, nem hívódik fel a destructor
			}
		}

		~A() { 
			std::cout << m_n; 
		}

	public:
		const int m_n;
	};

	void Excercise_23()
	{
		try {
			A a(1); // a konctruálása befejezősik, le is fog futni a destruktor
			A b(0); // b kontruálása nem fejeződik be, nem fog lefutni a destruktor
			A c(2); // c konctruálása el sem kezdődik, nem fog lefutni a destruktor
		}
		catch (const std::exception &) {
			std::cout << 3;
		}

		std::cout << std::endl;
	}

	void Extra01() {
		try {
			A b(0); // nem hívódik fel a destructor mert nem felejődött be a construálás
		}
		catch (const std::exception &) {
			std::cout << 3;
		}

		std::cout << std::endl;
	}
}
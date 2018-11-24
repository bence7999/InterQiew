#include "Excercices.h"
#include <set>

namespace Ex18 {
	struct C
	{
		bool operator()(const int &a, const int &b) const
		{
			return a % 10 < b % 10;
		}
	};

	void Excercise_18()
	{
		std::set<int> x({ 4, 2, 7, 11, 12, 14, 17, 2 });
		std::cout << x.size();
		std::set<int, C> y(x.begin(), x.end());
		std::cout << y.size() << std::endl;
	}

	class Alma {
	public:
		Alma(int n = 0) : m_n(n) { }
		bool operator<(const Alma& a) const {
			return a.m_n < this->m_n;
		}
		bool operator<(const int& a) const {
			return a < this->m_n;
		}
	private:
		int m_n;
	};

	void Extra01() {
		std::set<int> setInt;
		std::set<std::string> setString;
		std::set<Alma> setAlma;

		std::cout << setInt.size() << std::endl;
		std::cout << setString.size() << std::endl;
		std::cout << setAlma.size() << std::endl;

		setInt.insert(1);
		setInt.insert(2);
		setInt.insert(3);

		setString.insert("alma");
		setString.insert("korte");
		setString.insert("szilva");

		Alma a;
		setAlma.insert(a);
		Alma b(2);
		setAlma.insert(b);
		Alma c = {3};
		setAlma.insert(c);

		std::cout << setInt.size() << std::endl;
		std::cout << setString.size() << std::endl;
		std::cout << setAlma.size() << std::endl;
	}

	void Extra02() {
		//std::set<int, Alma> intAlma; // first is the type, secons is the compare
		//Alma a(5);
		//intAlma.insert(1);

		//std::set<Alma, int> intAlma2; // first is the type, secons is the compare
		//intAlma2.insert(2);
		//intAlma2.insert(a);
	}

	struct D {
		bool operator()(const int &a, const int &b) const
		{
			return a < b;
		}
	};

	void Extra03() {
		std::set<int> d = { 4, 2, 7, 11, 12, 14, 17, 2 };
		std::set<int, D> y(d.begin(), d.end());

		std::set<int> e = { 5, 7, 2, 4, 1, 3, 2, 10, 8, 7, 1, 6 };

	}
}

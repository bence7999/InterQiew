#include "Excercices.h"

namespace Ex07 {
	
	template<class T, T t = T()> // lesz egy t param, amire a default constructor fog vonatkozni
	class A
	{
	private:
		template<bool b> // inner class, belül felhasználható
		class B
		{
		public:
			static const int m_n = b ? 1 : 0;
		};

	public:
		static const int m_value = B<(t > T())>::m_n - B<(t < T())>::m_n;
	};

	void Excercise_07()
	{
		std::cout << A<int, -9>::m_value // t = -9
			<< A<bool, true>::m_value // t = ture
			<< A<char>::m_value << std::endl; // t = ''

	}

	template<class T>
	class Alma {
	public:
		Alma(T n) : param(n) { }
	private:
		T param;
	};

	void Extra01() {
		Alma<int> a1(1);
		Alma<std::string> a2("alma");
		Alma<char> a3('a');
		Alma<double> a4(98765.4321);
	}

	template<class T, T t = T()> 
	class B {
		T param = t;
	public:
		bool check() {
			std::cout << t << " " << T() << std::endl;
			if (t > T()) {
				std::cout << "yes" << std::endl;
			}
			else
				std::cout << "no" << std::endl;
			return 1;
		}
	};

	void Extra02() {
		B<int, 3> b1;
		bool b2 = b1.check(); // default int = 0

		B<int> b1_2;
		bool b2_2 = b1_2.check();

		B<bool, true> b3;
		bool b4 = b3.check(); // default bool = false(0)

		B<bool> b3_2;
		bool b4_2 = b3_2.check();

		B<char, 'a'> b5;
		bool b6 = b5.check(); // default char='' 

		B<char> b5_2;
		bool b6_2 = b5_2.check();

	}
}
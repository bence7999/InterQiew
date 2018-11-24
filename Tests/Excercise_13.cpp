#include "Excercices.h"
#include <algorithm>
#include <vector>

namespace Ex13 {
	class A
	{
	public:
		A(int i) : m_i(i) { }

	public:
		int operator()(int i = 0) const { return m_i + i; } // // Function call operator

		operator int() const { return m_i; } // User - defined conversion

	private:
		int m_i;

		friend int g(const A&);
	};

	int f(char c)
	{
		return c;
	}

	int g(const A& a)
	{
		return a.m_i;
	}

	void Excercise_13()
	{
		A f(2);  // A példány, konstruktor 2-őt kap
		A g(3);  // A példány, konstruktor 3-at kap

		std::cout << f(1) << std::endl; // Function call operator -> f callable -> 1 a paraméter -> m_i + 1
		std::cout << g(f) << std::endl; // User - defined conversion -> f-ből int lesz -> 2 -> Function call operator -> g callable -> 2 a paraméter -> m_i + 2
	}

	// Function call operator	
	struct Sum
	{
		int sum;
		Sum() : sum(0) { }
		void operator()(int n) { sum += n; }
	};

	void Extra01() {
		std::vector<int> v = { 1, 2, 3, 4, 5 };
		Sum s = std::for_each(v.begin(), v.end(), Sum());
	}

	// User - defined conversion
	struct X {
		//implicit conversion
		operator int() const { return 7; }
	};

	void Extra02() {
		X x;
		int a = x;
	}

	//Friend function
	class Distance
	{
	private:
		int meter;
	public:
		Distance() : meter(0) { }
		//friend function
		friend int addFive(Distance);
	};

	int addFive(Distance d)
	{
		//accessing private data from non-member function
		d.meter += 5;
		return d.meter;
	}

	void Extra03() {
		Distance D;
		std::cout << "Distance: " << addFive(D);
	}

}
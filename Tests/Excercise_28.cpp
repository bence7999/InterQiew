#include "Excercices.h"
#include <string>
#include <stdexcept>
#include <vector>

namespace Ex28 {
	template<unsigned N>
	class A
	{
	public:
		A() { std::cout << N; }

	private:
		A<N - 1> m_a;	// a construálás vége előtt lefut a member initialization
	};

	template<>
	class A<0>
	{
	public:
		A() { std::cout << 'A'; } // Az A fog legelőször kiíródni
	};

	void Excercise_28()
	{
		{ A<4>(); }

		std::cout << std::endl;
	}

	// Function templates

	class Alma {
	public:
		Alma(int a = 0) : i(a) { }
		int i;

		bool operator>(Alma& a) {
			return i > a.i ? true : false;
		}
	};

	template <class T>
	T GetMax(T a, T b) {
		T result;
		result = (a > b) ? a : b;
		return (result);
	}

	void Extra01() {
		int i = 5, j = 6, k;
		long l = 10, m = 5, n;
		k = GetMax<int>(i, j);
		n = GetMax<long>(l, m);
		std::cout << k << std::endl;
		std::cout << n << std::endl;
		Alma a1(1);
		Alma a2(2);
		Alma a3 = GetMax<Alma> (a1, a2);

		// == //

		k = GetMax(i, j);
		n = GetMax(l, m);
		a3 = GetMax(a1, a2);
	}

	template <class T, class U>
	T GetMin(T a, U b) {
		return (a < b ? a : b);
	}

	void Extra02() {
		int i = 5, j = 6, k;
		long l = 10, m = 5, n;
		k = GetMin<int, long>(j, m);
		n = GetMin<long, int>(l, i);

		// == //

		k = GetMin(j, m);
		n = GetMin(l, i);
	}

	template <typename T>
	inline T const& Max(T const& a, T const& b) {
		return a < b ? b : a;
	}

	void Extra03() {
		int i = 39;
		int j = 20;
		std::cout << "Max(i, j): " << Max(i, j) << std::endl;

		double f1 = 13.5;
		double f2 = 20.7;
		std::cout << "Max(f1, f2): " << Max(f1, f2) << std::endl;

		std::string s1 = "Hello";
		std::string s2 = "World";
		std::cout << "Max(s1, s2): " << Max(s1, s2) << std::endl;
	}

	// A template function to implement bubble sort. 
	// We can use this for any data type that supports 
	// comparison operator < and swap works for it. 
	template <class T>
	void bubbleSort(T a[], int n) {
		for (int i = 0; i < n - 1; i++)
			for (int j = n - 1; i < j; j--)
				if (a[j] < a[j - 1])
					std::swap(a[j], a[j - 1]);
	}

	// Driver Code 
	void Extra04() {
		int a[5] = { 10, 50, 30, 40, 20 };
		int n = sizeof(a) / sizeof(a[0]);

		// calls template function  
		bubbleSort(a, 5);

		std::cout << " Sorted array : ";
		for (int i = 0; i < n; i++)
			std::cout << a[i] << " ";
		std::cout << std::endl;

	}

	// Class templates

	template <class T>
	class mypair {
		T a, b;
	public:
		mypair(T first, T second)
		{
			a = first; b = second;
		}
		T getmax();
	};

	template <class T>
	T mypair<T>::getmax()
	{
		T retval;
		retval = a > b ? a : b;
		return retval;
	}

	void Extra05() {
		mypair <int> myobject(100, 75);
		std::cout << myobject.getmax();
	}

	template <class T>
	class Stack {
	private:
		std::vector<T> elems;    // elements 

	public:
		void push(T const&);  // push element 
		void pop();               // pop element 
		T top() const;            // return top element 

		bool empty() const {      // return true if empty.
			return elems.empty();
		}
	};

	template <class T>
	void Stack<T>::push(T const& elem) {
		// append copy of passed element 
		elems.push_back(elem);
	}

	template <class T>
	void Stack<T>::pop() {
		if (elems.empty()) {
			throw std::out_of_range("Stack<>::pop(): empty stack");
		}

		// remove last element 
		elems.pop_back();
	}

	template <class T>
	T Stack<T>::top() const {
		if (elems.empty()) {
			throw std::out_of_range("Stack<>::top(): empty stack");
		}

		// return copy of last element 
		return elems.back();
	}

	void Extra06() {
		try {
			Stack<int>         intStack;  // stack of ints 
			Stack<std::string> stringStack;    // stack of strings 

			// manipulate int stack 
			intStack.push(7);
			std::cout << intStack.top() << std::endl;

			// manipulate string stack 
			stringStack.push("hello");
			std::cout << stringStack.top() << std::endl;
			stringStack.pop();
			stringStack.pop();
		}
		catch (std::exception const& ex) {
			std::cerr << "Exception: " << ex.what() << std::endl;
		}
	}

	template <typename T>
	class Array {
	private:
		T *ptr;
		int size;
	public:
		Array(T arr[], int s);
		void print();
	};

	template <typename T>
	Array<T>::Array(T arr[], int s) {
		ptr = new T[s];
		size = s;
		for (int i = 0; i < size; i++)
			ptr[i] = arr[i];
	}

	template <typename T>
	void Array<T>::print() {
		for (int i = 0; i < size; i++)
			std::cout << " " << *(ptr + i);
		std::cout << std::endl;
	}

	void Extra07() {
		int arr[5] = { 1, 2, 3, 4, 5 };
		Array<int> a(arr, 5);
		a.print();
	}

	// Rekurzio

}
// Copy-move.cpp : Definition and operation of different functions to copy and move data from an array. Also usage of overloaded operators for array.
//

#include "stdafx.h"
#include <iostream>
#include <initializer_list>
#include <memory>

class Container
{
public:
	// constructors
	Container(){//1 (might need to write it as length(0) data(nullptr))
		length = 0;
		data = nullptr;
		std::cout << "Default constructor" << std::endl;
	}

	Container(int length) :length(length), data(new double[length]){//2
		std::cout << "Delegating constructor for initialization using arguments to define the container" << std::endl;
	}

	Container(std::initializer_list<double> list) : Container((int)list.size()){//3
		std::uninitialized_copy(list.begin(), list.end(), data);
		std::cout << "Yet another constructor" << std::endl;
	}

	Container(const Container& other) : Container(other.length){//4 We have delegated over here as well. Deep copy
		for (auto i = 0; i<other.length; i++)
			data[i] = other.data[i];
		std::cout << "Function creates a deep copy of data from one (new) Container to another (original): move" << std::endl;
	}

	Container(Container&& other) : length(other.length), data(other.data){//5
		other.length = 0;
		other.data = nullptr;
		std::cout << "Function deletes the information from the (new) container" << std::endl;
	}

	// destructor

	~Container(){//6
		length = 0;
		delete[] data;

		std::cout << "Constructor (is not automatically created by the compiler) " << std::endl;
	}
	// operators

	Container operator=(Container& other){//7     
		Container b(other);
		//std::cout << "Function for making one container's arguments equal anothers " << std::endl;
		return b;
	}

	Container operator=(Container&& a){//8
		Container b(std::move(a));
		std::cout << "Function for making one container's arguments equal anothers by using the 'move' function " << std::endl;
		return b;
	}

	Container operator+(Container& other){//9
		for (auto i = 0; i<other.length; i++)
			data[i] += other.data[i];
		std::cout << "Function to add the arguments of one array to another and stoer them in the (original) Container" << std::endl;
		return *this;
	}

	void print(const std::string &info) const
	{
		// print the address of this instance, the attributes `length` and
		// `data` and the `info` string
		//std::cout << "  " << this << " " << length << " " << data << "  "<< info << std::endl;
		}

private:
	int length;
	double *data;
};

int main()
{
	std::cout << "Container a({ 1, 2, 3 });" << std::endl;//Create container
	Container a({ 1, 2, 3 });
	std::cout << "  a has address " << &a << std::endl;
	std::cout << "Container b = { 4, 5, 6 };" << std::endl;//Create container
	Container b = { 4, 5, 6 };
	std::cout << "  b has address " << &b << std::endl;
	std::cout << "Container c(a);" << std::endl;
	Container c(a);//Copy container calling the copy function (#5)
	std::cout << "  c has address " << &c << std::endl;
	std::cout << "Container d = a + b;" << std::endl;
	Container d = a + b;//The addition operator "+" uses the copy function as well. It copies the result of a+b (which is stored in a) into d 
	std::cout << "  d has address " << &d << std::endl;
	std::cout << "Container e;" << std::endl;
	Container e;
	std::cout << "  e has address " << &e << std::endl;
	std::cout << "e = a + b;" << std::endl;// Same as in previous comment
	e = a + b;
	std::cout << "Container f(std::move(a + b));" << std::endl;
	Container f(std::move(a + b));//By using move, data is eliminated from original array
	std::cout << "  f has address " << &f << std::endl;
	std::cout << "Container g = a + b + c;" << std::endl;
	Container g = a + b + c;
	std::cout << "  g has address " << &g << std::endl;
	std::cout << "Container h;" << std::endl;
	Container h;
	std::cout << "  h has address " << &h << std::endl;
	std::cout << "h = a + b + c;" << std::endl;
	h = a + b + c;
	std::cout << "Container i = { a + b + c };" << std::endl;
	Container i = { a + b + c };
	std::cout << "  i has address " << &i << std::endl;
	std::cout << "end" << std::endl;

	std::cin.clear(); // reset any error flags
	std::cin.ignore(32767, '\n'); // ignore any characters in the input buffer until we find an enter character
	std::cin.get(); // get one more char from the user
	return 0;
}


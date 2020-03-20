// derivatives.cpp: Computes derivatives with central and forward differences. Usage of virtual class and lambda inline functions. Alejandro Rozene Vallespín 
//


#include "stdafx.h"
#include<functional>
#include<iostream>


class Derivative//     1
{
public:
	double h;
	virtual double differentiate(std::function<double(double)> func, double x) = 0;

	Derivative() {
		h = 1e-8;
	}

	Derivative(double h) {
	}
};

class CentralDifference : public Derivative //     2
{
public:
	using Derivative::Derivative;


	double Centraldiff(const double(*func)(const double x), double m, double h)
	{
		m += h;
		double y = m - h;
		return (func(m) - func(y)) / (2 * h);
	}

	
	double forward(std::function<double(double)> func, double m, double h)
	{
		m += h;
		double y = m - h;
		return (func(m) - func(y)) / (2 * h);
	}
};

/**class ForwardDifference : public Derivative//     3
{
public:
using Derivative::Derivative;

double ForwardDifference(double x, double xsq()) {
y =x+h;
return (func(y) - func(x)) / h;
}
};*/

const double Power(const double x) {
	return x*x;
};

auto myfunc2 = [](double x) { return x; };

int main()
{
	CentralDifference AB;
	std::cout << AB.centraldiff(Power, 1, 1) << std::endl;

	C AB;
	std::cout << AB.forward(Power, 1, 1) << std::endl;
	
	


	std::cin.clear(); // reset any error flags
	std::cin.ignore(32767, '\n'); // ignore any characters in the input buffer until we find an enter character
	std::cin.get(); // get one more char from the user
	return 0;
}

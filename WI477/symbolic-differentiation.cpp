// H09-symbolic-differentiation.cpp : Usage of templates for symbolic differentiation. Alejandro Rozene

#include "stdafx.h"
#include<iostream>
#include<cmath>
#include<directive>

template<int value> struct constInt{
	static const double eval(double x) { return value; }
	typedef constInt<0> derivative;
};

template<typename A, typename B> struct Add{
static const double eval(double x) { return A::eval(x) + B::eval(x); }
typedef Add<typename A::derivative, typename B::derivative> derivative;
};

template<typename A, typename B> struct Mul{
	static const double eval(double x) { return A::eval(x)*B::eval(x); }
	typedef Add<Mul<typename A::derivative, typename B>,Mul<typename A, typename B::derivative>> derivative;//Slightly abstract: derivative uses chain rule. It is the addittion of A'B+ AB'
};

template<int a> struct Monomial {
	static const double eval(double x) { return pow(x, a); }
	typedef Mul<constInt<a>, Monomial<a - 1>> derivative;
};

template<typename A> struct Neg {
	static const double eval(double x) { return -typename A::inverse(x); }
	typedef Neg<typename A> inverse;
};


template<typename A> struct Cos;// Forward declaration to enable usage of Cos in struct Sin
template<typename A> struct Sin {
	static const double eval(double x) { return sin(x); }
	typedef Cos<typename A::eval(x)> derivative;
};

template<typename A> struct Cos {
	static const double eval(double x) { return cos(x); }
	typedef Sin<Neg<typename A>::inverse> derivative;
};

int main()
{
	
	std::cout << constInt<12>::eval(10) << std::endl;
	std::cout << constInt<1>::derivative::eval(2) << std::endl;
	std::cout << Add<constInt<2>, constInt<2>>::eval(2) << std::endl;
	std::cout << ""<< std::endl;
	
	std::cin.clear(); // reset any error flags
	std::cin.ignore(32767, '\n'); // ignore any characters in the input buffer until we find an enter character
	std::cin.get(); // get one more char from the user
	return 0;
}


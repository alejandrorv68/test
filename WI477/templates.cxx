#include <iostream>
#include <typeinfo>
#define PRINT_EXPRESSION(expr) std::cout << #expr << ": " << (expr) \
            << " (type: " << typeid(expr).name() << ")" << std::endl


template<typename A>//1
auto add_simple(A a, A b)->decltype(a+b) 
{ return a+b; }

template<typename A, typename B> auto add(A a, B b)->decltype(a+b) //2__________________________
{return a+b;}

template<typename A> bool is_int(A a){//3 ________________________
return false;//un-specialized template
}
template<> bool is_int<int>(int a) // is_int<int> specilizes the template. The first <> is empty because there is no change in the inside, we still use a template.
   {return true;}     



template<typename T> class Number{//4_________________________________
public: 
Number(T value):value(value){}
template<typename U>
auto operator+(const Number<U> &other) const //->decltype( Number<decltype(value+other.value)>(value+other.value)) for c++11
{
auto b = this->value+other.value;
return Number<decltype(b)>(b) ;
} 
const T value;
};

template<typename T> class Number {
public:
	Number(T value) :value(value) {}
	template<typename U>
	auto operator-(const Number<U> &other) const 
	{
		auto b = this->value - other.value;
		return Number<decltype(b)>(b);
	}
	const T value;
};

template<typename T> class Number {
public:
	Number(T value) :value(value) {}
	template<typename U>
	auto operator*(const Number<U> &other) const
	{
		auto b = this->value * other.value;
		return Number<decltype(b)>(b);
	}
	const T value;
};

template<typename T> class Number {
public:
	Number(T value) :value(value) {}
	template<typename U>
	auto operator/(const Number<U> &other) const
	{
		auto b = this->value / other.value;
		return Number<decltype(b)>(b);
	}
	const T value;
};


template<int T> struct fibonacci{//5____________________________________
static const int value =fibonacci<T-1>::value+fibonacci<T-2>::value;
};
template<> struct fibonacci<1>{
static const int value =1;
};
template<> struct fibonacci<2>{
static const int value =1;
}; 
 


int main()
        {

auto a= Number<int>(4);
auto b= Number<double>(4.2);
auto c=a+b;
fibonacci<5>::value;
            PRINT_EXPRESSION(add_simple(1, 2));
            PRINT_EXPRESSION(add_simple(1.5, 2.2));
            return 0;
        }

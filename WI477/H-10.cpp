#ifdef _MSC_VER
#  define NOINLINE __declspec(noinline)
#else
#  define NOINLINE __attribute__((noinline))
#endif

#include <vector>
using namespace std;

// TODO: Replace the following function template.  You may change the template
// arguments and function arguments if necessary.
template<typename V>
auto add_elems(const int& i, const std::vector<V>& head)
{
	return head[i];
}
template<typename V, typename ...T>
auto add_elems(const int& i, const std::vector<V>& head, const T&... tail)
{
	auto result = add_elems(i, tail...);
	{
		result = result + head[i];
	}
	return result;
}

template<typename V>
std::vector<V> add_vectors_singleloop(const std::vector<V>& head)
{
	return head;
}

template<typename V, typename... T>
std::vector<V> add_vectors_singleloop(const std::vector<V>& head, const T&... tail)
{
	std::vector<V> result = add_vectors_singleloop(tail...);
	for (auto i = 0; i<head.size(); ++i)
		result[i] = head[i] + add_elems(i, tail...);
	return result;
}

// TODO: Replace the following function template.  You may change the template
// arguments and function arguments if necessary.
template<typename V>
std::vector<V> add_vectors_simple(const std::vector<V>& head)
{
	return head;
}

template<typename V, typename... T>
std::vector<V> add_vectors_simple(const std::vector<V>& head, const T&... tail)
{
	std::vector<V> result = add_vectors_simple(tail...);
	for (auto i = 0; i<head.size(); ++i)
		result[i] += head[i];
	return result;
}
NOINLINE std::vector<double> test_add_vectors_singleloop(
	const std::vector<double>& a, const std::vector<double>& b,
	const std::vector<double>& c, const std::vector<double>& d)
{
	return add_vectors_singleloop(a, b, c, d);
}

NOINLINE std::vector<double> test_add_vectors_simple(
	const std::vector<double>& a, const std::vector<double>& b,
	const std::vector<double>& c, const std::vector<double>& d)
{
	return add_vectors_simple(a, b, c, d);
}

#include <iostream>
#include <cstring>

int main(int argc, char **argv)
{
	int n = 1000000;
	std::vector<double> a(n);
	std::vector<double> b(n);
	std::vector<double> c(n);
	std::vector<double> d(n);

	if (argc == 2)
	{
		if (strcmp(argv[1], "simple") == 0)
		{
			std::cout << "testing simple" << std::endl;
			for (int i = 0; i < 100; i++)
				test_add_vectors_simple(a, b, c, d);
			return 0;
		}
		else if (strcmp(argv[1], "singleloop") == 0)
		{
			std::cout << "testing singleloop" << std::endl;
			for (int i = 0; i < 100; i++)
				test_add_vectors_singleloop(a, b, c, d);
			return 0;
		}
	}

	std::cout << "USAGE: " << argv[0] << " simple|singleloop" << std::endl;
}
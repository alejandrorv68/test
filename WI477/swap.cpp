// Script exercise 1 for swapping
//

#include "stdafx.h"
#include <iostream>
using namespace std;

void swap1(int a, int b) {
	int temp = a;
	a = b;
	b = temp;
}

void swap2(int &m, int &n){
	int temp1 = m;
	m = n;
	n = temp1;

}

void swap3(int* s, int* d) {
	int temp1 = s;
	*s = *d;
	*d = *temp1;

}

int main()
{
	// Read two integer values
    int i1; std::cin >> i1;
	int i2; std::cin >> i2;

	swap1(i1, i2);

	std::cout << "i1=" << std::endl;
	std::cout << i1 << std::endl;

	std::cout << "i2=" << std::endl;
	std::cout << i2 << std::endl; 

	return 0;
}


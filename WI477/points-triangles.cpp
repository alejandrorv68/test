// Homework2.cpp. Script for exercise points-triangles. Alejandro Rozene Vallespín
/*

*/
// Support for precompiled header files (only under MS Visual Studio)
#include "stdafx.h"
#include <cmath>
#include <ostream>
#include <iomanip>

class Point
{
public:
	// constructors-------------------------
	Point() {
		double x = 0;
		double y = 0;
	}
	Point(double a, double b) {
		double x = a;
		double y = b;
			}
	// operators ---------------------------
	Point operator+(Point other) {
		Point sum;
		sum.x = x + other.x;
		sum.y = y + other.y;
		return sum;
	}
	Point operator-(Point other){
		Point subs;
		subs.x = x - other.x;
		subs.y = y - other.y;
		return subs;
	}
	Point &operator+=(Point other) {
		x+=other.x;
		y+= other.y;
		return *this;
	}
	Point &operator-=(Point other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	// methods----------------------------------
	double distance() { 
		double distan = sqrt(pow(x,2) + pow(y,2));
		 return distan;
	}
	double distance(Point other) { 
		double distance = sqrt(pow(other.x-x, 2) + pow(other.y-y, 2));
		return distance;
	}
	Point rotated(double angle) {
		Point rotated;
		rotated.x = x*cos(angle)-y*sin(angle);
		rotated.y = x*sin(angle) + y*cos(angle);
	}
	Point rotated(double angle, Point other) {
		Point rotreference;
		rotreference.x = (other.x-x)*cos(angle) - (other.y-y)*sin(angle) +other.x;
		rotreference.y = (other.x - x)*sin(angle) + (other.y - y)*cos(angle) +other.y;
	}
	Point &rotate(double angle) {
		double xold = x; double yold = y;
		x = xold*cos(angle) - yold*sin(angle);
		y = xold*sin(angle) + yold*cos(angle);
		return *this;
	}
	Point &rotate(double angle, Point other) {
		double xOld = x; double yOld = y;
		x = ((xOld - other.x)*cos(angle) - (yOld - other.y)*sin(angle)) + other.x;
		y = ((xOld - other.x)*sin(angle) + (yOld - other.y)*cos(angle)) + other.y;
		return *this;
	}

	double x;
	double y;
	//
};
//______________________________________________________________
class Triangle
{
public:
	// constructors
	Triangle() {
		Point a;
		Point b;
		Point c;
	}
	Triangle(Point a, Point b, Point c):a(a),b(b),c(c) {}
	
	// operators
	Triangle translated(Point t) {
		Triangle transt;
		transt.a = a +t; transt.b = b + t; transt.c = c + t;
		return transt;
	}
	Triangle &translate(Point t) { 
		Triangle trans;
		a += t; b += t; c += t;
		return *this;
	}
	Triangle rotated(double angle) { 
		Triangle rot;
		rot.a = a.rotate(angle); 
		rot.b = b.rotate(angle); 
		rot.c = c.rotate(angle);
		return rot;
	}
	Triangle rotated(double angle, Point other) { 
		Triangle rotate;
		rotate.a = a.rotate(angle, other); rotate.b = b.rotate(angle, other); rotate.c = c.rotate(angle, other);
		return rotate;
	}
	Triangle &rotate(double angle) { 
		a = a.rotate(angle); b = b.rotate(angle); c = c.rotate(angle);
		return *this;
	}
	Triangle &rotate(double angle, Point other) { 
		Triangle rota;
		a = a.rotate(angle, other); b = b.rotate(angle, other); c = c.rotate(angle, other);
		return *this;
	}
	// methods

	double area()
	{
		double areat;
		areat = 0.5*(a.x*b.y + b.x*c.y + c.x*a.y - b.x*a.y - c.x*b.y - a.x*c.y);
		return areat;
	}

	Point a, b, c;
};

// ostream operator for `Point`s
std::ostream &operator<<(std::ostream &os, const Point &p)
{
	// remember current flags, precision
	auto flags = os.flags();
	auto current_precision = os.precision();
	// output numers with fixed point and three decimal precision
	os.setf(std::ios::fixed, std::ios::floatfield);
	os.precision(3);
	// output point `p`
	os << "(" << std::setw(6) << std::setfill(' ') << p.x
		<< "," << std::setw(6) << std::setfill(' ') << p.y << ")";
	// restore current flags, precision
	os.flags(flags);
	os.precision(current_precision);
	return os;
}

// ostream operator for `Triangle`s
std::ostream &operator<<(std::ostream &os, const Triangle &t)
{
	return os << "Triangle< " << t.a << ", " << t.b << ", " << t.c << " >";
}


#include <iostream>
using namespace std;

int main()
{
	// example, replace with your tests

	Point p;
	//Triangle t;
	Point a = { 1,2 };
	Point b = { 3,6 };
	b += a;

	Triangle t = { { 0, 0 },{ 0, 1 },{ 1, 0 } };
	//t.translate({ 2, 3 }).rotate(M_PI / 2, { -1, -3 }).translate({ 5, 6 });

	// set point `p` to (1, 2)
	p.x = 1;
	p.y = 2;

	// set triangle `t` to (1, 2), (3, 4), (5, 6)
	t.a.x = 1;
	t.a.y = 2;
	t.b.x = 3;
	t.b.y = 4;
	t.c.x = 5;
	t.c.y = 6;

	// print point `p` and triangle `t`
	cout << p << endl;
	cout << t << endl;
}


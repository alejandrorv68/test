#define _USE_MATH_DEFINES
#include<initializer_list>//Used for accessing the values of vector 
#include<iostream>//Input output stream library
#include<exception>//Exception handler
#include<vector>//If not used, third constructor will throw following error: 'uninitialized_copy' is not a member of 'std'. (So package needed)
#include<map>
#include<math.h>
#include<iomanip>//Header for the setprecision (I have used it in Matrix class
#include<array>

template<typename T> 
class Vector {  
public:
    //Constructor. Default
	Vector<T>() : values(nullptr), length(0) {}
    
    //Constructor. Takes length of the vector only
	Vector<T>(int length) :values(new T[length]), length(length) {}
    // Constructor. Assign values
	Vector<T>(std::initializer_list<T> list) : Vector<T>((int)list.size()) {
		std::uninitialized_copy(list.begin(), list.end(), values);
	}
		
	//Destructor   	 
	~Vector<T>() { length = 0; delete[] values; }

	//Copy vector   	 
	Vector<T>(const Vector<T>& v) :Vector<T>(v.length) {
		for (auto i = 0; i<v.length; i++) {
			values[i] = v.values[i];
		}
		//std::cout << "only copies" << std::endl;
	}
    
	// = operator. Generates a copy
	Vector<T>& operator=(const Vector<T>& other) {
		if (this != other) {
			delete[] values;
			length = other.length;
			values = new auto(other.values);
			for (auto i = 0; i<other.length; i++) {
				values[i] = other.values[i];
			}
		}
		//std::cout<< "Copy is being used" << std::endl;
		return *this;
	}
	//Move vector with = operator
	Vector<T>&    operator =(Vector<T>&& other) {
		if (this != &other) {
			delete[] values;
			length = other.length;
			values = other.values;
			other.length = 0;
			other.values = nullptr;
		}
		//std::cout << "Move is being used" << std::endl;
		return *this;
	}
		
	    //+, -, Pointwise multiplication and dot product. [http://users.cms.caltech.edu/~donnie/cs11/cpp/cpp-ops.html]
		Vector<T>& operator +=(const Vector<T>& other) {
			if (length != other.length) throw "Vectors don't have the same length";
				for (auto i = 0; i < other.length; i++) {
					values[i] += other.values[i];
				}
			return *this;
		}

		const Vector<T> operator +(const Vector<T>& other) const{
			return Vector<T> (*this) += other;
		}

		Vector<T>& operator -=(const Vector<T>& other) {
			if (length != other.length) throw "Vectors don't have the same length";
				for (auto i = 0; i < other.length; i++) {
					values[i] -= other.values[i];
				}
			return *this;
		}

		const Vector<T> operator -(const Vector<T>& other) const {
			return Vector<T>(*this) -= other;
		}


		// Multiply with a scalar (as in templates.cpp)
		Vector<T>& operator*=(T scalar)
		{
			for (auto i = 0; i<length; i++)
				values[i] *= scalar;
			return *this;
		}

		const Vector operator *(T scalar) {
			return Vector<T>(*this) *= scalar;
		}
		
		// Print content of a vector
		const void print() const
	{
		std::cout << "Vector: ";
		for (auto i = 0; i < length; i++)
			std::cout << values[i] << " ";
		std::cout << std::endl;
	}


// These are made public although it is bad programming practice. Better use friend when needed
T* values;
int length;
};

// Dot product of two vectors
template<typename T> T dot(const Vector<T>& l, const Vector<T>& r){// Dot product function. As in dot-product-struct. For which length is made public
	if (l.length != r.length) throw "Vectors have different size!";
	T a=0; // Can be declared as an int, will undergo conversion
    for(auto i=0;i<l.length;i++){
        a +=l.values[i]*r.values[i];
        }
        return a;
    }

// Matrix class containing matvec and print methods
template<typename T> 
class Matrix {

	typedef std::map<std::array<int, 2>, T> map; // Define a type for the map

public:

	//Constructor. Default
	Matrix<T>() : row(0), col(0) {}

    //Constructor. Size given
	Matrix<T>(int r, int c) : row(r), col(c), entry() {}

    //Destructor
	~Matrix<T>() { int row = 0; int col = 0; entry.clear(); std::cout << "matrix is being deleted" << std::endl; }

    // Operator [] to assign values to an entry. Used as a lhs operator
	T&   operator [](const std::array<int, 2>&ij) {
		if (ij[0] <= 0 || ij[1] <= 0) throw "Invalid index argument";
		else if (ij[0] > row || ij[1] > col) throw "Index argument out of bounds";

		return entry[ij];

	}

	void print() {
		for (auto i = 1; i <= row; i++) {
			for (auto j = 1; j <= row; j++) {

				std::array<int, 2> ij = { i,j };

				if (entry.find(ij) == entry.end())
				{
					if (j == col) {
						std::cout << "" << std::endl;
					}
					else {
						std::cout << " " << " ";
					}
				}
				else {
					std::cout << entry[ij] << " ";
					if (j == col) {
						std::cout << "" << std::endl;
					}
				}
			}
		}
	}

	Vector<T> matvec(const Vector<T>& vec) const
	{
		int row = this->row;
		int col = this->col;
		if (vec.length != col) throw "Vector does not have the appropriate size";
		Vector<T> mv(col);

		for (auto ii = 1; ii <= row; ii++) {

			mv.values[ii - 1] = 0;
		}

		for (auto it = entry.begin(); it != entry.end(); it++ ) {

			auto ij = it->first;
			mv.values[ij[0] - 1] = mv.values[ij[0] - 1] + vec.values[ij[1] - 1] * it->second;
		}

		return mv;
	}

private:	
	map entry;
	int row;
	int col;
};

// Conjugate gradient method which solves Ax=b for unknown x which is also the first guess vector
template<typename T> 
int cg(const Matrix<T> &A, const Vector<T> &b, Vector<T> &x, T tol, int maxiter) {
	
	
	Vector<T> r = b - A.matvec(x);
	
	Vector<T> p = r;
	
	for (auto k = 0; k < maxiter - 1; k++) {

		auto dotr = dot(r, r);

		auto alpha = dotr / dot(A.matvec(p), p);
		x += p*alpha;

		
		r -= A.matvec(p) *alpha;

		if (dot(r, r) < tol*tol) {
			break;
		}

		auto beta = dot(r, r) / dotr;

		p*=beta;
		p += r;
	}

}

// Heat 1D. Contains print, exact solution and iterative solution methods
class Heat1D {
public:

    //Default constructor
	Heat1D() :alpha(0), m(1), dt(0.1) {}

    //Full constructor with alpha, number of evaluation points ant time for which to solve the problem
	Heat1D(double a, int dim, double t) :alpha(a), m(dim), dt(t), M(m, m) {

		if (m == 0) throw  "Introduce a value of m>0";
		Ax = 1.0 / (m + 1);
		double r = alpha*dt / pow(Ax, 2.0);

		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= m; j++) {
				if (i == j) {
					M[{i, j}] = 1 + (2 * r);
				}
				else if (j == i + 1 || j == i - 1) {
					M[{i, j}] = -1.0*r;
				}
				else {
					//M[{i, j}] = 0.0;
				}
			}
		}
	}

	~Heat1D() { alpha = 0; m = 0; dt = 0; std::cout << "heat is being deleted" << std::endl; }

	void Matprint(){
		M.print();
	}

	Vector<double> exact(const double t) const {

		Vector<double> exsol(m);

		double fact = -1.0*pow(M_PI, 2.0)*alpha*t;
		fact = exp(fact);


		for (int i = 0; i < m; i++) {
			exsol.values[i] = (sin(M_PI*Ax*(i + 1)));
		}

		Vector<double> exactsolution = exsol *= fact;
		//delete[] exsol.values;
		return exactsolution;
	}

	void printEx(double time) {
		std::cout << "exact solution at time t is the " << std::endl;

		Vector<double> print_val = Heat1D::exact(time);
		print_val.print();

	}

	Vector<double> solve(const double t_end) const {

		if (remainder(t_end, dt) >= 1e-12) throw "time is not a multiple of dt";
		auto limit = (t_end / dt);
		std::cout << limit << std::endl;
		double t_0 = 0.0;
		double tol = 1e-9;
		int max = 500;

		Vector<double> iniguess = Heat1D::exact(t_0);
		Vector<double> sol(m);
		for (auto i = 0; i < m; i++) {
			sol.values[i] = 1.0;
		}

		for (auto l = 0; l < limit - 1; l++) {

			cg(M, iniguess, sol, tol, max);

			Vector<double> inigues(sol);
			iniguess = std::move(inigues);

		}
		std::cout << "Finite difference approximation at time t is the " << std::endl;
		sol.print();

		return sol;

	}

private:
	double alpha;
	int m;
	double dt;
	double Ax;
	Matrix<double> M;
};

// Heat 2D. Contains print, exact solution and iterative solution methods
class Heat2D {
public:
	//Constructor
	Heat2D(double a, int dim, double t) :alpha(a), m(dim), dt(t), M(pow(m, 2), pow(m, 2)) {

		if (m == 0) { throw "Introduce a value of m>0"; }
		Ax = 1.0 / (m + 1);

		double r = alpha*dt / pow(Ax, 2.0);


		for (int i = 1; i <= pow(m, 2); i++) {
			for (int j = i; j <= pow(m, 2); j++) {
				if (i == j) {
					M[{i, j}] = 1 + 2 * (2 * r);
					M[{j, i}] = M[{i, j}];
				}
				else if (j == i + pow(m, 1.0) || j == i - pow(m, 1.0)) {
					M[{i, j}] = -1.0*r;
					M[{j, i}] = M[{i, j}];
				}
				else if (j == i + pow(m, 0.0) && i%m != 0 || j == i - pow(m, 0.0) && j%m != 0) {
					M[{i, j}] = -1.0*r;
					M[{j, i}] = M[{i, j}];
				}
				else {
					//M[{i, j}] = 0.0;
					//M[{j, i}] = M[{i, j}];
				}

			}

		}
	}

	~Heat2D() { alpha = 0; m = 0; dt = 0; }

	void Matprint() {
		M.print();
	}

	Vector<double> exact(double t) const {

		Vector<double> exsol(m*m);
		double fact = -2.0*pow(M_PI, 2.0)*alpha*t;
		fact = exp(fact);

		for (int j = 0; j < m; j++) {
			for (int i = 0; i < m; i++) {
				exsol.values[(m*i + j)] = (sin(M_PI*Ax*(i + 1)))*(sin(M_PI*Ax*(j + 1)));
			}
		}
		Vector<double> exactsolution = exsol *= fact;
		return exactsolution;
	}

	void printEx(const double time) {
		std::cout << "exact solution at time t is the " << std::endl;

		Vector<double> print_val = Heat2D::exact(time);
		print_val.print();

	}

	Vector<double> solve(double t_end) {

		if (remainder(t_end, dt) >= 1e-12) throw "time is not a multiple of dt";
		auto limit = (t_end / dt);
		std::cout << limit << std::endl;
		double t_0 = 0.0;
		double tol = 1e-9;
		int max = 500;

		Vector<double> iniguess = Heat2D::exact(t_0);
		Vector<double> sol(m*m);
		for (auto i = 0; i < (m*m) ; i++) {
			sol.values[i] = 0.0;
		}

		for (auto l = 0; l < limit - 1; l++) {
			cg(M, iniguess, sol, tol, max);

			Vector<double> inigues = sol;
			iniguess = std::move(inigues);
		}
		std::cout << "Finite difference approximation at time t is the " << std::endl;
		sol.print();
		return sol;
	}

private:
	double alpha;
	int m;
	double dt;
	double Ax;
	Matrix<double> M;
};

int main(){
	
	double alpha = 0.3125;
	int m = 3;
	double dt = 0.1;
	Heat1D N(alpha, m, dt);
	N.Matprint();
	double time = 1;
	//N.printEx(time);
	//N.solve(time);

	double dtTest = 0.001;
	int mTest = 99;
	Heat1D ToTest(alpha, mTest, dtTest);
	//ToTest.printEx(time);
	//ToTest.solve(time);

	Heat2D G(alpha, m, dt);
	//G.printEx(time);
	//G.solve(time);
	//G.Matprint();

	Heat2D tdtest(alpha, mTest, dtTest);
	tdtest.printEx(time);
	tdtest.solve(time);


	/*
	Matrix<double> Test(2, 2);
	Test[{1, 1}] = 4.0;
	Test[{1, 2}] = 1.0;
	Test[{2, 1}] = 1.0;
	Test[{2, 2}] = 3.0;
	Test.print();
	Vector<double> xot = { 2,1 };
	Vector<double> b_ot = { 1,2 };
	Vector<double> gfa = Test.matvec(xot);
	gfa.print();

	double tol = 1e-10;
	int maxiter = 51;
	cg(Test, b_ot, xot, tol, maxiter);
	xot.print();
	*/

	return 0;
}
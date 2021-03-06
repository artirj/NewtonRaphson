#include<vector>
#include<functional>
#include <iterator>
#include <algorithm>
#include <ostream>
#include <iostream>
#include "defines.h"
#include "invert.h"

using std::vector;

//Constructors and methods for the Vector class
Vector::Vector(const  Vector &in) { nums = in.get_n(); }
Vector::Vector(vector<double> in) { nums = in; }
Vector::Vector(std::initializer_list<double> i) { nums = i; }
Vector::Vector(int siz) { nums.resize(siz, 0); }
Vector::Vector(const unsigned &a) { nums.resize(a); }
void Vector::set(std::initializer_list<double> in) { nums = in; }
void Vector::set(vector<double> in) { nums = in; }
unsigned Vector::len() const { return (unsigned)nums.size(); }

// Overload the << operator for the Vector class
std::ostream& operator<<(std::ostream& os, const Vector& obj)
{
	for (unsigned i = 0; i < obj.len(); i++) {
		os << obj.get_n()[i] << " ";
	}
	return os;
}
//Overload the + operator to add vectors
Vector operator+(const Vector& a, const Vector& b) {
	Vector result;
	vector <double> work;
	vector <double> va=a.get_n();
	vector <double> vb=b.get_n();
	work.reserve(va.size());
	std::transform(va.begin(), va.end(), vb.begin(),std::back_inserter(work), std::plus<double>());
	result.set(work);
	return result;
}
//Overload the - operator to substract vectors
Vector operator-(const Vector& a, const Vector& b) {
	
	vector <double> work;
	vector <double> va = a.get_n();
	vector <double> vb = b.get_n();
	std::transform(va.begin(),va.end(), vb.begin(), std::back_inserter(work), std::minus<double>());
	Vector result(work);
	return result;
}
//Overload the - operator to substract a constant from a vector
Vector operator-(const Vector & a, const double b)
{
	Vector result;
	vector <double> va = a.get_n();
	std::transform(va.begin(), va.end(), va.begin(), bind2nd(std::minus<double>(), b));
	result.set(va);
	return result;
}
//Overload the + operator to add a constant to a vector
Vector operator+(const Vector& a, const double b) {
	Vector result;
	vector <double> va = a.get_n();
	std::transform(va.begin(), va.end(), va.begin(),bind2nd(std::plus<double>(), b));
	result.set(va);
	return result;
	}
//Overload the * operator to multiply (scalar) vectors
Vector operator*(const Vector& a, const Vector& b) {
	Vector result;
	vector <double> work;
	work.reserve(a.get_n().size());
	std::transform(a.get_n().begin(), a.get_n().end(), b.get_n().begin(), std::back_inserter(work), std::multiplies<double>());
	result.set(work);
	return result;
}
//Overload the * operator to multiply a constant by a vector
Vector operator*(const double & a, const Vector & b)
{
	Vector result;
	vector <double> va = b.get_n();
	std::transform(va.begin(), va.end(), va.begin(), bind2nd(std::multiplies<double>(), a));
	result.set(va);
	return result;
}
//Overload the / operator to divide vectors
Vector operator/(const Vector& a, const Vector& b) {
	Vector result;
	vector <double> work;
	work.reserve(a.get_n().size());
	std::transform(a.get_n().begin(), a.get_n().end(), b.get_n().begin(), std::back_inserter(work), std::divides<double>());
	result.set(work);
	return result;
}
//Overload the / operator to divide vectors by a constant
Vector operator/(const Vector& a, const double b) {
	Vector result;
	vector <double> va = a.get_n();
	std::transform(va.begin(), va.end(), va.begin(), bind2nd(std::divides<double>(), b));
	result.set(va);
	return result;
}
//Overload the abs function for vectors
Vector abs(const Vector &a) {
	Vector result;
	vector <double> va = a.get_n();
	for (int i = 0; i < va.size(); i++) {
		if (va[i] < 0) va[i] = -va[i];
	}
	result.set(va);
	return result;
}
//Overload the < operator to compare vector to constants
bool operator<(const Vector &a, const double b) {
	vector <double> va = a.get_n();
	for (int i = 0; i < va.size(); i++) {
		if (va[i] > b) return 0;
	}
	return 1;
}
//Overload the > operator to compare vector to constants
bool operator>(const Vector &a, const double b) {
	vector <double> va = a.get_n();
	for (int i = 0; i < va.size(); i++) {
		if (va[i] < b) return 0;
	}
	return 1;
}
//Overload the = operator to make all of the elements of a vector equal to a constant
void Vector::operator=( const double& b) {
	vector <double> va = this->get_n();
	for (int i = 0; i < va.size(); i++) {
		this->assign(i, b);
	
	}
	
}
//Overload isnan to see if there is any nan elements in the vector
bool isnan(const Vector& a) {
	vector <double> va = a.get_n();
	for (int i = 0; i < va.size(); i++) {
		if (isnan(va[i])) return 1;
	}
	return 0;
}
//

//Overload the () operator for vector to get values
double Vector::operator()(const unsigned & a) const {
	return this->nums[a];
}
//Method to assign values to vector elements (setter)
void Vector ::assign(const unsigned & pos, const double & val){
	nums[pos] = val;
}


//Methods and constructors for the Matrix class
vector<vector<double>>  const Matrix::get_n() { return nums; }
vector<vector<double>>*  Matrix::get_np() { return &nums; }
Matrix::Matrix(int r, int c) {
	rows = r;
	cols = c;
	nums.resize(r);
	for (unsigned i = 0; i < nums.size(); i++) {
		nums[i].resize(cols,0);
	}

}
Matrix::Matrix(const Matrix & a) {
	nums = a.nums;
	rows = a.get_rows();
	cols = a.get_cols();
}
unsigned Matrix::get_cols() const { return cols; }
unsigned Matrix::get_rows() const { return rows; }

//Overload the () operator for Matrix
double Matrix::operator()(const unsigned & r, const unsigned & c) const {
	return this->nums[r][c];
}

//Overload the *  operator to multiply matrices by vectors
Vector operator*(const Matrix& mat, const Vector& rhs) {
	Vector result(rhs.len());

	for (unsigned i = 0; i<mat.get_rows(); i++) {
		for (unsigned j = 0; j<mat.get_cols(); j++) {
			result.assign(i, mat(i,j) * rhs(j)+result(i));
			
		}
	}

	return result;
}
//Overload the * operator to multiply a constant by a Matrix
Matrix operator*(const double & a, const Matrix & mat) {
	Matrix result = mat;

	for (unsigned i = 0; i<mat.get_rows(); i++) {
		for (unsigned j = 0; j<mat.get_cols(); j++) {
			result.assign(i, j, result(i, j)*a);

		}
	}

	return result;
}
//Overload * to multiply matrices together
Matrix operator*(const Matrix & a, const Matrix & b) {
	Matrix result(a.get_rows(), b.get_cols());
	double suma = 0;
	for (unsigned i = 0; i<a.get_rows(); i++) {
		for (unsigned j = 0; j<b.get_cols(); j++) {
			for (unsigned k = 0; k < a.get_cols(); k++) {
				suma += a(i, k)*b(k, j);
			}
			result.assign(i, j, suma);
			suma = 0;

		}
	}

	return result;
}
//Overload - to substract matrices
Matrix operator-(const Matrix & a, const Matrix & b) {
	Matrix result = a;
	for (unsigned i = 0; i < a.get_rows(); i++) {
		for (unsigned j = 0; j < a.get_cols(); j++) {
			result.assign(i, j, a(i, j) - b(i, j));
		}
	}
	return result;
}

//Method to invert matrices. Use easy rules for the n=1,2 cases
//If n>=3, call a function that uses iteration to calculate
Matrix Matrix::inv() const{
	Matrix ret = *this;
	//Check if the matrix is square
	try {
		if (this->get_cols() == ret.get_rows()) {
			if (ret.get_cols() == 1) {
			ret.assign(0, 0, 1 / ret(0, 0));
			return ret;
		}
			else if (this->get_cols() == 2) {
				double i = ret(0, 0);
				double det = ret(0, 0)*ret(1, 1) - ret(0, 1)*ret(1, 0);
				ret.assign(0, 0, ret(1, 1)/det);
				ret.assign(1, 0, -ret(1, 0)/det);
				ret.assign(0, 1, -ret(0, 1)/det);
				ret.assign(1, 1, i/det);
				return ret;
			}
			else {
				ret=invert(ret);
				return ret;
			}

		}
		else {
			throw(2);
		}
	}
	catch (int n) { std::cout <<n<< "Columns and rows are not equal!"; }
	//Don't invert the Matrix if it is not possible
	return ret;
}

//Setter for Matrix
void Matrix::assign(const unsigned & i, const unsigned& j, const double&val) {
	nums[i][j] = val;
}

//Transpose method for Matrix
Matrix Matrix::tr()const {
	Matrix sol=*this;
	double temp;
	for (unsigned i = 0; i < this->get_rows(); i++) {
		for (unsigned j = i; j < this->get_cols(); j++) {
			temp = (*this)(i, j);
			sol.assign(i, j, (*this)(j, i));
			sol.assign(j, i,temp);
		}
	}
	return sol;
}

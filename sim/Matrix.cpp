/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2015 by Alexander Grau
  
  Private-use only! (you need to ask for a commercial-use)
 
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
  Private-use only! (you need to ask for a commercial-use)
*/


#include "Matrix.h"
#include <math.h>
//#include <iostream>
Matrix::Matrix(unsigned char m, unsigned char n, double* data, bool transposed) {
	this->isTransposed = transposed;
	this->m = m;
	this->n = n;
	this->data = 0;
	if (data) {
		this->data = data;
		isAllocated = false;
	} else {
		allocate();
		for (unsigned char i=0; i<m * n; i++) {
			this->data[i] = 0.0;
		}
	}
}

Matrix::Matrix(const Matrix &rhs) {
	m = 0;
	n = 0;
	data = 0;
	copyMatrix(rhs);
}

Matrix::~Matrix() {
	release();
}
Matrix& Matrix::copyMatrix(const Matrix& another) {
	if (this != &another) {
		if (m * n != another.m * another.n) {
			m = another.m;
			n = another.n;
			allocate();
		}
		m = another.m;
		n = another.n;
		isTransposed = another.isTransposed;
		for (unsigned char i = 0; i<m; i++)
			for (unsigned char j=0; j<n; j++)
				set(i,j) = another.get(i, j);
	}
	return *this;
}

Matrix& Matrix::copyData(const double* data) {
	for (unsigned char i=0; i<m*n; i++)
		this->data[i] = data[i];
	return *this;
}

Matrix& Matrix::operator=(const Matrix &rhs) {
	return copyMatrix(rhs);
}

Matrix& Matrix::operator+=(const Matrix &rhs) {
	for (unsigned char i=0; i<m; i++)
		for (unsigned char j=0; j<n; j++)
			set(i, j) += rhs.get(i, j);
	return *this;
}

Matrix& Matrix::operator-=(const Matrix &rhs) {
	for (unsigned char i=0; i<m; i++)
		for (unsigned char j=0; j<n; j++)
			set(i, j) -= rhs.get(i, j);
	return *this;
}

Matrix& Matrix::multiplySelf(const Matrix &rhs) {
	// element-wise multiplication with self-modification
	for (unsigned char i=0; i<m; i++)
		for (unsigned char j=0; j<n; j++)
			set(i, j) *= rhs.get(i, j);
	return *this;
}
Matrix Matrix::multiply(const Matrix &rhs) const{
	// element-wise multiplication
	return Matrix(*this).multiplySelf(rhs);
}

Matrix& Matrix::dotSelf(const Matrix &b, bool left){
	Matrix& a = *this;

	if (( left ? a.m : a.n ) == ( left ? b.n : b.m )) {
		if (( left ? b.m : b.n ) == ( left ? a.m : a.n )) { // very memory-effective. using only n extra floats.
			if (left) {
				a.transpose();
			}
			double* row = new double[a.n];

			for (unsigned char i=0; i<a.m; i++) {
				for (unsigned char jj=0; jj<a.n; jj++) {
					row[jj] = a.get(i, jj);
					a(i, jj) = 0.0;
				}
				for (unsigned char j=0; j<( left ? b.m : b.n ); j++)
					for (unsigned char k=0; k < a.n; k++)
						a(i, j) += row[k] * ( left ? b.get(j, k) : b.get(k, j));
			}
			delete[] row;
			if (left) {
				transpose();
			}
		} else {
			*this = a.dot(b, left);
		}
	}

	return *this;
}

Matrix Matrix::dot(const Matrix &other, bool left) const {
	if ((left && m != other.n) || (!left && n != other.m)) {
		return Matrix(0, 0);
	}
	Matrix result(left ? n : m, left ? other.m : other.n);
	for (unsigned char i=0; i < (left ? n : m); i++)
		for (unsigned char j=0; j < (left ? other.m : other.n); j++)
			for (unsigned char k=0; k < (left ? m : n); k++)
				result(i, j) += (left ? get(k, i) : get(i, k)) * (left ? other.get(j, k) : other.get(k, j));
	if(left) {
		result.transpose();
	}
	return result;
}

Matrix& Matrix::operator*=(double scalar){
	for (unsigned char i=0; i<m * n; i++)
		data[i] *= scalar;
	return *this;
}



Matrix Matrix::operator+(const Matrix &rhs) const{
	return Matrix(*this) += rhs;
};

Matrix Matrix::operator-(const Matrix &rhs) const{
	return Matrix(*this) -= rhs;
}
Matrix Matrix::operator-() const{
	return Matrix(*this) *= -1.0;
}
Matrix Matrix::operator~() const{
	Matrix result(*this);
	result.inverse();
	return result;
}


Matrix Matrix::operator*(double scalar) const {
	return Matrix(*this) *= scalar;
}

double& Matrix::operator()(unsigned char i, unsigned char j){
	return set(i, j);
}

const double& Matrix::get(unsigned char i, unsigned char j) const{
	return data[index(i, j)];
}

double& Matrix::set(unsigned char i, unsigned char j) {
	return data[index(i, j)];
}
unsigned char Matrix::index(unsigned char i, unsigned char j) const{
	if (isTransposed)
		return j * m + i;
	else
		return i * n + j;
}


bool  Matrix::operator==(const Matrix &other) const{
	if (m != other.m || n != other.n)
		return false;

	for (unsigned char i=0; i<m; i++)
		for (unsigned char j=0; j<n; j++)
			if (get(i, j) != other.get(i,j))
				return false;
	return true;
}

bool  Matrix::operator!=(const Matrix &other) const{
	return !(*this == other);
}


Matrix& Matrix::transpose() {
	isTransposed = !isTransposed;
	unsigned char tmp = m; m = n; n=tmp;
	return *this;
}

Matrix Matrix::transposed() const { // extremely memory-optimal but be aware- data reference is copied! Do not use transposed after parent deletion.
	return Matrix(n,m,data,!isTransposed);
}

Matrix& Matrix::inverse() {
	int pivrow;     // keeps track of current pivot row
	int k;
	unsigned int i,j;      // k: overall index along diagonal; i: row index; j: col index
	unsigned int* pivrows = new unsigned int[n]; // keeps track of rows swaps to undo at end
    double tmp;      // used for finding max value and making column swaps

    for (k = 0; k < n; k++)
    {
        // find pivot row, the row with biggest entry in current column
        tmp = 0;
        for (i = k; i < n; i++)
        {
            if (fabs(get(i,k)) >= tmp)   // 'Avoid using other functions inside abs()?'
            {
                tmp = fabs(get(i,k));
                pivrow = i;
            }
        }

        // check for singular matrix
        if (get(pivrow,k) == 0.0)
        {
        	delete[] pivrows;
        	this->release();
            return *this;
        }

        // Execute pivot (row swap) if needed
        if (pivrow != k)
        {
            // swap row k with pivrow
            for (j = 0; j < n; j++)
            {
                tmp = get(k, j);
                set(k, j) = get(pivrow,j);
                set(pivrow, j) = tmp;
            }
        }
        pivrows[k] = pivrow;    // record row swap (even if no swap happened)

        tmp = 1.0/get(k,k);    // invert pivot element
        set(k,k) = 1.0;        // This element of input matrix becomes result matrix

        // Perform row reduction (divide every element by pivot)
        for (j = 0; j < n; j++)
        {
            set(k,j) *= tmp;
        }

        // Now eliminate all other entries in this column
        for (i = 0; i < n; i++)
        {
            if (i != k)
            {
                tmp = get(i,k);
                set(i,k) = 0.0;  // The other place where in matrix becomes result mat
                for (j = 0; j < n; j++)
                {
                    set(i,j) -= get(k,j) * tmp;
                }
            }
        }
    }

    // Done, now need to undo pivot row swaps by doing column swaps in reverse order
    for (k = n-1; k >= 0; k--)
    {
        if (pivrows[k] != k)
        {
            for (i = 0; i < n; i++)
            {
                tmp = get(i,k);
                set(i, k) = get(i,pivrows[k]);
                set(i,pivrows[k]) = tmp;
            }
        }
    }
    delete[] pivrows;
    return *this;
}

double Matrix::trace() const {
	double result = 0.0;
	for (unsigned char i=0; i<m && i<n; i++) {
		result += get(i, i);
	}
	return result;
}

Matrix Matrix::cross(const Matrix& rhs, bool left) const {
	if (m!=1 || rhs.m!=1 || n!=3 || rhs.n!=3) // for row vectors only
		return Matrix(); //empty
	const Matrix& u = left ? rhs : *this;
	const Matrix& v = left ? *this : rhs;

	Matrix result(1,3);
	result(0,0) = u.get(0,1) * v.get(0,2) - u.get(0,2) * v.get(0,1);
	result(0,1) = u.get(0,2) * v.get(0,0) - u.get(0,0) * v.get(0,2);
	result(0,2) = u.get(0,0) * v.get(0,1) - u.get(0,1) * v.get(0,0);
	return result;
}

Matrix Matrix::quaternion_multiply(const Matrix& rhs, bool left) const {
	if (m!=1 || rhs.m!=1 || (n!=4 && n!=3) || (rhs.n!=4 && rhs.n!=3)) // for row vectors only
		return Matrix(); //empty
	const Matrix& v = left ? rhs : *this;
	const Matrix& u = left ? *this : rhs;

	double w0,x0,y0,z0;
	if (u.n==4) {
		w0 = u.get(0,0);
		x0 = u.get(0,1);
		y0 = u.get(0,2);
		z0 = u.get(0,3);
	} else {
		w0 = 0;
		x0 = u.get(0,0);
		y0 = u.get(0,1);
		z0 = u.get(0,2);
	}

	double w1,x1,y1,z1;
	if (v.n==4) {
		w1 = v.get(0,0);
		x1 = v.get(0,1);
		y1 = v.get(0,2);
		z1 = v.get(0,3);
	} else {
		w1 = 0;
		x1 = v.get(0,0);
		y1 = v.get(0,1);
		z1 = v.get(0,2);
	}

	double res_[4] = {
		-x1*x0 - y1*y0 - z1*z0 + w1*w0,
		 x1*w0 + y1*z0 - z1*y0 + w1*x0,
		-x1*z0 + y1*w0 + z1*x0 + w1*y0,
		 x1*y0 - y1*x0 + z1*w0 + w1*z0
	};
	Matrix result(1,4,res_);
	return result;
}

Matrix Matrix::quaternion_inverse() const {
	if (m!=1 || n!=4) // for row vectors only
		return Matrix(); //empty

	double w0 = get(0,0);
	double x0 = get(0,1);
	double y0 = get(0,2);
	double z0 = get(0,3);

	double sqr_norm_inv = 1.0/(w0*w0 + x0*x0 + y0*y0 + z0*z0);

	double res_[4] = {
		 w0 * sqr_norm_inv,
		-x0 * sqr_norm_inv,
		-y0 * sqr_norm_inv,
		-z0 * sqr_norm_inv
	};
	Matrix result(1,4,res_);
	return result;
}

Matrix Matrix::quaternion_rotate(Matrix& Q) const {
	if (m!=1 || n!=3|| Q.m!=1 || Q.n!=4) // for row vectors only
		return Matrix();
		
	
	Matrix tmp = Q.quaternion_multiply(*this).quaternion_multiply(Q.quaternion_inverse());
	
	return tmp.submatrix(0,1,0,3);
}

Matrix& Matrix::normalize() {
	double k = norm();
	if (k > 0) {
		*this *= (1 / k);
	}
	return *this;
}

double Matrix::norm() const {
	double result = 0.0;
	for (unsigned char i=0; i<m; i++)
		for (unsigned char j=0; j<n; j++)
			result += get(i, j)*get(i, j);
	result = sqrt(result);
	return result;
}

double Matrix::sum() const {
	double result = 0.0;
	for (unsigned char i=0; i<m; i++)
		for (unsigned char j=0; j<n; j++)
			result += get(i, j);
	return result;
}

Matrix Matrix::identity(unsigned char m) {
	Matrix result(m,m);
	for(unsigned char i=0; i<m; i++) {
		result(i,i) = 1.0;
	}
	return result;
}

void Matrix::release() {
	if (data && isAllocated) {
//		std::cout << "release: " << m*n << " doubles\n";
		delete[] data;
		data = 0;
		isAllocated = false;
	}
}
void Matrix::allocate() {
	release();
	if (m && n)
		this->data = new double[m * n];
	else
		this->data = 0;
	isAllocated = true;
//	std::cout << "allocate: " << m*n << " doubles\n";
}

Matrix Matrix::submatrix(unsigned char row_top, unsigned char col_left, unsigned char row_bottom, unsigned char col_right) const {
	unsigned char rows = row_bottom-row_top+1;
	unsigned char cols = col_right-col_left+1;
	Matrix result(rows, cols);

	for(unsigned char i=0;i<rows; i++)
		for(unsigned char j=0; j<cols; j++)
			result(i,j) = get(row_top+i, col_left+j);
	return result;
}

bool Matrix::closeEnough(const Matrix& another) {
	if (another.m !=m || another.n != n) {
		return false;
	}
	bool result = true;

	for (unsigned char i=0; result && i<m; i++)
	{
		for(unsigned char j=0; j<n; j++){
			if (fabs(get(i,j)-another.get(i,j)) > 1.0e-6) {
				result = false;
				break;
			}
		}
	}
	return result;
}

Matrix Matrix::estimate_quaternion(Matrix& A, Matrix& B, Matrix& A2, Matrix& B2) {
	Matrix N1 = A.cross(B);
	N1.normalize();

	Matrix N2 = A2.cross(B2);
	N2.normalize();

	double cosa = N1.dot(N2.transposed()).get(0,0);
	double sina = sqrt(0.5 - 0.5*cosa);
	cosa = sqrt(0.5 + 0.5*cosa);

	Matrix NN = N1.cross(N2);
	NN.normalize();
	NN *= sina;
	double Q1_[] = {cosa, NN(0,0), NN(0,1), NN(0,2)};
	Matrix Q1(1,4,Q1_);
	A = A.quaternion_rotate(Q1);
	B = B.quaternion_rotate(Q1);
	cosa = A.dot(A2.transposed()).get(0,0);
	sina = sqrt(0.5 - 0.5*cosa);
	cosa = sqrt(0.5 + 0.5*cosa);
	Matrix ax2 = A.cross(A2);
	ax2.normalize();
	ax2 *= sina;
	double Q2_[] = {cosa, ax2(0,0), ax2(0,1), ax2(0,2)};
	Matrix Q2(1, 4, Q2_);

	Matrix Q = Q2.quaternion_multiply(Q1);

	return Q;
}

#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix {
public:
	Matrix(unsigned char m=0, unsigned char n=0, double* data=0, bool transposed=false);
	Matrix(const Matrix &rhs);
	virtual ~Matrix();
	static Matrix identity(unsigned char m);
	static Matrix estimate_quaternion(Matrix& A, Matrix& B, Matrix& A2, Matrix& B2);
	Matrix& copyData(const double * data);
	Matrix& copyMatrix(const Matrix& m);
	Matrix& operator=(const Matrix &rhs);
	Matrix& operator+=(const Matrix &rhs);
	Matrix& operator-=(const Matrix &rhs);
	Matrix& operator*=(double scalar);
	Matrix& multiplySelf(const Matrix &rhs);
	Matrix& dotSelf(const Matrix &rhs, bool left=false);
	Matrix& normalize();
	double norm() const;
	double sum() const;

	Matrix  dot(const Matrix &rhs, bool left=false) const;
	Matrix  cross(const Matrix &rhs, bool left=false) const;
	Matrix  quaternion_multiply(const Matrix &rhs, bool left=false) const;
	Matrix quaternion_inverse() const;
	Matrix quaternion_rotate(Matrix& Q) const;
	Matrix multiply(const Matrix &rhs) const;
	Matrix operator+(const Matrix &rhs) const;
	Matrix operator-(const Matrix &rhs) const;
	Matrix operator-() const;
	Matrix operator~() const; // inverse
	Matrix operator*(double scalar) const;
	Matrix submatrix(unsigned char row_top, unsigned char col_left, unsigned char row_bottom, unsigned char col_right) const;
	double& operator()(unsigned char i, unsigned char j=0);

	const double& get(unsigned char i, unsigned char j) const;
	double& set(unsigned char i, unsigned char j);
	unsigned char index(unsigned char i, unsigned char j) const;

	bool  operator==(const Matrix &other) const;
	bool  operator!=(const Matrix &other) const;

	Matrix&  inverse();
	double trace() const;

	Matrix& transpose();
	Matrix transposed() const;
	void release();
	void allocate();
	bool closeEnough(const Matrix& another);

	double* data;
	unsigned char m;
	unsigned char n;
	bool isAllocated;
	bool isTransposed;
};



#endif /* MATRIX_H_ */

/*
 * Kalman.h
 *
 */

#ifndef KALMAN_H_
#define KALMAN_H_
#include "KalmanParams.h"

class ExtendedKalman {

public:
	ExtendedKalman();
	virtual ~ExtendedKalman();
	void predict();
	void correct(const Matrix& z);
    // ------ to be overriden in subclass ------
    virtual void getR(Matrix& R) {}
    virtual void getH(Matrix& H, const Matrix& X) {}
    virtual void getQ(Matrix& Q) {}
    virtual void getF(Matrix& F, Matrix& z) {}
    virtual int getN(){ return 0; }
	// -----------------------------------------
	Matrix X;
	Matrix P;
};

#endif /* KALMAN_H_ */

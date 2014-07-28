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
	Matrix X;
	Matrix P;
};

#endif /* KALMAN_H_ */

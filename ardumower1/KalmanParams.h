#ifndef KALMAN_PARAMS_H_
#define KALMAN_PARAMS_H_

#include "Matrix.h"

void getR(Matrix& R);
void getH(Matrix& H, const Matrix& X);
void getQ(Matrix& Q);
void getF(Matrix& F, Matrix& z);
int getN();

#endif

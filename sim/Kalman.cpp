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

#include "Kalman.h"
#include "Matrix.h"
//#include "utils.h"

ExtendedKalman::ExtendedKalman() {
	int N = getN();
	X = Matrix(N, 1); // column vector
	P = Matrix(N, N);
}

ExtendedKalman::~ExtendedKalman() {

}



void ExtendedKalman::predict() {
	{
		Matrix F;
		getF(F, X);
	//  X = F * X
		X.dotSelf(F, true);
	//	P = F * P * F.T + Q

		P.dotSelf(F, true).dotSelf(F.transposed());
	}
	{
		Matrix Q;
		getQ(Q);
		P += Q;
	}
}

void ExtendedKalman::correct(const Matrix& Z) {
	Matrix K = P;
	Matrix H(7,7);
	getH(H, X);
	{
		K.dotSelf(H, true);
		H.transpose();
		K.dotSelf(H);// H=H.T
	}
	{
		Matrix R(7,7);
		getR(R);
		K += R;
	}
	K.inverse();

	K.dotSelf(H, true).dotSelf(P, true); // H.T

	// K = (P * H.T * (H * P * H.T)^-1)

	{
		Matrix xz(X);
		xz.dotSelf(H.transpose(), true);// H = H.T.T (transpose back)
		xz -= Z;
		xz *= -1;
		xz.dotSelf(K, true);
		X += xz;
		// X = X + K * (Z - H * X)
	}
	K.dotSelf(H); // H
	K -= Matrix::identity(getN());
	K *= -1;
	P.dotSelf(K, true);
	// P = (I - K * H) * P

}

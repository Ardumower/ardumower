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

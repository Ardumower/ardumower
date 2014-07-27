 /*******************************************************************************
  * 
  *  JKalman - KALMAN FILTER (Java)
  *
  *  Copyright (C) 2007 Petr Chmelar
  *
  *  By downloading, copying, installing or using the software you agree to 
  *  the license in licenseIntel.txt or in licenseGNU.txt
  *
  **************************************************************************** */

package jkalman;

import jama.Matrix;

import java.util.*;

/**
 * Kalman filter (state).
 * <p>
 * The structure <code>JKalman</code> is used to keep 
 * Kalman filter state. It is created by constructor function, updated by 
 * <code>Predict</code> and <code>Correct</code> functions.
 * <p>
 * Normally, the structure is used for standard JKalman filter 
 * (notation and the formulae below are borrowed from the JKalman 
 * tutorial <a href="http://www.cs.unc.edu/~welch/kalman/">[Welch95]</a>):
 * <pre>
 * x<sub>k</sub>=A*x<sub>k-1</sub>+B*u<sub>k</sub>+w<sub>k</sub>
 * z<sub>k</sub>=Hx<sub>k</sub>+v<sub>k</sub>,
 * </pre>
 * <p>where:
 * <pre>
 * x<sub>k</sub> (x<sub>k-1</sub>) - state of the system at the moment k (k-1)
 * z<sub>k</sub> - measurement of the system state at the moment k
 * u<sub>k</sub> - external control applied at the moment k
 * w<sub>k</sub> and v<sub>k</sub> are normally-distributed process and measurement noise, respectively:
 * p(w) ~ N(0,Q)
 * p(v) ~ N(0,R),
 * that is,
 * Q - process noise covariance matrix, constant or variable,
 * R - measurement noise covariance matrix, constant or variable
 * </pre>
 * <p>
 * In case of standard JKalman filter, all the matrices: A, B, H, Q and R 
 * are initialized once after JKalman structure is allocated via constructor.
 * However, the same structure and the same functions may be used to simulate 
 * extended JKalman filter by linearizing extended JKalman filter equation in the 
 * current system state neighborhood, in this case A, B, H (and, probably, 
 * Q and R) should be updated on every step.
 */
public class JKalman {

    /** number of measurement vector dimensions */
    int mp;
    /** number of state vector dimensions */
    int dp;
    /** number of control vector dimensions */
    int cp;
    
    /** predicted state (x'(k)): x(k)=A*x(k-1)+B*u(k) */
    Matrix state_pre;           
    /** corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k)) */
    Matrix state_post;
    /** state transition matrix (A) */
    Matrix transition_matrix;
    /** control matrix (B) (it is not used if there is no control)*/
    Matrix control_matrix;
    /** measurement matrix (H) */    
    Matrix measurement_matrix;
    /** process noise covariance matrix (Q) */
    Matrix process_noise_cov;
    /** measurement noise covariance matrix (R) */
    Matrix measurement_noise_cov;
    /** priori error estimate covariance matrix (P'(k)): P'(k)=A*P(k-1)*At + Q) */
    Matrix error_cov_pre;
    /** Kalman gain matrix (K(k)): K(k)=P'(k)*Ht*inv(H*P'(k)*Ht+R) */
    Matrix gain;
    /** posteriori error estimate covariance matrix (P(k)): P(k)=(I-K(k)*H)*P'(k) */
    Matrix error_cov_post;

    /** temporary matrices */
    Matrix temp1;
    Matrix temp2;
    Matrix temp3;
    Matrix temp4;
    Matrix temp5;

    /**
     * The construstor allocates JKalman filter and all its matrices and 
     * initializes them somehow.
     * @param dynam_params
     * @param measure_params
     * @param control_params
     * 
     * @exception IllegalArgumentException Kalman filter dimensions exception.
     */
    public JKalman(int dynam_params, int measure_params, int control_params) 
                throws Exception {
        
        if( dynam_params <= 0 || measure_params <= 0 ) {
            throw new IllegalArgumentException("Kalman filter: Illegal dimensions.");
        }
        
        if( control_params < 0 ) {
            control_params = dynam_params;
        }
        
        // init
        dp = dynam_params;
        mp = measure_params;
        cp = control_params;

        state_pre = new Matrix(dp, 1); // init by transition _matrix*state_post

        // following variables must be initialized properly in advance        
        state_post = new Matrix(dp, 1); // init by the first measurement!!!
        transition_matrix = Matrix.identity(dp, dp); // or init the matrix as:
/*      double[][] tr = { {1, 0, 1, 0},              // { {1, 1},   // x
                           {0, 1, 0, 1},             //   {0, 1} }; // dx
                           {0, 0, 1, 0}, 
                           {0, 0, 0, 1} };
        kalman.transition_matrix = new Matrix(tr);
*/      
        process_noise_cov = Matrix.identity(dp, dp, 1e-3); // 1e-5 (1 in OpenCV)

        measurement_matrix = Matrix.identity(mp, dp); // 1 (0 in OpenCV)
        measurement_noise_cov = Matrix.identity(mp, mp, 1e-1); // 1e-1 (1 in OpenCV)

        error_cov_pre = new Matrix(dp, dp); // initialized in Predict
        error_cov_post = Matrix.identity(dp, dp); // 1 (0 in OpenCV)

        gain = new Matrix(dp, mp);

        if( cp > 0 )
        {
            control_matrix = new Matrix(dp, cp);
        }
        else { // TODO possibly an error in OpenCV
            control_matrix = null;
        }

        temp1 = new Matrix(dp, dp);
        temp2 = new Matrix(mp, dp);
        temp3 = new Matrix(mp, mp);
        temp4 = new Matrix(mp, dp);
        temp5 = new Matrix(mp, 1);        
    }

    /**
     * Constructor in case of no control.
     * @param dynam_params
     * @param measure_params
     */
    public JKalman(int dynam_params, int measure_params) throws Exception {
        this(dynam_params, measure_params, 0);
    }

    
    /**
     * Alias for prediction with no control.
     * @return Predict(no control).
     */
    public Matrix Predict() {
        return Predict(null);
    }
    
    /**
     * Estimates subsequent model state.
     * <p> The function estimates the subsequent 
     * stochastic model state by its current state and stores it at 
     * <code>state_pre</code>:
     * <pre>
     * x'<sub>k</sub>=A*x<sub>k</sub>+B*u<sub>k</sub>
     * P'<sub>k</sub>=A*P<sub>k-1</sub>*A<sup>T</sup> + Q,
     * where
     * x'<sub>k</sub> is predicted state (state_pre),
     * x<sub>k-1</sub> is corrected state on the previous step (state_post)
     *     (should be initialized somehow in the beginning, zero vector by default),
     * u<sub>k</sub> is external control (<code>control</code> parameter),
     * P'<sub>k</sub> is prior error covariance matrix (error_cov_pre)
     * P<sub>k-1</sub> is posteriori error covariance matrix on the previous step (error_cov_post)
     *     (should be initialized somehow in the beginning, identity matrix by default),
     * </pre>
     * @param control Control vector (u<sub>k</sub>), should be NULL if there 
     * is no external control (<code>control_params</code>=0).
     * @return The function returns the estimated state.
     */
    public Matrix Predict(Matrix control) {

        // (1) Project the state ahead
        // update the state: x'(k) = A*x(k)
        state_pre = transition_matrix.times(state_post);
        if( control != null && cp > 0 ) {
             // x'(k) = x'(k) + B*u(k)
             state_pre = control_matrix.gemm(control, state_pre, 1, 1);
        }

        // (2) Project the error covariance ahead
        // update error covariance matrices: temp1 = A*P(k)
        temp1 = transition_matrix.times(error_cov_post);
        // P'(k) = temp1*At + Q
        error_cov_pre = temp1.gemm(transition_matrix.transpose(), process_noise_cov, 1, 1);

        return state_pre;
    }
    
    /**
     * Adjusts model state.
     * The function <code>KalmanCorrect</code> adjusts stochastic model state 
     * on the basis of the given measurement of the model state:</p>
     * <pre>
     * K<sub>k</sub>=P'<sub>k</sub>*H<sup>T</sup>*(H*P'<sub>k</sub>*H<sup>T</sup>+R)<sup>-1</sup>
     * x<sub>k</sub>=x'<sub>k</sub>+K<sub>k</sub>*(z<sub>k</sub>-H*x'<sub>k</sub>)
     * P<sub>k</sub>=(I-K<sub>k</sub>*H)*P'<sub>k</sub>
     * where
     * z<sub>k</sub> - given measurement (<code>mesurement</code> parameter)
     * K<sub>k</sub> - JKalman "gain" matrix.
     * </pre>
     * <p>The function stores adjusted state at <code>state_post</code> and 
     * returns it on output.
     * @param measurement Matrix containing the measurement vector.
     * @return
     */
    public Matrix Correct(final Matrix measurement) {

        // (1) Compute the Kalman gain
        // temp2 = H*P'(k)
        temp2 = measurement_matrix.times(error_cov_pre);        

        // temp3 = temp2*Ht + R 
        temp3 = temp2.gemm(measurement_matrix.transpose(), measurement_noise_cov, 1, 1);

        // temp4 = inv(temp3)*temp2 = Kt(k) 
        temp4 = temp3.solve(temp2);
        // hokus pokus...
        // temp4 = temp3.svd().getU().times(temp2);

        // K(k) 
        gain = temp4.transpose();
        
        // (2) Update estimate with measurement z(k)
        // temp5 = z(k) - H*x'(k) 
        temp5 = measurement_matrix.gemm(state_pre, measurement, -1, 1);

        // x(k) = x'(k) + K(k)*temp5 
        state_post = gain.gemm(temp5, state_pre, 1, 1);

        // (3) Update the error covariance.
        // P(k) = P'(k) - K(k)*temp2 
        error_cov_post = gain.gemm(temp2, error_cov_pre, -1, 1);

        return state_post;
    }

    /**
     * Setter
     * @param state_pre
     */
    public void setState_pre(Matrix state_pre) {
        this.state_pre = state_pre;
    }

    /**
     * Getter
     * @return
     */
    public Matrix getState_pre() {
        return state_pre;
    }

    /**
     * Setter
     * @param state_post
     */
    public void setState_post(Matrix state_post) {
        this.state_post = state_post;
    }

    public Matrix getState_post() {
        return state_post;
    }

    /**
     * Getter
     * @param transition_matrix
     */
    public void setTransition_matrix(Matrix transition_matrix) {
        this.transition_matrix = transition_matrix;
    }

    public Matrix getTransition_matrix() {
        return transition_matrix;
    }

    /**
     * Setter
     * @param control_matrix
     */
    public void setControl_matrix(Matrix control_matrix) {
        this.control_matrix = control_matrix;
    }

    /**
     * Getter
     * @return
     */
    public Matrix getControl_matrix() {
        return control_matrix;
    }

    /**
     * Setter
     * @param measurement_matrix
     */
    public void setMeasurement_matrix(Matrix measurement_matrix) {
        this.measurement_matrix = measurement_matrix;
    }

    /**
     * Getter
     * @return
     */
    public Matrix getMeasurement_matrix() {
        return measurement_matrix;
    }

    /**
     * Setter
     * @param process_noise_cov
     */
    public void setProcess_noise_cov(Matrix process_noise_cov) {
        this.process_noise_cov = process_noise_cov;
    }

    /**
     * Getter
     * @return
     */
    public Matrix getProcess_noise_cov() {
        return process_noise_cov;
    }

    /**
     * Setter
     * @param measurement_noise_cov
     */
    public void setMeasurement_noise_cov(Matrix measurement_noise_cov) {
        this.measurement_noise_cov = measurement_noise_cov;
    }

    /**
     * Getter
     * @return
     */
    public Matrix getMeasurement_noise_cov() {
        return measurement_noise_cov;
    }

    /**
     * Setter
     * @param error_cov_pre
     */
    public void setError_cov_pre(Matrix error_cov_pre) {
        this.error_cov_pre = error_cov_pre;
    }

    /**
     * Getter
     * @return
     */
    public Matrix getError_cov_pre() {
        return error_cov_pre;
    }

    /**
     * Setter
     * @param gain
     */
    public void setGain(Matrix gain) {
        this.gain = gain;
    }

    /**
     * Getter
     * @return
     */
    public Matrix getGain() {
        return gain;
    }

    /**
     * Setter
     * @param error_cov_post
     */
    public void setError_cov_post(Matrix error_cov_post) {
        this.error_cov_post = error_cov_post;
    }

    /**
     * Getter
     * @return
     */
    public Matrix getError_cov_post() {
        return error_cov_post;
    }
}

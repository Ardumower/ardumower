/* author: Louis Hugues - created on 27 janv. 2005  */
package simbad.sim;

import java.text.DecimalFormat;
import javax.media.j3d.Transform3D;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

/**
 *  This class models the differential drive kinematic common.
 * The two control parameters are left and right velocity.
 */
public class DifferentialKinematic extends KinematicModel {

    private Transform3D t3d;
    private double leftWheelVelocity;
    private double rightWheelVelocity;
    private double wheelsDistance;
    private Point3d tempPoint;

    public DifferentialKinematic(double wheelsDistance){
        this.wheelsDistance = wheelsDistance;
        tempPoint = new Point3d();
         t3d = new Transform3D();
        reset();
    }

    /** Compute instant translation and rotation vectors .
     * 
     * @param elapsedSecond time elapsed
     * @param rotation current rotation
     * @param instantTranslation to store translation
     * @param instantRotation to store rotation
     */ 
 
    protected void   update(double elapsedSecond,Transform3D rotation,Vector3d instantTranslation,Vector3d instantRotation)
    {
    // perform translation - according to current position and orientation
        //For details see :
        //Computational Principles of Mobile Robotic - Dudek & Jenkins -
        // Cambridge University Press - Differential drive chapter.
        double epsilon = 0.001;
        double vl = leftWheelVelocity;
        double vr = rightWheelVelocity;
        // distance between the two wheels.
        double l = wheelsDistance;
        double r, omega;

		double  dtheta;
        // forward kinematic : find position knowing the velocity of the two
        // wheels.
        if (Math.abs(vl - vr) < epsilon) {
            dtheta = 0;
            instantTranslation.set(vl * elapsedSecond, 0, 0);
            rotation.transform(instantTranslation);
        } else {
            // compute position (r,omega) of instantaneous center of curvature (ICC)
            r = l * (vl + vr) / (2 * (vr - vl));
            omega = (vr - vl) / l;
            double omegadt = omega * elapsedSecond;
            // move in XZ plane
            // rotate position around the ICC of omega x dt radians
            instantTranslation.set(0, 0, r);
            t3d.setIdentity();
            t3d.rotY(omegadt);
            t3d.transform(instantTranslation);
            // back to origin
            tempPoint.set(0, 0, r);
            instantTranslation.sub(tempPoint);
            // take into account current robot orientation
            rotation.transform(instantTranslation);
            dtheta = omegadt;
        }
       
        // perform rotation -
        instantRotation.set(0,dtheta,0);
    }

    /** Resets all control parameters to their initial values. */       
    protected void reset() {
        leftWheelVelocity = 0;
        rightWheelVelocity = 0;
    }

    /** Resets all control parameters to their initial values. */       
  protected String toString(DecimalFormat format) {
        return "kinematic \t= DifferentialKinematic\n" + "left velocity   \t= "
                + format.format(leftWheelVelocity) + " m/s\n"
                + "right velocity \t= " + format.format(rightWheelVelocity)
                + " m/s\n";
    }

  /** Sets the velocity of the left wheel in meter/s. */  
  public void setLeftVelocity(double vel) {
        leftWheelVelocity = vel;
    }

  /** Sets the velocity of the right wheel in meter/s. */  
    public void setRightVelocity(double vel) {
        rightWheelVelocity = vel;
    }

    /** Sets the velocity of both  wheels in meter/s. */  
    public void setWheelsVelocity(double vl, double vr) {
        leftWheelVelocity = vl;
        rightWheelVelocity = vr;
    }
    /** Gets the velocity of the left wheel in meter/s. */  
    public double  getLeftVelocity() {
          return leftWheelVelocity;
      }
    /** Gets the velocity of the right wheel in meter/s. */  
    public double  getRightVelocity() {
          return rightWheelVelocity;
      }
}
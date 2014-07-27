package algernon.subsumption.demo;

import algernon.subsumption.Behavior;
import algernon.subsumption.Sensors;
import algernon.subsumption.Velocities;

/**
 * 
 */
public class Tracking extends Behavior {
	
	double leftPWM = 1;
	double rightPWM = 1;
	int counter = 0;
	boolean isInside = true;

   /**
    * @param sensors
    */
   public Tracking(Sensors sensors) {
      super(sensors);
   }

   /*
    * (non-Javadoc)
    * 
    * @see labyrinth.subsumption.Behavior#act()
    */
   @Override
   public Velocities act() {
	  if (getSensors().getPerimeter().isInside() != isInside){
		  isInside = getSensors().getPerimeter().isInside();
		  if (!isInside) counter++;		   
	  }
	  
	  
	  //double translationalVelocity = 0.5 / (llum + rlum);
      //double rotationalVelocity = (llum - rlum) * Math.PI / 4;
      //return new Velocities(translationalVelocity, rotationalVelocity);
	        
	  Velocities v = new Velocities();
	  double  lms = leftPWM;
	  double  rms = rightPWM;	  
	  if (counter > 0){
		  if (isInside) {
			    rms += 0.8;
			    lms -= 0.1;
		  }
		  else
			  {
			    rms -= 0.1;
			    lms += 0.8;
		  }
		  if (rms > 2) rms = 2;
		  if (lms > 2) lms = 2;
		  if (rms < -1) rms = -1;
		  if (lms < -1) lms = -1;  
	  }
	    
	  v.setWheelVelocities( lms,  rms );
	  return v;
   }

   /*
    * (non-Javadoc)
    * 
    * @see labyrinth.subsumption.Behavior#isActive()
    */
   @Override
   public boolean isActive() {
	  return true;      
   }

   /*
    * Returns a description of this behavior.
    */
   @Override
   public String toString() {
      return "[Tracking: " + super.toString() + "]";
   }
}

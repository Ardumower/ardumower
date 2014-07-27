/*    
  	Algernon is an implementation of a subsumption architecture for Simbad.
  	
    Copyright (C) 2007  Paul Reiners

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
    
    You may reach the author, Paul Reiners, by email at <paul.reiners@gmail.com>
    or at the following postal address:
    
    	503 15th Avenue SW
    	Rochester, MN  55902
 */

package algernon.subsumption;

/**
 * @author Paul Reiners
 * 
 */
public class Velocities {

   public double translationalVelocity = 0;
   public double rotationalVelocity = 0;
   
   public double rightWheelVelocity = 0;
   public double leftWheelVelocity = 0;
   
   public boolean useWheelVelocity = false;
   
   public Velocities(){	   
   }

   public Velocities(double translationalVelocity, double rotationalVelocity) {
      this.translationalVelocity = translationalVelocity;
      this.rotationalVelocity = rotationalVelocity;
      this.useWheelVelocity = false;
   }
   
   public void setWheelVelocities(double leftWheelVelocity, double rightWheelVelocity){
	  this.leftWheelVelocity = leftWheelVelocity;
	  this.rightWheelVelocity = rightWheelVelocity;
	  this.useWheelVelocity = true;
   }
   
   double getLeftWheelVelocity(){
	   return leftWheelVelocity;
   }

   double getRightWheelVelocity(){
	   return rightWheelVelocity;
   }
   
   /**
    * @return the translationalVelocity
    */
   double getTranslationalVelocity() {
      return translationalVelocity;
   }

   /**
    * @return the rotationalVelocity
    */
   double getRotationalVelocity() {
      return rotationalVelocity;
   }

   /*
    * Returns a description of these velocities.
    */
   @Override
   public String toString() {
      return "[Velocities: translationalVelocity=" + translationalVelocity
            + ", rotationalVelocity=" + rotationalVelocity + "]";
   }
}

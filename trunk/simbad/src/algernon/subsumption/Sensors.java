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

import simbad.sim.IMUSensor;
import simbad.sim.LightSensor;
import simbad.sim.PerimeterSensor;
import simbad.sim.RangeSensorBelt;

/**
 * @author Paul Reiners
 * 
 */
public class Sensors {

   private RangeSensorBelt sonars, bumpers;
   private LightSensor lightSensorLeft;
   private LightSensor lightSensorRight;
   private IMUSensor imu;
   private PerimeterSensor perimeter;

   public Sensors(PerimeterSensor perimeter, IMUSensor imu, RangeSensorBelt sonars, RangeSensorBelt bumpers,
         LightSensor lightSensorLeft, LightSensor rightSensorRight) {
      //this(sonars, bumpers);
	  this.sonars = sonars;
	  this.bumpers = bumpers;
      this.perimeter = perimeter;
      this.imu = imu;
      this.lightSensorLeft = lightSensorLeft;
      this.lightSensorRight = rightSensorRight;
   }

   /*public Sensors(RangeSensorBelt sonars, RangeSensorBelt bumpers) {
      this.sonars = sonars;
      this.bumpers = bumpers;
   }*/

   public RangeSensorBelt getSonars() {
      return sonars;
   }

   public RangeSensorBelt getBumpers() {
      return bumpers;
   }
   
   public IMUSensor getIMU(){
	   return imu;
   }
   
   public PerimeterSensor getPerimeter(){
	   return perimeter;
   }

   /**
    * @return the lightSensorLeft
    */
   public LightSensor getLightSensorLeft() {
      return lightSensorLeft;
   }

   /**
    * @return the rightSensorRight
    */
   public LightSensor getLightSensorRight() {
      return lightSensorRight;
   }

   /*
    * Returns a description of these sensors.
    */
   @Override
   public String toString() {
      return "[Sensors: imu=" + imu + ", sonars=" + sonars + ", bumpers=" + bumpers
            + ", lightSensorLeft=" + lightSensorLeft + ", lightSensorRight="
            + lightSensorRight + "]";
   }
}

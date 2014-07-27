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

package algernon.subsumption.demo;

import algernon.subsumption.Behavior;
import algernon.subsumption.Sensors;
import algernon.subsumption.Velocities;

/**
 * @author Paul Reiners
 * 
 */
public class LightSeeking extends Behavior {

   private static final double LUMINANCE_SEEKING_MIN = 0.1;

   /**
    * @param sensors
    */
   public LightSeeking(Sensors sensors) {
      super(sensors);
   }

   /*
    * (non-Javadoc)
    * 
    * @see labyrinth.subsumption.Behavior#act()
    */
   @Override
   public Velocities act() {
	  // turn towards light
      float llum = getSensors().getLightSensorLeft().getAverageLuminance();
      float rlum = getSensors().getLightSensorRight().getAverageLuminance();
      double translationalVelocity = 0.5 / (llum + rlum);
      double rotationalVelocity = (llum - rlum) * Math.PI / 4;

      return new Velocities(translationalVelocity, rotationalVelocity);
   }

   /*
    * (non-Javadoc)
    * 
    * @see labyrinth.subsumption.Behavior#isActive()
    */
   @Override
   public boolean isActive() {
	  return false;
      /*float llum = getSensors().getLightSensorLeft().getAverageLuminance();
      float rlum = getSensors().getLightSensorRight().getAverageLuminance();
      double luminance = (llum + rlum) / 2.0;

      // Seek light if it's near.
      return luminance > LUMINANCE_SEEKING_MIN;*/
   }

   /*
    * Returns a description of this behavior.
    */
   @Override
   public String toString() {
      return "[LightSeeking: " + super.toString() + "]";
   }
}

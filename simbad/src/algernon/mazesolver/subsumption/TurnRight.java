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

package algernon.mazesolver.subsumption;

import simbad.sim.RangeSensorBelt;
import algernon.subsumption.Velocities;

/**
 * @author Paul Reiners
 * 
 */
public class TurnRight extends algernon.subsumption.Behavior {

   private int backingUpCount = 0;
   private int turningRightCount = 0;

   /**
    * @param sensors
    */
   public TurnRight(algernon.subsumption.Sensors sensors) {
      super(sensors);
   }

   /*
    * (non-Javadoc)
    * 
    * @see algernon.subsumption.Behavior#act()
    */
   @Override
   public Velocities act() {
      if (backingUpCount > 0) {
         // We back up a bit (we just ran into a wall) before turning right.
         backingUpCount--;

         return new Velocities(-TRANSLATIONAL_VELOCITY, 0.0);
      } else {
         turningRightCount--;

         return new Velocities(0.0, -Math.PI / 2);
      }
   }

   /*
    * (non-Javadoc)
    * 
    * @see algernon.subsumption.Behavior#isActive()
    */
   @Override
   public boolean isActive() {
      if (turningRightCount > 0) {
         return true;
      }

      RangeSensorBelt bumpers = getSensors().getBumpers();
      // Check the front bumper.
      if (bumpers.hasHit(0)) {
         backingUpCount = 10;
         turningRightCount = getRotationCount();

         return true;
      } else {
         return false;
      }
   }

   /*
    * Returns a description of this behavior.
    */
   @Override
   public String toString() {
      return "[TurnRight: backingUpCount=" + backingUpCount
            + ", turningRightCount=" + turningRightCount + ", "
            + super.toString() + "]";
   }
}

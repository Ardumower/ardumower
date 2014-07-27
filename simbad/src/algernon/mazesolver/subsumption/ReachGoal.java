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
public class ReachGoal extends algernon.subsumption.Behavior {

   /**
    * @param sensors
    */
   public ReachGoal(algernon.subsumption.Sensors sensors) {
      super(sensors);
   }

   /*
    * (non-Javadoc)
    * 
    * @see algernon.subsumption.Behavior#act()
    */
   @Override
   public Velocities act() {
      System.out.println("Reached goal!!!");

      // Stop
      return new Velocities(0.0, 0.0);
   }

   /*
    * (non-Javadoc)
    * 
    * @see algernon.subsumption.Behavior#isActive()
    */
   @Override
   public boolean isActive() {
      RangeSensorBelt sonars = getSensors().getSonars();

      // Is there open space all around us? That is, are we out of the maze?
      double clearDistance = 1.2;
      return sonars.getMeasurement(0) > clearDistance
            && sonars.getMeasurement(1) > clearDistance
            && sonars.getMeasurement(3) > clearDistance
            && sonars.getMeasurement(2) > clearDistance;
   }

   /*
    * Returns a description of this behavior.
    */
   @Override
   public String toString() {
      return "[ReachGoal: " + super.toString() + "]";
   }
}

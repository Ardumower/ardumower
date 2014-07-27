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
import simbad.sim.RangeSensorBelt;

/**
 * @author Paul Reiners
 * 
 */
public class Avoidance extends Behavior {

   public Avoidance(Sensors sensors) {
      super(sensors);
   }

   /*
    * (non-Javadoc)
    * 
    * @see labyrinth.subsumption.Behavior#act()
    */
   @Override
   public Velocities act() {
      double translationalVelocity = 0.8;
      double rotationalVelocity = 0;
      RangeSensorBelt sonars = getSensors().getSonars();
      double rotationalVelocityFactor = Math.PI / 32;
      /*if (!getSensors().getPerimeter().isInside()){
          // if ran outside perimeter
          translationalVelocity = -0.1;
          rotationalVelocity = Math.PI / 8 
                - (rotationalVelocityFactor * Math.random());
      } else*/ if (getSensors().getBumpers().oneHasHit()) {
         // if ran into something
         translationalVelocity = -0.1;
         rotationalVelocity = Math.PI / 8
               - (rotationalVelocityFactor * Math.random());
      } else if (sonars.oneHasHit()) {
         // reads the three front quadrants
         double left = sonars.getFrontLeftQuadrantMeasurement();
         double right = sonars.getFrontRightQuadrantMeasurement();
         double front = sonars.getFrontQuadrantMeasurement();
         // if obstacle near
         if ((front < 0.7) || (left < 0.7) || (right < 0.7)) {
            double maxRotationalVelocity = Math.PI / 4;
            if (left < right)
               rotationalVelocity = -maxRotationalVelocity
                     - (rotationalVelocityFactor * Math.random());
            else
               rotationalVelocity = maxRotationalVelocity
                     - (rotationalVelocityFactor * Math.random());
            translationalVelocity = 0;
         } else {
            rotationalVelocity = 0;
            translationalVelocity = 0.6;
         }
      }

      return new Velocities(translationalVelocity, rotationalVelocity);
   }

   /*
    * (non-Javadoc)
    * 
    * @see labyrinth.subsumption.Behavior#isActive()
    */
   @Override
   public boolean isActive() {
      return getSensors().getBumpers().oneHasHit()
            || getSensors().getSonars().oneHasHit() ; 
           // || (!getSensors().getPerimeter().isInside());
   }

   /*
    * Returns a description of this behavior.
    */
   @Override
   public String toString() {
      return "[Avoidance: " + super.toString() + "]";
   }
}

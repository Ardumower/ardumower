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
public class StraightLine extends Behavior {

   public StraightLine(Sensors sensors) {
      super(sensors);
   }

   /*
    * (non-Javadoc)
    * 
    * @see labyrinth.subsumption.Behavior#act()
    */
   @Override
   public Velocities act() {
      return new Velocities(0.8, 0.0);
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
      return "[StraightLine: " + super.toString() + "]";
   }
}

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

package algernon.mazesolver;

import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;

import simbad.sim.Box;
import simbad.sim.EnvironmentDescription;

/**
 * @author Paul Reiners
 * 
 */
public class MazeEnvironmentDescription extends EnvironmentDescription {
   private static final double SCALE_FACTOR = 1.5;

   public MazeEnvironmentDescription(Maze maze) {
      Vector3f vertical = new Vector3f(0.25f, 0.5f,
            (float) (SCALE_FACTOR * 1.0f));
      Vector3f horizontal = new Vector3f((float) (SCALE_FACTOR * 1.0f), 0.5f,
            0.25f);
      boolean rows[][] = maze.getRows();
      double trans = SCALE_FACTOR * (-rows[0].length / 2.0);
      double xTrans = trans;
      double zTrans = trans;
      for (int i = 0; i < rows.length; i++) {
         int row = i / 2;
         if (i % 2 == 0) {
            for (int j = 0; j < rows[i].length; j++) {
               if (rows[i][j]) {
                  Vector3d wallLoc = new Vector3d(SCALE_FACTOR * row + xTrans,
                        0.0, -SCALE_FACTOR * (-(0.5 + j)) + zTrans);
                  add(new Box(wallLoc, vertical, this));
               }
            }
         } else {
            for (int j = 0; j < rows[i].length; j++) {
               if (rows[i][j]) {
                  Vector3d wallLoc = new Vector3d(SCALE_FACTOR * (0.5 + row)
                        + xTrans, 0.0, -SCALE_FACTOR * (-j) + zTrans);
                  add(new Box(wallLoc, horizontal, this));
               }
            }
         }
      }
   }

   public Vector3d getStartPos() {
      return new Vector3d(-SCALE_FACTOR * 2.5, 0, 0);
   }

   /*
    * Returns a description of this maze environment description.
    */
   @Override
   public String toString() {
      return "[MazeEnvironmentDescription: " + super.toString() + "]";
   }
}

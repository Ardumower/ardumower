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

import simbad.gui.Simbad;
import algernon.mazesolver.Maze;
import algernon.mazesolver.MazeEnvironmentDescription;

/**
 * @author Paul Reiners
 * 
 */
public class WallFollower {

   /**
    * @param args
    */
   public static void main(String[] args) {
      WallFollower wallFollower = new WallFollower();
      wallFollower.runMaze();
   }

   public void runMaze() {
      boolean mazeRows[][] = {
            { false, false, false, false, false, false, false },
            { false, false, false, false, false, false, false, false },
            { false, true, true, false, true, true, false },
            { false, true, false, false, true, false, true, false },
            { false, false, true, true, false, false, false },
            { false, true, true, false, false, true, true, false },
            { false, false, false, false, true, false, false },
            { false, true, false, true, true, false, true, false },
            { false, true, true, false, false, false, false },
            { false, true, true, false, true, true, true, false },
            { false, false, false, true, true, false, false },
            { false, true, false, false, false, false, true, false },
            { false, true, true, false, true, true, false },
            { false, false, false, false, false, false, false, false },
            { false, false, false, false, false, false, false } };
      MazeEnvironmentDescription mazeEnvironmentDescription = new MazeEnvironmentDescription(
            new Maze(mazeRows));
      algernon.subsumption.BehaviorBasedAgent wallFollowingAgent = new algernon.subsumption.BehaviorBasedAgent(
            mazeEnvironmentDescription.getStartPos(), "Wall Follower", 4, false);

      initBehaviorBasedAgent(wallFollowingAgent);

      mazeEnvironmentDescription.add(wallFollowingAgent);
      Simbad frame = new Simbad(mazeEnvironmentDescription, false);

      System.out.println("frame: " + frame);
   }

   /**
    * @return
    */
   private void initBehaviorBasedAgent(
         algernon.subsumption.BehaviorBasedAgent behaviorBasedAgent) {
      algernon.subsumption.Sensors sensors = behaviorBasedAgent.getSensors();
      algernon.subsumption.Behavior[] behaviors = { new ReachGoal(sensors),
            new TurnLeft(sensors), new TurnRight(sensors),
            new GoStraightAlways(sensors) };
      boolean subsumes[][] = { { false, true, true, true },
            { false, false, true, true }, { false, false, false, true },
            { false, false, false, false } };
      behaviorBasedAgent.initBehaviors(behaviors, subsumes);
   }

   /*
    * Returns a description of this wall follower.
    */
   @Override
   public String toString() {
      return "[WallFollower: " + super.toString() + "]";
   }
}

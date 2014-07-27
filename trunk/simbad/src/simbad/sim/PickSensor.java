/*
 *  Simbad - Robot Simulator
 *  Copyright (C) 2004 Louis Hugues
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 -----------------------------------------------------------------------------
 * $Author: sioulseuguh $ 
 * $Date: 2005/01/09 14:51:36 $
 * $Revision: 1.3 $
 * $Source: /cvsroot/simbad/src/simbad/sim/PickSensor.java,v $
 */
package simbad.sim;

import javax.media.j3d.BranchGroup;


/**
 * Base class for all sensors using picking.
 */
public abstract class PickSensor extends SensorDevice {
    protected BranchGroup pickableSceneBranch;
    
    /**
     * It should be called before update.
     * @param pickableSceneBranch
     */
   protected  void setPickableSceneBranch(BranchGroup pickableSceneBranch)
    { this.pickableSceneBranch = pickableSceneBranch;}

}

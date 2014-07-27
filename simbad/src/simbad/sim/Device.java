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
 * $Date: 2005/04/25 17:54:58 $
 * $Revision: 1.5 $
 * $Source: /cvsroot/simbad/src/simbad/sim/Device.java,v $
 */
package simbad.sim;

import javax.swing.JPanel;


/**
 * A abstract device, base class for sensorDevice and ActuatorDevice.
 * The class manages an update rate which will be used by the simulator.
 */
public abstract class Device extends BaseObject{

    private SimpleAgent owner;
    private String name;
    private double updatePerSecond;
    private double elapsedSinceUpdate;
    private boolean firstUpdate;
    private boolean updateOnEachFrame;
  
    Device() {
        owner = null;
        name = "<name>";
        updatePerSecond = 1.0;
        elapsedSinceUpdate = 0.0;
        firstUpdate = true;
        updateOnEachFrame =false;;
    }
    /**
     * @return device's name .
     */
    public String getName(){
        return name;
    }
   
    protected void setName(String name){ this.name = name;}
    
    /** Set the agent owner of this device */
    protected void setOwner(SimpleAgent agent){
        this.owner = agent;
    }
 
    /** Get the agent owner of this device */
    protected SimpleAgent getOwner(){
        return this.owner;
    }
    
    /**
     * Creates the panel associated to the device. 
     * This panel can be inserted in the inspector window for monitoring.
     * 
     * @return the JPanel.
     * null if no panel can be associated
     */
    public JPanel createInspectorPanel(){ return null;}
    
    /** Sets the number of update per seconds for this sensor. */
    public void setUpdatePerSecond(double ups) { updatePerSecond = ups;}

    /** Sets if update happens on each frame . */
    public void setUpdateOnEachFrame(boolean on ) { updateOnEachFrame = on;}

    /**
     * Returns the number of updates per second requested for this sensor.
     * @return requested number of update per second (in virtual time). 
     */
    public double getUpdatePerSecond(){    return updatePerSecond;}
   
    
    /** to be overriden */
    protected void update() {}
    
    /** to be overriden */
    protected void reset() {}
    
    /** Called by the simulator loop */
    protected void update(double elapsedSeconds) {
        if (updateOnEachFrame) {
            update();
        } else {
            elapsedSinceUpdate += elapsedSeconds;
            double delta = 1.0 / updatePerSecond;
            if ((elapsedSinceUpdate > delta) || (firstUpdate)) {
                update();
                elapsedSinceUpdate -= delta;
                firstUpdate = false;
            }
        }
    }
      
}
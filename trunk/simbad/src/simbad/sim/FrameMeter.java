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
 * $Date: 2005/03/17 17:49:37 $
 * $Revision: 1.6 $
 * $Source: /cvsroot/simbad/src/simbad/sim/FrameMeter.java,v $
 */

package simbad.sim;

/* A helper class to measure the frame per second  at a given point. */
 final class FrameMeter {

    private long lastTime;
    private long startTime;
    private long  count;
    private long totalCount;
    /** Instant fps */
    public float fps;
    public float fpsSinceStart;
    private int updateRate;
    
    public FrameMeter() {
        updateRate = 200;
        reset();
    }

    
    /*
     *  Method to be called at the measure point 
     *  
     */
    public void measurePoint(int inc) {
        count += inc;
        totalCount += inc;
        if (count >= updateRate) {
            long currTime = System.currentTimeMillis();
            long dt = (currTime - lastTime);
            if (dt != 0) fps = (1000f * count) / (float) dt;
            fpsSinceStart =(1000f *totalCount)/(float)(currTime - startTime);
            lastTime = currTime;
            count = 0;
        }
    }

    public int getUpdateRate(){
        return updateRate;
    }
    public void setUpdateRate(int rate){
        updateRate = rate;
        reset();
    }
    /*  Resets the measure */
    public void reset() {
        startTime = lastTime = System.currentTimeMillis();
        totalCount =0;
        count= 0;
        fps=0;fpsSinceStart=0;
    }
}
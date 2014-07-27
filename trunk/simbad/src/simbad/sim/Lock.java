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
 * $Revision: 1.1 $
 * $Source: /cvsroot/simbad/src/simbad/sim/Lock.java,v $
 */
package simbad.sim;

/**
 * A Simple lock for mutual exclusion.
 */
public class Lock  {
    boolean locked = false;;
    
    
    Lock(){    }
 
    /** Obtain the lock. Only one thread at each time.*/ 
    public synchronized void lock(){
        while(locked){
            try {
                wait();
            } catch (InterruptedException e) {             
            }
            
        }
        locked = true;
    }
    /** Release the lock.*/
    public synchronized void unlock(){
        locked = false;
        notifyAll();
    }
}

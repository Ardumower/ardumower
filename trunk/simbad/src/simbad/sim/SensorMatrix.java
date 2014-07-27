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
 * $Date: 2005/01/13 15:21:24 $
 * $Revision: 1.4 $
 * $Source: /cvsroot/simbad/src/simbad/sim/SensorMatrix.java,v $
 */
package simbad.sim;

/**
 * A luminance Matrix : a 2d array of normalized luminances. It can be obtained
 * from a vision sensor (Eye).
 */
public class SensorMatrix extends SensorData{

    private float array[];
    public int width;
    public int height;

    public SensorMatrix(int width, int height) {
        this.width = width;
        this.height = height;
        array = new float[width * height];
    }

    public SensorMatrix(SensorMatrix lm) {
        this.width = lm.width;
        this.height = lm.height;
        this.array = (float[]) lm.array.clone();
    }

    /** Return the matrix height in pixels. */
    public int getHeight(){ return height;}
    /** Return the matrix width in pixels. */
    public int getWidth(){return width;}
    /** Access matrix element. */
    public float get(int x, int y) {
        return array[x + y * width];
    }

    /**
     * Access matrix element.
     * 
     * @param xf x coord in range 0..1
     * @param yf y coord in range 0..1
     * @return
     */
    public float get(float xf, float yf) {
        return array[(int) (xf * width) + (int) (yf * height) * width];
    }

    public float[] getArray() {
        return array;
    }
    
    public Object clone(){
        return new SensorMatrix(this);
    }
   
}
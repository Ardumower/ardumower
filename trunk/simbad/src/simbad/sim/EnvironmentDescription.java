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
 * $Date: 2005/04/25 17:54:59 $
 * $Revision: 1.12 $
 * $Source: /cvsroot/simbad/src/simbad/sim/EnvironmentDescription.java,v $
 */
package simbad.sim;

import javax.vecmath.Color3f;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;
import java.util.ArrayList;
/**
 * This class is intend to describe easily a the world and its components.
 * It is only used during the building process of the World and the Simulator.
 * The user may specific  colors and rendering attributes and add object which should be settled 
 * in the World (Arch,Box, Wall ..) 
 * It also adds the agent(s) which should be simulated.
 * 
 * @author Louis Hugues
 */
public class EnvironmentDescription {
    
    
    ArrayList objects;
    
    public Color3f white, black, red, green, blue, ligthgray, gray, darkgray;
    // configurable values
    public Color3f ambientLightColor;
    public boolean light1IsOn;
    public Color3f light1Color;
    public Vector3d light1Position;
    public Color3f light2Color;
    public boolean light2IsOn;
    public Vector3d light2Position;
    public Color3f wallColor;
    public Color3f archColor;
    public Color3f boxColor;
    public Color3f floorColor;
    public Color3f backgroundColor;
    public int worldViewPoint;
    public boolean hasAxis;
    public int normalsStyle;
    public final static int NORMALS_SIMPLE = 1;
    public final static int NORMALS_REALISTIC = 2;
    /** if true the simulator uses physical laws. */
    public boolean usePhysics;

    /** The size of the square containing the world */
    public  float worldSize;
    
    

    public EnvironmentDescription() {
        worldSize = 20;
        objects = new ArrayList();
        white = new Color3f(1, 1, 1);
        black = new Color3f(0, 0, 0);
        green = new Color3f(0, 1, 0);
        red = new Color3f(1, 0, 0);
        blue = new Color3f(0, 0, 1);
        ligthgray = new Color3f(0.8f, 0.8f, 0.8f);
        gray = new Color3f(0.8f, 0.8f, 0.8f);
        darkgray = new Color3f(0.2f, 0.2f, 0.2f);
        light1Position =new Vector3d(0,worldSize/4,worldSize);
        light2Position = new Vector3d(worldSize,worldSize/4,0);
        defaultSettings();
    }

    void defaultSettings() {
        light1IsOn = true;
        light2IsOn = false;
        ambientLightColor = white;
        light1Color = white;
        light2Color = white;
        wallColor = blue;
        archColor = green;
        boxColor = red;
        floorColor = ligthgray;
        backgroundColor = ligthgray;
        hasAxis = true;
        normalsStyle = NORMALS_SIMPLE;
        worldViewPoint = World.VIEW_FROM_EAST;
        usePhysics = false;
        

    }
    
    /** Add a object (Agent or BlockWorldObject). */
    public void add(Object object){

        objects.add(object);
    }
    
   public void light1SetPosition(double x,double y,double z){
       light1Position.set(x,y,z);
   }
   public void light2SetPosition(double x,double y,double z){
       light2Position.set(x,y,z);
   }
   
   /** Use physics in simulation. */
   public void setUsePhysics(boolean use){
       usePhysics = use;
   }
   
   /** Shows or hide the X,Y and Z axis.*/
   public void showAxis(boolean show){
       hasAxis = show;
   }

   /** Sets the size of the world.
    * 
    * @param size in meters.
    */ 
   public void setWorldSize(float size){ worldSize = size;}
   

   public void addMap(String[] map){
 
       int sx = map[0].length();
       int sy = map.length;
       int cx = sx/2;
       int cy= sy/2;
       for(int y =0; y < sy;y++){
       for(int x =0; x < map[y].length();x++){
           if (map[y].charAt(x)=='#'){
               add(new Box(new Vector3d(x-cx,0,y-cy),new Vector3f(1,1,1),this));
           }
       } }   
      
   }
}
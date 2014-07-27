/* author: Louis Hugues - created on 13 janv. 2005  *//*
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
 * $Revision: 1.2 $
 * $Source: /cvsroot/simbad/src/simbad/sim/LampActuator.java,v $
 */
package simbad.sim;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import javax.media.j3d.Appearance;
import javax.media.j3d.Material;
import javax.media.j3d.Node;
import javax.swing.JPanel;
import javax.vecmath.Color3f;

/**
 * A lamp which can be turn on or off or blink.
 */
public class LampActuator extends ActuatorDevice {

    private Material material;
    private boolean lampIsOn;
    private boolean blinkIsOn;
    private boolean blink;
    private Color3f onColor;
    private Color3f offColor;
    private Color3f blinkColor;
    private boolean changed;

    /**
     * Constructs a LampActuator of the given size.
     * @param size in meter
     */
    public LampActuator(float size) {
        changed = blink = false;
        create3D(size);
    }

    protected void update() {
        if (changed || blinkIsOn) {
            if (blinkIsOn && blink){
                material.setDiffuseColor(blinkColor);
                material.setAmbientColor(blinkColor);
            }
            else if (lampIsOn){
                material.setDiffuseColor(onColor);
                material.setAmbientColor(onColor);
            }
            else {
                material.setDiffuseColor(offColor);
                material.setAmbientColor(offColor);
            }
            if (blinkIsOn) blink = !blink;
            changed = false;
         }
    }

    void create3D(float size) {
        super.create3D(true);
        // lamp body
        onColor = new Color3f(0.1f, 1f, 1f);
        offColor = new Color3f(0.3f, 0.3f, 0.3f);
        blinkColor = new Color3f(1f, 0.3f, 0.3f);
        Appearance appear = new Appearance();
        material = new Material();
        material.setAmbientColor(offColor);
        material.setDiffuseColor(offColor);
        material.setCapability(Material.ALLOW_COMPONENT_WRITE);
        material.setSpecularColor(offColor);
        material.setColorTarget(Material.DIFFUSE);
        appear.setMaterial(material);
        Node node = new com.sun.j3d.utils.geometry.Cylinder(size, size, appear);
        node.setCollidable(false);
        node.setPickable(false);
        addChild(node);
    }

    /** Sets the lamp state on or off.
     * @param on true is on.
     */
    public void setOn(boolean on) {
        lampIsOn = on;
        changed = true;
    }
    /** 
     * Returns the lamp state .
     * @return  true if  on.
     */
    public boolean getOn() {
        return lampIsOn;
    }


    /** Sets the lamp blink state on or off.
     * @param on true is on.
     */public void setBlink(boolean blink) {
        blinkIsOn = blink;
        changed = true;
    }

    /** 
     * Returns the lamp blink state .
     * @return  true if  on.
     */
    public boolean getBlink() {
        return blinkIsOn;
    }
    
    public JPanel createInspectorPanel(){
        return new LampActuatorJPanel();
    }
    /*
     * a JPanel for displaying the lamp state . 
     */
     public class LampActuatorJPanel extends JPanel{
 
		private static final long serialVersionUID = 1L;
		Color color;
         Font font;
         final static int HEIGHT=12;
         public LampActuatorJPanel(){
             color = new Color(0,0,0);
             Dimension d= new Dimension(50,HEIGHT);
            setPreferredSize(d);
            setMinimumSize(d);
            font = new Font("Arial",Font.PLAIN,HEIGHT-2);
            
        }
         protected void paintComponent( Graphics g){
            super.paintComponent(g);
            g.setFont(font);
            g.drawString("on :"+lampIsOn + " - blink : "+blinkIsOn,HEIGHT+10,HEIGHT-1);
    	        
        }       
    }
    
}
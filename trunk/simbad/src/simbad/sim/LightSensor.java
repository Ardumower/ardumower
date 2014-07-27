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
 * $Date: 2005/08/07 12:24:57 $
 * $Revision: 1.3 $
 * $Source: /cvsroot/simbad/src/simbad/sim/LightSensor.java,v $
 */
package simbad.sim;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.text.DecimalFormat;
import javax.swing.JPanel;


/**
 * This class models a single light sensor. The sensor outputs a float proportionnal to received light.
 * <br>
 * Implementation Note: <br>
 * We use a small camera to implement the light sensor. The camera must look back at the sensor body 
 * so as to measured the light received.
 */
public class LightSensor extends Eye {

    float luminance;

    public LightSensor() {
       super(0.5f, 10, 10);
       // super(0.5f, 50, 50);
         luminance = 0;
         rotateY(Math.PI);
    }

    /** Returns the measured luminance. 
     * @return 0.0 means no light , 1.0 f maximum enlightment*/
    public float getAverageLuminance() {
        return luminance;
    }
    
    void create3D(float radius) {
        // small body
        super.create3D(0.05f);
    }

    /** Called by simulator  */
    protected void update() {
        super.update();
        visionImage.getRGB(0, 0, imageWidth, imageHeight, tempRGBABuffer, 0,
                imageWidth);
        float sum = 0;
        int n = tempRGBABuffer.length;
        for (int i = 0; i < n; i++) {
            int pix = tempRGBABuffer[i];
            int r = (pix >> 16) & 0xff;
            int g = (pix >> 8) & 0xff;
            int b = (pix) & 0xff;
            sum += ((float)r*0.299f + 0.587f *(float)g + 0.114f*(float)b) /  255.0f;
        }
        luminance = sum/ (float) n;
    }
    
    public JPanel createInspectorPanel(){
        return new LigthSensorJPanel();
    }
    /*
     * a JPanel for displaying the eye image. 
     */
     public class LigthSensorJPanel extends JPanel{

		private static final long serialVersionUID = 1L;
		Color color;
         Font font;
         DecimalFormat format; 
         final static int HEIGHT=12;
         public LigthSensorJPanel(){
             color = new Color(0,0,0);
             Dimension d= new Dimension(50,HEIGHT);
            setPreferredSize(d);
            setMinimumSize(d);
            font = new Font("Arial",Font.PLAIN,HEIGHT-2);
            // display format for numbers
            format = new DecimalFormat();
            format.setMaximumFractionDigits(2);
            format.setMinimumFractionDigits(2);
            format.setPositivePrefix("");
            format.setMinimumIntegerDigits(1);
            
        }
         /* should not be called too often */
         protected void paintComponent( Graphics g){
            super.paintComponent(g);
            g.setFont(font);
            color = new Color(luminance,luminance,luminance);
            g.setColor(color);
            g.fillRect(0,0,HEIGHT,HEIGHT);
            g.setColor(Color.BLACK);
            g.drawString("luminance="+format.format(luminance),HEIGHT+10,HEIGHT-1);
    	        
        }       
    }
}
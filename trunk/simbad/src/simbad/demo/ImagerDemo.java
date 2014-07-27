/*
 * Simbad - Robot Simulator Copyright (C) 2004 Louis Hugues
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * -----------------------------------------------------------------------------
 * $Author: sioulseuguh $ 
 * $Date: 2005/03/17 17:55:54 $
 * $Revision: 1.6 $
 * $Source: /cvsroot/simbad/src/simbad/demo/ImagerDemo.java,v $
 */
package simbad.demo;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;
import simbad.sim.*;
import javax.swing.JPanel;
import javax.swing.JInternalFrame;

/**
 * An image processing demo. This demo shows how to capture the camera image ,
 * process it and display it in a dedicated window.
 *  
 */
public class ImagerDemo extends Demo {

    class DemoRobotImager extends Agent {
        double elapsed;

        CameraSensor camera;

        SensorMatrix luminanceMatrix;

        JPanel panel;

        JInternalFrame window;

        class ImagerPanel extends JPanel {

			private static final long serialVersionUID = 1L;

			protected void paintComponent(Graphics g) {
                int width = luminanceMatrix.getWidth();
                int height = luminanceMatrix.getHeight();
                super.paintComponent(g);
                g.setColor(Color.WHITE);
                g.fillRect(0, 0, width, height);
                g.setColor(Color.BLACK);
                for (int y = 0; y < height; y += 4) {
                    for (int x = 0; x < width; x += 4) {
                        float level = luminanceMatrix.get(x, y);
                        if (level < 0.5) {
                            g.fillRect(x, y, 4, 4);
                        }
                    }
                }

            }
        }

        public DemoRobotImager(Vector3d position, String name) {
            super(position, name);
            camera = RobotFactory.addCameraSensor(this);
            // prepare a buffer for storing gray level image
            luminanceMatrix = camera.createCompatibleSensorMatrix();
            // Prepare UI panel for image display
            panel = new ImagerPanel();
            Dimension dim = new Dimension(luminanceMatrix.getWidth(),
                    luminanceMatrix.getHeight());
            panel.setPreferredSize(dim);
            panel.setMinimumSize(dim);
            setUIPanel(panel);
        }

        /** Initialize Agent's Behavior */
        public void initBehavior() {
            elapsed = getLifeTime();

        }

        /** Perform one step of Agent's Behavior */
        public void performBehavior() {

            // progress at 0.5 m/s
            setTranslationalVelocity(0.5);
            // frequently change orientation
            if ((getCounter() % 100) == 0)
                setRotationalVelocity(Math.PI / 2 * (0.5 - Math.random()));

            // display every second a binarized representation of camera image.
            if ((getLifeTime() - elapsed) > 1) {
                elapsed = getLifeTime();
                camera.copyVisionImage(luminanceMatrix);
                panel.repaint();
            }
            if (collisionDetected()) moveToStartPosition();
        }
    }

    public ImagerDemo() {
        Wall w1 = new Wall(new Vector3d(9, 0, 0), 19, 1, this);
        w1.rotate90(1);
        add(w1);
        Wall w2 = new Wall(new Vector3d(-9, 0, 0), 19, 2, this);
        w2.rotate90(1);
        add(w2);
        Wall w3 = new Wall(new Vector3d(0, 0, 9), 19, 1, this);
        add(w3);
        Wall w4 = new Wall(new Vector3d(0, 0, -9), 19, 2, this);
        add(w4);
        Box b1 = new Box(new Vector3d(-3, 0, -3), new Vector3f(1, 1, 2), this);
        add(b1);
        Arch a1 = new Arch(new Vector3d(3, 0, -3), this);
        add(a1);
        add(new DemoRobotImager(new Vector3d(0, 0, 0), "DemoRobot"));
    }
}
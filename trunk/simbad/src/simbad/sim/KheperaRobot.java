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
 * $Revision: 1.3 $
 * $Source: /cvsroot/simbad/src/simbad/sim/KheperaRobot.java,v $
 */

package simbad.sim;

import javax.media.j3d.Appearance;
import javax.media.j3d.BoundingSphere;
import javax.media.j3d.Bounds;
import javax.media.j3d.GeometryArray;
import javax.media.j3d.Material;
import javax.media.j3d.Node;
import javax.media.j3d.Shape3D;
import javax.media.j3d.TriangleArray;
import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;
import com.sun.j3d.utils.geometry.Cylinder;
import com.sun.j3d.utils.geometry.Primitive;

/**
 * A KheperaRobot Agents. This class provides a prebuild khepera robot with the
 * following functionalities:
 * <li>8 IR sensors</li>
 * <li>Two wheels control</li>
 * Note the numbering and angle in degrees of the IR sensors:
 * 0 ->+85
 * 1 -> +45
 * 2 -> +10
 * 3 -> -10
 * 4 -> -45
 * 5 ->-85
 * 6 et 7 ->180
 * 
 *  
 */
public class KheperaRobot extends Agent {

    RangeSensorBelt IRBelt;

    /**
     * Constructs a new KheperaRobot .
     * 
     * @param pos
     *            start position.
     * @param name
     */
    public KheperaRobot(Vector3d pos, String name) {
        super(pos, name);
        
        // dimensions
        this.height = 0.03f;
        this.radius = 0.055f / 2f;
        this.mass = 0.07f;
        // sensors
        addIRSensors();
        // two wheels control.
        setKinematicModel(new DifferentialKinematic(getRadius()));
    }

    /**
     * Adds the standard set of IR Sensors.
     *  
     */
    private void addIRSensors() {
        double pi = Math.PI;
        double range = 0.05;
        // Angular position of each sensor
        double anglesPos[] = { pi / 2 - pi / 8, // 0
                pi / 4, // 1
                pi / 4 - pi / 6, // 2 front
                pi / 4 - pi / 3, // 3 front
                -pi / 4, // 4
                -pi / 2 + pi / 8, // 5
                pi + pi / 8, // 6 back
                pi - pi / 8 // 7 back
        };
        // Orientation of each sensor ray.
        double anglesDirs[] = { pi / 2, // 0
                pi / 4, // 1
                0, // 2 front
                0, // 3 front
                -pi / 4, // 4
                -pi / 2, // 5
                pi, // 6 back
                pi // 7 back
        };
        Vector3d pos[] = new Vector3d[8];
        Vector3d dirs[] = new Vector3d[8];
        // construct positions : relative to belt center
        // and direction : relative to sensor pos.
        for (int i = 0; i < pos.length; i++) {
            double a1 = anglesPos[i];
            double a2 = anglesDirs[i];
            // Bug corrected : due to z axis inversion must negate sinus 
            pos[i] = new Vector3d(Math.cos(a1) * radius, 0, -Math.sin(a1)
                    * radius);
            dirs[i] = new Vector3d(Math.cos(a2) * range, 0, -Math.sin(a2)
                    * range);
        }
        int flags = RangeSensorBelt.FLAG_SHOW_FULL_SENSOR_RAY;
        IRBelt = new RangeSensorBelt(pos, dirs, RangeSensorBelt.TYPE_IR, flags);
        IRBelt.setUpdatePerSecond(3);
        IRBelt.setName("IR");
        Vector3d position = new Vector3d(0, 0, 0.0);
        addSensorDevice(IRBelt, position, 0);
    }

    /** Create 3D geometry. */
    protected void create3D() {
        Color3f color = new Color3f(0.3f, 0.8f, 0.8f);
        Color3f color2 = new Color3f(1.0f, 0.0f, 0.0f);
        // body
        Appearance appear = new Appearance();
        Material mat = new Material();
        mat.setDiffuseColor(color);
        appear.setMaterial(mat);
        int flags = Primitive.GEOMETRY_NOT_SHARED
                | Primitive.ENABLE_GEOMETRY_PICKING
                | Primitive.GENERATE_NORMALS;
        flags |= Primitive.ENABLE_APPEARANCE_MODIFY;
        body = new Cylinder(radius, height, flags, appear);
        // we must be able to change the pick flag of the agent
        body.setCapability(Node.ALLOW_PICKABLE_READ);
        body.setCapability(Node.ALLOW_PICKABLE_WRITE);
        body.setPickable(true);
        body.setCollidable(true);
        addChild(body);
        // direction indicator
        float coords[] = { radius / 2, height, -radius / 2,//
                radius / 2, height, radius / 2,//
                radius, height, 0 //
        };
        float normals[] = { 0, 1, 0, 0, 1, 0, 0, 1, 0 };
        TriangleArray tris = new TriangleArray(coords.length,
                GeometryArray.COORDINATES | GeometryArray.NORMALS);
        tris.setCoordinates(0, coords);
        tris.setNormals(0, normals);
        appear = new Appearance();
        appear.setMaterial(new Material(color2, black, color2, white, 100.0f));
        Shape3D s = new Shape3D(tris, appear);
        s.setPickable(false);
        addChild(s);
        
        // Add bounds for interactions and collision
	    Bounds bounds = new BoundingSphere(new Point3d(0,0,0),radius);
	    setBounds(bounds);
    }

    /**
     * Returns the set of IR sensor.
     * 
     * @return a RangeSensorBelt.
     */
    public RangeSensorBelt getIRSensors() {
        return IRBelt;
    }

    /**
     * Sets the wheels velocity.
     * 
     * @param left
     *            wheel velocity in m/s.
     * @param right
     *            wheel velocity in m/s.
     */
    public void setWheelsVelocity(double left, double right) {
        ((DifferentialKinematic) kinematicModel).setWheelsVelocity(left, right);
    }
}

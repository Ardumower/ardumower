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
 * $Date: 2005/02/05 11:00:26 $
 * $Revision: 1.1 $
 * $Source: /cvsroot/simbad/src/simbad/sim/MouseOrbiter.java,v $
 */package simbad.sim;

import java.awt.event.MouseEvent;
import javax.swing.event.MouseInputListener;
import javax.media.j3d.TransformGroup;
import javax.media.j3d.Transform3D;
import javax.vecmath.Vector3d;
import javax.vecmath.Point3d;
import javax.vecmath.Matrix3d;
/** Manages changes of the view point  view under the control of mouse movement.
 * The mouse enables to modify lattitude and longitude of the viewpoint.
 * This class is largely inspired from Sun's OrbitBehavior. 
 * It is intented to be used only with the main Canvas3d object (see World class).
*
 */
public class MouseOrbiter implements MouseInputListener {

    private Transform3D longditudeTransform = new Transform3D();
    private Transform3D latitudeTransform = new Transform3D();
    private Transform3D rotateTransform = new Transform3D();
    // needed for integrateTransforms but don't want to new every time
    private Transform3D temp1 = new Transform3D();
    private Transform3D temp2 = new Transform3D();
    private Transform3D translation = new Transform3D();
    private Vector3d transVector = new Vector3d();
    private Vector3d distanceVector = new Vector3d();
    private Vector3d centerVector = new Vector3d();
    private Vector3d invertCenterVector = new Vector3d();
    private double longditude = 0.0;
    private double latitude = 0.0;
    private double rollAngle = 0.0;
    private double startDistanceFromCenter = 20.0;
    private double distanceFromCenter = 20.0;
    private final double MAX_MOUSE_ANGLE = Math.toRadians(3);
    private final double ZOOM_FACTOR = 1.0;
    private Point3d rotationCenter = new Point3d();
    private Matrix3d rotMatrix = new Matrix3d();
    private Transform3D currentXfm = new Transform3D();
    private int mouseX = 0;
    private int mouseY = 0;
    private double rotXFactor = 1;
    private double rotYFactor = 1;
    private double transXFactor = 1;
    private double transYFactor = 1;
    private double zoomFactor = 1.0;
    private double xtrans = 0.0;
    private double ytrans = 0.0;
    private double ztrans = 0.0;
    private boolean zoomEnabled = true;
    private boolean rotateEnabled = true;
    private boolean translateEnabled = true;
    private boolean reverseRotate = true;
    private boolean reverseTrans = true;
    private boolean reverseZoom = true;
    private double minRadius = 0.0;
    private static final double NOMINAL_ZOOM_FACTOR = .01;
    private static final double NOMINAL_PZOOM_FACTOR = 1.0;
    private static final double NOMINAL_ROT_FACTOR = .01;
    private static final double NOMINAL_TRANS_FACTOR = .01;
    private double rotXMul = NOMINAL_ROT_FACTOR * rotXFactor;
    private double rotYMul = NOMINAL_ROT_FACTOR * rotYFactor;
    private double transXMul = NOMINAL_TRANS_FACTOR * transXFactor;
    private double transYMul = NOMINAL_TRANS_FACTOR * transYFactor;
    private double zoomMul = NOMINAL_ZOOM_FACTOR * zoomFactor;
    private boolean motion = false;
    TransformGroup targetTG;
    Transform3D targetTransform;

    /**
     * Creates a new OrbitBehavior
     * 
     * @param c
     *            The Canvas3D to add the behavior to
     * @param targetTransformGroup
     *            The transformgroup affected by mouse movement 
     */
    public MouseOrbiter(javax.media.j3d.Canvas3D c, TransformGroup targetTransformGroup) {
        c.addMouseListener(this);
        c.addMouseMotionListener(this);
        this.targetTG = targetTransformGroup;
        targetTransform = new Transform3D();
        resetView();
        integrateTransforms();
    }

    protected void processMouseEvent(final MouseEvent evt) {
        if (evt.getID() == MouseEvent.MOUSE_PRESSED) {
            mouseX = evt.getX();
            mouseY = evt.getY();
            motion = true;
        } else if (evt.getID() == MouseEvent.MOUSE_DRAGGED) {
            int xchange = evt.getX() - mouseX;
            int ychange = evt.getY() - mouseY;
            // rotate
            if (!evt.isAltDown() && !evt.isMetaDown()) {
                if (reverseRotate) {
                    longditude -= xchange * rotXMul;
                    latitude -= ychange * rotYMul;
                } else {
                    longditude += xchange * rotXMul;
                    latitude += ychange * rotYMul;
                }
            }
            // translate
            else if (!evt.isAltDown() && evt.isMetaDown()) {
                if (reverseTrans) {
                    xtrans -= xchange * transXMul;
                    ytrans += ychange * transYMul;
                } else {
                    xtrans += xchange * transXMul;
                    ytrans -= ychange * transYMul;
                }
            }
            // zoom
            else if (evt.isAltDown() && !evt.isMetaDown()) {
                        if (reverseZoom) {
                            distanceFromCenter -= ychange * zoomMul;
                        } else {
                            distanceFromCenter += ychange * zoomMul;
                        }
                    
               
            }
            mouseX = evt.getX();
            mouseY = evt.getY();
            motion = true;
        } 
        integrateTransforms();
        

    }

    /**
     * Reset the orientation and distance of this behavior to the current values
     * in target Transform Group
     */
    public void resetView() {
        //Vector3d centerToView = new Vector3d();
        Vector3d centerToView = new Vector3d(0,0,0);
        
        targetTG.getTransform(targetTransform);
        targetTransform.get(rotMatrix, transVector);
        centerToView.sub(transVector, rotationCenter);
        distanceFromCenter = centerToView.length();
        startDistanceFromCenter = distanceFromCenter;
        targetTransform.get(rotMatrix);
        rotateTransform.set(rotMatrix);
        // compute the initial x/y/z offset
        temp1.set(centerToView);
        rotateTransform.invert();
        rotateTransform.mul(temp1);
        rotateTransform.get(centerToView);
        xtrans = centerToView.x;
        ytrans = centerToView.y;
        ztrans = centerToView.z;
        // reset rotMatrix
        rotateTransform.set(rotMatrix);
    }

    protected synchronized void integrateTransforms() {
        // Check if the transform has been changed by another
        // behavior
        targetTG.getTransform(currentXfm);
        if (!targetTransform.equals(currentXfm)) resetView();
        longditudeTransform.rotY(longditude);
        latitudeTransform.rotX(latitude);
        rotateTransform.mul(rotateTransform, latitudeTransform);
        rotateTransform.mul(rotateTransform, longditudeTransform);
        distanceVector.z = distanceFromCenter - startDistanceFromCenter;
        temp1.set(distanceVector);
        temp1.mul(rotateTransform, temp1);
        // want to look at rotationCenter
        transVector.x = rotationCenter.x + xtrans;
        transVector.y = rotationCenter.y + ytrans;
        transVector.z = rotationCenter.z + ztrans;
        translation.set(transVector);
        targetTransform.mul(temp1, translation);
        // handle rotationCenter
        temp1.set(centerVector);
        temp1.mul(targetTransform);
        invertCenterVector.x = -centerVector.x;
        invertCenterVector.y = -centerVector.y;
        invertCenterVector.z = -centerVector.z;
        temp2.set(invertCenterVector);
        targetTransform.mul(temp1, temp2);
        targetTG.setTransform(targetTransform);
        // reset yaw and pitch angles
        longditude = 0.0;
        latitude = 0.0;
    }

    /**
     * Sets the center around which the View rotates. The default is (0,0,0).
     * 
     * @param center
     *            The Point3d to set the center of rotation to
     */
    public synchronized void setRotationCenter(Point3d center) {
        rotationCenter.x = center.x;
        rotationCenter.y = center.y;
        rotationCenter.z = center.z;
        centerVector.set(rotationCenter);
    }

    public void mouseClicked(MouseEvent arg0) {}

    public void mousePressed(MouseEvent event) {
        processMouseEvent(event);
    }

    public void mouseReleased(MouseEvent event) {
        processMouseEvent(event);
    }

    public void mouseEntered(MouseEvent arg0) {}

    public void mouseExited(MouseEvent arg0) {}

    public void mouseDragged(MouseEvent event) {
        processMouseEvent(event);
    }

    public void mouseMoved(MouseEvent event) {
        processMouseEvent(event);
    }
}
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
 * $Date: 2005/08/07 12:24:57 $
 * $Revision: 1.3 $
 * $Source: /cvsroot/simbad/src/simbad/sim/PhysicalEngine.java,v $
 */
package simbad.sim;

import java.util.ArrayList;

import javax.media.j3d.BoundingBox;
import javax.media.j3d.BoundingSphere;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

/**
 * Centralize resources and algorithms related to physical interactions.
 * Most of this is experimental for the time being.
 */
public class PhysicalEngine {

    /** gravitational acceleration constant in m/s**2 */
    protected final static float g= 9.8f;
    
    double epsilonContact = 0.00001;
 
    // temp 3d resources
    private BoundingSphere bs1;
    private BoundingSphere bs2;
    private Vector3d v1;
    private Vector3d v2;
    private Vector3d v3;
    private Vector3d v4;
    private Vector3d v5;
       private Point3d p1;
    private Point3d p2;
    private Point3d p3;

    PhysicalEngine() {
        // Allocate some permanent resources to avoid gc.
        p1 = new Point3d();
        p2 = new Point3d();
        p3 = new Point3d();
        v1 = new Vector3d();
        v2 = new Vector3d();
        v3 = new Vector3d();
        v4 = new Vector3d();
        v5 = new Vector3d();
        bs1 = new BoundingSphere();
        bs2 = new BoundingSphere();

    }

    
    /**
     * Compute all external force contributions on an agent before any impact.
     * 
     * @param dt
     *            virtual time elapsed since last call.
     */
    protected void computeForces(double dt, SimpleAgent a) {
        // Gravity
        // apply F = mg  pointing down .
        if ( a.distanceToGround() > 0 ){
            
            v1.set(0,-a.mass*g,0);
        	a.linearAcceleration.add(v1);
        }
        
        // Friction 
        // apply friction reaction if velocity>0
        if ((a.staticFrictionCoefficient > 0)
                && (a.linearVelocity.lengthSquared() > 0)) {
            // Friction reaction is fx|N| - with N = mg
            float reaction = a.mass * g * a.staticFrictionCoefficient;
            // It is colinear to Velocity vector and in opposite direction.
            // Obtain a unit vector oriented like velocity.
            v1.set(a.linearVelocity);
            v1.normalize(); 
            // scale it to reaction
            v1.scale(reaction );
            a.linearAcceleration.sub(v1);
        }

    }
    /**
     * Check all agents/agent  pairs and verify physical interactions and/or collision. 
     * 
     * Complexity is O(n^2).
     */
    protected void checkAgentAgentPairs(double dt,ArrayList agents, boolean computeImpact,boolean checkCollision) {

        int nagents = agents.size();
        // At least two agents
        if (nagents >= 2) {
            // Check bounds of each couple of agent.
            for (int i = 0; i < nagents - 1; i++) {
                SimpleAgent a1 = ((SimpleAgent) agents.get(i));
                if (a1.detachedFromSceneGraph) continue;
                a1.interactionDetected = false;
                // because there are no other transform above
                // translation
                // we can use it directly and not localToVWorld
                // But this works only on non oriented bounds (spheres).
                // a1.group.getLocalToVworld(tempt3d);
                bs1.set(a1.getBounds());
                bs1.setRadius(bs1.getRadius());
                // bs1.transform(tempt3d);
                bs1.transform(a1.translation);
                // add predicted displacement
                bs1.getCenter(p1);
                p1.add(a1.instantTranslation);
                bs1.setCenter(p1);
                if (checkCollision){
                    a1.collisionDetected = false;
                    a1.clearVeryNear();
                }
                
                for (int j = i + 1; j < nagents; j++) {
                    SimpleAgent a2 = ((SimpleAgent) agents.get(j));
                    if (a2.detachedFromSceneGraph) continue;
                    // at least one of them has moved.
                    if ((a1.positionChanged) || (a2.positionChanged)) {

                        a2.interactionDetected = false;

                        //a2.group.getLocalToVworld(temp2t3d);
                        bs2.set(a2.getBounds());
                        //bs2.transform(temp2t3d);
                        bs2.transform(a2.translation);
                        //   add predicted displacement
                        bs2.getCenter(p1);
                        p1.add(a2.instantTranslation);
                        bs2.setCenter(p1);
                        if (checkCollision) {  
                            a2.collisionDetected = false;
                            a2.clearVeryNear();
                        }

                        if (bs1.intersect(bs2)) {

                            a1.veryNear(a2);
                            a2.veryNear(a1);
                            // Processs collision Indication
                            if (checkCollision) {
                                // collision indicator. 
                                // If one of them can be traversed there is no collision.
                                if (!((a1.canBeTraversed)|| (a2.canBeTraversed))){
                                a1.collisionDetected = true;
                                a2.collisionDetected = true;
                                }
	                            
                            }
                            // Process collision impact.
                            if (computeImpact){
	                            computeAgentAgentImpact(a1, a2, bs1, bs2);
	                            
	                            a1.interactionDetected = true;
	                            a2.interactionDetected = true;
                            }
                        }

                    }

                }
            }
        }
    }

    /**
     * Check all agents/static objetc  pairs and verify physical interactions and/or collision. 
     */
    protected void checkAgentObjectPairs(ArrayList agents,
            ArrayList objects, boolean computeInteraction,boolean checkCollision) {

        int nobjs = objects.size();
        int nagents = agents.size();
        // At least two agents
        for (int i = 0; i < nagents; i++) {
            SimpleAgent a1 = ((SimpleAgent) agents.get(i));
          
            // because there are no other transform above
            // translation
            // we can use it directly and not localToVWorld
            // But this works only on non oriented bounds (spheres).
           if (checkCollision) 
               a1.collisionDetected = false;
            bs1.set(a1.getBounds());
            bs1.transform(a1.translation);
            // add predicted displacement
            bs1.getCenter(p1);
            p1.add(a1.instantTranslation);
            bs1.setCenter(p1);

            // Check each agent / objects couple (once)
            for (int j = 0; j < nobjs; j++) {
                Object o = objects.get(j);
                if (o instanceof StaticObject) {
                    if (intersect(bs1, (StaticObject) o))
                    {
                        if (checkCollision) 
                            a1.collisionDetected = true;
                        
                        if (computeInteraction){
                            computeAgentObjectImpact(a1,(StaticObject)o,bs1);
                        }
                    }
                }
            }
        }

    }

    /** experimental */
    private void computeAgentAgentImpact(SimpleAgent a1, SimpleAgent a2,
            BoundingSphere bs1, BoundingSphere bs2) {
        Vector3d n = v1;
        Vector3d vrel = v2;
        double coefficientOfRestitution = 1.0; // coefficient of restitution
        bs1.getCenter(p1);
        bs2.getCenter(p2);

        // compute normal of a2 surface (simple 2 spheres case)
        p3.sub(p1, p2);
        n.set(p3);
        n.normalize();

        // relative velocity
        vrel.sub(a1.linearVelocity, a2.linearVelocity);
        double ndotvrel = n.dot(vrel);

        if (ndotvrel <= 0) {
            // Compute impulse magnitude in the normal direction
            // j = (-(1+epsilon)vrel.n ) / (n.n (1/a1_mass + 1/a2_mass))
            double num = -(1 + coefficientOfRestitution) * n.dot(vrel);

            double denum = 1 / a1.mass + 1 / a2.mass;
            double j = num / denum;

            // update a1 velocity
            // Va1 = Va1 + (j/a1_mass) (n)
            v2.set(n);
            v2.scale(j / (a1.mass));
            a1.linearVelocity.add(v2);
            // update a2 velocity
            // Va1 = Va1 - (j/a2_mass)(n)
            v2.set(n);
            v2.scale(j / (a2.mass));
            a2.linearVelocity.sub(v2);
        }
    }
    
    /** experimental */
    private void computeAgentObjectImpact(SimpleAgent a, StaticObject o,
            BoundingSphere bsa ) {
        Vector3d n = v5;
        double coefficientOfRestitution = 1.0; 
 
        //  Compute normalized normal and contact point 	
        computeContactNormal(bsa,(BoundingBox)o.getBounds(),n);
        
          // velocity component in normal direction 
        double ndotva = n.dot(a.linearVelocity);
       // System.out.println("ndotva " + ndotva );
        if (ndotva <= 0) {
            // Compute impulse magnitude in the normal direction
            // j = (-(1+epsilon)vrel.n ) / (n.n (1/a_mass + 1/o_mass))
            // And  Va = Va + (j/a_mass)(n)
            // but o_mass is infinite  and o is static
            // and a_mass can be canceled thus:
            // j = (-(1+epsilon)avel.n ) 
            // And  Va = Va + jn
            double j = -(1 + coefficientOfRestitution ) * ndotva ;
            
            v2.set(n);
            v2.scale(j);
            a.linearVelocity.add(v2);
           // System.out.println("add " + v2.toString() +" normal "+n.toString());

        }

    }

    protected boolean intersect(BoundingSphere bs, StaticObject obj) {

        return obj.intersect(bs);
    }

    /** */
    protected boolean intersect(BoundingSphere bs, BoundingBox bb) {
        return (bb.intersect(bs));

        /*
         * double radiussq = bs.getRadius()*bs.getRadius(); bb.getLower(p1);
         * bb.getUpper(p2); bs.getCenter(p3); double xmin = Math.min(p1.x,p2.x);
         * double ymin = Math.min(p1.y,p2.y); double zmin = Math.min(p1.z,p2.z);
         * double xmax = Math.max(p1.x,p2.x); double ymax = Math.max(p1.y,p2.y);
         * double zmax = Math.max(p1.z,p2.z);
         * 
         * double dmin = 0; if (p3.x < xmin) dmin += (p3.x - xmin)*(p3.x -
         * xmin); else if (p3.x >xmax ) dmin += (p3.x - xmax)*(p3.x - xmax);
         * 
         * if (p3.y < ymin) dmin += (p3.y - ymin)*(p3.y - ymin); else if (p3.y
         * >ymax ) dmin += (p3.y - ymax)*(p3.y - ymax);
         * 
         * if (p3.z < zmin) dmin += (p3.z - zmin)*(p3.z - zmin); else if (p3.z
         * >zmax ) dmin += (p3.z - zmax)*(p3.z - zmax);
         * 
         * return ( dmin <= radiussq );
         */

    }
    
    
    protected void computeContactNormal(BoundingSphere bs, BoundingBox bb,Vector3d n){
        
         // NEEDS :  BB is Axis Aligned  !!!!!
        
          bb.getLower(p1);
          bb.getUpper(p2); 
          bs.getCenter(p3); 
          // pour chaque face
          // normal de la face 
          // projete centre sphere sur normale 
          // retourne normale ayant longueur proejectio + petite
       
          //double sqradius = bs.getRadius() * bs.getRadius();
          double p;
          double min = Double.MAX_VALUE;
          // six faces
          p = projNormal(p1.x,p1.y,p1.z, p1.x,p2.y,p1.z, p2.x,p1.y,p1.z);
         if (p  <  min) { min = p; n.set(v3);}
          p = projNormal(p2.x,p1.y,p1.z ,p2.x,p2.y,p1.z, p2.x,p1.y,p2.z);
          if (p  <  min) { min = p; n.set(v3);}
         /* p = projNormal(p2.x,p1.y,p2.z, p2.x,p2.y,p2.z, p1.x,p1.y,p2.z);
          if (p  <  min) { min = p; n.set(v3);}*/
         /* p = projNormal(p1.x,p1.y,p2.z, p1.x,p2.y,p2.z, p1.x,p1.y,p1.z);
          if (p  <  min) { min = p; n.set(v3);}*/
        /* p = projNormal(p1.x,p2.y,p1.z, p1.x,p2.y,p2.z, p2.x,p2.y,p1.z);
          if (p  <  min) { min = p; n.set(v3);}
          p = projNormal(p1.x,p1.y,p2.z, p1.x,p1.y,p1.z, p2.x,p1.y,p2.z);
          if (p  <  min) { min = p; n.set(v3);} */
        
    }
    protected double projNormal(double x1,double y1,double z1,double x2,double y2,double z2,double x3,double y3,double z3)
    {
        // Normal =  (P2 - P1) ^ (P3 -P1)   = V3  
        v1.set(x1,y1,z1);
        v2.set(x2,y2,z2);
        v3.set(x3,y3,z3);
        v2.sub(v1);v3.sub(v1);
        v4.sub(p3,v1);
        v3.cross(v2,v3);
        
        v3.normalize(); 
        
        return Math.abs(v3.dot(v4));
    }    
        

    
    
}
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
 * $Revision: 1.13 $
 * $Source: /cvsroot/simbad/src/simbad/sim/RangeSensorBelt.java,v $
 * 21/02/2005 measurrment init value is Double.POSITIVE_INFINITY.
 * 
 * History:
 * Modif. LH 01-oct-2006 : correct getLeftQuadrantMeasurement.
 */
package simbad.sim;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import javax.media.j3d.Appearance;
import java.awt.Font;
import java.text.DecimalFormat;
import javax.media.j3d.ColoringAttributes;
import javax.media.j3d.GeometryArray;
import javax.media.j3d.LineArray;
import javax.media.j3d.Material;
import javax.media.j3d.Node;
import javax.media.j3d.PickCylinderRay;
import javax.media.j3d.PickSegment;
import javax.media.j3d.SceneGraphPath;
import javax.media.j3d.Shape3D;
import javax.media.j3d.Transform3D;
import javax.swing.JPanel;
import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;




/**
 * This class models a circular belt of range sensors : Sonar , Bumpers (future : Laser, Ir).
 * Sensors are arranged circularly around the robot. User can access to the measurement and hits state of each sensor individualy
 * or obtain an average measurement in a quadrant. 
 * <br><br>
 * Note that the sensors are not affected by noise. however you can easily add some gaussian noise with the java.util.Random class.
 * <br><code> Random generator = new Random(seed); </code>
 * <br>and<br>
 * <code> value = sonars.getMeasurement(0)+generator.nextGaussian()*stddev;</code>
 * <br> <br><br>
 * Implementation notes :
 * We use java 3D picking feature to emulate sensing. 
 * A PickCylinderRay is used on each update to test whether there is an potential obstacle.
 * Each ray is then checked  with a PickSegement.
 */
public class RangeSensorBelt extends PickSensor {
 
    private int type;
    private float maxRange;
    private float radius;
    private int nbSensors;
    /** for storing results */
    private double measurements[];
    private boolean hits[];
    private boolean oneHasHit;
    /** angular position (deduced from positions infos) */
    private double angles[];
    /*** position of each sensor relative to center */
    private Vector3d positions[];
    /** direction vector of each sensor - relative to sensor position. */
    private Vector3d directions[];
    
    
    private Transform3D t3d;
  //  private Transform3D t3d_2;
    private Point3d start;
    private Point3d end;
    private Color3f color;
    /** for picking */
    private PickCylinderRay pickCylinder;
    private PickSegment pickSegment;
    private Point3d cylinderStart;
    private float cylinderRadius;
    private Vector3d cylinderDirection;

    private int flags;
    // constants
    public final static int TYPE_SONAR=0;
    public final static int TYPE_IR=1;
    public final static int TYPE_LASER=2;
    public final static int TYPE_BUMPER=3;
    
    
    // FLAGS
    public final static int FLAG_SHOW_FULL_SENSOR_RAY=0X01;
    
     /**
     * Constructs a RangeSensorBelt.
     * The sensor type can be either TYPE_BUMPER,TYPE_SONAR,TYPE_IR or TYPE_LASER.
     * Ranges are measured from the belt perimeter (not from the belt center).
     * @param radius - the radius of the belt.
     * @param minRange - the minimal range of each sensor ray. Not used for TYPE_BUMPER.
     * @param maxRange - the maximal range of each sensor ray. Not used for TYPE_BUMPER.
     * @param nbsensors - the number of sensors in the belt (typically 4,6,12,24 or 36).
     * @param type - to specify  the sensor behavior 
     */
    public RangeSensorBelt(float radius, float minRange, float maxRange,
            int nbsensors, int type,int flags) {
        // compute angles ,positions , directions
        positions = new Vector3d[nbsensors];
        directions = new Vector3d[nbsensors];
        Vector3d frontPos = new Vector3d(radius, 0, 0);
        Vector3d frontDir = new Vector3d(maxRange, 0, 0);
        angles = new double[nbsensors];
        Transform3D transform = new Transform3D();
        for (int i = 0; i < nbsensors; i++) {
            angles[i] = i * 2 * Math.PI / (double) nbsensors;
            transform.setIdentity();
            transform.rotY(angles[i]);
            Vector3d pos = new Vector3d(frontPos);
            transform.transform(pos);
            positions[i] = pos;
            Vector3d dir = new Vector3d(frontDir);
            transform.transform(dir);
            directions[i] = dir;
         }
        initialize(radius, maxRange, nbsensors, type,flags);
    }
    
    
    
    /**
    * Constructs a RangeSensorBelt.
    * The sensor type can be either TYPE_BUMPER,TYPE_SONAR,TYPE_IR or TYPE_LASER. 
    * @param positions : the position of each sensor relative to belt center.
    * @param directions : the sensing ray direction of each sensor relative to sensor positions.
    * the magnitude of the vector corresponds to the max range.
    */
 public RangeSensorBelt(Vector3d []positions,Vector3d[] directions,int type,int flags){
 
        int nbsensors = positions.length;
        
        // compute angles
        float radius = Float.MIN_VALUE;
        float maxRange = Float.MIN_VALUE;
        Vector3d frontVector = new Vector3d(1,0,0); 
        angles = new double[nbsensors];
               for (int i=0;i< nbsensors;i++){
            Vector3d v = positions[i];
             angles[i] = v.angle(frontVector);
             double norm = v.length();
             // find the max radius
             if (norm> radius) radius = (float)norm;
             double range = directions[i].length();
             if (range > maxRange) maxRange = (float)range;
             
        }
        this.directions = directions;
        this.positions = positions;
        
        initialize(radius,maxRange,nbsensors,type,flags);
  
    }
    
    private void initialize(float radius, float maxRange,int nbsensors,int type,int flags){
        this.flags = flags;
        this.nbSensors = nbsensors;
        this.maxRange = maxRange;
        this.radius = radius;
        this.type = type;
        // reserve to avoid gc.
        t3d = new Transform3D();
        //t3d_2 = new Transform3D();
        pickSegment = new PickSegment();
        pickCylinder= new PickCylinderRay();
        cylinderDirection = new Vector3d(0.0,0.5,0.0);
        cylinderRadius = maxRange+radius;
        cylinderStart = new Point3d(0f,0f,0.f);
        start = new Point3d();
        end = new Point3d();
              
        if (type == TYPE_BUMPER) 
            color = new Color3f(1.0f, 0f, 0f);
        else
        color = new Color3f(1.0f, 0.5f, 0.25f);
        
        measurements = new double[nbsensors];
        hits = new boolean[nbsensors];
        for (int i=0;i< nbsensors;i++){
            measurements[i]= Double.POSITIVE_INFINITY;
            hits[i] = false;
        }
        oneHasHit =false;
        create3D();

    }
    private void create3D() {
        super.create3D(true);
        // construct sensor body - a line for each individual sensor ray.
        Point3d[] coords = new Point3d[nbSensors*2];
        for (int i=0;i< nbSensors;i++){
            Point3d start =  new Point3d(positions[i]); 
            coords[i*2]=start;
            Point3d end = new Point3d(start);
            Point3d direction  =  new Point3d(directions[i]);
            if (((flags & FLAG_SHOW_FULL_SENSOR_RAY) ==0) && (type != TYPE_BUMPER))
                direction.scale(0.05f); // just a small ray
            end.add(direction);
            coords[i*2+1]=end;
                      
        }
        LineArray line = new LineArray(
            coords.length,
            GeometryArray.COORDINATES );
        line.setCoordinates( 0, coords );

        Appearance appear = new Appearance();
        Material material = new Material();

        ColoringAttributes ca = new ColoringAttributes();
		ca.setColor(color);
		
		appear.setColoringAttributes(ca);
        appear.setMaterial(material);
        Shape3D shape = new Shape3D( line, appear );
        shape.setCollidable(false);
        shape.setPickable(false);
        addChild(shape);
       
    }  
    protected void update() {
        oneHasHit = false;
        for (int s=0;s<nbSensors;s++) {
            hits[s]= false;
            measurements[s] = Double.POSITIVE_INFINITY;
        }
        //update the pickShape with current position
        // TODO factor this getLocalToVWorld 
        group.getLocalToVworld(t3d);
        cylinderStart.set(0.0f,0.0f,0.f);
        cylinderDirection.set(0.0,0.5,0.0);
        
        // set a pickCylinder around the belt 
        t3d.transform(cylinderStart);
        t3d.transform(cylinderDirection);
        pickCylinder.set(cylinderStart,cylinderDirection,cylinderRadius); 
        
        // pick possibly intersecting shapes
        // rem: pickAllSorted costs too much
        SceneGraphPath[] picked = pickableSceneBranch.pickAll(pickCylinder);
        boolean intersect= false;
        double minDist;
        double[] dist = new double[1];
        if (picked != null){
          
            // now check each sensor ray
            for (int s=0;s<nbSensors;s++)
            {
                start.set(positions[s]);
                end.set(start);
                end.add(directions[s]);
                
                	t3d.transform(start);
                t3d.transform(end);
                
                pickSegment.set(start,end);
                // find the nearest
                minDist = Double.MAX_VALUE;
                intersect=false;
                // Pick again but on the segment
               
                picked = pickableSceneBranch.pickAll(pickSegment);
                if (picked != null) {
                    // for all picked objects
                    for (int i = 0; i < picked.length; i++) {
                        Node obj = picked[i].getObject();
                        if (obj instanceof Shape3D) {
                            if (((Shape3D) obj).intersect(picked[i],
                                    pickSegment, dist)) {
                                if  (dist[0] < minDist){
                                    minDist = dist[0];
                                    intersect = true;
                                }
                            }
                        }
                    }
                }
                hits[s] =intersect;
                oneHasHit |= intersect; 
                if (intersect){
                    
                    measurements[s]= minDist;
                    //System.out.println ("Sensor "+s+"="+(minDist));
                }
           }
        }
        
    }

 
    /**
     * Returns the last measure collected for the individual sensor. Measurement is made from the circle perimeter.
     * @param sensorNum num of the sensor.
     * @return the range measurment.
      */
    public double getMeasurement(int sensorNum){
       return measurements[sensorNum];
   }

    /**
     * Returns the averaged measure of the sensors situated in the front quadrant: [-PI/4,PI/4].
     * @return the averaged measurment.
      */
    public double getFrontQuadrantMeasurement() {
        return (getQuadrantMeasurement(0, Math.PI / 4) + getQuadrantMeasurement(
                7*Math.PI / 4, Math.PI * 2)) / 2.0;
    }
    /**
     * Returns the averaged measure of the sensors situated in the front left quadrant: [0,PI/4].
     * @return the averaged measurment.
      */
    public double getFrontLeftQuadrantMeasurement() {
        return getQuadrantMeasurement(0, Math.PI / 2); 
    }
    /**
     * Returns the averaged measure of the sensors situated in the front right quadrant: [3PI/2,2*PI].
     * @return the averaged measurment.
      */
    public double getFrontRightQuadrantMeasurement() {
        return getQuadrantMeasurement(3*Math.PI/2.0, 2*Math.PI); 
    }
    /**
     * Returns the averaged measure of the sensors situated in the left quadrant: [PI/4,PI*3/4].
     * @return the averaged measurment.
      */
    public double getLeftQuadrantMeasurement() {
        return getQuadrantMeasurement(Math.PI / 4,3*Math.PI/4); 
    }
   
    /**
     * Returns the averaged measure of the sensors situated in the bacck left quadrant: [PI/2,PI].
     * @return the averaged measurment.
      */
    public double  getBackLeftQuadrantMeasurement() {
        return getQuadrantMeasurement(Math.PI / 2,Math.PI); 
    }
    
    /**
     * Returns the averaged measure of the sensors situated in the back quadrant: [3PI/4,4*PI/4].
     * @return the averaged measurment.
      */
   public double getBackQuadrantMeasurement() {
        return getQuadrantMeasurement(3*Math.PI / 4,5*Math.PI/4); 
    }
   /**
    * Returns the averaged measure of the sensors situated in the back right quadrant: [PI,3*PI/2].
    * @return the averaged measurment.
     */
   public double getBackRightQuadrantMeasurement() {
       return getQuadrantMeasurement(Math.PI ,3*Math.PI/2); 
   }
   /**
    * Returns the averaged measure of the sensors situated in the right quadrant: [5*PI/4,7*PI/4].
    * @return the averaged measurment.
     */public double getRightQuadrantMeasurement() {
       return getQuadrantMeasurement(5*Math.PI/4 ,7*Math.PI/4); 
   }
    /**
     * Returns the averaged measure of the sensors situated in quadrant [minAngle,maxAngle].
     * @param minAngle in radians the right limit of the quadrant.
     * @param maxAngle in radians the left limit of the quadrant.
     * @return the averaged measurment.
      */
    public double getQuadrantMeasurement(double minAngle,double maxAngle){
        double sum=0.0,n=0;
        for (int i=0;i< nbSensors;i++){
            if ((angles[i]>= minAngle) &&(angles[i]<= maxAngle)) {
                if (hits[i]){
                    n += 1.0 ;
                   sum += measurements[i];
                }
            }
        } 
        if (n==0)return Double.POSITIVE_INFINITY;
        else return sum/n;
   }
 
    /**
     * Returns number of sensor hits in the front quadrant: [-PI/4,PI/4].
     * @return the number of hits.
      */
    public int getFrontQuadrantHits() {
        return (getQuadrantHits(0, Math.PI / 4) + getQuadrantHits(
                7*Math.PI / 4, Math.PI * 2)) ;
    }
    /**
     * Returns  number of sensor hits in the front left quadrant: [0,PI/4].
     * @return the  number of hits.
      */
    public int getFrontLeftQuadrantHits() {
        return getQuadrantHits(0, Math.PI / 2); 
    }
    /**
     * Returns  number of sensor hits in the front right quadrant: [3PI/2,2*PI].
     * @return the  number of hits.
      */
    public int getFrontRightQuadrantHits() {
        return getQuadrantHits(3*Math.PI/2.0, 2*Math.PI); 
    }
    /**
     * Returns  number of sensor hits in the left quadrant: [PI/4,PI*3/4].
     * @return the  number of hits.
      */
    public int getLeftQuadrantHits() {
        return getQuadrantHits(Math.PI / 4,3*Math.PI/4); 
    }
    /**
     * Returns  number of sensor hits in the back left quadrant: [PI/2,PI].
     * @return the  number of hits.
      */
    public int  getBackLeftQuadrantHits() {
        return getQuadrantHits(Math.PI / 2,Math.PI); 
    }
    /**
     * Returns  number of sensor hits in the back  quadrant: [3PI/4,5PI/4].
     * @return the  number of hits.
      */
    public int getBackQuadrantHits() {
        return getQuadrantHits(3*Math.PI / 4,5*Math.PI/4); 
    }
    /**
     * Returns  number of sensor hits in the back right quadrant: [PI,3PI/2].
     * @return the  number of hits.
      */
    public int getBackRightQuadrantHits() {
        return getQuadrantHits(Math.PI ,3*Math.PI/2); 
    }
    /**
     * Returns  number of sensor hits in the right quadrant: [5PI/4,7PI/4].
     * @return the  number of hits.
      */
    public int getRightQuadrantHits() {
        return getQuadrantHits(5*Math.PI/4 ,7*Math.PI/4); 
    }
    /**
     * Returns number of hits  in quadrant [minAngle,maxAngle].
     * @param minAngle in radians the right limit of the quadrant.
     * @param maxAngle in radians the left limit of the quadrant.
     * @return the  number of hits.
      */
    public int getQuadrantHits(double minAngle,double maxAngle){
        int n=0;
        for (int i=0;i< nbSensors;i++){
            if ((angles[i]>= minAngle) &&(angles[i]<= maxAngle)) {
                if (hits[i]) n++;
            }
        } 
        return n;
   }
    /**
     * Returns the hit state of the sensor.
	 * @param sensorNum num of the sensor.
	 * @return true if the sensor ray has hit an obstacle 
	 */
    public boolean hasHit(int sensorNum){
       return hits[sensorNum];
   }
    /**
     * Returns true if one of the sensors has hit.
	 * @return true if one  ray has hit an obstacle 
	 */
    public boolean oneHasHit(){
       return oneHasHit;
   }
   /**
    * Return the number of individual sensor in the belt.
    * @return the number of sensors.
    */
   public int getNumSensors(){ return nbSensors;}

   /**
    * Returns the angle of this sensor.
    * @param sensorNum - num of the sensor.
   * @return the angle in radians.
   */
   public double getSensorAngle(int sensorNum){
       return angles[sensorNum];
   }

   /**
    * Returns the maximum sensing range in meters. 
    * @return the maximum range.
   */
   public float getMaxRange(){ return maxRange;}
   
   public JPanel createInspectorPanel(){
       return new RangeSensorBeltJPanel();
   }

 
   /**
    * A JPanel Inner class for displaying the sensor belt rays in 2d. 
    */
    private class RangeSensorBeltJPanel extends JPanel{
   
    		private static final long serialVersionUID = 1L;
		Font font;
        int lineSize=8;
        DecimalFormat format; 
        final static int IMAGE_SIZEX = 200;
        final static int IMAGE_SIZEY = 100;
           public RangeSensorBeltJPanel(){
            Dimension d= new Dimension(IMAGE_SIZEX,IMAGE_SIZEY);
           setPreferredSize(d);
           setMinimumSize(d);
           font = new Font("Arial",Font.PLAIN,lineSize-1);
           // display format for numbers
           format = new DecimalFormat();
           format.setMaximumFractionDigits(3);
           format.setMinimumFractionDigits(2);
           format.setPositivePrefix("");
           format.setMinimumIntegerDigits(1);
       }
        /** Caution not synchronised */
           
       protected void paintComponent( Graphics g){
           super.paintComponent(g);
           g.setFont(font);
         //  Color c;
           g.setColor(Color.LIGHT_GRAY);
           g.fillRect(0,0,IMAGE_SIZEX,IMAGE_SIZEY);
           g.setColor(Color.GRAY);
           int x =IMAGE_SIZEX/2;int y =0;
           for (int i=0;i< nbSensors;i++){
                y += lineSize;
                if (y > IMAGE_SIZEY){
                    y = lineSize; x+= 50;
                }
               if(type == TYPE_BUMPER)
                   g.drawString("["+i+"] "+hits[i],x,y);
               else
                   g.drawString("["+i+"] "+format.format(measurements[i]),x,y);
           }     	
           int cx,cy;
           cx=cy=IMAGE_SIZEX/4;
           // display factor
           float f = (float)cx/(float)(maxRange+radius);
           int r = (int)(radius*f);
           g.setColor(Color.BLUE);
           g.drawOval(cx-r,cy-r,2*r,2*r);
           g.drawLine(cx,cy,cx+r,cy);
           // draw each ray
            for (int i=0;i< nbSensors;i++){
              
                int x1=	(int)(positions[i].x *f);
                int y1= (int)(positions[i].z *f);
                if( type == TYPE_BUMPER){
                    g.setColor(Color.BLUE);	
                    g.drawRect(cx+x1-1,cy+y1-1,2,2);
                }   
                g.setColor(Color.RED);
                if (hits[i]){
                   double ratio =  measurements[i]/directions[i].length();
                   
                    int x2=	x1 +(int)(directions[i].x *ratio*f);
                    int y2= y1+(int)(directions[i].z *ratio*f);
                   if( type == TYPE_BUMPER){
                       g.fillOval(cx+x1-1,cy+y1-1,3,3);
                   }else
                   g.drawLine( cx+x1, cy+y1,cx+x2,cy+y2);
               }
           }
       }       
   }
}

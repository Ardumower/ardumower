package simbad.sim;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Polygon;
import java.awt.geom.PathIterator;
import java.awt.geom.Point2D;
import java.util.ArrayList;

import javax.media.j3d.Appearance;
import javax.media.j3d.ColoringAttributes;
import javax.media.j3d.Material;
import javax.media.j3d.Transform3D;
import javax.swing.JPanel;
import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3f;

import com.sun.j3d.utils.geometry.Sphere;


public class PerimeterSensor extends SensorDevice {
        
   final static int VALUECOUNT=200;
   //double isInside[] = new double[VALUECOUNT];   
   double magnitude[] = new double[VALUECOUNT];   

   Color3f color = new Color3f(1.0f, 0f, 0f);
   JPanel panel;  
   Polygon perimeterPolgyon;      
   Point pt = new Point(0,0);
   Point3d coord = new Point3d();
   
   public  PerimeterSensor(){
        create3D(true);
        
        //KeyboardFocusManager kfm = KeyboardFocusManager.getCurrentKeyboardFocusManager();
        //Component comp = kfm.getPermanentFocusOwner();
        //comp.addKeyListener(this);
   }
   
   @Override
	public void create3D(boolean allowTransformReadWrite) {
		super.create3D(allowTransformReadWrite);
		
		Appearance appear = new Appearance();
        Material material = new Material();

        ColoringAttributes ca = new ColoringAttributes();
		ca.setColor(color);
		
		appear.setColoringAttributes(ca);
        appear.setMaterial(material);
        //Shape3D shape = new Shape3D( line, appear );
        Sphere shape = new Sphere(0.1f, appear);		
		shape.setCollidable(false);
        shape.setPickable(false);
        addChild(shape);
	}
   
   // called by simulator to inform about perimeter shape
   public void setPolgyon(Polygon perimeter){
	   this.perimeterPolgyon = perimeter;
   }
   
   public JPanel createInspectorPanel(){
       panel = new PerimeterSensorJPanel();
       return panel;
   }
    /*
     * a JPanel for displaying the eye image. 
     */
     public class PerimeterSensorJPanel extends JPanel {

		private static final long serialVersionUID = 1L;
		Font font;
         Color color;
         final static int HEIGHT=60;
         public PerimeterSensorJPanel(){
             color = new Color(0,0,0);
             Dimension d= new Dimension(50,HEIGHT);
            setPreferredSize(d);
            setMinimumSize(d);
            font = new Font("Arial",Font.PLAIN,HEIGHT-2);
        }

         protected void paintComponent( Graphics g){
             super.paintComponent(g);
             //g.setFont(font);             
             int h = HEIGHT;
             double lastY1 = h/2;
             double lastY2 = h + h/2;
             //double lastY3 = 2*h + h/2;
             Color c1 = new Color(255,0,0);
             Color c2 = new Color(0,200,0);
             //Color c3 = new Color(0,0,255);            
             for (int i=1; i < VALUECOUNT; i++){
             	double y1 = magnitude[i] * 3.0 + h/2;
             	//double y2 = magnitude[i] + h + h/2;
             	//double y3 = (comYaw[i] / Math.PI) * 15.0 + 2*h + h/2;
             	g.setColor(c1);
             	g.drawLine(i-1, (int)lastY1, i, (int)y1);
             	//g.setColor(c2);
             	//g.drawLine(i-1, (int)lastY2, i, (int)y2);
             	//g.setColor(c3);
             	//g.drawLine(i-1, (int)lastY3, i, (int)y3);            	
             	lastY1 = y1;
             	//lastY2 = y2;
             	//lastY3 = y3;
             }
             g.drawString("inside :"+ isInside() +  "  mag:" + getMagnitude() ,HEIGHT+10,HEIGHT-1);                                       
        }     
           
    }
          
     /**
      * The distance between two points squared
      * @param v the first point
      * @param w the second point
      * @return the distance between v and w squared
      */
     static double dist2( Point2D v, Point2D w ) 
     { 
         double xDiff = v.getX() - w.getX();
         double yDiff = v.getY() - w.getY();
         return xDiff*xDiff + yDiff*yDiff;
     }
     /**
      * Distance from a point to a line-segment squared
      * @param p the point
      * @param v the 1st point of the segment
      * @param w the 2nd point of the segment
      * @return the distance as a float
      */
     static double distToSegmentSquared( Point2D p, Point2D v, Point2D w) 
     {
         double l2 = dist2(v, w);
         if (l2 == 0.0f) 
             return dist2(p, v);
         double t = ((p.getX()-v.getX())*(w.getX()-v.getX())+(p.getY()-v.getY())*(w.getY()-v.getY()))/l2;
         if (t < 0) 
             return dist2(p, v);
         if (t > 1) 
             return dist2(p, w);         
         Point2D q = new Point2D.Double(v.getX()+t*(w.getX()-v.getX()), v.getY() +t*(w.getY()-v.getY()) );
         return dist2( p, q );
     }
     /**
      * Compute the distance from a point to a line segment
      * @param p the point
      * @param v first point of the line
      * @param w second point of the line
      * @return the distance as a float
      */
     public static double distanceToSegment( Point2D p, Point2D v, Point2D w )
     {
         double squared = distToSegmentSquared(p,v,w);
         return (double)Math.sqrt(squared);
     }
     /**
      * Get the minimal separation between two polygons
      * @param P the first polygon
      * @param Q the second polygon
      * @return the smallest distance between segments or vertices of P, Q
      */
     public static double distanceBetween( Polygon P, Polygon Q )
     {
         double minDist = Double.MAX_VALUE;
         ArrayList<Point2D> points1 = polygonToPoints(P);
         ArrayList<Point2D> points2 = polygonToPoints(Q);
         Point2D last1=null,last2=null;
         for ( int i=0;i<points1.size();i++ )
         {
             Point2D p1 = points1.get(i);
             for ( int j=0;j<points2.size();j++ )
             {
                 Point2D p2 = points2.get(j);
                 double x = Math.abs(p1.getX()-p2.getX());
                 double y = Math.abs(p1.getY()-p2.getY());
                 // distance between vertices
                 double dist = Math.hypot(x,y);
                 if ( dist < minDist )
                     minDist = dist;
                 // distance between p1 and a segment of Q
                 if ( last2 != null )
                 {
                     double fDist2 = distanceToSegment( p1, last2, p2 );
                     if ( fDist2 < minDist )
                         minDist = fDist2;
                 }
                 // distance between p2 and a segment of P
                 if ( last1 != null )
                 {
                     double fDist1 = distanceToSegment( p2, last1, p1 );
                     if ( fDist1 < minDist )
                         minDist = fDist1;
                 }
                 last2 = p2;
             }
             last1 = p1;
         } 
         return minDist;
     }
     
     /**
      * Get the minimal separation between polygon and point
      * @param P the polygon
      * @param Q the point
      * @return the smallest distance between segments or vertices of P, Q
      */
     public static double distanceBetween( Polygon P, Point2D Q )
     {
         double minDist = Double.MAX_VALUE;
         ArrayList<Point2D> points1 = polygonToPoints(P);
         //ArrayList<Point> points2 = polygonToPoints(Q);
         Point2D last1=null,last2=null;
         for ( int i=0;i<points1.size();i++ )
         {
             Point2D p1 = points1.get(i);             
             {
                 Point2D p2 = Q;
                 double x = Math.abs(p1.getX()-p2.getX());
                 double y = Math.abs(p1.getY()-p2.getY());
                 // distance between vertices
                 double dist = Math.abs(Math.hypot(x,y));
                 if ( dist < minDist )
                     minDist = dist;
                 // distance between p1 and a segment of Q
                 if ( last2 != null )
                 {
                     double fDist2 = distanceToSegment( p1, last2, p2 );
                     if ( fDist2 < minDist )
                         minDist = fDist2;
                 }
                 // distance between p2 and a segment of P
                 if ( last1 != null )
                 {
                     double fDist1 = distanceToSegment( p2, last1, p1 );
                     if ( fDist1 < minDist )
                         minDist = fDist1;
                 }
                 last2 = p2;
             }
             last1 = p1;
         } 
         /*if (minDist > 5){
        	 System.out.println(Q);
        	 System.out.println(P);
         }*/
         return minDist;
     }
     
     /**
      * Convert a polygon to an array of points
      * @param pg the poly
      * @return an arraylist of type Point
      */
     public static ArrayList<Point2D> polygonToPoints( Polygon pg )
     {
         ArrayList<Point2D> points = new ArrayList<>();
         PathIterator iter = pg.getPathIterator(null);
         float[] coords = new float[6];
         while ( !iter.isDone())
         {
             int step = iter.currentSegment(coords);
             switch ( step )
             {
                 case PathIterator.SEG_CLOSE: case PathIterator.SEG_LINETO:
                     case PathIterator.SEG_MOVETO:
                     points.add( new Point2D.Double(coords[0], coords[1]) );
                     break;
                 default:
                     break;
             }
             iter.next();
         }
         return points;
     }        
     
   @Override
    protected void update() {	   
	   super.update();
	   for (int i=1; i < VALUECOUNT; i++) {		   
		   magnitude[i-1]=magnitude[i];		   		   
	   }
	   
	   
	   // get world position of perimeter sensor
	   Transform3D tr = new Transform3D();
	   Vector3f pos = new Vector3f();
	   group.getLocalToVworld(tr);
	   tr.get(pos);	   
	   
	   // http://www.java3d.org/position.html
	   
	   //getOwner().getCoords(coord);	   	  
	   //pt.x = (int)coord.getX();
	   //pt.y =  (int)coord.getZ();
	   	   
	   Point2D pt = new Point2D.Double(pos.getX(), pos.getZ());
	   double dist = distanceBetween(perimeterPolgyon, pt);
	   double mag = Math.min(10.0, 1.0/dist);	   
	   if (perimeterPolgyon.contains(pt))  mag *= -1; 	   
	   magnitude[VALUECOUNT-1] = mag; 
	   //isInside = ((pt.x > -7) && (pt.x < 7) && (pt.y > -7)  && (pt.y < 7));
    }

    public boolean isInside(){
    	// https://www.java.net/node/691913
    	return (magnitude[VALUECOUNT-1] < 0);
    }
    
    public double getMagnitude(){
    	return magnitude[VALUECOUNT-1];
    }
   
}

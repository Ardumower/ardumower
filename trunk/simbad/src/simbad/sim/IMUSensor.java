package simbad.sim;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.Random;

import javax.media.j3d.Transform3D;
import javax.swing.JPanel;
import javax.vecmath.Point3d;
import javax.vecmath.Quat4d;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;

import simbad.gui.Simbad;


public class IMUSensor extends SensorDevice {
        
   final static int VALUECOUNT=200;
   double accYaw[] = new double[VALUECOUNT];   
   double gyroYaw[] = new double[VALUECOUNT];
   double comYaw[] = new double[VALUECOUNT];
   double velocity = 0;
   JPanel panel;   
   
   public  IMUSensor(){
        super.create3D(true);
        
        //KeyboardFocusManager kfm = KeyboardFocusManager.getCurrentKeyboardFocusManager();
        //Component comp = kfm.getPermanentFocusOwner();
        //comp.addKeyListener(this);
   }
   
   
   public JPanel createInspectorPanel(){
       panel = new IMUSensorJPanel();
       return panel;
   }
    /*
     * a JPanel for displaying the eye image. 
     */
     public class IMUSensorJPanel extends JPanel {

		private static final long serialVersionUID = 1L;
		Font font;
         Color color;
         final static int HEIGHT=90;
         public IMUSensorJPanel(){
             color = new Color(0,0,0);
             Dimension d= new Dimension(50,HEIGHT);
            setPreferredSize(d);
            setMinimumSize(d);
            font = new Font("Arial",Font.PLAIN,HEIGHT-2);
        }
         protected void paintComponent( Graphics g){
            super.paintComponent(g);
            //g.setFont(font);
            int h = HEIGHT / 3;
            double lastY1 = h/2;
            double lastY2 = h + h/2;
            double lastY3 = 2*h + h/2;
            Color c1 = new Color(255,0,0);
            Color c2 = new Color(0,200,0);
            Color c3 = new Color(0,0,255);            
            for (int i=1; i < VALUECOUNT; i++){
            	double y1 = (gyroYaw[i] / Math.PI) * 300 + h/2;
            	double y2 = accYaw[i]*700 + h + h/2;
            	double y3 = (comYaw[i] / Math.PI) * 15.0 + 2*h + h/2;
            	g.setColor(c1);
            	g.drawLine(i-1, (int)lastY1, i, (int)y1);
            	g.setColor(c2);
            	g.drawLine(i-1, (int)lastY2, i, (int)y2);
            	g.setColor(c3);
            	g.drawLine(i-1, (int)lastY3, i, (int)y3);            	
            	lastY1 = y1;
            	lastY2 = y2;
            	lastY3 = y3;
            }
            
            g.drawString( "course :"+ ((comYaw[VALUECOUNT-1]/Math.PI)*180.0), HEIGHT+10,HEIGHT-1);
                
        }     
           
    }
        
     
     private Vector3d getEulerAngles(Quat4d q1)
     {
    	 Vector3d euler = new Vector3d();      
         double sqw = q1.w*q1.w;
         double sqx = q1.x*q1.x;
         double sqy = q1.y*q1.y;
         double sqz = q1.z*q1.z;
         euler.z = Math.atan2(2.0 * (q1.x*q1.y + q1.z*q1.w),  sqx - sqy - sqz + sqw);     // heading
         euler.y = Math.atan2(2.0 * (q1.y*q1.z + q1.x*q1.w), -sqx - sqy + sqz + sqw);    // pitch
         euler.x = Math.asin(-2.0 * (q1.x*q1.z - q1.y*q1.w));                            // roll
         return euler;
     }
       
 	private double getCourse(){
 		Quat4d q1 = new Quat4d();
 		//Matrix3d m = new Matrix3d();
 		//Vector3d t;
 		//rotation.get(m);		
 		getOwner().rotation.get(q1);
 		double x,y,z,w;
 		x=q1.x;
 		y=q1.y;
 		z=q1.z;
 		q1.y=z;
 		q1.z=y;
 		//q1.normalize();
 		double course = getEulerAngles(q1).z;
 		//System.out.println("course=" + m);
 		return course;
 	}
          
     
     
   @Override
    protected void update() {
	   super.update();
	   for (int i=1; i < VALUECOUNT; i++) {
		   gyroYaw[i-1]=gyroYaw[i];
		   accYaw[i-1]=accYaw[i];		   
		   comYaw[i-1]=comYaw[i];
	   }
	   
	  // default kinematic vs. differential drive kinematic
	  // http://simbad.sourceforge.net/guide.php
      	
	  // get instant rotation, translation
	  Vector3d irot = getOwner().instantRotation;
	  Vector3d itransl = getOwner().instantTranslation;	 
	  
	  // get coordinates
	  Point3d coord = new Point3d();
      getOwner().getCoords(coord);
      
      comYaw[VALUECOUNT-1] = getCourse();
      	           
         
      double time = getOwner().getLifeTime();
	  //gyroYaw[VALUECOUNT-1] = Math.sin(time) * 10;
      gyroYaw[VALUECOUNT-1] = irot.getY();
      double acc =  itransl.length() - velocity;
      velocity = itransl.length();
      accYaw[VALUECOUNT-1] = acc;
           
      //gyroYaw[VALUECOUNT-1] = 
	  
    }


    public double getGyroYaw() {
        return gyroYaw[VALUECOUNT-1];
    }
    
   
}

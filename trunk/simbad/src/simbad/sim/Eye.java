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
 * $Revision: 1.7 $
 * $Source: /cvsroot/simbad/src/simbad/sim/Eye.java,v $
 */
package simbad.sim;


import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.GraphicsConfigTemplate;
import java.awt.GraphicsConfiguration;
import java.awt.GraphicsEnvironment;
import java.awt.image.BufferedImage;
import javax.media.j3d.Appearance;
import javax.media.j3d.Canvas3D;
import javax.media.j3d.GraphicsConfigTemplate3D;
import javax.media.j3d.ImageComponent;
import javax.media.j3d.ImageComponent2D;
import javax.media.j3d.Material;
import javax.media.j3d.Node;
import javax.media.j3d.PhysicalBody;
import javax.media.j3d.PhysicalEnvironment;
import javax.media.j3d.View;
import javax.media.j3d.ViewPlatform;
import javax.swing.JPanel;
import javax.vecmath.Color3f;
import javax.media.j3d.RestrictedAccessException;


import com.sun.j3d.utils.geometry.Sphere;

/*
 * A  visual sensor (and its 3d body) used to emulate monoscopic color camera. 
 *  Vision image (offscreen rendered) is accessible via copyVisionImage().
 * 
 * Implementation:
 *  Vision is rendered  offscreen via a j3d viewPlatform.
 * Calling update() method cause update of the associated buffered Image 
 * The Subclass EyeJPanel is used to display image (in AgentInspector)
 * 
 */
public class Eye extends SensorDevice {

    private ViewPlatform viewPlatform;
    private View view;
    private OffScreenCanvas3D offscreenCanvas3D;
    
    protected int tempRGBABuffer[];
    // the rendered offscreen image
    BufferedImage visionImage;
    
    protected int imageWidth ;
    protected int imageHeight;
    

    /*
     * a JPanel for displaying the eye image in user interface windows. 
     */
     public class EyeJPanel extends JPanel{
		private static final long serialVersionUID = 1L;
		BufferedImage bim;
         public EyeJPanel(){
             Dimension d= new Dimension(imageWidth,imageHeight);
            setPreferredSize(d);
            setMinimumSize(d);
            // allocates a bim for capture
            bim  =  new BufferedImage(imageWidth, imageHeight,
                    BufferedImage.TYPE_INT_RGB);
        }
         /* should not be called too often */
         protected void paintComponent( Graphics g){
            super.paintComponent(g);
            copyVisionImage(bim);
            g.drawImage(bim, 0, 0, null);
    	       
        }       
    }
    
    /**
     * An off screen Canvas3D for offscreen rendering of a 3D scene - call render to ask rendering
     */
    private class OffScreenCanvas3D extends Canvas3D {

		private static final long serialVersionUID = 1L;
		boolean rendering;
   
        public OffScreenCanvas3D(GraphicsConfiguration gconfig) {
            super(gconfig, true);
            ImageComponent2D buffer = new ImageComponent2D(
                    ImageComponent.FORMAT_RGB, visionImage);
            buffer.setCapability(ImageComponent2D.ALLOW_IMAGE_READ);
            setOffScreenBuffer(buffer);
            rendering = false;
            
        }

        synchronized void render() {
            
           try{
                renderOffScreenBuffer();
           }catch(RestrictedAccessException e)   
           {
               // rendering is already in process,but  we don't care
              // System.err.println("Exception caught"+e.getMessage() );
           }
           // } 
            //waitForOffScreenRendering();
        }

        synchronized public void postSwap() {
            // copy rendered image 
             BufferedImage bim = getOffScreenBuffer().getImage();
             visionImage.setData(bim.getData());
            rendering = false;
        }
    }

    Eye(float radius,int imageWidth,int imageHeight  ) {
        this.imageWidth = imageWidth;
        this.imageHeight = imageHeight;
       // BufferedImage bim = new BufferedImage(imageWidth, imageHeight,
       //         BufferedImage.TYPE_INT_RGB);
        visionImage = new BufferedImage(imageWidth, imageHeight,
                BufferedImage.TYPE_INT_RGB);
        tempRGBABuffer= new int[imageWidth*imageHeight];
        create3D(radius);
        createViewPlatform();
    }

    void create3D(float radius) {
        super.create3D(true);
        // body
        if (radius > 0) {
            Color3f color = new Color3f(0.8f, 0.8f, 0.0f);
            Appearance appear = new Appearance();
            appear
                    .setMaterial(new Material(color, black, color, white,
                            100.0f));
            Node node = new Sphere(radius, appear);
            node.setCollidable(false);
            node.setPickable(false);
            addChild(node);
        }
    }
    void createViewPlatform(){
        // viewplatform
        viewPlatform = new ViewPlatform();
        viewPlatform.setActivationRadius(100f);
        viewPlatform.setViewAttachPolicy(View.NOMINAL_HEAD);
        // view
        view = new View();
        
        view.setProjectionPolicy(View.PERSPECTIVE_PROJECTION);
        view.setViewPolicy(View.SCREEN_VIEW);
        view.attachViewPlatform(viewPlatform);
        // physical body
        PhysicalBody phyBody = new PhysicalBody();
        view.setPhysicalBody(phyBody);
        // physical environment
        PhysicalEnvironment phyEnv = new PhysicalEnvironment();
        view.setPhysicalEnvironment(phyEnv);
        // ???? pas compris , pour l'antiliasing
        GraphicsConfigTemplate3D template = new GraphicsConfigTemplate3D();
        template.setSceneAntialiasing(GraphicsConfigTemplate.PREFERRED);
        GraphicsConfiguration config = GraphicsEnvironment
                .getLocalGraphicsEnvironment().getDefaultScreenDevice()
                .getBestConfiguration(template);
        // antialiasing
        view.setSceneAntialiasingEnable(true);
        /* to add a onscreen canvas
            canvas3d = new Canvas3D(config);
            view.addCanvas3D(canvas3d);
        */
        // attach  offscreen canvas to the view
        offscreenCanvas3D = new OffScreenCanvas3D(config);
        offscreenCanvas3D.getScreen3D().setSize(imageWidth, imageWidth);
        offscreenCanvas3D.getScreen3D().setPhysicalScreenHeight(0.5);
        offscreenCanvas3D.getScreen3D().setPhysicalScreenWidth(0.5);
        view.addCanvas3D(offscreenCanvas3D);
        addChild(viewPlatform);
        // turn canvas in front of X axis  
        rotateY(-Math.PI/2);
    }

    
     
    /** for allocating a working copy of the vision image */
    final public BufferedImage createCompatibleImage()
    {
        return  new BufferedImage(imageWidth, imageHeight,
                BufferedImage.TYPE_INT_RGB);
    }
    /** for allocating a SensorMatrix compabtible with device dimensions */
    final public SensorMatrix createCompatibleSensorMatrix()
    {
        return  new SensorMatrix(imageWidth, imageHeight);
        
    } 
    
    /**
     * Request to fill a bufferedImage with last capture.
     * @param bim - buffered image to be filled.
     */
    final public synchronized void copyVisionImage(BufferedImage bim){
        bim.setData(visionImage.getData());
    }
    /**
     * Request to fill a SensorMatrix with last capture.
     * @param matrix  - to be filled
     */
    final public synchronized void copyVisionImage(SensorMatrix matrix){
        visionImage.getRGB(0,0,imageWidth,imageHeight,tempRGBABuffer,0,imageWidth);
        float array[] = matrix.getArray();
            for (int i = 0; i < array.length; i++) {
                int pix = tempRGBABuffer[i];
                int r = (pix >> 16) & 0xff;
                int g = (pix >> 8) & 0xff;
                int b = (pix) & 0xff;
                array[i] = (float) (r + g + b) / (3.0f * 255.0f);
            }
       
    }
       
    /** Called by simulator to render a new vision image */
   protected  void update(){
        this.offscreenCanvas3D.render();
    }
    
    public JPanel createInspectorPanel(){
        return new EyeJPanel();
    }

    /**
     * Returns the width of captured image.
     * @return width in pixels
     */
    public int getImageWidth(){
        return imageWidth;
    }
    /**
     * Returns the height of captured image.
     * @return height in pixels
     */
    public int getImageHeight(){
        return imageHeight;
    }
}
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
 * $Date: 2005/08/07 12:25:03 $
 * $Revision: 1.16 $
 * $Source: /cvsroot/simbad/src/simbad/sim/World.java,v $
 */
package simbad.sim;

import java.awt.GraphicsConfigTemplate;
import java.awt.GraphicsConfiguration;
import java.awt.GraphicsEnvironment;
import java.awt.Point;
import java.awt.Polygon;
import java.util.Map;

import javax.media.j3d.*;
import javax.sound.sampled.LineEvent;
import javax.vecmath.*;

import com.sun.j3d.utils.behaviors.interpolators.CubicSplineCurve;
import com.sun.j3d.utils.geometry.Primitive;
import com.sun.j3d.utils.geometry.Sphere;



/**
 * Represents a 3d world - this class use intensively JAVA3D.
 * It creates the scenegraph and the view platform.
 * The building process uses a EnvironmentDescription object containing  colors ,
 *  objects and attributes given by the user.  This class is thighly coupled with Simulator Class.
 * 
 * Remember to call System.setProperty("j3d.implicitAntialiasing", "true") at the 
 * very beginning of your program in order to enable antialiasing. 
 *
 */
public  class World   {

    /** J3D universe */
    VirtualUniverse universe;
    /** The content branch. */
    private BranchGroup sceneBranch;
    /** The base translation of the sceneBranch. */
    private TransformGroup sceneTrans;
    /** The base rotation of the sceneBranch. */
    private TransformGroup sceneRot;

 
    /** All the pickable/collidable objects should be attached under this sub-branch */
    private BranchGroup  pickableSceneBranch;
    /** The view branch */ 
    private BranchGroup viewBranch;
    private TransformGroup viewTransformGroup;
    private ViewPlatform viewPlatform;
    private View view;
    
        
    /** The main canvas for viewing the world. */   
    private Canvas3D canvas3d;
    /** For managing the mouse mouvement in the Canvas3D */
    MouseOrbiter mouseOrbiter;

    // lights 
    private Light light1;
    private Light light2;
    
    // perimeter
    public Shape3D perimeterShape;
    public Polygon perimeterPolgyon;
     
    // constants used to specify the viewpoint
    public static final int VIEW_FROM_TOP=1;
    public static final int VIEW_FROM_EAST=2;
    public static final int VIEW_BEHIND_AGENT=3;
    public static final int VIEW_ABOVE_AGENT=4;
    public static final int VIEW_ABOVE_AGENT_NEAR=5;
    public static final int VIEW_AGENT_SIDE=6;
          

    /** The size of the square containing the world */
    protected  float worldSize;

    /** Prepared colors. */
    Color3f white = new Color3f(1,1,1);
    Color3f black = new Color3f(0,0,0);
    Color3f green = new Color3f(0,1,0);
    
    /** Construct a World from a given  EnvironmentDescription. */
    public World(EnvironmentDescription ed) {
        create(ed);
    }

    /** Creates the world from the given environement Description. 
     * Used only in the creation phase.
     * @param ed the environment description.
     */
    private void create(EnvironmentDescription ed) {
        worldSize = ed.worldSize;
        createUniverse(ed);
   
    }
    
   
    /** Creates the universe to attach the scenegraph. 
     * Used only in the creation phase.
     * @param ed the environment description.
     */
    private void createUniverse(EnvironmentDescription ed) {
        System.out.println("create Universe");
        // show infos 
        Map map  = VirtualUniverse.getProperties();
        System.out.println("----------------------------------------");
        System.out.println("j3d.version = "+map.get("j3d.version"));
        System.out.println("j3d.vendor = "+map.get("j3d.vendor"));
        System.out.println("j3d.specification.version = "+map.get("j3d.specification.version"));
        System.out.println("j3d.specification.vendor = "+map.get("j3d.specification.vendor"));
        System.out.println("j3d.renderer = "+map.get("j3d.renderer"));
        System.out.println("J3DThreadPriority = "+VirtualUniverse.getJ3DThreadPriority());
        System.out.println("----------------------------------------");

         createCanvas3D();
        createSceneBranch(ed);

        universe = new VirtualUniverse();
           
        Locale locale = new Locale(universe);
 
        // Create and add VIEW branch
        // locale->viewBranch->viewTransformGroup->viewPlatform
        viewBranch = new BranchGroup();
        viewTransformGroup = new TransformGroup();
        viewTransformGroup.setCapability(TransformGroup.ALLOW_TRANSFORM_READ);
        viewTransformGroup.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
        Transform3D t3d =new Transform3D();
        t3d.setIdentity();
        viewTransformGroup.setTransform(t3d);
        viewBranch.addChild(viewTransformGroup);
        
        // Creates View and viewplatform
        viewPlatform = new ViewPlatform();
        viewPlatform.setViewAttachPolicy(View.NOMINAL_HEAD);
        viewPlatform.setActivationRadius(100);
        view = new View();
        view.setProjectionPolicy(View.PERSPECTIVE_PROJECTION);
        
          view.setViewPolicy(View.SCREEN_VIEW);
        view.setVisibilityPolicy(View.VISIBILITY_DRAW_ALL);
        
        view.setFrontClipDistance(0.02);
        
        GraphicsConfigTemplate3D template = new GraphicsConfigTemplate3D();
        template.setSceneAntialiasing(GraphicsConfigTemplate.REQUIRED);
        template.setDoubleBuffer(GraphicsConfigTemplate.PREFERRED);
       /* GraphicsConfiguration config = GraphicsEnvironment
                .getLocalGraphicsEnvironment().getDefaultScreenDevice()
                .getBestConfiguration(template);*/
        // request antialiasing
        view.setSceneAntialiasingEnable(true);
        
 
        view.addCanvas3D(canvas3d);
        PhysicalBody phyBody = new PhysicalBody();
        PhysicalEnvironment phyEnv = new PhysicalEnvironment();
        view.setPhysicalBody(phyBody);
        view.setPhysicalEnvironment(phyEnv);
        view.attachViewPlatform(viewPlatform);
        viewTransformGroup.addChild(viewPlatform);
        
        // Add both branch to the unique locale
        locale.addBranchGraph(viewBranch);
        locale.addBranchGraph(sceneBranch);
      
        
        // Add mouse control in the canvas3d 
        mouseOrbiter = new MouseOrbiter(canvas3d,viewTransformGroup);

        	// sets initial viewpoint
        changeViewPoint(ed.worldViewPoint,null);
    }
    
    /** Creates the Canvas3D to visualize the 3D World. 
     * Used only in the creation phase.
     */
    private void createCanvas3D(){
         GraphicsConfigTemplate3D template = new GraphicsConfigTemplate3D();
        template.setSceneAntialiasing(GraphicsConfigTemplate.PREFERRED);
        GraphicsConfiguration config = GraphicsEnvironment
                .getLocalGraphicsEnvironment().getDefaultScreenDevice()
                .getBestConfiguration(template);
        // create canvas
        canvas3d = new Canvas3D(config);
        canvas3d.setDoubleBufferEnable(true);
        
        // display j3d info
        Map map = canvas3d.queryProperties();
        System.out.println("doubleBufferAvailable = "
                + map.get("doubleBufferAvailable"));
        System.out.println("sceneAntialiasingNumPasses = "
                + map.get("sceneAntialiasingNumPasses"));
        System.out.println("sceneAntialiasingAvailable = "
                + map.get("sceneAntialiasingAvailable"));
        System.out.println("texture3DAvailable = "
                + map.get("texture3DAvailable"));
        
             
    }



    /** Adds a 3D object to the world. 
     * Used only in the creation phase.*/
      public void addObjectToPickableSceneBranch(BaseObject obj3d) {
         obj3d.compile();
         pickableSceneBranch.addChild(obj3d.getNode());
     }
     
      /** Detach a previously attached object from the scenegraph. */
      public void detach(BaseObject obj3d) {
          pickableSceneBranch.removeChild(obj3d.getNode());
      }
      /** attach a 3d object to the scenegraph. */
      public void attach(BaseObject obj3d) {
          pickableSceneBranch.addChild(obj3d.getNode());
      }
      

      // Catmull-Rom spline interpolation function
      // System.out.println(q(t, 5, 10, 20, 10));
      /*private double spline(double t, double p0, double p1, double p2, double p3) {
          return 0.5 * ((2 * p1) + (-p0 + p2) * t
                  + (2 * p0 - 5 * p1 + 4 * p2 - p3) * (t * t) + (-p0 + 3 * p1 - 3
                  * p2 + p3)
                  * (t * t * t));
      }*/

      
      // http://www.itk.ilstu.edu/faculty/javila/ITk356/Java3D/geometry.htm      
    public Shape3D addPerimeter(){
    	Point pts[] = {
    			new Point(-7, -7),
    			new Point(0, -7),
    	        new Point(7, -6),
    	        new Point(6, 0),
    	        new Point(7, 7),    	       
    	        new Point(0, 6),
    	        new Point(-6, 7),    	        
    	        new Point(-7, -7),
    	};    	
    	//Builder builder = Polygon.Builder();
    	perimeterPolgyon = new Polygon();
    	LineStripArray arr = new LineStripArray(pts.length, LineStripArray.COORDINATES, new int[]{pts.length});
    	for (int i=0; i < pts.length; i++){
    		//builder.addVertex(pts[i]);
    		perimeterPolgyon.addPoint(pts[i].x, pts[i].y);
    		arr.setCoordinate(i, new Point3d(pts[i].x, 0.002, pts[i].y));
    	}
    	//perimeterPolgyon = builder.build();    	
    	Appearance pa = new Appearance();
    	LineAttributes la =new LineAttributes();
    	la.setLineWidth(2);
    	PolygonAttributes pla = new PolygonAttributes( PolygonAttributes.POLYGON_LINE, PolygonAttributes.CULL_NONE, 0);    	    	
    	ColoringAttributes ca = new ColoringAttributes();
		ca.setColor(green);		
    	pla.setPolygonMode(PolygonAttributes.POLYGON_LINE);    	
    	pa.setPolygonAttributes(pla);
    	pa.setLineAttributes(la);
    	pa.setColoringAttributes(ca);
    	perimeterShape = new Shape3D(arr, pa);
    	perimeterShape.setCollidable(false);
    	sceneTrans.addChild(perimeterShape);
    	return perimeterShape;
    }

    /** Add a light to the 3d world.   
     * Used only in the creation phase.
     */
    Light addLight(Vector3d pos, Color3f color) {
        BoundingSphere bounds = new BoundingSphere(new Point3d(0.0, 0.0, 0.0),
                worldSize*2);

        TransformGroup tg = new TransformGroup();
        Transform3D t3d = new Transform3D();
        t3d.set(pos);
        tg.setTransform(t3d);
        PointLight light = new PointLight();
        light.setAttenuation(0.5f,0,0);
         // light.setAttenuation(0f,.08f,0);
        // light.setAttenuation(1.2f,0,0);
        // note : light pos not affected by transform (but bound is).
       light.setPosition((float) pos.x, (float) pos.y, (float) pos.z);
       light.setInfluencingBounds(bounds);
        sceneTrans.addChild(light);
        // light geometry
        ColoringAttributes ca = new ColoringAttributes();
        ca.setColor(color);
        Appearance appL1 = new Appearance();
        appL1.setColoringAttributes(ca);
        Primitive s = new Sphere(0.4f, appL1);
        s.setCollidable(true);
        tg.addChild(s);
        sceneTrans.addChild(tg);
        return light;
    }
    
    /** Creates the branch for the visible content of the scenegraph.  
     * Used only in the creation phase.
     */
    private  void createSceneBranch(EnvironmentDescription wd) {
  
   
        sceneBranch = new BranchGroup();
        sceneRot = new TransformGroup();
        sceneRot.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
        sceneRot.setCapability(TransformGroup.ALLOW_TRANSFORM_READ);
        sceneRot.setCapability(TransformGroup.ALLOW_CHILDREN_EXTEND);
        // add transform 
        sceneTrans = new TransformGroup();
        // allow  transform access
        sceneTrans.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
        sceneTrans.setCapability(TransformGroup.ALLOW_TRANSFORM_READ);
        sceneTrans.setCapability(TransformGroup.ALLOW_CHILDREN_EXTEND);
        sceneBranch.addChild(sceneRot);
        sceneRot.addChild(sceneTrans);
        
        // bounds (lights,background, behaviors)
        BoundingSphere bounds = new BoundingSphere(new Point3d(0.0, 0.0, 0.0),
                worldSize*3);

        // background
        Color3f bgColor = wd.backgroundColor;
        Background bgNode = new Background(bgColor);
        bgNode.setApplicationBounds(bounds);
        sceneTrans.addChild(bgNode);
        
        // ambient light
        TransformGroup tga = new TransformGroup();
        AmbientLight ambientLight = new AmbientLight(wd.ambientLightColor);
        ambientLight.setInfluencingBounds(bounds);
        tga.addChild(ambientLight);
        sceneBranch.addChild(tga);
        
        // directional lights
        light1 = addLight(wd.light1Position ,wd.light1Color);
        light2 = addLight(wd.light2Position,wd.light2Color);
        light1.setEnable(wd.light1IsOn);
        light2.setEnable(wd.light2IsOn);
        
        // perimeter
        addPerimeter();
        
        createFloor(wd);
        if (wd.hasAxis) createAxis();
        
        pickableSceneBranch = new BranchGroup();
        sceneTrans.addChild(pickableSceneBranch);
        pickableSceneBranch.setCapability(BranchGroup.ALLOW_CHILDREN_EXTEND);
        pickableSceneBranch.setCapability(BranchGroup.ALLOW_DETACH);
        pickableSceneBranch.setCapability(BranchGroup.ALLOW_CHILDREN_WRITE);
        
            
    }

    
    /** Creates the floor of the 3d world.  
     * Used only in the creation phase.
     * @param ed the environment description.
     */
    private void createFloor(EnvironmentDescription wd){

        float minx = -worldSize/2, maxx = worldSize/2;
        float minz = -worldSize/2,maxz = worldSize/2;

 
        Point3f[] floorCoords = {
                new Point3f(  minx, 0.0f,minz),
                new Point3f(  minx, 0.0f,maxz ),
                new Point3f(  maxx, 0.0f,maxz),
                new Point3f(  maxx, 0.0f,minz )
            };
        Vector3f[] floorNormals = {
                new Vector3f(  -0.6f, 0.6f, -0.6f ),
                new Vector3f(  -0.6f, 0.6f, 0.6f ),
                new Vector3f(  0.6f, 0.6f, 0.6f ),
                new Vector3f(  0.6f, 0.6f, -0.6f )
            };
        Vector3f[] floorNormalsSimple = {
                new Vector3f(  0, 1, 0 ),
                new Vector3f(  0, 1, 0 ),
                new Vector3f(  0, 1, 0 ),
                new Vector3f(  0, 1, 0 )
            };
   
  
        QuadArray floorQuads=null;
        switch(wd.normalsStyle){
        	case EnvironmentDescription.NORMALS_REALISTIC:
                floorQuads= new QuadArray(
                        floorCoords.length,
                        GeometryArray.COORDINATES |
                        GeometryArray.NORMALS );
            floorQuads.setNormals( 0, floorNormals );
            break;
          	case EnvironmentDescription.NORMALS_SIMPLE:
                floorQuads= new QuadArray(
                        floorCoords.length,
                        GeometryArray.COORDINATES|GeometryArray.NORMALS );
          		floorQuads.setNormals( 0, floorNormalsSimple );
            break;
            
        
        }
        floorQuads.setCoordinates( 0, floorCoords );
        Appearance floorAppear = new Appearance();
    
        Material mat = new Material();
        mat.setDiffuseColor(wd.floorColor);
        Color3f specular = new Color3f(wd.floorColor);
        specular.scale(1.1f);
        specular.clampMax(0.8f);
        mat.setSpecularColor(specular);
        floorAppear.setMaterial(mat);
        Shape3D floor = new Shape3D( floorQuads, floorAppear );
        floor.setPickable(false);
        floor.setCollidable(false);
        
        sceneTrans.addChild(floor);     
    }

    /** Creates a representation of the 3 axis of the 3d world.  
     * Used only in the creation phase.
     */
    private void createAxis(){
        Point3f[] axisCoords = {
                // X axis arrow
                new Point3f(  0.0f, 0.001f,0.0f),
                new Point3f(  1, 0.001f,0.0f ),
                new Point3f(  1, 0.001f,0.0f ),
                new Point3f(  0.95f, 0.001f,0.05f ),
                new Point3f(  1, 0.001f,0.0f ),
                new Point3f(  0.95f, 0.001f,-0.05f ),
                
                // a small X
                new Point3f(  1.0f, 0.001f,0.1f ),
                new Point3f(  0.9f, 0.001f,0.2f ),
                new Point3f(  1.0f, 0.001f,0.2f ),
                new Point3f(  0.9f, 0.001f,0.1f ),
                // Z axis  arrow
                new Point3f(  0.0f, 0.001f,0.0f),
                new Point3f(  0, 0.001f,1.0f ),
                new Point3f(  0, 0.001f,1.0f ),
                new Point3f(  0.05f, 0.001f,0.95f ),
                new Point3f(  0, 0.001f,1.0f ),
                new Point3f(  -0.05f, 0.001f,0.95f ),
                
                // a small Z
                new Point3f(  0.1f, 0.001f,1.0f ),
                new Point3f(  0.2f, 0.001f,1.0f ),
                new Point3f(  0.1f, 0.001f,0.9f ),
                new Point3f(  0.2f, 0.001f,0.9f ),
                new Point3f(  0.1f, 0.001f,1.0f ),
                new Point3f(  0.2f, 0.001f,0.9f ),
                // Y axis  arrow
                new Point3f(  0.0f, 0.001f,0.0f),
                new Point3f(  0, 1.0f,0.0f ),
                new Point3f(  0, 1.0f,0.0f ),
                new Point3f(  0.05f, 0.95f,0f ),
                new Point3f(  0, 1f,0f ),
                new Point3f(  0.00f, 0.95f,0.05f ),
                
                // a small Y
                new Point3f(  0.2f, 1f,0.0f ),
                new Point3f(  0.1f, 0.9f,0f ),
                new Point3f(  0.1f, 1.0f,0.0f ),
                new Point3f(  0.15f, 0.95f,0.0f )
                  
             };
        // scale axis drawing to 5% of word size
        for (int i = 0;i < axisCoords.length;i++){
            axisCoords[i].scale(worldSize*0.05f);
        }
        
        LineArray axisLines = new LineArray(
            axisCoords.length,
            GeometryArray.COORDINATES );
        axisLines.setCoordinates( 0, axisCoords );

        Appearance axisAppear = new Appearance();
        ColoringAttributes ca = new ColoringAttributes();
		ca.setColor(white);
		axisAppear.setColoringAttributes(ca);
		Material mat = new Material();
		mat.setDiffuseColor(white);
        axisAppear.setMaterial(mat);
        Shape3D axis = new Shape3D( axisLines, axisAppear );
        axis.setCollidable(false);
        axis.setPickable(false);
        sceneTrans.addChild(axis);
      
     }
    
  
    /**
     * Change the user view Point .
     * Note that we modify the ViewBranch transform not the scene transform.
     * @param type  can be VIEW_FROM_TOP,VIEW_FROM_EAST,VIEW_BEHIND_AGENT
     * @param agent : specify the agent  if VIEW_BEHIND_AGENT
     * 
     * The VIEW_BEHIND_AGENT case has to be called regularly because of the agent 
     * displacement.
     */

    public void changeViewPoint(int type, SimpleAgent agent) {
        Point3d p1 = new Point3d();
        Point3d p2 = new Point3d();

        Transform3D t1 = new Transform3D();
        Transform3D t2 = new Transform3D();
        t1.setIdentity();
        t2.setIdentity();
        mouseOrbiter.resetView();
        switch (type) {
        case VIEW_FROM_TOP:
            t1.lookAt(new Point3d(0, worldSize * 1.2, 0),
                    new Point3d(0, 0, 0), new Vector3d(0, 0, -1));
            t1.invert();
            viewTransformGroup.setTransform(t1);
            break;
        case VIEW_FROM_EAST:
            t1.lookAt(new Point3d(worldSize, worldSize, 0), new Point3d(0, 0,
                    0), new Vector3d(-1, 0, 0));
            t1.invert();
            viewTransformGroup.setTransform(t1);
            break;
        case VIEW_BEHIND_AGENT:
            t1.setTranslation(new Vector3d(-agent.getRadius() * 2, 0, 0));
            agent.getGroup().getLocalToVworld(t2);
            t1.mul(t2);
            viewTransformGroup.setTransform(t1);
            break;
        case VIEW_ABOVE_AGENT:
            agent.getRotationTransformGroup().getLocalToVworld(t1);
            t1.transform(p1);
            t1.transform(p2);
            p2.y = worldSize * .8;
            t1.lookAt(p2, p1, new Vector3d(0, 0, -1));
            t1.invert();
            viewTransformGroup.setTransform(t1);
            break;

        case VIEW_ABOVE_AGENT_NEAR:
            agent.getRotationTransformGroup().getLocalToVworld(t1);
            t1.transform(p1);
            t1.transform(p2);
            p2.y = agent.getHeight() * worldSize *0.5;
            // avoid front clipping
            if (p2.y <0.2) p2.y =0.2;
            t1.lookAt(p2, p1, new Vector3d(0, 0, -1));
            t1.invert();
            viewTransformGroup.setTransform(t1);

            break;
        case VIEW_AGENT_SIDE:

           
            agent.getRotationTransformGroup().getLocalToVworld(t1);
            t1.transform(p1);
            t1.transform(p2);
            agent.rotation.transform(p2);
            t2.setTranslation(new Vector3d(0,agent.getHeight()*2,agent.getRadius()*10));
            t2.transform(p2);
            t1.lookAt(p2, p1, new Vector3d(0, 1, 0));
            t1.invert();
            viewTransformGroup.setTransform(t1);

            break;
        }
    }
    
    boolean checkCollisionAgainstBlockWorldObjects(BoundingSphere bs){
        return false;
    }
    
   

    /** Stop rendering on main canvas 3D . Used for background mode. */
    public void stopRendering(){
        canvas3d.stopRenderer();
    }
    /** Restart  rendering on main canvas 3D . Used for background mode. */
    public void startRendering(){
        canvas3d.startRenderer();
    }
    /** Do one rendering on main canvas 3D . Used for background mode. */
    public void renderOnce(){
        canvas3d.startRenderer();
       
        try {
            Thread.sleep((int)(100));
        } catch (InterruptedException e) {
           
            e.printStackTrace();
        }
        canvas3d.stopRenderer();
    }
    /** Destroy the java3d graph */
    public void dispose(){
        universe.removeAllLocales();
        view.removeAllCanvas3Ds();
    }
    /**
     * @return the canvas3D associated to the world view platform 
     */
    public Canvas3D getCanvas3D(){ return canvas3d;}

    /** @return the scene branchgroup containing the world's object  which can be picked*/
    BranchGroup getPickableSceneBranch(){ return pickableSceneBranch;}


  
}
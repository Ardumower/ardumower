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
 * $Revision: 1.11 $
 * $Source: /cvsroot/simbad/src/simbad/sim/BaseObject.java,v $
 * 
 * Note :  LH - 12/08/2005 made class public.
 */
package simbad.sim;


import javax.media.j3d.Bounds;
import javax.media.j3d.BranchGroup;
import javax.media.j3d.Group;
import javax.media.j3d.Material;
import javax.media.j3d.Node;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.vecmath.Color3f;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;

/**
 * Base class for all objects added in the environment. It mainly contains the translation and
 * rotation transform groups- Descendants should
 * override create3D and call super.create3D().
 *
 */
public  abstract class BaseObject {

    /** Material used for the object body.*/
    Material material;
    /** Branch group corresponding to this object */
    BranchGroup branchGroup;
    /** rotation applied to this object */
    TransformGroup rotationGroup;

    /** translation applied  to this object */
    TransformGroup translationGroup;

    /** Link back to containing world.*/
    World world;
    
    /** indicates that the object is detached from the scenegraph. */
    protected boolean detachedFromSceneGraph;
 
    
    /**  A Group to attach all sub objects.  */
    Group group;
    /** Current rotation transform  - same  transform as in rotationGroup */ 
    Transform3D rotation;
    /** Current translation transform  - same transform as in translationGroup */ 
    Transform3D translation;
    
    /** A prepared color */
    static Color3f black = new Color3f(0.0f, 0.0f, 0.0f);
    /** A prepared color */
    static Color3f white = new Color3f(1.0f, 1.0f, 1.0f);

    /** Indicates that the wall object branch can be compiled to optimize sceneGraph */ 
    boolean compilable;
    
    /** keep direct pointer onto bounds object associated  to group node. */
    protected Bounds localBounds;

    /** if true the  object can be traversed - no collision  */
    boolean canBeTraversed;
    
    BaseObject() {
        compilable = false;  
        canBeTraversed = false;
        // Material for object body.
        material = new Material();
        material.setCapability(Material.ALLOW_COMPONENT_WRITE);
       
    }

    /** Translates (relative to current pos) the object to given position. */
    public void translateTo(Vector3d t) {
        Transform3D t3d = new Transform3D();
        t3d.setTranslation(t);
        translation.mul(t3d);
        translationGroup.setTransform(translation); 
        
    }

    /** Rotates (relative to current rotation) the object about Y axis. */
   public void rotateY(double angle) {
        Transform3D t3d = new Transform3D();
        t3d.rotY(angle);
        rotation.mul(t3d);
        rotationGroup.setTransform(rotation);
    }
   /** Resets translation and rotation transforms. */
   	void resetTransforms(){
        translation.setIdentity();
        rotation.setIdentity();
        translationGroup.setTransform(translation);
        rotationGroup.setTransform(rotation);
   	}
   
   	/** Create the object geometry. */
    void create3D(boolean allowTransformReadWrite) {
        //STRUCTURE Branch group->Translation Transform Group -> Rotation Transform Group->Group
        
        branchGroup = new BranchGroup();
        branchGroup.setCapability(BranchGroup.ALLOW_LOCAL_TO_VWORLD_READ);
        branchGroup.setCapability(BranchGroup.ALLOW_DETACH);
        
        translation = new Transform3D();
        translation.setIdentity();
        translationGroup = new TransformGroup();
        translationGroup.setTransform(translation);
        branchGroup.addChild(translationGroup);
        if (allowTransformReadWrite){      	
	        translationGroup.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
	        translationGroup.setCapability(TransformGroup.ALLOW_TRANSFORM_READ);
	        translationGroup.setCapability(TransformGroup.ALLOW_LOCAL_TO_VWORLD_READ);
	        translationGroup.setCapabilityIsFrequent(TransformGroup.ALLOW_TRANSFORM_WRITE);
	        translationGroup.setCapabilityIsFrequent(TransformGroup.ALLOW_TRANSFORM_READ);
	        translationGroup.setCapabilityIsFrequent(TransformGroup.ALLOW_LOCAL_TO_VWORLD_READ);
        }
        // rotation transform
        rotation = new Transform3D();
        rotation.setIdentity();
        rotationGroup = new TransformGroup();
        rotationGroup.setTransform(rotation);
        translationGroup.addChild(rotationGroup);
        if (allowTransformReadWrite){      	
	        rotationGroup.setCapability(TransformGroup.ALLOW_TRANSFORM_READ);
	        rotationGroup.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
	        rotationGroup.setCapability(TransformGroup.ALLOW_LOCAL_TO_VWORLD_READ);
	        rotationGroup.setCapabilityIsFrequent(TransformGroup.ALLOW_TRANSFORM_READ);
	        rotationGroup.setCapabilityIsFrequent(TransformGroup.ALLOW_TRANSFORM_WRITE);
	        rotationGroup.setCapabilityIsFrequent(TransformGroup.ALLOW_LOCAL_TO_VWORLD_READ);
        }
        // Create group to attach all gemotries
        group = new Group();
        group.setCapability(Group.ALLOW_LOCAL_TO_VWORLD_READ);
        // we want to setup the bounds manually
        group.setBoundsAutoCompute(false);
     //   group.setCapability(Group.ALLOW_BOUNDS_READ); // No more needed, use localBounds
        rotationGroup.addChild(group);
        
        }

    void compile(){
        if (compilable) branchGroup.compile();
    }
    final Node getNode() {
        return branchGroup;
    }

    protected void addChild(BaseObject object) {
        group.addChild(object.getNode());
    }

    final void addChild(Node node) {
        group.addChild(node);
      }

    Vector3f getTranslation() {
        Vector3f v = new Vector3f();
        translation.get(v);
        return v;
    }
    TransformGroup getRotationTransformGroup(){
        return rotationGroup;
    }
    TransformGroup getTranslationTransform(){
        return translationGroup;
    }
    Group getGroup(){ return group;}
    
    
    /** Sets the bounds object for collision/interaction detection */
    void setBounds(Bounds bounds){
        localBounds = bounds;
        group.setBounds(bounds);
    }
    Bounds getBounds (){
        return localBounds;
       // return group.getBounds();
    }
 
    
 	 /**
	  * Obtain  translation transform.
	 */
	public void getTranslationTransform(Transform3D t){
	    t.set(translation);
	}
	 /**
	  * Obtain  rotation transform.
	 */
	public void getRotationTransform(Transform3D t){
	    t.set(rotation);
	}

	/** Sets the containing world.*/
	protected void setWorld(World world){
	    this.world = world;
	}
	
    /** Removes object from the scenegraph. */
    public void detach(){
        
        world.detach(this);
        detachedFromSceneGraph = true;
    }
    /** Re-add object to the scenegraph. */
    public void attach(){
        world.attach(this);
        detachedFromSceneGraph = false;
    }
    
    /** Sets the canBeTraversed Flag. */
    public void setCanBeTraversed(boolean canbetraversed){
        this.canBeTraversed = canbetraversed;
    }

   
    /** Gets the canBeTraversed Flag. */
    public boolean getCanBeTraversed(){
        return canBeTraversed;
    }
 
    
	 /** Change the color while the  simulation is running.*/
    public void setColor(Color3f color){
        material.setDiffuseColor(color);
        material.setAmbientColor(color);
    }

}
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
 * $Revision: 1.13 $
 * $Source: /cvsroot/simbad/src/simbad/sim/Simulator.java,v $
 */
package simbad.sim;


import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;


import javax.media.j3d.VirtualUniverse;
import javax.swing.JComponent;
import javax.swing.JInternalFrame;



/**
 * The Simulator class. It manages the list of agents and performs the simulation steps. 
 * For each agent a simulation step is is as follow:
 * 	<li>update sensors </li>
 *  <li>call agent performBehavior </li>
 *  <li>update position </li>
 * In normal operation the steps are triggered by a timer event.
 * <br>
 * The Simulator class also provides a Background Mode with limited rendering. 
 * This mode is mainly useful for batch simulation ( ie genetic algorithms).
 * See Also Simbatch class. 
 * 
 * Cooperates with: World, PhysicalEngine
*
 */
public class Simulator {
    
    /** Used for mutual exclusion. all methods accessing agents shoud use this lock. */ 
    private Lock lock;
    /** Keeps track of application's main component  -- can be null*/
    private JComponent applicationComponent;
    World world; // link to associated world
    FrameMeter fps; // for fps measurement
    private Timer timer;
    
    /** The list of all objects  in the world. (static objects and agents).  */
    private ArrayList objects;

    /** The list of all agents.  */
      private ArrayList agents;

    /** number of frames per virtual seconds -  20 is a good value */
    private int framesPerSecond;
    
    private float virtualTimeFactor;
    /** Thread for the background mode */
    private SimulatorThread simulatorThread;

    
    /** Control the usage of physical law in the simulation */
    private boolean usePhysics;
    
    /** Handles all algorithms and resources related to agent interactions. */
    PhysicalEngine physicalEngine;
    
   /** Count simulation steps. */
    private long counter;
    
    
    ///////////////////////////////////////////////////////
    // CREATION / DESTRUCTION
 
    /** Constructs the simulator object
     * 
     * @param applicationComponent - A reference to the main Application container.
     * @param world - The 3d world object.
     * @param ed - the Environment description.
     */
    public Simulator(JComponent applicationComponent,World world, EnvironmentDescription ed) {
        this.world = world;
        simulatorThread = null;
        this.applicationComponent = applicationComponent;
        lock = new Lock();
        initialize(ed);
    }

    /** Initialize the simulator - only called once.*/
    private void initialize(EnvironmentDescription ed) {
        counter = 0;
        timer = null;
        setFramesPerSecond(20);
        setVirtualTimeFactor(1);
        fps = new FrameMeter();
        agents = new ArrayList();
        objects = new ArrayList();
        usePhysics =ed.usePhysics;
        physicalEngine = new PhysicalEngine();
        
        addMobileAndStaticObjects(ed);
        createAgentsUI();
    }

    /** Dispose all ressources. only called once.*/
    public synchronized void dispose(){
        stopSimulation();
        // dirty - wait rendering end. 
        try {Thread.sleep(500); } catch(Exception e){}
        for (int i = 0; i < agents.size(); i++)
            ((SimpleAgent) agents.get(i)).dispose();
   
    }
    /** Add all agents and objects. Only called once.*/
    private void addMobileAndStaticObjects(EnvironmentDescription ed) {
        // add all agents requested by the user
        for (int i = 0 ; i < ed.objects.size();i++){
            Object o = ed.objects.get(i);
            objects.add(o);
            if (o instanceof StaticObject){
                // The object is of type static, we add it to the world
                // and precompute anything possible.
                StaticObject so = (StaticObject) o;
                so.setWorld(world);
                world.addObjectToPickableSceneBranch(so);
                // pre compute necessary stuff.
                so.createLocalToVworld();
                so.createTransformedBounds();
                
                
            }else if (o instanceof  SimpleAgent){
                // The object is of type agent, we add it to the
                // simulator and call create.
                SimpleAgent agent = (SimpleAgent)o;
                agent.setSimulator(this);
                agent.setWorld(world);
                agent.create();
                agent.reset();
                agents.add(agent);
                world.addObjectToPickableSceneBranch(agent);           
            }
        }
    }
    /** Creates the UI that may be associated to each agent.
     * If the agent has set a Panel with setUIPanel a window is created containing the panel.
     * Only called once.
     **/
    private void createAgentsUI() {
        for (int i = 0; i < agents.size(); i++) {
            SimpleAgent agent = ((SimpleAgent) agents.get(i));
            // Only Agents have ui - not all SimpleAgents.
            if (agent instanceof Agent) {
                JInternalFrame window = ((Agent) agent).createUIWindow();
                if ((window != null) && (applicationComponent != null)){
                    applicationComponent.add(window);
                    window.show();
                    window.toFront();
                }
            }
        }
    }
            
    /////////////////////////////////////////////////////////////////////////////////////
    // SIMULATION LOOP
    
    /**
     * The main simulator method. It is called  cyclicaly or step by step. (see startSimulation).
     */
    public  synchronized void simulateOneStep() {
        // start critical section. only one thread.
        lock(); 
        int nagents = agents.size();
        
        // Print memory info (rarely)
        if (counter % 100000==0){
            Runtime.getRuntime().gc();
            System.out.println("Memory heap total: "+Runtime.getRuntime().totalMemory()/1024+
                    "k  max: "+Runtime.getRuntime().maxMemory()/1024+
                    "k  free: "+Runtime.getRuntime().freeMemory()/1024+"k");
        }
        counter++;
        
        // seconds are elapsed in virtual agent time.
        double dt = 1.0 / framesPerSecond;
      
        
        // update sensors and actuators
        for (int i = 0; i < nagents; i++) {
            SimpleAgent a = ((SimpleAgent) agents.get(i));
            a.updateSensors(dt, world.getPickableSceneBranch());
            a.updateActuators(dt);
           
           
        }
 
        // perform behavior
        for (int i = 0; i < nagents; i++) {
            SimpleAgent a = ((SimpleAgent) agents.get(i));
            a.performPreBehavior();
            a.performBehavior();
           
        }
        // Compute forces
        for (int i = 0; i <  nagents; i++) {
            SimpleAgent a = ((SimpleAgent) agents.get(i));
            a.clearVeryNear();
            a.setMotorsAcceleration(dt);
            if (usePhysics)
                physicalEngine.computeForces(dt,a);
            a.integratesVelocities(dt);
            a.integratesPositionChange(dt);
            
        }
       
        // Check physical interactions.
        if (usePhysics){
            physicalEngine.checkAgentAgentPairs(dt,agents,true,false);
            physicalEngine.checkAgentObjectPairs(agents,objects,true,false);
            
            // integrate position again  cause velocity may have changed due to impact.
            for (int i = 0; i < nagents; i++) {
                SimpleAgent a = ((SimpleAgent) agents.get(i));
                a.integratesPositionChange(dt);
            }
            
        }
        // Check collision
        physicalEngine.checkAgentAgentPairs(dt,agents,false,true);
        physicalEngine.checkAgentObjectPairs(agents,objects,false,true);
    
        // Update position and all counters
        for (int i = 0; i < nagents; i++) {
            SimpleAgent a = ((SimpleAgent) agents.get(i));
            a.updatePosition();
            a.updateCounters(dt);
        }
        fps.measurePoint(1);
        // end of critical section
        unlock();
    }

    
    /** initialize the behavior of all agents. */
    public synchronized void initBehaviors() {
        lock();// start of critical section
        // init behaviors
        for (int i = 0; i < agents.size(); i++) {
            SimpleAgent agent = ((SimpleAgent) agents.get(i));
                agent.initPreBehavior();
                agent.initBehavior();
            
        }
        unlock();// end of critical section
    }
    /** Starts the simulator loop. */
    public synchronized void startSimulation() {
        stopSimulation();
        initBehaviors();
        timer = new Timer();
        System.out.println("[SIM] start ...");
        timer.scheduleAtFixedRate(new TimerTask() {

            public void run() {
                simulateOneStep();
            }
        }, 0, (long) (1000 / (framesPerSecond * virtualTimeFactor)));
    }

    /** Stop (or pause) the simulator loop. */
    public synchronized void stopSimulation() {
        if (timer != null) timer.cancel();
         System.out.println("[SIM] stop ...");
    }
    /** Simulator control. */
    public synchronized void restartSimulation() {
        stopSimulation();
        resetSimulation();
        startSimulation();
        System.out.println("[SIM] restart ...");
    }
    /** Reset the simulation. Resets any living agents. */
    public synchronized void resetSimulation() {
        stopSimulation();
        lock();
        for (int i = 0; i < agents.size(); i++) {
            SimpleAgent agent = ((SimpleAgent) agents.get(i));
            agent.reset();
        }
        unlock();
        System.out.println("[SIM] reset ...");
    }
    /** Perform a single step of simulation */
    public synchronized void performSimulationStep() {
        stopSimulation();
        System.out.println("[SIM] Step ...");
        simulateOneStep();
    }


       public ArrayList getAgentList() {
        return agents;
    }
    /** Sets use physics indicator.*/
    protected void setUsePhysics(boolean usePhysics){
        this.usePhysics = usePhysics;
    }
    /** Gets use physics indicator.*/
    protected boolean getUsePhysics(){
        return usePhysics;
    }
    protected void setFramesPerSecond(int fps){
        framesPerSecond = fps;
    }
    protected int getFramesPerSecond(){
        return framesPerSecond ;
    }
    /** Set the time factor. Used to increase or decrease the simulation rate.
     *  
     * @param factor : typical value 1.0 (default) , 2.0 or 0.5
     */
    public void setVirtualTimeFactor(float fact){
        System.out.println("[SIM] virtualTimeFactor = " + fact);
        virtualTimeFactor = fact;
    }
    public float getVirtualTimeFactor(){
        return virtualTimeFactor ;
    }
    
    public  void setApplicationComponent(JComponent component){ applicationComponent= component;}
    /** This class runs the simulator in a background process.
     * It is only used for simulator  background mode. 
     */
    
    /** Obtain simulator critical resources.*/
    public void lock(){lock.lock();}
    /** Release simulator critical resources.*/
    public void unlock(){lock.unlock();}
    
    
    /////////////////////////////////////////////////////////////////////////////////////
    // BACKGROUND MODE THREAD 
    /** Starts special background mode */
    public synchronized void startBackgroundMode(){
        simulatorThread = new SimulatorThread();
        // j3d threads must have priority
        simulatorThread.setPriority(Thread.MIN_PRIORITY);
        simulatorThread.start();
    }
    /** Stops special background mode */
    public synchronized void stopBackgroundMode(){
        if (simulatorThread != null)   simulatorThread.requestStop();
    }

    private class SimulatorThread extends Thread {

        private boolean stopped;

        SimulatorThread() {
            stopped = false;
        }

        public void requestStop() {
            stopped = true;
        }

        public void run() {
            setPriority(Thread.MAX_PRIORITY);
            VirtualUniverse.setJ3DThreadPriority(Thread.MIN_PRIORITY);
            int count = 0;
            int rendererRate = 100000;
            System.out.println("[SIM] Starting Background mode");
            try {
                // First wait a bit so J3d is settled ?
                sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            world.stopRendering();
            world.renderOnce();
            // adjust fps update because we're running too fast to have precise
            // measure
            fps.setUpdateRate(rendererRate);
            for (int i = 0; i < agents.size(); i++) {
                SimpleAgent agent = (SimpleAgent) agents.get(i);
                agent.reset();
                if (agent instanceof Agent)
                    ((Agent) agent).setFrameMeterRate(rendererRate);
            }
            initBehaviors();
            // loop until flag change
            while (!stopped) {
                simulateOneStep();
                count++; 
                if ((count % rendererRate) == 0) {
                    world.renderOnce();
                    // inspector update seems to cause memory leak (priority ?)
                    for (int i = 0; i < agents.size(); i++) {
                        Object o =  agents.get(i);
                        if (o instanceof Agent)
                            ((Agent) o).getAgentInspector().update();
                    }
                }
            }
            System.out.println("[SIM] Stopping Background mode");
            world.startRendering();
        }
    }
 }

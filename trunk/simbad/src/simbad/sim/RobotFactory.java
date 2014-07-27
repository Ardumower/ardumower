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
 * $Revision: 1.13 $
 * $Source: /cvsroot/simbad/src/simbad/sim/RobotFactory.java,v $
 */
package simbad.sim;

import javax.media.j3d.Transform3D;
import javax.vecmath.Vector3d;

/**
 *  A helper class to aid building robot bodies and sensors.
 * It only contains only static methods and thus should not be instanciated. 
 * 
 * 
 * 
 */
public class RobotFactory extends Factory {

    
    /**
     * Adds a prebuild camera sensor to the agent. Image resolution is 100x100 pixels.
     * Camera is situated on the top of the agent.
     * @param agent
     * @return the sensor object
     */
    static public CameraSensor addCameraSensor(Agent agent) {
        double agentHeight = agent.getHeight();
        float cameraBodyRadius = 0.1f;
        CameraSensor camera = new CameraSensor(cameraBodyRadius, 100, 100);
        camera.setUpdatePerSecond(3);
        camera.setName("Camera");
        Vector3d pos = new Vector3d(0.0, (agentHeight / 2)
                + (cameraBodyRadius * 3) / 4, 0);
        agent.addSensorDevice(camera, pos, 0);
        return camera;
    }

    

    /**
     * Adds a prebuild belt of sonar sensor to the agent.
     * @param agent
     * @return the sensor object
     */
    static public RangeSensorBelt addSonarBeltSensor(Agent agent) {
        double agentHeight = agent.getHeight();
        double agentRadius = agent.getRadius();
        RangeSensorBelt sonarBelt = new RangeSensorBelt((float) agentRadius,
                0f, 1.5f, 9, RangeSensorBelt.TYPE_SONAR,0);
        sonarBelt.setUpdatePerSecond(3);
        sonarBelt.setName("sonars");
        Vector3d pos = new Vector3d(0, agentHeight / 2, 0.0);
        agent.addSensorDevice(sonarBelt, pos, 0);
        return sonarBelt;
    }
    /**
     * Adds a prebuild belt of sonar sensor to the agent.
     * @param agent
     * @param nbSonars the number of sonars.
     * @return the sensor object
     */
    static public RangeSensorBelt addSonarBeltSensor(Agent agent,int nbSonars) {
        double agentHeight = agent.getHeight();
        double agentRadius = agent.getRadius();
        RangeSensorBelt sonarBelt = new RangeSensorBelt((float) agentRadius,
                0f, 1.5f, nbSonars, RangeSensorBelt.TYPE_SONAR,0);
        sonarBelt.setUpdatePerSecond(3);
        sonarBelt.setName("sonars");
        Vector3d pos = new Vector3d(0, agentHeight / 2, 0.0);
        agent.addSensorDevice(sonarBelt, pos, 0);
        return sonarBelt;
    }

    /**
     * Adds a prebuild belt of bumpers sensor to the agent.
     * @param agent
     * @return the sensor object
     */
    static public RangeSensorBelt addBumperBeltSensor(Agent agent) {
       // double agentHeight = agent.getHeight();
        double agentRadius = agent.getRadius();
        RangeSensorBelt bumperBelt = new RangeSensorBelt((float) agentRadius-0.1f,
                0f, 0.2f, 9, RangeSensorBelt.TYPE_BUMPER,0);
        bumperBelt.setUpdatePerSecond(6);
        bumperBelt.setName("bumpers");
        Vector3d pos = new Vector3d(0, 0, 0.0);
        agent.addSensorDevice(bumperBelt, pos, 0);
        return bumperBelt;
    }
    /**
     * Adds a prebuild belt of bumpers sensor to the agent. Specify the number of sensors.
     * @param agent
     * @param nbSensors
     * @return the sensor object
     */
    static public RangeSensorBelt addBumperBeltSensor(Agent agent,int  nbSensors) {
       // double agentHeight = agent.getHeight();
        double agentRadius = agent.getRadius();
        RangeSensorBelt bumperBelt = new RangeSensorBelt((float) agentRadius-0.1f,
                0f, 0.2f, nbSensors, RangeSensorBelt.TYPE_BUMPER,0);
        bumperBelt.setUpdatePerSecond(6);
        bumperBelt.setName("bumpers");
        Vector3d pos = new Vector3d(0, 0, 0.0);
        agent.addSensorDevice(bumperBelt, pos, 0);
        return bumperBelt;
    }

    /**
     * Adds a prebuild light sensor  to the agent.
     * @param agent
     * @return the sensor object
     */
    static public LightSensor addLightSensor(Agent agent) {
        double agentHeight = agent.getHeight();
        LightSensor sensor = new LightSensor();
        sensor.setUpdatePerSecond(3);
        sensor.setName("Light Sensor");
        Vector3d pos = new Vector3d(0.0, (agentHeight / 2), 0);
        agent.addSensorDevice(sensor, pos, -Math.PI / 2);
        return sensor;
    }

    /**
     * Adds a prebuild light sensor  to the agent at a given position.
     * @param agent
     * @return the sensor object
     */
    static public LightSensor addLightSensor(Agent agent, Vector3d pos,
            float angle, String label) {
        LightSensor sensor = new LightSensor();
        sensor.setUpdatePerSecond(3);
        sensor.setName("Light Sensor " + label);
        agent.addSensorDevice(sensor, pos, angle);
        return sensor;
    }

    /**
     * Adds a prebuild light sensor on the left of the agent .
     * @param agent
     * @return the sensor object
     */
    static public LightSensor addLightSensorLeft(Agent agent) {
        Vector3d front = new Vector3d(agent.getRadius()+0.5, 0, 0);
        Transform3D t3d = new Transform3D();
        t3d.rotY(Math.PI / 4);
        Vector3d left = new Vector3d(front);
        t3d.transform(left);
        return RobotFactory.addLightSensor(agent, left, (float) Math.PI / 4,
                "left");
    }

    /**
     * Adds a prebuild light sensor on the right of the agent .
     * @param agent
     * @return the sensor object
     */
    static public LightSensor addLightSensorRight(Agent agent) {
        Vector3d front = new Vector3d(agent.getRadius()+0.5, 0, 0);
        Transform3D t3d = new Transform3D();
        t3d.rotY(-Math.PI / 4);
        Vector3d right = new Vector3d(front);
        t3d.transform(right);
        return RobotFactory.addLightSensor(agent, right, (float) -Math.PI / 4,
                "left");
    }

    
    
    /**
     * Adds a prebuild key  input  to the agent.
     * @param agent
     * @return the sensor object
     */
    static public KeyInputSensor addKeyInputSensor(Agent agent) {
        KeyInputSensor sensor = new KeyInputSensor();
      
        sensor.setUpdatePerSecond(3);
        sensor.setName("key input");
        // position has no meaning in the case of that sensor.
        Vector3d pos = new Vector3d(0, 0.0, 0.0);
        agent.addSensorDevice(sensor, pos, 0);
        return sensor;
    }
    
    static public IMUSensor addIMUSensor(Agent agent) {
        IMUSensor sensor = new IMUSensor();      
        sensor.setUpdatePerSecond(20);
        sensor.setName("IMU (gyro,acc,com)");
        Vector3d pos = new Vector3d(0, 0.0, 0.0);
        agent.addSensorDevice(sensor, pos, 0);
        return sensor;
    }
    
    static public PerimeterSensor addPerimeterSensor(Agent agent) {
    	double agentHeight = agent.getHeight();
        double agentRadius = agent.getRadius();        
    	PerimeterSensor sensor = new PerimeterSensor();      
        sensor.setUpdatePerSecond(10);
        sensor.setName("perimeter");        
        Vector3d pos = new Vector3d(0.3, agentHeight*0.02, 0);
        //Vector3d pos = new Vector3d(0, agentHeight*0.02, 0);
        agent.addSensorDevice(sensor, pos, 0);
        return sensor;
    }
    
    
    /////////////////////////////////////////////////////////////////////////////////////
    //  Prebuild Actuators 
    
    
    /**
     * Adds a prebuild lamp actuator on the top  of the agent .
     * @param agent
     * @return the actuator object
     */
    static public LampActuator addLamp(Agent agent) {
        LampActuator la = new LampActuator(0.15f);
        la.setName("lamp");
        la.setUpdatePerSecond(5f);
        agent.addActuatorDevice(la, new Vector3d(0,agent.getHeight(),0),0);
       
        return la;
    }
    
    

    /////////////////////////////////////////////////////////////////////////////////////
    //  Prebuild KinelaticModels

    /** Sets the kinematic model to be DifferentialDrive (instead of DefaultKinematic)
     * @param agent
     */
    static public DifferentialKinematic setDifferentialDriveKinematicModel(Agent agent){
       agent.setKinematicModel(new DifferentialKinematic(agent.getRadius()));
       return (DifferentialKinematic)agent.getKinematicModel();
    }
    
}
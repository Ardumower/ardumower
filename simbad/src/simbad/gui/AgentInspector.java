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
 * $Date: 2005/08/07 12:24:56 $
 * $Revision: 1.10 $
 * $Source: /cvsroot/simbad/src/simbad/gui/AgentInspector.java,v $
 */
package simbad.gui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.util.ArrayList;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JInternalFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import simbad.sim.*;

/**
 * The AgentInspector implements a window showing agent's state. The informations update is
 * made by a thread.
 * Due to cyclic update this class can cause frequent GC. 
 * The AgentInspector can also be used without a thread. In this case one must call update to refresh display.
 */
public class AgentInspector extends JInternalFrame implements Runnable {

	private static final long serialVersionUID = 1L;
	Simulator simulator;
    private SimpleAgent agent;
    private JTextArea textArea;
    /** The list of all agent's sensor panels */
    private ArrayList sensorPanels;
    /** The list of all agent's actuator panels */
    private ArrayList actuatorPanels;
    private Thread thread;
    float framesPerSecond;
    Font font;

    public AgentInspector(Agent agent,boolean useThread,Simulator simulator) {
        super(agent.getName() + " Inspector");
        this.agent = agent;
        this.simulator = simulator;
        agent.setAgentInspector(this);
        sensorPanels = new ArrayList();
        actuatorPanels = new ArrayList();
        initialize();
        //setFramesPerSecond(2.0f);
        setFramesPerSecond(5.0f);
        if (useThread){
            thread = new Thread(this);
            thread.start();
        }
     }

    public void setFramesPerSecond(float fps){
        framesPerSecond = fps;
    }
    private void initialize() {
        font = new Font("Arial",Font.PLAIN,11);
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel,BoxLayout.PAGE_AXIS));
        // 
        
        // create sensor panels
        ArrayList sensors = agent.getSensorList();
        for (int i =0 ; i< sensors.size();i++){
            SensorDevice sd = (SensorDevice)sensors.get(i);
            if (sd == null) continue;
            JPanel sdpanel =sd.createInspectorPanel();
            if (sdpanel != null){
                JPanel p =  new JPanel();
                p.setLayout(new BoxLayout(p,BoxLayout.PAGE_AXIS));
                JLabel l = new JLabel(sd.getName());
                l.setFont(font);
                p.add(l);
                p.add(sdpanel);
                p.setBorder(BorderFactory.createEtchedBorder());
                p.setBackground(Color.WHITE);
                panel.add(p);
                sensorPanels.add(sdpanel);
            }
        }
        // create Actuators panels
        ArrayList actuators = agent.getActuatorList();
        for (int i =0 ; i< actuators.size();i++){
            ActuatorDevice ad = (ActuatorDevice)actuators.get(i);
            if (ad == null) continue;
            JPanel adpanel =ad.createInspectorPanel();
            if (adpanel != null){
                JPanel p =  new JPanel();
                p.setLayout(new BoxLayout(p,BoxLayout.PAGE_AXIS));
                JLabel l = new JLabel(ad.getName());
                l.setFont(font);
                p.add(l);
                p.add(adpanel);
                p.setBorder(BorderFactory.createEtchedBorder());
                p.setBackground(Color.WHITE);
                panel.add(p);
                actuatorPanels.add(adpanel);
            }
        }

        // agent info
        textArea = new JTextArea("", 8, 6);
        textArea.setBorder(BorderFactory.createEtchedBorder());
        textArea.setMinimumSize(new Dimension(200,200));
        textArea.setPreferredSize(new Dimension(200,200));
        textArea.setFont(font);
        textArea.setEditable(false);
  
        panel.add(textArea);
        setContentPane(panel);
       // panel.setPreferredSize(new Dimension(200, 280));
        pack();
      
    }

    /** update loop */
    public void run() {
        while (true) {
            try {
                // don't need precise time tick
                Thread.sleep((int)(1000f / framesPerSecond));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            update();
        }
    }
    
    public void update() {
        simulator.lock(); // start of critical section
        textArea.setText(agent.asString());
        for (int i = 0; i < sensorPanels.size(); i++)
            ((JPanel) sensorPanels.get(i)).repaint();
        for (int i = 0; i < actuatorPanels.size(); i++)
            ((JPanel) actuatorPanels.get(i)).repaint();

        simulator.unlock(); // end of critical section
    }
    
   
        
}
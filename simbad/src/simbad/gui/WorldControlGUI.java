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
 * $Date: 2005/02/05 11:05:27 $
 * $Revision: 1.6 $
 * $Source: /cvsroot/simbad/src/simbad/gui/WorldControlGUI.java,v $
 */
package simbad.gui;

import java.awt.Container;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JPanel;
import simbad.sim.SimpleAgent;
import simbad.sim.Simulator;
import simbad.sim.World;

/**
 * The GUI for controlling the world.
 */
public class WorldControlGUI extends JPanel implements ActionListener {
	private static final long serialVersionUID = 1L;
    World world;
    Simulator simulator;
    AgentFollower agentFollower;
    Font smallFont;

    public WorldControlGUI(World world, Simulator simulator) {
        this.world = world;
        smallFont = new Font("Arial",Font.PLAIN,11);
        createGUI();
        agentFollower = new AgentFollower(world, (SimpleAgent) simulator
                .getAgentList().get(0));
    }

    void createGUI() {
    /*    setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createTitledBorder("World"),
                BorderFactory.createEmptyBorder(5,5,5,5)));*/
        setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
        
        // View Buttons
        JPanel panel1 = new JPanel();
        panel1.setLayout(new BoxLayout(panel1, BoxLayout.Y_AXIS));
        panel1.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createTitledBorder("View From:"),
                BorderFactory.createEmptyBorder()));
        JPanel panel1_1 = new JPanel();
        panel1_1.setLayout(new BoxLayout(panel1_1, BoxLayout.X_AXIS));
        createButton(panel1_1, "top", "topview");
        createButton(panel1_1, "side", "eastview");
        panel1.add(panel1_1);
             
        JPanel panel2 = new JPanel();
        panel2.setLayout(new BoxLayout(panel2, BoxLayout.Y_AXIS));
        panel2.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createTitledBorder("Follow:"),
                BorderFactory.createEmptyBorder()));
        JPanel panel2_1 = new JPanel();
        panel2_1.setLayout(new BoxLayout(panel2_1, BoxLayout.X_AXIS));
        createButton(panel2_1, "far", "followfar");
        createButton(panel2_1, "near", "follownear");
        createButton(panel2_1, "side", "followside");
        panel2.add(panel2_1);
        add(panel1);
        add(panel2);
        
    }

    /** helper function */
    private void createButton(Container container, String label, String action) {
        JButton b = new JButton(label);
        b.setFont(smallFont);
        b.setActionCommand(action);
        b.addActionListener(this);
        container.add(b);
    }


    public void actionPerformed(ActionEvent actionEvent) {
        String action = actionEvent.getActionCommand();
        if (action.equals("topview")) {
            agentFollower.suspend();
            world.changeViewPoint(World.VIEW_FROM_TOP, null);
        } else if (action.equals("eastview")) {
            agentFollower.suspend();
            world.changeViewPoint(World.VIEW_FROM_EAST, null);
        } else if (action.equals("followfar")) {
            agentFollower.setViewPointType(World.VIEW_ABOVE_AGENT);
            agentFollower.resume();
        }
        else if (action.equals("follownear")) {
            agentFollower.setViewPointType(World.VIEW_ABOVE_AGENT_NEAR);
            agentFollower.resume();
        }
        else if (action.equals("followside")) {
            agentFollower.setViewPointType(World.VIEW_AGENT_SIDE);
            agentFollower.resume();
        }
    }
}
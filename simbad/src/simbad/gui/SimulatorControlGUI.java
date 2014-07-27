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
 * $Date: 2005/01/27 22:09:12 $
 * $Revision: 1.8 $
 * $Source: /cvsroot/simbad/src/simbad/gui/SimulatorControlGUI.java,v $
 */
package simbad.gui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.ButtonGroup;
import javax.swing.JPanel;
import java.awt.Container;
import java.awt.Font;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JFormattedTextField;
import javax.swing.JRadioButton;
import simbad.sim.Simulator;
import javax.swing.JFrame;
import javax.swing.JMenu;

/**
 * The GUI panel for controlling the simulator.
 */
public class SimulatorControlGUI extends JPanel implements ActionListener {

	private static final long serialVersionUID = 1L;
    Simulator simulator;
    JFormattedTextField timeFactorField;
    JFrame parentFrame;
    Font smallFont;
    
    public SimulatorControlGUI(JFrame parentFrame,Simulator simulator) {
        this.simulator = simulator;
        
        smallFont = new Font("Arial",Font.PLAIN,11);
        setFont(smallFont);
        createGUI();
        this.parentFrame = parentFrame;
     }
    
    public JMenu createMenu(){
        JMenu menu = new JMenu("Simulator");
        // TODO
        return menu;
    }
    void createGUI() {
        setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createTitledBorder("Simulator"),
                BorderFactory.createEmptyBorder(5,5,5,5)));
  
        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
        // Control buttons
        JPanel panel1 = new JPanel();
        panel1.setLayout(new BoxLayout(panel1, BoxLayout.X_AXIS));
        createButton(panel1, "run", "run");
        createButton(panel1, "pause", "pause");
        createButton(panel1, "reset", "reset");
        createButton(panel1, "restart", "restart");
        createButton(panel1, "step", "step1");
        add(panel1);
        // time factor buttons
        JPanel panel2 = new JPanel();
        panel2.setLayout(new BoxLayout(panel2, BoxLayout.X_AXIS));
        createLabel(panel2,"Time Factor");
        ButtonGroup bgroup = new ButtonGroup();
        createRadioButton(panel2, bgroup, "0.2", "tf0.2",false);
        createRadioButton(panel2, bgroup, "0.5", "tf0.5",false);
        createRadioButton(panel2, bgroup, "1.0", "tf1.0",true);
        createRadioButton(panel2, bgroup, "5.0", "tf5.0",false);
        createRadioButton(panel2, bgroup, "10.0", "tf10.0",false);
        createRadioButton(panel2, bgroup, "20.0", "tf20.0",false);
     
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

    /** helper function */
    private void createRadioButton(Container container, ButtonGroup group,
            String label, String action,boolean selected) {
        JRadioButton b = new JRadioButton(label);
        b.setActionCommand(action);
        b.setFont(smallFont);
        b.addActionListener(this);
        b.setSelected(selected);
        group.add(b);
        container.add(b);
    }
    /** helper function */
    private void createLabel(Container container, String label) {
        JLabel l = new JLabel(label);
        l.setFont(smallFont);
        container.add(l);
    }


    public void actionPerformed(ActionEvent actionEvent) {
        String action = actionEvent.getActionCommand();
        if (action.equals("run")) {
            simulator.startSimulation();
        } else if (action.equals("pause")) {
            simulator.stopSimulation();
        } else if (action.equals("reset")) {
            simulator.resetSimulation();
        } else if (action.equals("restart")) {
            simulator.restartSimulation();
        } else if (action.equals("tf0.2")) {
            simulator.setVirtualTimeFactor(0.2f);
        } else if (action.equals("tf0.5")) {
            simulator.setVirtualTimeFactor(0.5f);
        } else if (action.equals("tf1.0")) {
            simulator.setVirtualTimeFactor(1.0f);
        } else if (action.equals("tf2.0")) {
            simulator.setVirtualTimeFactor(2.0f);
        } else if (action.equals("tf5.0")) {
            simulator.setVirtualTimeFactor(5.0f);
        } else if (action.equals("tf10.0")) {
            simulator.setVirtualTimeFactor(10.0f);
        } else if (action.equals("tf20.0")) {
            simulator.setVirtualTimeFactor(20.0f);
        } else if (action.equals("tf50.0")) {
            simulator.setVirtualTimeFactor(50.0f);
        } else if (action.equals("step1")) {
            simulator.performSimulationStep();
       
        }
 
    }
 
}

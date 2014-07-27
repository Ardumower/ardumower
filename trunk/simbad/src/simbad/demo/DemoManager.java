/*
 * Simbad - Robot Simulator Copyright (C) 2004 Louis Hugues
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * -----------------------------------------------------------------------------
 * $Author: sioulseuguh $ 
 * $Date: 2005/04/25 17:58:17 $
 * $Revision: 1.7 $
 * $Source: /cvsroot/simbad/src/simbad/demo/DemoManager.java,v $
 */
package simbad.demo;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JMenu;
import javax.swing.JMenuItem;

/**
 *  Manages (simply) a list of demonstrations and is used by Simbad main class.
 *  This class is used statically only.
 */
public class DemoManager {

    // available demos classes
    final static String classNames[] = { "simbad.demo.BaseDemo","simbad.demo.BumpersDemo",
            "simbad.demo.SingleAvoiderDemo", "simbad.demo.AvoidersDemo",
            "simbad.demo.ImagerDemo", "simbad.demo.LightSearchDemo",
            "simbad.demo.SimplestDemo", "simbad.demo.BlinkingLampDemo",
            "simbad.demo.DifferentialKinematicDemo","simbad.demo.KheperaDemo","simbad.demo.PickCherriesDemo",
            "simbad.demo.PushBallsDemo"};

    /** Creates a menu corresponding to the demo set. */
    public final static JMenu createMenu(ActionListener actionListener) {
        JMenu menu = new JMenu("Examples");
        for (int i = 0; i < classNames.length; i++) {
            JMenuItem item = new JMenuItem(classNames[i]);
            item.setActionCommand("demo");
            item.addActionListener(actionListener);
            menu.add(item);
        }
        return menu;
    }

    /** Creates a demo corresponding to the menu item. */
       public static Demo getDemoFromActionEvent(ActionEvent event) {
        Class cl = null;
        Demo demo=null;
        String demoName = ((JMenuItem) event.getSource()).getText();
        try {
            cl = Class.forName(demoName);
            demo = (Demo)cl.newInstance();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return demo;
    }
}
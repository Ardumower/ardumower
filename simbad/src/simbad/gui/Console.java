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
 * $Date: 2005/01/08 16:51:30 $
 * $Revision: 1.3 $
 * $Source: /cvsroot/simbad/src/simbad/gui/Console.java,v $
 */
package simbad.gui;
import java.awt.Font;
import java.io.IOException;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;
import java.io.PrintStream;
import javax.swing.JInternalFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;


/**
 * <p> Redirects all System.out.print in a window 
 * <p>
 */
public class Console extends JInternalFrame implements Runnable {


	private static final long serialVersionUID = 1L;
	Thread thread;
    PipedOutputStream out;
    PipedInputStream in;
    JTextArea jtextArea;
    JScrollPane jscrollPane;
    static int MAXLENGHT = 10*1024;

    public Console(int sizex, int sizey) {
        super("System.out");
        initialize();
        setSize(sizex, sizey);
    }

    private void initialize() {
        // redirige la System.out sur un pipe
        try {
            out = new PipedOutputStream();
            in = new PipedInputStream(out);
        } catch (IOException e) {
            System.err.println(" IO Exception");
        }
        System.setOut(new PrintStream(out));
        jtextArea = new JTextArea(30, 30);
        jtextArea.setEditable(false);
        jtextArea.setAutoscrolls(true);
        jtextArea.setFont(new Font("Courier", Font.PLAIN, 10));
             jscrollPane = new JScrollPane(jtextArea);
        jscrollPane
                .setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        setContentPane(jscrollPane);
        thread = new Thread(this);
        thread.start();
        setResizable(true);
    }

     public void run() {
        while (true) {
            try {
                Thread.sleep(100);
                if (in.available()> 0)
                {
                    byte buf[] = new byte[in.available()];
                    in.read(buf, 0, buf.length);
                    // devrait être bloquant ?
                    String text = jtextArea.getText();
                    text += new String(buf);
                    int l = text.length();
                    if (l > MAXLENGHT)
                            text = text.substring(l - MAXLENGHT, l - 1);
                    jtextArea.setText(text);
                    
                    jtextArea.setCaretPosition(jtextArea.getDocument().getLength());

                }
            } catch (IOException e) {
                System.err.println("Console IO Exception");
            } catch (InterruptedException e) {}
        }
    }
}
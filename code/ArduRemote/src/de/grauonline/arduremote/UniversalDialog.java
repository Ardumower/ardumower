/*
License
Copyright (c) 2013-2017 by Alexander Grau

Private-use only! (you need to ask for a commercial-use)
 
The code is open: you can modify it under the terms of the 
GNU General Public License as published by the Free Software Foundation, 
either version 3 of the License, or (at your option) any later version.

The code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Private-use only! (you need to ask for a commercial-use)
  
 */

package de.grauonline.arduremote;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.text.InputType;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;

public class UniversalDialog {
	
	private Context context; 	
 	private String title;
 	private String positiveButton;
 	private String negativeButton;
 	private UniversalDialogListener listener = null;	

	public interface UniversalDialogListener 
	{
		public void onClosed(boolean positiveButton);
	}
	
 	UniversalDialog(Context context, String title, String positiveButton, String negativeButton,
 			UniversalDialogListener listener){
 		this.context = context; 		
 		this.title = title;
 		this.positiveButton = positiveButton;
 		this.negativeButton = negativeButton;
 		this.listener = listener;
 	}
 	 	
	void run(){
		AlertDialog.Builder alert = new AlertDialog.Builder(context);
		
    	alert.setTitle(title);
    	//alert.setMessage(text);
    	
    	alert.setPositiveButton(positiveButton, new DialogInterface.OnClickListener() {
    	  public void onClick(DialogInterface dialog, int whichButton) {    		  
    		  listener.onClosed(true);
    	  }
    	  });

    	alert.setNegativeButton(negativeButton, new DialogInterface.OnClickListener() {
    	  public void onClick(DialogInterface dialog, int whichButton) {
    		 listener.onClosed(false);
    	  }
     	  });
        
    	AlertDialog menu = alert.create();    	       	    
    	menu.show();		
		
	}
	
	

}

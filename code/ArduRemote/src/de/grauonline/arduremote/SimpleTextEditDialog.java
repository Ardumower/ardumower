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

public class SimpleTextEditDialog {
	
 	public Context context;
 	public String text;
 	public String title; 	
 	public int inputType;
 	private SimpleTextEditListener listener = null;	

	public interface SimpleTextEditListener 
	{
		public void onTextEdit(String text);
	}
	
 	SimpleTextEditDialog(Context context, String title, String text, int inputType, SimpleTextEditListener listener){
 		this.context = context;
 		this.text = text;
 		this.title = title;
 		this.inputType = inputType;
 		this.listener = listener;
 	}
 	 	
	void run(){
		AlertDialog.Builder alert = new AlertDialog.Builder(context);
		
    	alert.setTitle(title);
    	//alert.setMessage(text);
    	
	    LinearLayout linear=new LinearLayout(context); 
	    linear.setOrientation(LinearLayout.VERTICAL);    	
    	
    	// Set an EditText view to get user input 
    	final EditText input = new EditText(context);
    	input.setText(text);
    	input.setInputType(inputType);
    	alert.setView(input);
    	
    	/*LinearLayout buttons=new LinearLayout(context); 
	    buttons.setOrientation(LinearLayout.HORIZONTAL);
	    for (int i=0; i < keys.length(); i++){
	       Button button = new Button(context);
		   button.setTextSize(24);
		   button.setText(String.valueOf(keys.charAt(i)));
		   buttons.addView(button);
	    }
	    linear.addView(input);
	    linear.addView(buttons); 	    	    
	    alert.setView(linear); */
	    

    	alert.setPositiveButton("OK", new DialogInterface.OnClickListener() {
    	  public void onClick(DialogInterface dialog, int whichButton) {    		  
    		  listener.onTextEdit(input.getText().toString());
    	  }
    	  });

    	alert.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
    	  public void onClick(DialogInterface dialog, int whichButton) {
    		  // listener.onTextEdit("");
    	  }
     	  });
        
    	AlertDialog menu = alert.create();
    	menu.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_VISIBLE);       	    	
    	menu.show();		
		
	}
	
	

}

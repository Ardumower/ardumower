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

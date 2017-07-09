package de.grauonline.arduremote;

import de.grauonline.arduremote.SimpleFileDialog.SimpleFileDialogListener;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.widget.ArrayAdapter;

public class SimpleListDialog {
	
 	public Context context;
 	public String[] items;
 	public String title; 	
 	private SimpleListDialogListener listener = null;	

	public interface SimpleListDialogListener 
	{
		public void onChosenItem(int choosenItem);
	}

 	
 	SimpleListDialog(Context context, String title, String[] items, SimpleListDialogListener listener){
 		this.context = context;
 		this.items = items;
 		this.title = title;
 		this.listener = listener;
 	}
 	
 	
	void run(){
		 final AlertDialog.Builder menuAleart = new  AlertDialog.Builder(context);
		 menuAleart.setTitle(title);
		 menuAleart.setItems(items,new DialogInterface.OnClickListener() {
		  public void onClick(DialogInterface dialog, int item) {
		     listener.onChosenItem(item); 			 
		  }
		 });
		 AlertDialog menuDrop = menuAleart.create();
		 menuDrop.show();
	}    
}



package de.grauonline.arduremote;

import java.util.Calendar;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.DatePickerDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.text.InputType;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.LinearLayout;

public class SimpleDateDialog {
	
 	public Activity context;
 	public String title;
 	public Calendar calendar;
 	private SimpleDateListener listener = null;	

	public interface SimpleDateListener 
	{
		public void onDateChoosen(Calendar calendar);
	}
	
 	SimpleDateDialog(Activity context, Calendar calendar, SimpleDateListener listener){
 		this.context = context; 		
 		this.calendar = calendar;
 		this.listener = listener;
 	}
 	 	
	void run(){
		//final Calendar myCalendar = Calendar.getInstance();
		DatePickerDialog.OnDateSetListener dlgListener = new DatePickerDialog.OnDateSetListener() {

		    @Override
		    public void onDateSet(DatePicker view, int year, int monthOfYear,
		            int dayOfMonth) {
		        // TODO Auto-generated method stub
		        calendar.set(Calendar.YEAR, year);
		        calendar.set(Calendar.MONTH, monthOfYear);
		        calendar.set(Calendar.DAY_OF_MONTH, dayOfMonth);		        
		        //String myFormat = "MM/dd/yy"; //In which you need put here
		        //SimpleDateFormat sdf = new SimpleDateFormat(myFormat, Locale.US);
		        //edittext.setText(sdf.format(myCalendar.getTime()));
		        listener.onDateChoosen(calendar);
		    }
		};
				
		new DatePickerDialog(context, 
				dlgListener, 
				calendar.get(Calendar.YEAR), 
				calendar.get(Calendar.MONTH),
                calendar.get(Calendar.DAY_OF_MONTH)
        ).show();        			
	}

	
		


}

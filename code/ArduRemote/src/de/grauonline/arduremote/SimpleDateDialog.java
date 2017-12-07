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

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

import java.util.Timer;
import java.util.TimerTask;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnLongClickListener;
import android.view.View.OnTouchListener;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;

public class SimpleSliderDialog {
	
 	public Context context;
 	public float maxValue;
 	public float minValue;
 	public float defaultValue; 	
 	public float step;
 	public String title;
 	public Timer timer = new Timer();
 	public float timerSteps = 1;
 	private SimpleSliderListener listener = null;	

	public interface SimpleSliderListener 
	{
		public void onValueChanged(float value);
	}
	
 	SimpleSliderDialog(Context context, String title, float minValue, float maxValue, 
 			float defaultValue, float step,  SimpleSliderListener listener){
 		this.context = context; 		
 		this.title = title; 		
 		this.maxValue = maxValue;
 		this.minValue = minValue;
 		this.step = step;
 		this.defaultValue = defaultValue; 		
 		this.listener = listener;
 	}
 	 	
	void run(){
		final AlertDialog.Builder alert = new AlertDialog.Builder(context); 

	    //alert.setTitle(title + String.format("%d", defaultValue)); 
	    //alert.setMessage(title + String.format("%d", defaultValue)); 

	    LinearLayout linear=new LinearLayout(context); 
	    linear.setOrientation(LinearLayout.VERTICAL);
	    
	    final TextView text=new TextView(context);
	    text.setTextSize(24);
	    text.setText(String.format("%s %.2f", title, defaultValue)); 
	    text.setPadding(10, 10, 10, 10); 	    
	    
	    final SeekBar seek=new SeekBar(context);
	    seek.setPadding(0, 10, 0, 10);
	    // example:   progress    value  (min=-0.2, max=+0.2, step=0.2)
	    //            0           -0.2
	    //            1           0
	    //            2           +0.2
	    seek.setMax((int)((maxValue-minValue) / step));
	    seek.setProgress((int)((defaultValue-minValue) / step));
	    seek.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
			
			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
			}
			
			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
			}
			
			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				//Log.d("test", "changed ");
				text.setText(String.format("%s %.2f", title, progress * step +minValue));				
			}
		});	    	   
	    
	    final Button buttonPlus = new Button(context);
	    buttonPlus.setTextSize(24);
	    buttonPlus.setText("+");	    
	    final Button buttonMinus = new Button(context);
	    buttonMinus.setText("-");
	    buttonMinus.setTextSize(24);
	    buttonMinus.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {			
				//seek.setProgress(seek.getProgress() - 1);
			}
		});
	    buttonMinus.setOnTouchListener(new OnTouchListener() {			
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				switch(event.getAction()) {
		        case MotionEvent.ACTION_DOWN:
		        	timer.scheduleAtFixedRate(new TimerTask() {
						@Override
						public void run() {							
							seek.setProgress(seek.getProgress() - (int)(timerSteps));
							if (timerSteps < 100) timerSteps ++;
						}
					}, 0, 200);
		            break;
		        case MotionEvent.ACTION_UP:
		        	timer.cancel();
		        	timer = new Timer();
		        	timerSteps = 1;
		            break;
		        }
		        return false;
			}
		});
	    buttonPlus.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {			
				//seek.setProgress(seek.getProgress() + 1);
			}
		});
	    buttonPlus.setOnTouchListener(new OnTouchListener() {			
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				switch(event.getAction()) {
		        case MotionEvent.ACTION_DOWN:
		        	timer.scheduleAtFixedRate(new TimerTask() {
						@Override
						public void run() {																			
							seek.setProgress(seek.getProgress() + (int)(timerSteps));
							if (timerSteps < 100) timerSteps ++;
						}
					}, 0, 200);
		            break;
		        case MotionEvent.ACTION_UP:		        	
		        	timer.cancel();
		        	timer = new Timer();
		        	timerSteps = 1;
		            break;
		        }
		        return false;
			}
		});
	    	    
	    linear.addView(text);
	    linear.addView(seek); 	    
	    linear.addView(buttonPlus);
	    linear.addView(buttonMinus);
	    
	    alert.setView(linear); 


	    alert.setPositiveButton("Ok",new DialogInterface.OnClickListener() 
	    { 
	        public void onClick(DialogInterface dialog,int id)  
	        { 
	            listener.onValueChanged(seek.getProgress() * step +minValue); 
	            
	        } 
	    }); 

	    alert.setNegativeButton("Cancel",new DialogInterface.OnClickListener()  
	    { 
	        public void onClick(DialogInterface dialog,int id)  
	        { 
	            
	        } 
	    }); 

	    alert.create();
	    alert.show(); 			
		
	}
	
	

}

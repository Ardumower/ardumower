/*
 * Android remote control for Arduino 
 * 
 * 1.0 initial version
 *
 * 
 * request by ArduRemote:
 * {.}                                                                       request: get main menu
 * {key}                                                                     request: select menu item 'key'
 * {key`value}                                                               request: change slider to value
 * 
 * response from Arduino:
 * {.title`1000|key1~text1|key2~text2|key3~text3}                            response: create new sub-menu
 * {.title|key~min`value`max`min~unit~scale}                                 response: create menu with slider  
 * {.title|key~min`500`1000`0~unit~0.1}                                      response: create menu with slider 0..100  (scale 0.1)  
 * {.title|key~min`50`100`0~unit~1}                                          response: create menu with slider 0..100  (scale 1)
 * {.title|key~min`5`10`0~unit~10}                                           response: create menu with slider 0..100  (scale 10)
 * {=raw}	                                                                 response: create raw text dialog
 * {=battery`300|min`0|battery V`1|charge V`1|charge A`2|capacity Ah`3}      response: create plot dialog
 * {=battery`300|battery V`1|charge V`1|charge A`2|capacity Ah`3}            response: create plot dialog
 * {=odometry|position`0~~~x|`~~~y}	                                         response: create XY plot dialog
 * {=title`maxPoints|text1`0~max~min~unit| ... }  
 * {^navigate`1000|l~left|r~right|f~forward|b~reverse|s~stop}                response: create navigation menu  
 * {:|key1~Commands|key2~Manual|key3~Settings}                               response: update current menu
 * 
 * 
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

    
 *
 */

package de.grauonline.arduremote;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.DatePickerDialog;
import android.app.Dialog;
import android.app.ListActivity;
import android.app.PendingIntent;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.content.res.AssetFileDescriptor;
import android.content.res.Configuration;
import android.graphics.Color;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.BatteryManager;
import android.os.Bundle;
import android.os.Environment;
import android.preference.PreferenceManager.OnActivityResultListener;
import android.telephony.SmsManager;
import android.text.Html;
import android.text.InputType;
import android.text.TextUtils;
import android.text.format.DateFormat;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.SoundEffectConstants;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ViewFlipper;
import android.widget.ViewSwitcher;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.security.acl.LastOwnerException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.ListIterator;
import java.util.Locale;
import java.util.Map;
import java.util.Set;
import java.util.Stack;
import java.util.Timer;
import java.util.TimerTask;
import java.util.UUID;
import java.util.logging.Logger;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.GraphView.GraphViewData;
import com.jjoe64.graphview.GraphViewSeries;
import com.jjoe64.graphview.GraphViewSeries.GraphViewSeriesStyle;
import com.jjoe64.graphview.GraphViewStyle;
import com.jjoe64.graphview.LineGraphView;

import de.grauonline.arduremote.R.id;

public class ArduRemoteActivity extends ListActivity  {

	private static String TAG = "ArduRemoteActivity";
	private static final int ENABLE_BLUETOOTH_REQUEST = 1;  // The request code
	private static int COLORS[] = { Color.RED, Color.BLUE, Color.GREEN, Color.BLACK, 
		Color.MAGENTA, Color.RED, Color.GRAY, Color.BLUE, Color.GREEN };	

	static final int STATE_CONNECT   = 0;
	static final int STATE_MENU      = 1;
	static final int STATE_PLOT      = 2;	
	static final int STATE_NAVIGATE  = 3;
	static final int STATE_RAW       = 4;
	
		
	private Thread mBluetoothWorker = null;
	private BluetoothDevice mBtDevices[];
	private BluetoothAdapter mBluetoothAdapter = null;
	private BluetoothDevice mBtDevice = null;
	private BluetoothSocket mBtSocket = null;
	private OutputStream mBluetoothOutputStream = null;
	
	//private AudioManager mAudioManager;
	private ViewFlipper mViewFlipper;
	private View mView;
	private ProgressDialog mProgressDialog = null;
	private Timer mTimer = null;
	private int mTimerInterval = 0;
	private boolean mUpdatePageFlag = false;
	private int state = STATE_CONNECT;
    volatile private Stack<ListViewItem> mMenuStack = new Stack<ListViewItem>();	
	private volatile boolean mStopBluetooth = false;	
    private ArrayList<ListViewItem> listItems=new ArrayList<ListViewItem>();    
    private ArrayList<GraphViewSeries> graphDataCol2Series=new ArrayList<GraphViewSeries>();
    private int maxGraphValueCount;
    private int plotCmdCount = 0;
    private ListViewAdapter adapter;        
    private ListViewItem mChosenMenuItem = null;    
    private boolean mStopWaitDlg = false;
	private String mResponse = "";
	private boolean mBackButton = false;
	private boolean mEnableLogging = false;
	volatile private long mLastButtonPressTime = 0;
	//Map<String,String> mTitleIdMap = new HashMap<String,String>(); // menu title->id
	private int testx = 50;	
	private int testy = 50;	
		
    
    
    @Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.d(TAG, "onCreate");
		setContentView(R.layout.activity_main);
		mViewFlipper = (ViewFlipper)findViewById(R.id.viewFlipper);		
	
		//mAudioManager = (AudioManager) this.getSystemService(Context.AUDIO_SERVICE);		
					
		setKeepScreenOn(true);

		if(getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT) {
		    setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
		} else setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);			
						
		adapter = new ListViewAdapter(this, listItems);	
		setListAdapter(adapter);
		
		Timer t = new Timer();
	    t.scheduleAtFixedRate(new TimerTask() {				
			  @Override
			  public void run() {
				if (mUpdatePageFlag) updatePage();	    		
			  }
  	    }, 500, 500);		
	}
    
    	@Override
	protected void onStart() {
		// http://developer.android.com/reference/android/app/Activity.html
		Log.d(TAG, "onStart");		
		super.onStart();		
		
		//toast("started", true);
		startSession();
		
		/*String s = "|j05~Calibrate battery V  `3434`3000`0~ ~|";
    	Pattern p4 = Pattern.compile("([^~]*)~([^`]*)`([^`]*)`([^`]*)`([^~]*)~([^~]*)~([^~]*)"); // key~name`value`max`min~ ~scale 
    	Matcher m4 = p4.matcher(s);
    	if (m4.matches()){  // slider
    	  double value = str2Double(m4.group(3));
    	  double max = str2Double(m4.group(4));
    	  double min = str2Double(m4.group(5));      	    	  
    	  double scale = str2Double(m4.group(7));
    	  toast("" + scale, true);
    	}*/
		
		//Pattern p2 = Pattern.compile("([^`]*)(?:`?)([^~]*)(?:~?)([^~]*)(?:~?)([^~]*)(?:~?)([^~]*)"); // title`idx~max~min~unit 	       	      	    
		 /*
	      * {=battery`300|battery V`1|charge V`1|charge A`2|capacity Ah`3}            response: create plot dialog
	      * {=odometry|position`0~~~x|`~~~y}	                                         response: create XY plot dialog
	      * {=title`maxPoints|text1`0~max~min~unit| ... }   	     
	      */ 	      
	    //Matcher m2 = p2.matcher("title`idx~max~min~unit");
	    //Matcher m2 = p2.matcher("title`idx~max~min");
		//Matcher m2 = p2.matcher("title`idx");
		//Matcher m2 = p2.matcher("title`idx~max"); 		 
		//toast("res="+m2.matches(), true); 
				
		//state = STATE_MENU;
		//mChosenMenuItem = new ListViewItem(".", "");
		//parseResponse("{.}\r\n{.}\r\n");
		//parseResponse("{.menu`1000|t~test|a~abc}");
		//parseResponse("{.menu|t~test|a~abc|c~def}");		
		//parseResponse("{.menu`1000|tt~test|c~abc`500`1000`0~ ~0.1|d~def`50`100`0~ ~1.0|g~ghi`50`100`30~unit~0.01}");
		
		//parseResponse("{.battery`1000|j02~calibrate`2400`3000`0~ ~0.01}");
		
		/*parseResponse("{.Battery|j00~Battery 35.40 V|j01~Monitor YES|j05~Calibrate battery V  `3540`3000`0~ ~0.01|"
				 + "j02~Go home if below `237`293`211~ ~0.1|j03~Switch off if below `217`293`211~ ~0.1|j04~Charge 0.00V 0.00A|"
				+ "j06~Charge sense zero `0`600`400~ ~1|j08~Charge factor `270`1000`0~ ~0.01|j09~for config file:\n" 
			   + "batSenseZero 77.00\n"
			   + "batFactor 0.07}");*/			
		//parseResponse("{^navigate`1000|l~left|r~right|f~forward|b~reverse|s~stop}");
		
		
		//state = STATE_MENU;		
		
	    //parseResponse("{=battery`300|min`0|battery V`1|charge V`2|charge A`3|capacity Ah`4}");
		/*parseResponse("{=battery`128|battery V`1|charge V`2|charge A`3|capacity Ah`4}");
		Timer t = new Timer();	    
	    t.scheduleAtFixedRate(new TimerTask() {				
			  @Override
			  public void run() {
				  String n1 = String.format(Locale.US,  "%.02f", Math.sin(((double)(testx))/25.0*Math.PI) * 10.0); 
				  String n2 = String.format(Locale.US,  "%.02f", Math.sin(((double)(testx))/25.0*Math.PI) * -10.0);
				  String s = n1 + "," + n2 + ",22,-13\n";
				  parseResponse(s);
				  //toast(s, true);
				  testx++;				 
			  }
  	    }, 300, 300);*/
		
		
		/*parseResponse("{=odometry|position`0~~~x|`~~~y}");
		Timer t = new Timer();	    
	    t.scheduleAtFixedRate(new TimerTask() {				
			  @Override
			  public void run() {				  				  
				  parseResponse(String.format(Locale.ENGLISH, "%d,%d\n", testx, testy));
				  if (Math.random() < 0.2) testx++;
				    else testx--;
				  if (Math.random() < 0.2) testy++;
				    else testy--;				  
			  }
  	    }, 300, 300);*/
		
		
		/*parseResponse("{=spectrum`20|freq (Hz)`0|magnitude`0~60~-1|selected band`0~60~-1}");
	    Timer t = new Timer();	    
	    t.scheduleAtFixedRate(new TimerTask() {				
			  @Override
			  public void run() {
				  String s ="";
				  for (int i=0; i < 20; i++){
					  s = "" + i + ","; // freq
					  if (i == 10) s += "" + (int)(Math.random() * 30.0);  // mag
					    else s += "" + i;
					  s += ",5";  // sel band
					  if (i != 19) s += ",";
					  s+="\n";
  					  //toast(s, true);
					  parseResponse(s);
				  }
			  }
	    }, 500, 500);*/
				
	}

	@Override
	protected void onStop() {
		Log.d(TAG, "onStop");
		super.onStop();
		stopSession();		
	}
	
    @Override
    protected void onDestroy() {
    	Log.d(TAG, "onDestroy");    	        		        	   
    	super.onDestroy();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
    	// Inflate the menu; this adds items to the action bar if it is present.
    	getMenuInflater().inflate(R.menu.activity_main, menu);
    	return true;
    }
    
    public boolean onOptionsItemSelected(MenuItem item) {
    	switch (item.getItemId()) {
    	  case R.id.menu_log:
    		 toast("Logging enabled", true);
    		 mEnableLogging = true;
    		 return true; 
          default:
            return super.onOptionsItemSelected(item);
        }
    }
    
    
    
        
    @Override
    protected void onSaveInstanceState(Bundle outState) {   
    	Log.d(TAG, "onSaveInstanceState");
    	super.onSaveInstanceState(outState);    	
    }
    
    @Override
    protected void onRestoreInstanceState(Bundle state) {
    	Log.d(TAG, "onRestoreInstanceState");
    	super.onRestoreInstanceState(state);
    }
	
    private void setKeepScreenOn(boolean flag){
    	mView = getWindow().getDecorView().findViewById(android.R.id.content);    	
    	mView.setKeepScreenOn(flag);    	
    }
    
    private void showNavigationView(final int state){
    	runOnUiThread(new Runnable() {            
			  public void run() {
				  switch (state){
				    case STATE_MENU:
				    	while (mViewFlipper.getCurrentView().getId() != id.listView) mViewFlipper.showNext();
				    	break;				    	
				    case STATE_NAVIGATE:
				    	while (mViewFlipper.getCurrentView().getId() != id.navigateView) mViewFlipper.showNext();
				    	break;
				    case STATE_RAW:				    	
				    	while (mViewFlipper.getCurrentView().getId() != id.textView) mViewFlipper.showNext();
				    	break;
				  }
		}});    	
    }
    
    
    // add new menu to menu stack, setup timer if interval found
    // col:   title`interval
    private boolean registerNewMenu(String col){
    	Log.d(TAG, "registerNewMenu: "+ col);
    	boolean isNewMenu = false;
    	stopTimer();    	    
    	mTimerInterval = 0;    	
    	Pattern p1 = Pattern.compile("([^`]*)(?:`([^`]*))?"); // title[`interval] 
    	Matcher m1 = p1.matcher(col);
    	if (m1.matches()){ 
      	  String title = m1.group(1);
      	  String triggerId = "";
      	  String menuStackTopId = "";
      	  String menuStackTopTitle = "";
      	  if (!mMenuStack.isEmpty()) menuStackTopId = mMenuStack.peek().getId(); 
      	  if (!mMenuStack.isEmpty()) menuStackTopTitle = mMenuStack.peek().getText();
      	  if (mChosenMenuItem != null) triggerId = mChosenMenuItem.getId();
      	  //toast("chosen=" + triggerId + " title=" + title + " topTitle="+ menuStackTopTitle, true);
      	  Log.d(TAG, "triggerId " + triggerId);      	  
      	  if ( menuStackTopId.equals(triggerId) ){
      		Log.d(TAG, "trigger was timer");
      	  } else if (mBackButton){
      		Log.d(TAG, "trigger was back button");
      	    if (!mMenuStack.isEmpty()) mMenuStack.pop();
      		mBackButton = false;
      		isNewMenu = true;
      	  } else {      		
      		Log.d(TAG, "trigger was menu item");      		
      		if (!menuStackTopTitle.equals(title)){      		  
      		  mMenuStack.push(new ListViewItem(triggerId, title));
      		  isNewMenu = true;
      		}
      	  }
          if (m1.group(2) != null){	    	   
        	 mTimerInterval = str2Int(m1.group(2));	    	  	    	    
        	 runTimer();	    	    
          }  		      	  
    	}   
    	return isNewMenu;
    }
    

    public String getONOFFString(boolean flag){
		  if (flag) return "ON";
		    else return "OFF";
		}	

	public String getYESNOString(boolean flag){
		  if (flag) return "YES";
		    else return "NO";
		}	
	
	// button
	ListViewItem setListItem(int idx, String id, String text, double height){	  
      while (listItems.size()  <  idx+1 ) listItems.add(new ListViewItem());
      listItems.get(idx).setId(id);
	  listItems.get(idx).setText(text);
	  listItems.get(idx).setHeight(height);	  
	  listItems.get(idx).setSlider(0,0,0,0);
	  listItems.get(idx).clearSeries();
	  return listItems.get(idx);
	}
	
	// slider
	ListViewItem setListItem(int idx, String id, String text, double height, double value, double min, double max, double scale){
		  while (listItems.size()  <  idx+1 ) listItems.add(new ListViewItem());
		  if (listItems.get(idx).isUpdating()) return listItems.get(idx);
	      listItems.get(idx).setId(id);
		  listItems.get(idx).setText(text);
		  listItems.get(idx).setHeight(height);
		  listItems.get(idx).setSlider(value, min, max, scale);
		  listItems.get(idx).setHeight(height);
		  listItems.get(idx).clearSeries();
		  return listItems.get(idx);
		}		
	
	// graph series
	ListViewItem setListItem(int idx, String text){	  	  
	  while (listItems.size()  <  idx+1 ) listItems.add(new ListViewItem());	  
	  listItems.get(idx).setText(text);
	  listItems.get(idx).setSlider(0,0,0,0);
	  return listItems.get(idx);
    }
	
	
	private void startBluetoothSettings(){
		Intent intentBluetooth = new Intent();
		intentBluetooth.setAction(android.provider.Settings.ACTION_BLUETOOTH_SETTINGS);
		startActivity(intentBluetooth);     		
	}
	
	@Override
	protected void onListItemClick(ListView l, View v, int position, long id) {
		if (System.currentTimeMillis() < mLastButtonPressTime + 500) return;
		mLastButtonPressTime = System.currentTimeMillis(); 			
		//super.onListItemClick(l, v, position, id);
		//mAudioManager.playSoundEffect(SoundEffectConstants.CLICK);					
		ListViewItem item = (ListViewItem)adapter.getItem(position);
		Log.d(TAG, "click " + item.getText());		
		switch (state){
		  case STATE_CONNECT:			  
			if (position < mBtDevices.length){			  
			  mBtDevice = mBtDevices[position];
			  showWaitDialog("Connecting... " + mBtDevice.getName());
			  playSound("scroll3.ogg");
			  connectBluetooth();			  
			  //stopWaitDialog();
			} else if (position == mBtDevices.length){
			  playSound("scroll3.ogg");
			  startBluetoothSettings();			  
			}
			break;
		  case STATE_PLOT:
			break;
		  case STATE_MENU:			
			String resp ;
			if (item.getScale() > 0) { // slider
				//if (!item.isUpdating()){ 
				  resp = "{"+item.getId()+"`" + item.getValue()+ "}"; // slider request
				  //toast(resp, true);
				  //playSound("scroll3.ogg");
				  sendBluetooth("slider request", resp);				  
				  // showWaitDialog("Changing... " + item.getValue());
				//}  				
			} else {								
				resp = "{"+item.getId()+"}";  // menu request
				//toast(item.getText(), false);
				//showWaitDialog("Selecting... " + item.getText());
				mChosenMenuItem = item.clone();			
				playSound("scroll3.ogg");
				sendBluetooth("menu request", resp);				
			}						
			break;
		}
		v.setSelected(true);		
	}
	
	@Override
	public void onBackPressed() {
		if (System.currentTimeMillis() < mLastButtonPressTime + 500) return;
		mLastButtonPressTime = System.currentTimeMillis(); 				
		//mAudioManager.playSoundEffect(SoundEffectConstants.CLICK);		
		stopTimer();				
		playSound("scroll3.ogg");		
		Log.d(TAG, "click back");		
		switch (state){		  
		  case STATE_CONNECT:			  
			finish();
			break;
		  case STATE_NAVIGATE:											
		  case STATE_PLOT:
		  case STATE_RAW:
		  case STATE_MENU:			
			state = STATE_MENU;
			if (mMenuStack.size()<2){
			  mMenuStack.clear();
			  stopSession();			  
			  chooseBluetoothDevice();			  
			} else {			  			  		
			  mChosenMenuItem = mMenuStack.get(mMenuStack.size()-2).clone();
			  String s = "{"+mChosenMenuItem.getId()+"}";
			  //toast(mChosenMenuItem.getText() + " (" + mChosenMenuItem.getId()+ ")", true);
			  //showWaitDialog("Selecting... "+mChosenMenuItem.getText());			  
			  sendBluetooth("back", s);
			  mBackButton = true;
			}				
			break;
		}
		//super.onBackPressed();
	}
	
	 private void toast(final String message, final boolean showLong) {
         runOnUiThread(new Runnable() {
                 @Override
                 public void run() {
                         Context context = getApplicationContext();                         
                         int duration;
                         if (showLong) duration = Toast.LENGTH_LONG;
                           else duration = Toast.LENGTH_SHORT;

                         Toast toast = Toast.makeText(context, message, duration);
                         toast.show();
                 }
         });
    }	
	
    public void showMessage(String msg){
    	AlertDialog ad = new AlertDialog.Builder(this).create();  
    	ad.setCancelable(false);   
    	ad.setMessage(msg);  
    	ad.setButton("OK", new DialogInterface.OnClickListener() {          	     
    	    public void onClick(DialogInterface dialog, int which) {  
    	        dialog.dismiss();                      
    	    }  
    	});  
    	ad.show();
    }
    
    public void sendBluetooth(String debugInfo, String cmd){    	
    	Log.d(TAG, "sendBluetooth "+debugInfo + " :" +cmd);
    	//toast("sending: "+s, true);
    	if (mBluetoothOutputStream == null) return;
    	try {    		
    		mBluetoothOutputStream.write(cmd.getBytes());
			mBluetoothOutputStream.flush();
			logToFile(cmd, true, true);
		} catch (IOException e) {						
			e.printStackTrace();
			stopSession();
			startSession();
		}
    }

	public void startSession(){
		Log.d(TAG, "startSession");
		chooseBluetoothDevice();		
	}	
    
	public void stopSession(){				
		Log.d(TAG, "stopSession");
		stopTimer();
		stopBluetooth();
		state = STATE_CONNECT;		
	}	   
    
    public void stopTimer(){
    	Log.d(TAG, "stopTimer");
    	if (mTimer == null) return;
      	mTimer.cancel();
      	mTimer = null;    	
    }
    
    public void runTimer(){
    	Log.d(TAG, "runTimer");    	
    	if (mTimer != null) return;    	
    	if (mTimerInterval == 0) return;
    	if (mBackButton) return;
    	ListViewItem item = mMenuStack.peek();
    	if (item == null) return;
    	final String reloadCmd = item.getId();    	    
    	mTimer = new Timer();	    	      
	    mTimer.scheduleAtFixedRate(new TimerTask() {				
		    @Override
		    public void run() {				    			  					 		    
		    	sendBluetooth("timer", "{"+reloadCmd+"}");			  
		    }
	      }, mTimerInterval, mTimerInterval);	    
    }
    
    public double str2Double(String s){
    	try {
    		return Double.valueOf(s.trim());
    	} catch (Exception e){
    		return 0;
    	}
    }
    
    public int str2Int(String s){
    	try {
    		return Integer.valueOf(s.trim());
    	} catch (Exception e){
    		return 0;
    	}
    }
    
    public void stopBluetooth(){      
      Log.d(TAG, "stopBluetooth");
      if (mBtSocket == null) return;
      mStopBluetooth = true;
	  if (mBluetoothWorker != null) mBluetoothWorker.interrupt();	  
	  try {
		mBtSocket.close();
	  } catch (IOException e) {
	  }
	  mBtSocket = null;
	  mBluetoothOutputStream = null;	    		      	  
	  toast("disconnected", false);
	  playSound("error2.ogg");
    }    
    

    public void parseMenuCommandColumn(int colIdx, String col, boolean update){
    	//showMessage(col);
	      //Log.d(TAG, "col="+col);
	    if (colIdx == 0){  	    	// first column is menu name    	    		          	  	
	      if (update) {  // menu update
      		if (listItems.size() > 0){ 
      		  String firstCol = listItems.get(0).getText();      		  
      		  setListItem(0, "", firstCol, 1.0);
      		}      		
      	  } else {  // menu create      		      		      		      
      		//toast("cmd="+col, true);
      		registerNewMenu(col);
      		Pattern p1 = Pattern.compile("([^`]*)(?:`([^`]*))?"); // title[`interval] 
	    	Matcher m1 = p1.matcher(col);
	    	if (m1.matches()){ 
	      	  String title = m1.group(1);	      		    	 
	    	  setListItem(0, "", "|"+title+"|", 1.0);
	    	}      		
      	    //if (mTriggerMenuItem != null) mTriggerMenuItem.setText(col);  // we know the menu name, update chosen item	    	
	      }
	    }
	    else { 	    	
	    	Pattern p4 = Pattern.compile("([^~]*)~([^`]*)`([^`]*)`([^`]*)`([^~]*)~([^~]*)~([^~]*)"); // key~name`value`max`min~ ~scale 
	    	Matcher m4 = p4.matcher(col);
	    	if (m4.matches()){  // slider
	    	  double value = str2Double(m4.group(3));
	    	  double max = str2Double(m4.group(4));
	    	  double min = str2Double(m4.group(5));      	    	  
	    	  double scale = str2Double(m4.group(7));
	    	  setListItem(colIdx, m4.group(1), m4.group(2), 1.0, value, min, max, scale);      	    	  
	    	} else {
	    	  Pattern p3 = Pattern.compile("([^~]*)~([^~]*)"); // key~name  
	    	  Matcher m3 = p3.matcher(col);
	    	  if (m3.matches()){   // menu item 
	    	    setListItem(colIdx, m3.group(1), m3.group(2), 1.0);
	    	  }
	    	} 
	    }    	
    }
    
    
    public void parseMenuCommand(String cmd){
    	Log.d(TAG, "parseMenuCommand");
    	boolean update = cmd.startsWith(":");
		cmd = cmd.substring(1);		
		Pattern p2 = Pattern.compile("([^|]*)\\|"); // col|col|col|col
		Matcher m2 = p2.matcher(cmd + "|");
		int colIdx = 0;		
	    while (m2.find()){             	      
	      String col = m2.group(1);
	      parseMenuCommandColumn(colIdx, col, update);    	      
	      colIdx++;
	    }
	    if (!update) {
	      while (listItems.size() > colIdx) listItems.remove(listItems.size()-1);
	    }
	    updatePage();    	
    }
    
    // http://docs.oracle.com/javase/tutorial/essential/regex/quant.html
    public void parsePlotCommand(String cmd){
    	// {=battery`300|min`0|battery V`1|charge V`1|charge A`2|capacity Ah`3}      response: create plot dialog    	    			    	
    	Log.d(TAG, "parsePlotCommand");    	
    	Pattern p1 = Pattern.compile("([^|]*)\\|"); // col|col|col|col
 		Matcher m1 = p1.matcher(cmd + "|");
 		int colIdx = 0; 		
 		listItems.clear();
 		graphDataCol2Series.clear();
 		maxGraphValueCount = 60;
 		plotCmdCount = 0;
 		ListViewItem item = null;
	    GraphViewSeries series = null;
	    int graphIndex = 0; 	      
 	    while (m1.find()){             	      
 	      String col = m1.group(1);
 	      Log.d(TAG, "col "+col);
 	      Pattern p2 = Pattern.compile("([^`]*)(?:`?)([^~]*)(?:~?)([^~]*)(?:~?)([^~]*)(?:~?)([^~]*)"); // title`idx~max~min~unit 	       	       	     
 	     /*
 	      * {=spectrum|freq (Hz)`0|magnitude`0~60~-1|selected band`0~60~-1}
 	      * {=battery`300|battery V`1|charge V`1|charge A`2|capacity Ah`3}            response: create plot dialog
 	      * {=odometry|position`0~~~x|`~~~y}	                                         response: create XY plot dialog
 	      * {=title`maxPoints|text1`0~max~min~unit| ... }   	     
 	      */ 	       	      
 	      Matcher m2 = p2.matcher(col); 	      
  		  if (m2.matches()){             	        	        
  			String title = m2.group(1);  			  		
  			double minY = 0;  			
  			double maxY = 0;
  			boolean useMinY = false;
  			boolean useMaxY = false;
  	        try{
  	        	graphIndex = Integer.parseInt(m2.group(2));
  	        	maxY = Double.parseDouble(m2.group(3));
  	        	useMaxY = true;
  	        	minY = Double.parseDouble(m2.group(4));
  	        	useMinY = true;
  	        } catch (NumberFormatException  e) {  	        	
  	        }
  	        String unit = m2.group(5);
  	        Log.d(TAG, "col " + title + "=" + graphIndex);  	        
  	        if (colIdx == 0){ // first column is title
  	          registerNewMenu(title.substring(1));
  	          if (graphIndex > 0) maxGraphValueCount = graphIndex;
  	        } else {
  	          if (!col.equals("")){   	            
  	        	GraphViewData[] data = new GraphViewData[]{};
  	            int color = COLORS[graphDataCol2Series.size() % COLORS.length];
  	            GraphViewSeriesStyle style = new GraphViewSeriesStyle(color, 2);  	        	   	       
  	            series = new GraphViewSeries(title, style, data);      	      	                  	       
		        item = setListItem(graphIndex, "");
		        if (useMinY) item.setMinY(minY);
		        if (useMaxY) item.setMaxY(maxY);
  	            item.addSeries(series);  	            
  	          }
  	        }
  		  }
  		  if (colIdx != 0) {  			  
  			  graphDataCol2Series.add(series);  			  
  		  }
  	      colIdx++;
  	    }
 	    if (listItems.size() < 3){
 	      for (int i=0; i < listItems.size(); i++) listItems.get(i).setHeight(4); 	    	
 	    }
 	    updatePage();    	 
    }
    
    
    public void parsePlotData(final String resp){           
     runOnUiThread(new Runnable() {            
	  public void run() 
	  {
       Log.d(TAG, "----parsePlotData "+resp);      
       Pattern p1 = Pattern.compile("([^,]*),"); // col,col,col
	   Matcher m1 = p1.matcher(resp + ",");
	   int colIdx = 0;
	   //ArrayList<Double> values=new ArrayList<Double>();
	   double x = plotCmdCount++;	   
	   boolean customX = (listItems.get(0).getSeriesCount() > 0); 
	   Log.d(TAG, "customX=" + customX);
	   while (m1.find()){		  		 
		  Double value = 0.0;
    	  Log.d(TAG, "col=" + m1.group(1));
	      try {
	    	value = str2Double(m1.group(1));  
	      } catch (NumberFormatException e){	    	
	      }
	      if ((customX) && (colIdx == 0)) { 
	    	x = value;
	      } else {
	    	GraphViewSeries series = null;
	    	if (colIdx < graphDataCol2Series.size()) series = graphDataCol2Series.get(colIdx);
			if (series != null){
  	          Log.d(TAG, "appending " + x + "," + value + " maxcount="+maxGraphValueCount);
  	          //toast("appending " + x + "," + " maxcount="+maxGraphValueCount, true);
  	  	  	  series.appendData(new GraphViewData(x, value), false, maxGraphValueCount);
			}
	      }
	      colIdx++;
	   }	    	   
	   mUpdatePageFlag=true;
	  }
	 });
    }
        
    public void setNavigationButton(final Button btn, final TextView text, final String key, final String title) {
    	if (btn == null) return;
    	runOnUiThread(new Runnable() {            
    	  public void run() {
    		  btn.setVisibility(View.VISIBLE);
    		  if (text != null) {
    	    	text.setText(title);
    	    	text.setVisibility(View.VISIBLE);
    	      } else btn.setText(title);    	    	
    	  } 
    	});
    	btn.setOnClickListener(new OnClickListener() {		
			@Override
			public void onClick(View arg0) {
			  playSound("scroll3.ogg");
			  String s = "{"+key+"}";
			  //toast(s, true);
			  sendBluetooth("navigate", s);
			}
		});
    }
    
    public void hideNavigationButtons(){
  	  runOnUiThread(new Runnable() {            
	  	 public void run() {	  	    		
	  		 findViewById(R.id.buttonLeft).setVisibility(View.INVISIBLE);			  
	  		 findViewById(R.id.buttonRight).setVisibility(View.INVISIBLE);
	  		 findViewById(R.id.buttonDown).setVisibility(View.INVISIBLE);
	  		 findViewById(R.id.buttonUp).setVisibility(View.INVISIBLE);
	  		 findViewById(R.id.buttonCenter).setVisibility(View.INVISIBLE);
	  		 findViewById(R.id.textViewLeft).setVisibility(View.INVISIBLE);
	  		 findViewById(R.id.textViewRight).setVisibility(View.INVISIBLE);
	  		 findViewById(R.id.textViewDown).setVisibility(View.INVISIBLE);
	  		 findViewById(R.id.textViewUp).setVisibility(View.INVISIBLE);
	  	 }
  	  });
    }
    
    public void parseNavigationCommand(String cmd){
    	Log.d(TAG, "parseNavigationCommand");
    	//toast(cmd, true);
    	boolean update = cmd.startsWith(":");
		cmd = cmd.substring(1);		
		Pattern p1 = Pattern.compile("([^|]*)\\|"); // col|col|col|col
		Matcher m1 = p1.matcher(cmd + "|");
		int colIdx = 0;		
		while (m1.find()){
		  String col = m1.group(1);
		  if (colIdx == 0){
			  if (!update) {
				  if (registerNewMenu(col)) hideNavigationButtons();
			  }			  
		  } else {
		    Pattern p2 = Pattern.compile("([^~]*)~([^~]*)"); // key~title
		    Matcher m2 = p2.matcher(col);
		    if (m2.matches()){		    					 
			  String key = m2.group(1);
			  String title = m2.group(2);
			  Button btn = null;
			  TextView text = null;
			  switch (colIdx){
			    case 1:
			      btn = (Button)findViewById(R.id.buttonLeft);			      
			      text = (TextView)findViewById(R.id.textViewLeft);
			      break;
			    case 2:
			      btn = (Button)findViewById(R.id.buttonRight);
			      text = (TextView)findViewById(R.id.textViewRight);
			      break;
			    case 3:
			      btn = (Button)findViewById(R.id.buttonUp);
			      text = (TextView)findViewById(R.id.textViewUp);
			      break;
			    case 4:
			      btn = (Button)findViewById(R.id.buttonDown);
			      text = (TextView)findViewById(R.id.textViewDown);
			      break;
			    case 5:
			      btn = (Button)findViewById(R.id.buttonCenter);
				  break;			      
			  }
			  setNavigationButton(btn, text, key, title);
		    }		    
		  }	
		  colIdx++;
		}		
		updatePage();    	
    }
    
    public void parseRawCommand(String cmd){
    	state = STATE_RAW;   
    	String title = cmd.substring(1);
    	registerNewMenu(title);
    	final TextView tv = (TextView)findViewById(R.id.textView1);
    	runOnUiThread(new Runnable() {            
      	  public void run() {
      		tv.setText("");
      	  }
    	});    	
    	updatePage();
    }
    
    public void parseRawData(final String resp){           
       Log.d(TAG, "----parseRawData "+resp);      
       final TextView tv = (TextView)findViewById(R.id.textView1);
       runOnUiThread(new Runnable() {            
       	  public void run() {
       		tv.setText(tv.getText() + resp);
       	  }
     	});       
       updatePage();
     }
         
    
    // http://developer.android.com/reference/java/util/regex/Pattern.html
    public void parseMenuResponse(String resp){      
      Log.d(TAG, "----parseMenuResponse "+resp);
      //toast(resp, true);
      Pattern p1 = Pattern.compile("\\{([^}]*)\\}");  // command {  }
      Matcher m1 = p1.matcher(resp);      
      while (m1.find()){   // find next command               
    	String cmd = m1.group(1);    	
    	Log.d(TAG, "cmd="+cmd);    	
		//showMessage(cmd);    	
    	if ( (cmd.startsWith(".")) || ((cmd.startsWith(":")) && (state == STATE_MENU)) ){    // create/update menu {.}  {:} 
    		state = STATE_MENU;
    		parseMenuCommand(cmd);    		
    	} else if (cmd.startsWith("=")){
    		if (cmd.contains("|")){
    		  state = STATE_PLOT;     		
    		  parsePlotCommand(cmd);
    		} else {
    		  state = STATE_RAW;
    		  parseRawCommand(cmd);
    		}
    	} else if ( (cmd.startsWith("^")) || ((cmd.startsWith(":")) && (state == STATE_NAVIGATE)) ){
    		state = STATE_NAVIGATE;
    		parseNavigationCommand(cmd);
    	}
      }    			  			    
    }
    
    
    public boolean parseResponse(String resp){
    	switch (state){
    	  case STATE_RAW:
    		if (resp.endsWith("\n")){
    		  logToFile(resp, false, true);
    		  parseRawData(resp);
    		  return true;
    	     }
    		 break;    		 
		  case STATE_MENU:
		  case STATE_NAVIGATE:
			if (resp.endsWith("}")){  		    		  			   
			  //toast("cmd="+resp, true);			
			  logToFile(resp, false, true);
			  parseMenuResponse(resp);
	    	  return true;
	    	}
			break;
		  case STATE_PLOT:
			if (resp.endsWith("\n")){
			  logToFile(resp, false, true);
			  parsePlotData(resp);
		      return true;
	    	}
			break;
    	}
    	return false;
    }
        
    
    public void startBluetoothReading(){
      mBluetoothWorker = new Thread(new Runnable()
  	  {
  	     public void run()
  	     {  	        
  	        try {	  	            	            	         
  		      logToFile("connected to " + mBtDevice.getName(), true, false);
  	          mBluetoothOutputStream = mBtSocket.getOutputStream();
  		      InputStream is = mBtSocket.getInputStream();
  		      String s = "{.}";
  		      mChosenMenuItem = new ListViewItem(".", "");  		     
  		      Thread.sleep(700);
  		      sendBluetooth("main menu", s);  		        		        		     
  		      while ( (!Thread.currentThread().isInterrupted()) && (!mStopBluetooth) ) {  		    	
  		    	if (is.available() > 0){
  		    		int ch = is.read();
  		    		mResponse += Character.toString((char)ch);  		    		  		    	      			  	       
  			  	    if (parseResponse(mResponse)) mResponse = "";  			  	      
  		    	} else Thread.sleep(100);		    	  
  		      }  		        		    
  		    } catch (IOException e) {		        		      
  	       	  e.printStackTrace();  	       	  
  	       	} catch (InterruptedException e) {  	       	
  	       	  e.printStackTrace();  	       	  
  			}
  	        Log.d(TAG, "leaving bluetoothWorker...");
  	        stopSession();
  	        startSession();
  	    }
       });
       mBluetoothWorker.start();        	
     }

      
      /* BT types   http://stackoverflow.com/questions/5401445/android-bluetooth-pairing/5408118#5408118
       * pre 2.1  - PIN entry mechanism  (0000 or 1234)
       * 2.1      - Secure Simple Pairing (SSP): 
       *              a)  6 digit passkey:  "createRfcommSocket"
       *              b)  without user intervention: "createInsecureRfcommSocket"
       *                                             "createInsecureRfcommSocketToServiceRecord"
       *  $adb shell hcidump -XVt will show you the log. If I/O capabiltiies are being exchanged than its Bluetooth 2.1 pairing.
       *  BluetoothSocket_MTK   JSR82
       */
      
      private BluetoothSocket createBluetoothSocket(BluetoothDevice device) {    	
      	UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb"); //Standard SerialPortService ID
      	// if (Build.VERSION.SDK_INT >= 10){
      	for (int i=0; i < 3; i++){
            try {        		        	 
          	  //Method  m = device.getClass().getMethod("createInsecureRfcommSocketToServiceRecord", new Class[] { UUID.class });
          	  //BluetoothSocket tmp = (BluetoothSocket)m.invoke(device, uuid);
          	  BluetoothSocket tmp = device.createRfcommSocketToServiceRecord(uuid);        	  
  		       //m = device.getClass().getMethod("createRfcommSocket", new Class[] {int.class});
          	   //Method m = device.getClass().getMethod("createInsecureRfcommSocket", new Class[] {int.class});
  			   //BluetoothSocket tmp = (BluetoothSocket) m.invoke(device, 1);
      		if (tmp != null){    			
      			tmp.connect();
      			mBtSocket = tmp;
      			return tmp;
      		}    		
      	  } catch (IOException e) {
      		Log.d(TAG, e.getMessage());
      		try {
  				Thread.sleep(100);
  			} catch (InterruptedException e1) {
  			}
      	  }/* catch (NoSuchMethodException e) {
  		} catch (IllegalAccessException e) {
  		} catch (IllegalArgumentException e) {
  		} catch (InvocationTargetException e) {
  		}    */      
      	}
      	return null;
      }

      
      @Override
      protected void onActivityResult(int requestCode, int resultCode, Intent data) {    	
    	super.onActivityResult(requestCode, resultCode, data);
    	 if (requestCode == ENABLE_BLUETOOTH_REQUEST) {
    	   if (resultCode == RESULT_OK) {
    		 chooseBluetoothDevice(); 
    	   } else { 
    	     setResult(RESULT_CANCELED);
    		 finish();
    	   } 
        } 
      }

      public void chooseBluetoothDevice(){
    	//toast("choose BT device", true);
      	if (mBtSocket != null) return;    
      	state = STATE_CONNECT;
      	mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();      	
      	if(!mBluetoothAdapter.isEnabled())
      	{
      	   Log.d(TAG, "BT not enabled");
      	   Intent enableBluetooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
      	   startActivityForResult(enableBluetooth, ENABLE_BLUETOOTH_REQUEST);
      	   return;      	   
      	}    	
      	Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
      	String[] list = new String[pairedDevices.size()];
      	mBtDevices = new BluetoothDevice[pairedDevices.size()];	
      	int idx = 0;
      	for(BluetoothDevice bt : pairedDevices){
       	   list[idx] = bt.getName();
       	   mBtDevices[idx] = bt;
       	   idx++;
      	}
      	updatePage();
      }
      	
      	
      public void connectBluetooth(){      		    	   
    	  Timer t = new Timer();
  	      t.schedule(new TimerTask() {				
  			  @Override
  			  public void run() {
  				mStopBluetooth = false;
	      	    Log.d(TAG, "connectBluetooth " + mBtDevice.getName());  			
	    		if (createBluetoothSocket(mBtDevice) == null){    	      
	    		  stopWaitDialog();
	    		  toast("Error: cannot connect to " + mBtDevice.getName(), false);
	    		  playSound("error2.ogg");
	    		  return;
	    		}
	    		stopWaitDialog();
	    		toast("connected to "+mBtDevice.getName(), false);
	  			//btOutputStream = btSocket.getOutputStream();
	    		state = STATE_MENU;
	    		startBluetoothReading();	    		
  			  }
    	  }, 500);
      }
                      
      
      
    public String getMenuPath(boolean includeIds){
      String path = "";
      Iterator<ListViewItem> iter = mMenuStack.iterator();
	  while (iter.hasNext()){
	    ListViewItem item = iter.next(); 
	    path += item.getText();
	    if (includeIds) path += "(" +item.getId() + ")";
	    path += "/"; 
	  }
	  return path;  	
    }

	public void updatePage(){
		  mUpdatePageFlag = false;
		  runOnUiThread(new Runnable() {            
	  	    public void run() {	  	    	
	  	    	Log.d(TAG, "updatePage state="+state);
	  	    	Log.d(TAG, "path="+getMenuPath(true));
	  	    	stopWaitDialog();
	  	    	switch (state){
	  	          case STATE_CONNECT:
	  	        	showNavigationView(STATE_MENU);
	  	        	setTitle(getResources().getString(R.string.app_name) + ":  Choose paired BT device");
	  	        	listItems.clear();
	  	        	if (mBtDevices != null) {
	  	        	  for (int i=0; i < mBtDevices.length; i++){	  	        		
	  	        		if (mBtDevices[i] != null) setListItem(i, mBtDevices[i].getAddress(), mBtDevices[i].getName(), 2.0);	  	        		
	  	        	  }
	  	        	  setListItem(listItems.size(), "", "BT config >", 2.0);
	  	        	}
	  	    	    break;
	  	          case STATE_MENU:
	  	        	setTitle(getResources().getString(R.string.app_name) + ":  " + getMenuPath(false));
	  	        	showNavigationView(STATE_MENU);	  	        	
	  	        	break;
	  	          case STATE_PLOT:
	  	        	setTitle(getResources().getString(R.string.app_name) + ":  " + getMenuPath(false));
	  	        	showNavigationView(STATE_PLOT);	  	        	
	  	        	break;
	  	          case STATE_NAVIGATE:
	  	        	setTitle(getResources().getString(R.string.app_name) + ":  " + getMenuPath(false));
	  	        	showNavigationView(STATE_NAVIGATE);
	  	        	break;
	  	          case STATE_RAW:
	  	        	setTitle(getResources().getString(R.string.app_name) + ":  " + getMenuPath(false));
	  	        	showNavigationView(STATE_RAW);
	  	        	break;
	  	        }
	  		    adapter.notifyDataSetChanged();	  		  
	  	    }   	        	    
	  	  });
		}
	

	public void playSound(String fileName){
	  AssetFileDescriptor afd;
	  try {
		afd = getAssets().openFd(fileName);
		MediaPlayer player = new MediaPlayer();
		//player.setAudioStreamType(AudioManager.STREAM_ALARM);
		player.setDataSource(afd.getFileDescriptor(),afd.getStartOffset(),afd.getLength());
		player.prepare();
		player.start();
	  } catch (IOException e) {
		  //toast(e.getMessage());
		 //e.printStackTrace();
	  }	   	   	  	 
	}

	void stopWaitDialog(){
		mStopWaitDlg = true;
		if (mProgressDialog != null) {
			mProgressDialog.dismiss();
			mProgressDialog = null;
		}
	}

	void showWaitDialog(final String text){
	   runOnUiThread(new Runnable() {            
		public void run() {	  	    			 	
		  mProgressDialog = new ProgressDialog(ArduRemoteActivity.this);
          mProgressDialog.setMessage(text);
          mProgressDialog.setCancelable(false);
          mProgressDialog.show();
          Timer t = new Timer();
  	      t.schedule(new TimerTask() {				
  			  @Override
  			  public void run() {
  				  stopWaitDialog();
  			  }
    	  }, 20000);
		}});
	}
	
	public void logToFile(String cmd, boolean isSendCmd, boolean append){
		if (!mEnableLogging) return;
		try {	        
		  Date now = new Date();
		  String filename = "comm_" + DateFormat.format("yyyy_MM_dd", now).toString() + ".txt";
		  //String filename = "comm.txt";
		  File folder = new File(Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "ArduRemote");
		  if (!folder.exists()){
			folder.mkdirs();
		  }					  				       
          CharSequence time = DateFormat.format("hh:mm:ss", now);
          String dir;
          if (isSendCmd) dir = "OUT";
            else dir = "IN";                    		   
          String line = "" + time + ", " + dir + ", " +  cmd + "<br><br>\n\n";
          File file = new File(folder, filename);
          //if (file.length() > 5000000) append = false;
          FileOutputStream f = new FileOutputStream(file, true);          
          f.write(line.getBytes());
          f.close();
        } catch (Exception e) {
          //toast(e.getMessage(), true);
        }
	}
	
    
}
   
   
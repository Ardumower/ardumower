import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.util.Stack; 
import java.util.regex.*; 
import processing.serial.*; 
import processing.net.*; 
import java.util.Iterator; 
import java.util.ArrayList; 
import java.util.ArrayList; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class processing_remote extends PApplet {

/*
 * pfodApp-compatible remote control for PC (to be run in 'Processing 3')  
 * 
 * 0.1 initial version
 *
 * 
 * request by PCRemote:
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
 * {=raw}	                                                                   response: create raw text dialog
 * {=battery`300|min`0|battery V`1|charge V`1|charge A`2|capacity Ah`3}      response: create plot dialog
 * {=battery`300|battery V`1|charge V`1|charge A`2|capacity Ah`3}            response: create plot dialog
 * {=odometry|position`0~~~x|`~~~y}	                                   response: create XY plot dialog
 * {=title`maxPoints|text1`0~max~min~unit| ... }  
 * {^navigate`1000|l~left|r~right|f~forward|b~reverse|s~stop}                response: create navigation menu  
 * {:|key1~Commands|key2~Manual|key3~Settings}                               response: update current menu
 * 
 * 
 *    
 */
 






// configuration
String comPort = "COM9";
int comBaud = 19200;
boolean useTcp = false;
String tcpHost = "raspberrypi.local";
//String tcpHost = "localhost";
int tcpPort = 8083;
boolean demo = false;


  static final int STATE_CONNECT   = 0;
  static final int STATE_MENU      = 1;
  static final int STATE_PLOT      = 2;  
  static final int STATE_NAVIGATE  = 3;
  static final int STATE_RAW       = 4;

  private int nextStartMenuRequest = 6000;
  private int state = STATE_CONNECT;
  Serial mySerial;
  Client myTcp;
  private boolean started = false;
  private int maxGraphValueCount;
  private int plotCmdCount = 0;
  int serialLinesReceived = 0;
  private String mReloadCmd = "";
  private int mTimerInterval = 0;
  private int mNextReloadCmdTime=0;
  private boolean mBackButton = false;
  private ListViewItem mChosenMenuItem = null;  
  private MainView mMainView = null;
  private ListView mListView = null;
  private NavigationView mNavigationView = null;
  private boolean mUpdatePageFlag = false;
  private View lastPressedView = null;
  volatile private StringBuilder mResponse = new StringBuilder();
  private boolean mNeedsDraw = true;
  private int rawDataLines = 0;
  volatile private Stack<ListViewItem> mMenuStack = new Stack<ListViewItem>();
  private ArrayList<FloatList> graphDataCol2Series=new ArrayList<FloatList>();

  PFont pf;
  int drawCounter = 0;
  
  
  public float str2Float(String s){
  try {
        return Float.valueOf(s.trim());
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
 
 
  public void logToFile(String cmd, boolean isSendCmd, boolean append){
  }
  
  
  public void stopSession(){        
    println("stopSession");
    stopTimer();
    stopComm();
    state = STATE_CONNECT;    
  } 
  
  public void stopComm(){      
    println("stopPort");
    if ((mySerial == null) && (myTcp == null)) return;    
    if (useTcp) myTcp.stop();
      else mySerial.stop();    
    mySerial = null;
    myTcp = null;
  }    
    
   
  public void parseRawData(final String resp){
     println("----parseRawData "+resp);      
     mListView.setListItem(rawDataLines, "", resp, 1.0f);
     rawDataLines++;              
     updatePage();        
  }  
  
  // http://docs.oracle.com/javase/tutorial/essential/regex/quant.html
  public void parsePlotCommand(String cmd){
    // {=battery`300|min`0|battery V`1|charge V`1|charge A`2|capacity Ah`3}      response: create plot dialog                      
    println("parsePlotCommand");      
    Pattern p1 = Pattern.compile("([^|]*)\\|"); // col|col|col|col
    Matcher m1 = p1.matcher(cmd + "|");
    int colIdx = 0;     
    mListView.contentView.removeChildren();
    graphDataCol2Series.clear();
    maxGraphValueCount = 60;
    plotCmdCount = 0;
    ListViewItem item = null;   
    FloatList series = null;
    int graphIndex = 0;         
    while (m1.find()){                     
       String col = m1.group(1);
       println("col "+col);
       Pattern p2 = Pattern.compile("([^`]*)(?:`?)([^~]*)(?:~?)([^~]*)(?:~?)([^~]*)(?:~?)([^~]*)"); // title`idx~max~min~unit                          
        /*
         * {=spectrum|freq (Hz)`0|magnitude`0~60~-1|selected band`0~60~-1}
         * {=battery`300|battery V`1|charge V`1|charge A`2|capacity Ah`3}            response: create plot dialog
         * {=odometry|position`0~~~x|`~~~y}                                           response: create XY plot dialog
         * {=title`maxPoints|text1`0~max~min~unit| ... }          
         */                  
       Matcher m2 = p2.matcher(col);         
       if (m2.matches()){                                 
         String title = m2.group(1);              
         float minY = 0;        
         float maxY = 0;
         boolean useMinY = false;
         boolean useMaxY = false;
         try{
              graphIndex = Integer.parseInt(m2.group(2));
              maxY = Float.parseFloat(m2.group(3));
              useMaxY = true;
              minY = Float.parseFloat(m2.group(4));
              useMinY = true;
         } catch (NumberFormatException  e) {              
         }
         String unit = m2.group(5);
         println("col " + title + "=" + graphIndex);            
         if (colIdx == 0){ // first column is title
              registerNewMenu(title.substring(1));
              if (graphIndex > 0) maxGraphValueCount = graphIndex;
              println("maxGraphValueCount="+maxGraphValueCount);
         } else {
            if (!col.equals("")){                 
              series = new FloatList();
              int colorIdx = graphDataCol2Series.size();
              item = mListView.setListItem(graphIndex, "");
              item.setColorIdx(colorIdx);
              if (useMinY) item.setMinY(minY);
              if (useMaxY) item.setMaxY(maxY);
              item.addSeries(title, series);
              item.setHeight(80);
            }
        }
      }
      if (colIdx != 0) {          
        graphDataCol2Series.add(series);          
      }
      colIdx++;
   }
   /*if (listItems.size() < 3){
     for (int i=0; i < listItems.size(); i++) listItems.get(i).setHeight(4);         
   }*/
   updatePage();       
 }
    
    
public void parsePlotData(final String resp){           
  println("----parsePlotData "+resp);      
  Pattern p1 = Pattern.compile("([^,]*),"); // col,col,col
  Matcher m1 = p1.matcher(resp + ",");
  int colIdx = 0;
     //ArrayList<Double> values=new ArrayList<Double>();
  float x = plotCmdCount++;     
  boolean customX = ((ListViewItem)mListView.contentView.getChild(0)).getSeriesCount() > 0; 
  //println("customX=" + customX);
  while (m1.find()){           
    float value = 0.0f;
    //println("col=" + m1.group(1));
    try {
      value = str2Float(m1.group(1));  
    } catch (NumberFormatException e){        
    }
    if ((customX) && (colIdx == 0)) { 
      x = value;
    } else {
      FloatList series = null;
      if (colIdx < graphDataCol2Series.size()) series = graphDataCol2Series.get(colIdx);
      if (series != null){
         //println("appending " + x + "," + value + " maxcount="+maxGraphValueCount);                    
         series.append(value);
         if (series.size() > maxGraphValueCount) series.remove(0);         
      }
    }
    colIdx++;
  }           
  mUpdatePageFlag=true;
 }
 
    
  public void parseRawCommand(String cmd){
      println("parseRawCommand "+cmd);
      state = STATE_RAW ;   
      String title = cmd.substring(1);
      registerNewMenu(title);           
      updatePage();
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
  
  public void runTimer(){
      println("runTimer" + mTimerInterval);      
      //if (mTimer != null) return;      
      if (mTimerInterval == 0) return;
      if (mBackButton) return;
      ListViewItem item = null;
      if (!mMenuStack.empty()) item = mMenuStack.peek();
      if (item == null) return;
      mReloadCmd = item.getId();
      mNextReloadCmdTime = millis() + mTimerInterval;           
  }
  
  public void stopTimer(){
      println("stopTimer");
      mNextReloadCmdTime = 0;      
  }
  
  // add new menu to menu stack, setup timer if interval found
  // col:   title`interval
  private boolean registerNewMenu(String col){
      //println("registerNewMenu: "+ col);
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
          println("triggerId " + triggerId);          
          if ( menuStackTopId.equals(triggerId) ){
            println("trigger was timer "+millis());
          } else if (mBackButton){
            println("trigger was back button");
            if (!mMenuStack.isEmpty()) mMenuStack.pop();
            mBackButton = false;
            isNewMenu = true;
          } else {          
            println("trigger was menu item");          
            if (!menuStackTopTitle.equals(title)){
              ListViewItem li = new ListViewItem(0,0);
              li.setId(triggerId);
              li.setText(title);
              mMenuStack.push(li);
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
      
  public void hideNavigationButtons(){
  }
  
  
  public void parseNavigationCommand(String cmd){
    //println("parseNavigationCommand");    
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
        //TextView text = null;
        switch (colIdx){
          case 1:
            btn = mNavigationView.getLeftButton();            
            //text = (TextView)findViewById(R.id.textViewLeft);
            break;
          case 2:
            btn = mNavigationView.getRightButton();
            //text = (TextView)findViewById(R.id.textViewRight);
            break;
          case 3:
            btn = mNavigationView.getUpButton();
            //text = (TextView)findViewById(R.id.textViewUp);
            break;
          case 4:
            btn = mNavigationView.getDownButton();
            //text = (TextView)findViewById(R.id.textViewDown);
            break;
          case 5:
            btn = mNavigationView.getCenterButton();
            break;            
          }        
        if (btn != null) {          
          btn.setText(title);
          btn.setKey(key);
        }
      }
    }  
    colIdx++;
  }    
  updatePage();      
}
    

  public void parseMenuCommand(String cmd){
    //println("parseMenuCommand");    
    boolean update = cmd.startsWith(":");
    if (!update) mListView.contentView.removeChildren();
    cmd = cmd.substring(1);    
    Pattern p2 = Pattern.compile("([^|]*)\\|"); // col|col|col|col
    Matcher m2 = p2.matcher(cmd + "|");
    int colIdx = 0;    
      while (m2.find()){                     
        String col = m2.group(1);
        parseMenuCommandColumn(colIdx, col, update);            
        colIdx++;
      }
      /*i f (!update) {        
        while (mListView.contentView.childrenCount() > colIdx) mListView.contentView.removeChild(mListView.contentView.childrenCount()-1);
      }*/
      updatePage();      
  }
    
  public void parseMenuCommandColumn(int colIdx, String col, boolean update){
      if (colIdx == 0){          // first column is menu name                              
        if (update) {  // menu update
          if (mListView.childrenCount() > 0){ 
            String firstCol = ((ListViewItem)mListView.contentView.getChild(0)).getText();            
            mListView.setListItem(0, "", firstCol, 1.0f);
          }          
        } else {  // menu create                                    
          //toast("cmd="+col, true);
          registerNewMenu(col);
          Pattern p1 = Pattern.compile("([^`]*)(?:`([^`]*))?"); // title[`interval] 
          Matcher m1 = p1.matcher(col);
          if (m1.matches()){ 
            String title = m1.group(1);                   
            mListView.setListItem(0, "", "|"+title+"|", 1.0f);
          }          
          //if (mTriggerMenuItem != null) mTriggerMenuItem.setText(col);  // we know the menu name, update chosen item        
        }
      }
      else {         
        Pattern p4 = Pattern.compile("([^~]*)~([^`]*)`([^`]*)`([^`]*)`([^~]*)~([^~]*)~([^~]*)"); // key~name`value`max`min~ ~scale 
        Matcher m4 = p4.matcher(col);
        if (m4.matches()){  // slider
          float value = str2Float(m4.group(3));
          float max = str2Float(m4.group(4));
          float min = str2Float(m4.group(5));                
          float scale = str2Float(m4.group(7));          
          mListView.setListItem(colIdx, m4.group(1), m4.group(2), 1.0f, value, min, max, scale);                
        } else {
          Pattern p3 = Pattern.compile("([^~]*)~([^~]*)"); // key~name  
          Matcher m3 = p3.matcher(col);
          if (m3.matches()){   // menu item 
            mListView.setListItem(colIdx, m3.group(1), m3.group(2), 1.0f);
          }
        } 
      }      
    }
    
        
  public void parseMenuResponse(String resp){
    println("----parseMenuResponse "+resp);    
    Pattern p1 = Pattern.compile("\\{([^}]*)\\}");  // command {  }
    Matcher m1 = p1.matcher(resp);      
    while (m1.find()){   // find next command               
      String cmd = m1.group(1);      
      println("cmd="+cmd);               
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
    //println("parseResponse "+resp);
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
        resp = resp.trim();
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

  
  
public void sendData(String text, String data){
  println("sendData: "+text + ":" + data);
  if (demo) return;
  for (int i=0; i < data.length(); i++) {
    if (useTcp) myTcp.write( (int)data.charAt(i) );
      else mySerial.write( (int)data.charAt(i) );
      //delay(20);
  }
}
     

public void sendNavigation(View view){
  String s = "{"+view.key+"}";        
  sendData("navigate", s);
}


public void setup(){
  try{       
    pf = createFont("Arial Bold",14,true);
    textFont(pf,20);  
    
    mMainView = new MainView(600, 700);
    mListView = mMainView.getListView();
    mNavigationView = mMainView.getNavigationView();
    mMainView.setLeft(20);
    
    mNavigationView.getUpButton().setEventHandler( new EventHandler() {
        public void mousePressedEvent(View view){
          sendNavigation(view);
        }
    });
    mNavigationView.getDownButton().setEventHandler( new EventHandler() {
        public void mousePressedEvent(View view){
          sendNavigation(view);
        }
    });              
    mNavigationView.getLeftButton().setEventHandler( new EventHandler() {
        public void mousePressedEvent(View view){
          sendNavigation(view);
        }
    });              
    mNavigationView.getRightButton().setEventHandler( new EventHandler() {
        public void mousePressedEvent(View view){
          sendNavigation(view);
        }
    });
    mNavigationView.getCenterButton().setEventHandler( new EventHandler() {
        public void mousePressedEvent(View view){
          sendNavigation(view);
        }
    });
    
      
    if (demo){
      state = STATE_MENU;
      //parseResponse("{=logging}");  
      //parseResponse("{=plot|time min`0|battery V`1|charge V`1|charge A`2|capacity Ah`3|capacity Ah`4|capacity Ah`5|capacity Ah`6|capacity Ah`7|capacity Ah`8|capacity Ah`9}");   
      parseResponse("{.menu|j00~Battery 35.40 V|j01~Monitor YES\nbla bla|j05~Calibrate battery V  `3540`3000`0~ ~0.01|"
           + "j02~Day `3`6`0~ ~1|j03~Switch off if below `217`293`211~ ~0.1|j04~Charge 0.00V 0.00A|"
           + "j02~Scale-10..10/1 `5`10`-10~ ~1.0|j03~Scale-1000..1000/0.1 `500`1000`-1000~ ~0.1|j04~Charge 0.00V 0.00A|"
           + "j02~Scale-10..10/0.1 `5`10`-10~ ~0.1|j03~Switch off if below `217`293`211~ ~0.1|j04~Charge 0.00V 0.00A|"
           + "j02~Go home if below `237`293`211~ ~0.1|j03~Switch off if below `217`293`211~ ~0.1|j04~Charge 0.00V 0.00A|"
           + "j02~Go home if below `237`293`211~ ~0.1|j03~Switch off if below `217`293`211~ ~0.1|j04~Charge 0.00V 0.00A|"
           + "j02~Go home if below `237`293`211~ ~0.1|j03~Switch off if below `217`293`211~ ~0.1|j04~Charge 0.00V 0.00A|"
           + "j02~Go home if below `237`293`211~ ~0.1|j03~Switch off if below `217`293`211~ ~0.1|j04~Charge 0.00V 0.00A|"
           + "j06~Charge sense zero `0`600`400~ ~1|j08~Charge factor `270`1000`0~ ~0.01|j09~for config file:" 
           + "batSenseZero 77.00|"         
           + "j06~Charge sense zero `0`600`400~ ~1|j08~Charge factor `270`1000`0~ ~0.01|j09~for config file|"
           + "j06~Charge sense zero `0`600`400~ ~1|j08~Charge factor `270`1000`0~ ~0.01|j09~for config file|"
           + "j06~Charge sense zero `0`600`400~ ~1|j08~Charge factor `270`1000`0~ ~0.01|j09~for config file|"
           + "j06~Charge sense zero `0`600`400~ ~1|j08~Charge factor `270`1000`0~ ~0.01|j09~for config file|"
           + "batFactor 0.07}");
    } else {          
      if (useTcp) {
        connectDevice();
      } else {
        chooseDevice();
      }
    }
    mMainView.dump("");    
  } 
  catch (Exception e){
    javax.swing.JOptionPane.showMessageDialog(null, "Error: "+e);
    print("EX: "+e);
  }  
  
       
  started = true;
}

public void connectDevice(){
  if (useTcp){
    println("connectDevice "+tcpHost + ":" + tcpPort);
    myTcp =  new Client(this, tcpHost, tcpPort);
  } else {
    println("connectDevice "+comPort + " " + comBaud);
    mySerial = new Serial(this, comPort, comBaud, 'N', 8, 1);
    mySerial.buffer(1);
  }
    //port.bufferUntil('}');  
    //delay(2000);      
    //port.clear();  
  state = STATE_MENU;
  //delay(6000);    // wait 6s for connection to establish
  requestStartMenu();
}

public void chooseDevice(){
  if ((mySerial != null) || (myTcp != null)) return;    
  state = STATE_CONNECT;
  updatePage();
}


public void requestStartMenu(){
   String s = "{.}";
   mChosenMenuItem = new ListViewItem(0,0);
   mChosenMenuItem.setId(".");
   mChosenMenuItem.setText("");
   if ((!demo) && (!useTcp)) mySerial.clear();
   sendData("request main menu", s);
}

public void onListItemClick(ListViewItem item){
  println("click: "+item);
  switch (state){
    case STATE_CONNECT:              
      if (item.idx < Serial.list().length){        
        comPort = Serial.list()[item.idx];               
        surface.setTitle("Connecting...");
        connectDevice();       
      }
      break;
    case STATE_PLOT:
      break;
    case STATE_MENU:      
      String resp ;
      if (item.getScale() > 0) { // slider
        //if (!item.isUpdating()){ 
          resp = "{"+item.getId()+"`" + item.getValue()+ "}"; // slider request        
          sendData("slider request", resp);                    
        //}          
      } else {                
        resp = "{"+item.getId()+"}";  // menu request        
        mChosenMenuItem = item.clone();              
        sendData("menu request", resp);        
      }            
      break;
    }       
}


public void onBackPressed() {
    //if (System.currentTimeMillis() < mLastButtonPressTime + 500) return;
    //mLastButtonPressTime = System.currentTimeMillis();                
    stopTimer();               
    println("click back");    
    switch (state){      
      case STATE_CONNECT:        
      //finish();
      break;
      case STATE_NAVIGATE:                      
      case STATE_PLOT:
      case STATE_RAW:
      case STATE_MENU:      
      state = STATE_MENU;
      if (mMenuStack.size()<2){
        mMenuStack.clear();
        stopSession();        
        chooseDevice();        
      } else {                    
        mChosenMenuItem = mMenuStack.get(mMenuStack.size()-2).clone();
        String s = "{"+mChosenMenuItem.getId()+"}";               
        sendData("back", s);
        mBackButton = true;
      }        
      break;
    }    
}
  
   
public void draw(){
  if (!started) return;
  
  if (myTcp != null){
    while (myTcp.available() > 0) {           
      char ch = myTcp.readChar();
      processDataReceived(ch);      
    }      
  }  
  if (drawCounter == 0){
    frame.setLocation(40, 0);
    drawCounter++;
  }
  if (mNeedsDraw) {
    // background(127);
    mMainView.draw();
    mNeedsDraw = false;
  }
  
  View view = (mMainView.getMousePressRecursive());
  if (view != lastPressedView){
    if (view != null){                 
      if (view instanceof ListViewItem){
        onListItemClick((ListViewItem)view);
      } 
      else if (view == mMainView.getBackButton()){
        onBackPressed();  
      }
    }
    lastPressedView = view;
  }
  
  if ((demo) && ((state == STATE_RAW) ||(state == STATE_PLOT)) ) {    
    String s = str(Math.round(millis()/1000)) + "," + str(random(100))  + "," + str(random(100))  + "," + str(random(100))  + "," + str(random(100))
     + "," + str(random(100))  + "," + str(random(100))  + "," + str(random(100))  + "," + str(random(100))
      + "," + str(random(100))  + "," + str(random(100)) 
       + "\n";
    mResponse.append( s );
    delay(50);
  }
  
  // timer
  if ((mNextReloadCmdTime != 0) && (millis() >= mNextReloadCmdTime)){
    mNextReloadCmdTime = millis() + mTimerInterval;   
    sendData("timer", "{"+mReloadCmd+"}");        
  }
}


public void mousePressed(){  
  mMainView.triggerMousePressed(mouseX,  mouseY);
  mNeedsDraw = true;
}

public void mouseReleased(){  
  mMainView.triggerMouseReleased(mouseX,  mouseY);
  mNeedsDraw = true;
}

public void mouseMoved(){
  mNeedsDraw = true;  
}

public void mouseClicked(){
  mNeedsDraw = true;
}

public void mouseDragged(){
  mMainView.triggerMouseDragged(mouseX,  mouseY);
  mNeedsDraw = true;
}

public void processDataReceived(char ch){
  mResponse.append(ch);      
  if (state == STATE_CONNECT) state = STATE_MENU;
  String s = mResponse.toString(); 
  //println(s);
  if (parseResponse(s)) {       
    while (mResponse.length() > 0) mResponse.deleteCharAt(0);        
    mNeedsDraw = true;
  }
}

public void serialEvent(Serial port) {    
  try {
    while (port.available() > 0){      
      char ch = port.readChar();
      processDataReceived(ch);      
    }       
  } 
  catch (Exception e) {
    println("EX: "+e);
  }  
}


public void updatePage(){
  println("updatePage");   
  switch (state){
     case STATE_CONNECT:
                try{
                    printArray(Serial.list());
                    mMainView.showListView();
                    surface.setTitle("Choose serial device");
                    mListView.contentView.removeChildren();                                                               
                    for (int i=0; i < Serial.list().length; i++){                  
                      mListView.setListItem(i, Serial.list()[i], Serial.list()[i], 2);                                                    
                    }
                } catch (Exception e){
                    javax.swing.JOptionPane.showMessageDialog(null, "Error: "+e);
                    print("EX: "+e);  
                }
                break;
     case STATE_MENU:
                surface.setTitle(getMenuPath(false));
                mMainView.showListView();                
                break;
     case STATE_PLOT:
                //setTitle(getResources().getString(R.string.app_name) + ":  " + getMenuPath(false));
                mMainView.showListView();                               
                break;
     case STATE_NAVIGATE:
                //setTitle(getResources().getString(R.string.app_name) + ":  " + getMenuPath(false));
                mMainView.showNavigationView();
                break;
     case STATE_RAW:
                //setTitle(getResources().getString(R.string.app_name) + ":  " + getMenuPath(false));
                mMainView.showListView();
                break;
  }
}
  
/* subclassed UI classes
*/



  public String float2String(float number){
    String s = String.format("%.2f", number);
    s = s.replaceAll(",", ".");
    return s;
  }

  public int numberOfLines(String s){
    int count=1;
    int idx = 0;
    while (idx != -1){
      idx = s.indexOf("\n", idx);
      if (idx != -1){
        count++;
        idx ++;
      }
    }
    //println(count);
    return count;
  }



public class MainView extends View {
  protected ListView listView = new ListView(getWidth(), getHeight()-40);
  protected NavigationView navigationView = new NavigationView(getWidth(), getHeight()-40);
  protected ImageButton backButton = new ImageButton(getWidth()/2, 40, "img/back.png");  
  
  public ListView getListView(){
    return listView;
  }
  
  public NavigationView getNavigationView(){
    return navigationView;
  }  
  
  public ImageButton getBackButton(){
    return backButton;
  }
  
  public MainView(int aWidth, int aHeight){
    super(aWidth, aHeight);
    listView.setLeft(0);
    listView.setTop(0);
    navigationView.setLeft(0);
    navigationView.setTop(0);    
    backButton.setLeft( 0 );
    backButton.setTop( getHeight() - backButton.getHeight() );              
    addChild( listView );    
    addChild( navigationView );
    addChild( backButton );
  }
  
  public void showNavigationView(){
    navigationView.setVisible(true);
    listView.setVisible(false);
  }
  
  public void showListView(){
    navigationView.setVisible(false);
    listView.setVisible(true);
  }
    
}

// ----------------------------------------------------------------------------------------------------
public class NavigationView extends View {
  protected ImageButton upButton = new ImageButton(100, 100, "img/up.png");
  protected ImageButton downButton = new ImageButton(100, 100, "img/down.png");
  protected ImageButton leftButton = new ImageButton(100, 100, "img/left.png");
  protected ImageButton rightButton = new ImageButton(100, 100, "img/right.png");
  protected Button centerButton = new Button(150, 100, "");
  
  public ImageButton getUpButton(){
    return upButton;
  }
  
  public ImageButton getDownButton(){
    return downButton;
  }
  
  public ImageButton getLeftButton(){
    return leftButton;
  }
  
  public ImageButton getRightButton(){
    return rightButton;
  }
  
  public Button getCenterButton(){
    return centerButton;
  }
  
  public NavigationView(int aWidth, int aHeight){
    super(aWidth, aHeight);
    centerButton.setLeft( 200 );
    centerButton.setTop( 200 );
    upButton.setLeft( 225 );
    upButton.setTop( 50 );              
    downButton.setLeft( 225 );
    downButton.setTop( 350 );
    leftButton.setLeft( 50 );
    leftButton.setTop( 200 );
    rightButton.setLeft( 400 );
    rightButton.setTop( 200 );
    addChild( centerButton );
    addChild( upButton );       
    addChild( downButton );
    addChild( leftButton );
    addChild( rightButton );
  }     
}

// ----------------------------------------------------------------------------------------------------
public class ListView extends View  {
    
  protected int itemHeight = 30;
  protected int buttonWidth = 40;
  protected int itemWidth = getWidth() - buttonWidth;  
  protected int nextScrollTime = 0;
  public View contentView = new View(itemWidth, getHeight());  
  public ImageButton scrollUpButton = new ImageButton(buttonWidth, getHeight()/2, "img/up.png");
  //public Button scrollUpButton = new Button(buttonWidth, getHeight()/2, "up");
  public ImageButton scrollDownButton = new ImageButton(buttonWidth, getHeight()/2, "img/down.png");  
  
  public ListView(int aWidth, int aHeight){
    super(aWidth, aHeight);
    scrollUpButton.setLeft( getWidth() - scrollUpButton.getWidth() );
    scrollUpButton.setTop( 0 );
    scrollDownButton.setLeft( getWidth() - scrollUpButton.getWidth() );
    scrollDownButton.setTop( getHeight() -  scrollUpButton.getHeight());    
    addChild( scrollUpButton );
    addChild( scrollDownButton );
    addChild( contentView );
  }  
  
  // button
  public ListViewItem setListItem(int idx, String id, String text, float height){    
    int h = (int)(numberOfLines(text)*itemHeight * height);
    while (contentView.childrenCount()  <  idx+1 ) contentView.addChildBottom(new ListViewItem(itemWidth, h));
    ((ListViewItem)contentView.getChild(idx)).setId(id);
    ((ListViewItem)contentView.getChild(idx)).setIdx(idx);
    ((ListViewItem)contentView.getChild(idx)).setText(text);
    ((ListViewItem)contentView.getChild(idx)).setHeight(h);    
    ((ListViewItem)contentView.getChild(idx)).setSlider(0,0,0,0);
    ((ListViewItem)contentView.getChild(idx)).clearSeries();       
    return ((ListViewItem)contentView.getChild(idx));
  }
  
  // slider
  public ListViewItem setListItem(int idx, String id, String text, float height, float value, float  min, float max, float scale){
      int h = numberOfLines(text)*itemHeight;  
      while (contentView.childrenCount()  <  idx+1 ) contentView.addChildBottom(new ListViewItem(itemWidth, h));
      if (((ListViewItem)contentView.getChild(idx)).isUpdating()) return ((ListViewItem)children.get(idx));
      ((ListViewItem)contentView.getChild(idx)).setIdx(idx);
      ((ListViewItem)contentView.getChild(idx)).setId(id);
      ((ListViewItem)contentView.getChild(idx)).setText(text);
      ((ListViewItem)contentView.getChild(idx)).setHeight(h);
      ((ListViewItem)contentView.getChild(idx)).setSlider(value, min, max, scale);      
      ((ListViewItem)contentView.getChild(idx)).clearSeries();
      return ((ListViewItem)contentView.getChild(idx));
    }    
  
  // graph series
  public ListViewItem setListItem(int idx, String text){        
    int h = numberOfLines(text)*itemHeight;
    while (contentView.childrenCount()  <  idx+1 ) contentView.addChildBottom(new ListViewItem(itemWidth, h));    
    ((ListViewItem)contentView.getChild(idx)).setIdx(idx);
    ((ListViewItem)contentView.getChild(idx)).setText(text);
    ((ListViewItem)contentView.getChild(idx)).setHeight(h);
    ((ListViewItem)contentView.getChild(idx)).setSlider(0,0,0,0);
    return ((ListViewItem)contentView.getChild(idx));
  }
  
  public void childMousePressedEvent(View aChild){
    //if (millis() >= nextScrollTime){
      nextScrollTime = millis() + 100;
      int h = contentView.getChildrenHeight();
      //println(h);
      int step = getHeight() -40;
    
      if (aChild == scrollUpButton) {
        contentView.setTop( Math.min( contentView.getTop()+step, 0 ) );
        contentView.setHeight( getHeight()-contentView.getTop() );
      }
      else if (aChild == scrollDownButton) {
        if (h > getHeight()) contentView.setTop( Math.max( contentView.getTop()-step, -h+getHeight() ) );
        contentView.setHeight( getHeight()-contentView.getTop() );
      }
    //}
  }
  
             
}


// ----------------------------------------------------------------------------------------------------

public class ListViewItem extends View {	    
  protected int idx = 0;  
  protected String text = "";  // title
  protected String id = "";  // key
  private boolean isUpdating = false;    

  private ArrayList<FloatList> series = new ArrayList<FloatList>();  // plot series
  private ArrayList<String> seriesText = new ArrayList<String>();  // plot series text
  private int COLORS[] = { color(255,0,0), color(0,127,0), color(0,0,255), color(120,120,0), color(255,0,255), color(120,0,120), color(220,220,80) };
  
  private float min = 0;  // slider min
  private float max = 0;  // slider max
  private float value = 0;  // slider value
  private float scale = 0;  // slider scale
  private int colorIdx = 0;
  
  private boolean useMinX = false; // plot series 
  private boolean useMinY = false;
  private boolean useMaxX = false;
  private boolean useMaxY = false;
  private float minX = 0;
  private float minY = 0;
  private float maxX = 0;
  private float maxY = 0;    
 	
  public ListViewItem clone(){
    ListViewItem item = new ListViewItem(width, height);    
    item.parent = this.parent;
	  item.text = this.text;
	  item.id = this.id;
    item.idx = this.idx;
    item.top = this.top;
    item.left = this.left;
	  item.height = this.height;    
    item.width = this.width;
	  item.series = this.series;	
	  item.min = this.min;
	  item.max = this.max;
	  item.value = this.value;
	  item.scale = this.value;
	  item.isUpdating = this.isUpdating;
	  item.useMaxX = this.useMaxX;
	  item.useMaxY = this.useMaxY;
	  item.useMinX = this.useMinX;
	  item.useMinY = this.useMinY;
	  item.minX = this.minX;
	  item.minY = this.minY;
	  item.maxX = this.maxX;
	  item.maxY = this.maxY;
    item.colorIdx = this.colorIdx;  	  
	  return item;
  }
  
  public ListViewItem(int aWidth, int aHeight) {
    super(aWidth, aHeight);	
  }  
      
  public String getText(){
	  return text;
  }
    
  public void setIdx(int idx){
    this.idx  = idx;
  }
  
  public int getIdx(){
    return idx;
  }    
  
  public String getId(){
    return id;
  }
    
  public void setText(String aText){
	  this.text = aText;
    //println("ListViewItem setText: " + aText);
  }
  
  public void setId(String anId){
	  this.id = anId;
  }
    
  public void addSeries(String text, FloatList aseries){
	  this.seriesText.add(text);
    this.series.add(aseries);	
  }
    
  public void clearSeries(){
   	this.series.clear();	
  }
 
  
  public void setValue(float value){
	 this.value = value;  
  }
  
  public float getMin(){
	  return min;
  }

  public float getMax(){
	  return max;
  }
  
  public float getValue(){
	  return value;
  }  
  
  public float getScale(){
	  return scale;
  } 
  
  public void setSlider(float value, float min, float max, float scale){    
    //println("setSlider "+text);	  
    this.min = min;
	  this.max = max;
    this.value = Math.min( Math.max(min, value), max );
	  this.scale = scale;
  }
  
  public int getSeriesCount(){
   //	  return series.size();
   return 0;
  }
  
  public void setColorIdx(int idx){
    this.colorIdx = idx;
  }
  
  public FloatList getSeries(int idx){
	  return series.get(idx);
  }
  
  @Override 
  public String toString() {
   //	if (series.size() > 0) return "graphView"; else
	  return text; 
  }
  
  public void setIsUpdating(boolean flag){
    isUpdating = flag;
  }
  
  public boolean isUpdating(){
	  return isUpdating;
  }
  
  public float getMinX(){
	  return this.minX;
  }
  
  public float getMinY(){
	  return this.minY;
  }
  
  public float getMaxX(){
	  return this.maxX;
  }
  
  public float getMaxY(){
	  return this.maxY;
  }
  
  public void setMinX(float minX){
	  this.minX = minX;
	  this.useMinX = true;
  }
  
  public void setMaxX(float maxX){
	  this.maxX = maxX;
	  this.useMaxX = true;
  }

  public void setMinY(float minY){
	  this.minY = minY;
	  this.useMinY = true;
  }
  
  public void setMaxY(float maxY){
	  this.maxY = maxY;
	  this.useMaxY = true;
  }

  public boolean useMinX(){
	  return useMinX;
  }

  public boolean useMaxX(){
	  return useMaxX;
  }  

  public boolean useMinY(){
	  return useMinY;
  }

  public boolean useMaxY(){
	  return useMaxY;
  }
  
  protected void mouseActivity(){
    if (scale > 0){
       // slider             
       int x = Math.max(getLeft(), Math.min(getLeft()+getWidth(), mouseX)) - getLeft();
       value = Math.round( ((float)x)/((float)getWidth()) * (max-min) + min );
       //value = (((float)x)/((float)getWidth()) * (max-min) + min);
       //println(value);
     }
  }
  
  protected void mouseDraggedEvent(){
    mouseActivity();
  }
  
  protected void mousePressedEvent(){
    mouseActivity();
  }
   
    
  public void draw(){       
    //println("draw "+text+" "+getLeft()+","+getTop() + " - "+getWidth());
    if (series.size() > 0){
      for (int i=0; i < series.size(); i++){
        int col = COLORS[(colorIdx +i) % COLORS.length];      
        plot(i, minY, maxY, series.get(i), seriesText.get(i), getLeft(), getTop(), col);
      }
      return;
    }
    
    stroke(0,0,0);
    if (scale > 0){
      fill(255,255,255);
    } else {
      if (mouseOver) fill(0,0,0); else fill(255,255,255);
    }
    rect(getLeft(), getTop(), getWidth(), getHeight(), 0);    
    if (scale > 0){
      // slider
      if (mouseOver)  fill(0,0,0); else  fill(200,200,200);
      int x = (int)(getWidth()*(value-min)/(max-min));
      rect(getLeft(), getTop(), x, getHeight(), 0);            
      stroke(150,150,150);
      ellipse(getLeft() + x, getTop()+15, 30, 30);      
    }    
    stroke(0,0,0);
    textAlign(CENTER);
    if (scale > 0) fill(127,127,127);
    else 
    {
      if (mouseOver)  fill(255,255,255);   else fill(0,0,0);
    }
    String txt = getText();    
    if (scale > 0) {       
      if (scale < 1.0f){
        txt += " " + Math.round(value) * scale;
      } else {
        txt += " " + Math.round(value * scale);
      }
    }
    int h = numberOfLines(txt)*30;
    text(txt, getLeft()+width/2, getTop() + (getHeight()-h)/2+20);        
  }
  
  
  protected void plot(int idx, float minY, float maxY, FloatList list, String label, int posX, int posY, int col){  
    int h = getHeight();
    int w = getWidth();
    float px = posX;
    int oldpy = 0;  
    float oldpx = 0;
    int py;
    float stepx = (((float)w)/((float)list.size()));
    if ((minY == 0) && (maxY == 0)){
      for (int i=0; i < list.size(); i++){
        minY = min(minY, list.get(i));
        maxY = max(maxY, list.get(i));
      }
    }    
    float rangeY = abs(maxY-minY);   
    float stepY = ((float)h)/rangeY;      
    stroke(0,0,0);    
    fill(255,255,255);
    if (idx == 0){
      rect(px, posY, w, h, 10);
      // zero line
      stroke(200,200,200);
      py = posY + h-((int)( (0-minY) *stepY ));
      line(px, py, px+w, py);
    }
    fill(col);
    stroke(col);
    text(label, posX+100, posY+20+20*idx);
    if (list.size() < 2) return;
    text(float2String(list.get(list.size()-1)), posX+200, posY+20+20*idx);
    for (int i=0; i < list.size(); i++){
      //println(list.get(i));
      float value = max(minY, min(maxY, list.get(i)));
      py = posY + h-((int)( (value-minY) *stepY ));    
      if (i > 0) line(oldpx, oldpy, px, py);          
      oldpy = py;
      oldpx = px;
      px += stepx;
    }
    stroke(0,0,0);
    fill(255,255,255);
  }

  /*protected void addPlotData(FloatList list, float value){
    list.append( value );
    if (list.size() > 300) list.remove(0);
  }

  protected void drawPlots(int px, int py){
    int x = px;
    int y = py;  
    plot(0, -25, 25,     dataSpeedL, "speedL", x, y+0*ploth, 255, 0, 0);     
  }*/


}
/* general OO-classes (container view, button etc.) for GUI  
*/




public class EventHandler {
  public void mouseOverEvent(View view){
  }
  
  public void mousePressedEvent(View view){
  }   
  
  public void mouseReleasedEvent(View view){
  }
  
  public void mouseDraggedEvent(View view){
  }
}


public class View {
  
  protected ArrayList<View> children=new ArrayList<View>();
  
  protected String key = "";
  protected int top = 0;
  protected int left = 0;
  protected int width = 0;
  protected int height = 0;
  
  protected boolean visible = true;
  protected boolean mouseOver = false;  
  protected boolean mousePress = false;  
  protected boolean dataChanged = false; 
  protected View parent = null;
  protected EventHandler eventHandler = null;
   
  
  View(int aWidth, int aHeight){
    this.width = aWidth;
    this.height = aHeight;
  }
    
  View(View aParent, int aTop, int aLeft, int aWidth, int aHeight){
    this.top = aTop;
    this.left = aLeft;
    this.width = aWidth;
    this.height = aHeight;
    this.parent = aParent;
  }
  
  public void setEventHandler( EventHandler handler){
    this.eventHandler = handler;
  }
  
  public String getKey(){
    return key;
  }
  
  public void setKey(String aKey){
    this.key = aKey;
  }
  
  // call this to get an idea of the UI structure
  public void dump(String text){    
    println(text + this);
    for (int i=0; i < children.size(); i++){
      children.get(i).dump(text + ".");
    }
  }
  
  protected void mouseReleasedEvent(){
    if (eventHandler != null) eventHandler.mouseReleasedEvent(this);
  }
  
  protected void mouseDraggedEvent(){
    if (eventHandler != null) eventHandler.mouseDraggedEvent(this);
  }  
  
  protected void mouseOverEvent(){
    if (eventHandler != null) eventHandler.mouseOverEvent(this);
    if (parent != null) parent.childMouseOverEvent(this);
  }
  
  protected void mousePressedEvent(){
    if (eventHandler != null) eventHandler.mousePressedEvent(this);
    if (parent != null) parent.childMousePressedEvent(this);
  }  
  public boolean isMouseOver(){
    return mouseOver;
  }
  
  public void childMousePressedEvent(View aChild){
  }
  
  public void childMouseOverEvent(View aChild){
  }
  
  
  public boolean hasDataChanged(){
    boolean res = dataChanged;
    dataChanged = false;
    return res;    
  }
  
  public boolean isInside(int mx, int my){
    if (!visible) return false;
    boolean insideThis = (mx > getLeft()) && (mx < getLeft()+getWidth()) && (my >= getTop()) && (my < getTop()+getHeight());    
    boolean insideParent = true;
    if (parent != null) insideParent = parent.isInside(mx, my);    
    return ( (insideThis) && (insideParent) );  
  }  
  
  protected void resetChildrenRecursive(boolean clearMouseOver, boolean clearMouseDragged){
     for (int i=0; i < children.size(); i++){
       children.get(i).resetChildrenRecursive(clearMouseOver, clearMouseDragged);
     }
     if (clearMouseOver) mouseOver = false;     
     if (clearMouseDragged) mousePress = false;
  }
  
  protected View getMousePressRecursive(){       
    for (int i=0; i < children.size(); i++){
      View child = children.get(i).getMousePressRecursive();
      if (child != null) return child; 
    }
    if (mousePress) return this;
    return null; 
  }
  
  protected View getMouseOverRecursive(int mx, int my){       
    for (int i=0; i < children.size(); i++){
      View child = children.get(i).getMouseOverRecursive(mx, my);
      if (child != null) return child; 
    }
    //println(mouseOver + ":"+ this);
    if (mouseOver) return this;
    return null; 
  }  
  
  protected View getInsideRecursive(int mx, int my){       
    for (int i=0; i < children.size(); i++){
      View childat = children.get(i).getInsideRecursive(mx, my);
      if (childat != null) return childat; 
    }
    if (isInside(mx, my)) return this;
    return null; 
  }
  
  public boolean getVisible(){
    return visible;
  }
  
  public void setVisible(boolean flag){
    visible = flag;
  }
  
  public int getLeft(){
    if (parent == null) return left;
      else return parent.getLeft() + left;    
  }
  
  public int getTop(){
    if (parent == null) return top;
      else return parent.getTop() + top;
  }
  
  public int getWidth(){
    return width;
  }
  
  public int getHeight(){
    return height;
  }
  
  public void setHeight(int aHeight){
    this.height = aHeight;
  }  
  
  public void setWith(int aWidth){
    this.width = aWidth;
  }
  
  public void draw(){
    if (!visible) return; 
    stroke(0,0,0);
    fill(255,255,255);
    rect(getLeft(), getTop(), getWidth(), getHeight(), 0);    
    
    View childAt = getInsideRecursive(mouseX, mouseY);
    View childDragged = getMousePressRecursive();
    if (childAt != null) {
      if (childDragged == null){
        resetChildrenRecursive(true, false);
        childAt.mouseOver = true;
        childAt.mouseOverEvent();
      }
    }       
    
    clip(getLeft(), getTop(), getWidth(), getHeight());
    for (int i=0; i < children.size(); i++){
      View view = children.get(i);                   
      view.draw();      
    }    
    noClip();
  }
  
  
  public void triggerMousePressed(int mouseX, int mouseY){
    println("triggerMousePressed " + this);
    View childat = getMouseOverRecursive(mouseX, mouseY);
    if (childat != null){      
      println("child " + childat);
      childat.mousePress = true;
      childat.mousePressedEvent();
    }
  }
  
  public void triggerMouseReleased(int mouseX, int mouseY){         
    View child = getMousePressRecursive();
    if (child != null) child.mouseReleasedEvent();
    resetChildrenRecursive(true, true);
  }
  
  public void triggerMouseDragged(int mouseX, int mouseY){
    View child = getMousePressRecursive();
    if (child != null) child.mouseDraggedEvent();
  }
    
  public void setLeft(int aLeft){
    this.left = aLeft;
  }
  
  public void setTop(int aTop){
    this.top = aTop;
  }
  
  public void removeChildren(){
    children.clear();
  }
  
  public void removeChild(int idx){
     children.remove(idx);
  }
  
  public View getChild(int idx){
    return children.get(idx);
  }
  
  public int childrenCount(){
    return children.size();
  }
  
  public void addChild(View child){
    child.parent = this;
    children.add(child);     
  }  
  
  public void addChildBottom(View child){
    child.top = getChildrenHeight();
    //println("child.top="+child.top);
    child.parent = this;
    children.add(child);     
  }
  
  public void addChildRight(View child){
    child.left = getChildrenWidth();
    child.parent = this;
    children.add(child);     
  }
  
  public int getChildrenWidth(){
    int w = 0;
    for (int i=0; i < children.size(); i++) w += children.get(i).getWidth();
    return w;
  }
  
  public int getChildrenHeight(){
    int h = 0;
    //println(children.size());
    for (int i=0; i < children.size(); i++) h += children.get(i).getHeight();    
    return h;
  }
   
  
}

// ----------------------------------------------------------------------------------------------------


public class Button extends View  {
    
  protected String text = "";  // title
  
  public Button(int aWidth, int aHeight, String aText){
    super(aWidth, aHeight);
    this.text = aText;
  }
  
  public void setText(String aText){
    //println("button setText:"+aText);
    this.text = aText;
  }
  
  public String getText(){
    return text;
  }

  public void draw(){    
    if (mousePress){
      //println("mouseDragged");
      fill(0,0,0);      
    } else if (mouseOver) {
      fill(127,127,127);
    }     
    else {
      fill(255,255,255);      
    }
    rect(getLeft(), getTop(), getWidth(), getHeight(), 0);
    textAlign(CENTER);    
    fill(0,0,0);
    text(text, getLeft()+getWidth()/2, getTop() + 20);
  }
      
}  

// ----------------------------------------------------------------------------------------------------

public class ImageButton extends Button {
  protected PImage image = null;
  
  public ImageButton(int aWidth, int aHeight, String imageFilename){    
    super(aWidth, aHeight, "");
    image = loadImage(imageFilename);
    float aspect = ((float)image.width)/((float)image.height);    
    image.resize(40, (int)aspect*40);
  }
  
  
 public void draw(){     
    super.draw();
    image(image, getLeft()+getWidth()/2-image.width/2, getTop()+getHeight()/2-image.height/2);       
  }
}

// ----------------------------------------------------------------------------------------------------
public class TextView extends View {
  
  protected View view = new View(150, 100);
  protected String text = "";

  public TextView(int aWidth, int aHeight){
    super(aWidth, aHeight);       
    addChild( view );    
  } 
  
  public void setText(String aText){
    this.text = aText;
  }
  
  public void draw(){       
    String[] lines = text.split("\n");
    for (int i=0; i < lines.length; i++){
      text(lines[i], getLeft(), getTop() + i * 20);
    }
  }
}
  public void settings() {  size(640, 700); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "processing_remote" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}

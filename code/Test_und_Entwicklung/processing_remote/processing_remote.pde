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
 
import java.util.Stack;
import java.util.regex.*;
import processing.serial.*;
import processing.net.*;
import java.util.Iterator;

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
     mListView.setListItem(rawDataLines, "", resp, 1.0);
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
    float value = 0.0;
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
      
  void hideNavigationButtons(){
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
            mListView.setListItem(0, "", firstCol, 1.0);
          }          
        } else {  // menu create                                    
          //toast("cmd="+col, true);
          registerNewMenu(col);
          Pattern p1 = Pattern.compile("([^`]*)(?:`([^`]*))?"); // title[`interval] 
          Matcher m1 = p1.matcher(col);
          if (m1.matches()){ 
            String title = m1.group(1);                   
            mListView.setListItem(0, "", "|"+title+"|", 1.0);
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
          mListView.setListItem(colIdx, m4.group(1), m4.group(2), 1.0, value, min, max, scale);                
        } else {
          Pattern p3 = Pattern.compile("([^~]*)~([^~]*)"); // key~name  
          Matcher m3 = p3.matcher(col);
          if (m3.matches()){   // menu item 
            mListView.setListItem(colIdx, m3.group(1), m3.group(2), 1.0);
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

  
  
void sendData(String text, String data){
  println("sendData: "+text + ":" + data);
  if (demo) return;
  for (int i=0; i < data.length(); i++) {
    if (useTcp) myTcp.write( (int)data.charAt(i) );
      else mySerial.write( (int)data.charAt(i) );
      //delay(20);
  }
}
     

void sendNavigation(View view){
  String s = "{"+view.key+"}";        
  sendData("navigate", s);
}


void setup(){
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
  
  size(640, 700);     
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


void requestStartMenu(){
   String s = "{.}";
   mChosenMenuItem = new ListViewItem(0,0);
   mChosenMenuItem.setId(".");
   mChosenMenuItem.setText("");
   if ((!demo) && (!useTcp)) mySerial.clear();
   sendData("request main menu", s);
}

void onListItemClick(ListViewItem item){
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


void onBackPressed() {
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
  
   
void draw(){
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


void mousePressed(){  
  mMainView.triggerMousePressed(mouseX,  mouseY);
  mNeedsDraw = true;
}

void mouseReleased(){  
  mMainView.triggerMouseReleased(mouseX,  mouseY);
  mNeedsDraw = true;
}

void mouseMoved(){
  mNeedsDraw = true;  
}

void mouseClicked(){
  mNeedsDraw = true;
}

void mouseDragged(){
  mMainView.triggerMouseDragged(mouseX,  mouseY);
  mNeedsDraw = true;
}

void processDataReceived(char ch){
  mResponse.append(ch);      
  if (state == STATE_CONNECT) state = STATE_MENU;
  String s = mResponse.toString(); 
  //println(s);
  if (parseResponse(s)) {       
    while (mResponse.length() > 0) mResponse.deleteCharAt(0);        
    mNeedsDraw = true;
  }
}

void serialEvent(Serial port) {    
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
  
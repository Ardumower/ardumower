/* subclassed UI classes
*/

import java.util.ArrayList;

  String float2String(float number){
    String s = String.format("%.2f", number);
    s = s.replaceAll(",", ".");
    return s;
  }

  int numberOfLines(String s){
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
  ListViewItem setListItem(int idx, String id, String text, float height){    
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
  ListViewItem setListItem(int idx, String id, String text, float height, float value, float  min, float max, float scale){
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
  ListViewItem setListItem(int idx, String text){        
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
  private color COLORS[] = { color(255,0,0), color(0,127,0), color(0,0,255), color(120,120,0), color(255,0,255), color(120,0,120), color(220,220,80) };
  
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
        color col = COLORS[(colorIdx +i) % COLORS.length];      
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
      if (scale < 1.0){
        txt += " " + Math.round(value) * scale;
      } else {
        txt += " " + Math.round(value * scale);
      }
    }
    int h = numberOfLines(txt)*30;
    text(txt, getLeft()+width/2, getTop() + (getHeight()-h)/2+20);        
  }
  
  
  protected void plot(int idx, float minY, float maxY, FloatList list, String label, int posX, int posY, color col){  
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
/* general OO-classes (container view, button etc.) for GUI  
*/

import java.util.ArrayList;


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
  
  void setEventHandler( EventHandler handler){
    this.eventHandler = handler;
  }
  
  String getKey(){
    return key;
  }
  
  void setKey(String aKey){
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
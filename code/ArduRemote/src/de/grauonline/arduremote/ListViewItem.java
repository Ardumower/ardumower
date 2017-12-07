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

import java.util.ArrayList;

import com.jjoe64.graphview.GraphViewSeries;

import android.view.View;

public class ListViewItem {	  
  private String text = "";  // title
  private String id = "";  // key 
  private double height = 1.0; // item height
  
  private ArrayList<GraphViewSeries> series = new ArrayList<GraphViewSeries>();  // plot series  
  
  private double min = 0;  // slider min
  private double max = 0;  // slider max
  private double value = 0;  // slider value
  private double scale = 0;  // slider scale
  
  private boolean useMinX = false; // plot series 
  private boolean useMinY = false;
  private boolean useMaxX = false;
  private boolean useMaxY = false;
  private double minX = 0;
  private double minY = 0;
  private double maxX = 0;
  private double maxY = 0;
  
  private boolean isUpdating = false;
 
	
  public ListViewItem() {	  
  }
  
  public ListViewItem clone(){
	  ListViewItem item = new ListViewItem();
	  item.text = this.text;
	  item.id = this.id;
	  item.height = this.height;
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
	  return item;
  }
  
  public ListViewItem(String anId, String aText) {
	 this.id = anId;
	 this.text = aText;	 
  }  
  
  public String getText(){
	  return text;
  }
  
  public void setHeight(double height){
	  this.height = height;
  }
  
  public double getHeight(){
	  return height;
  }
  
  public String getId(){
    return id;
  }
  
  public void setText(String aText){
	  this.text = aText;
  }
  
  public void setId(String anId){
	  this.id = anId;
  }
    
  public void addSeries(GraphViewSeries aseries){
	  this.series.add(aseries);	
  }
  
  public void clearSeries(){
	  this.series.clear();	
  }
 
  
  public void setValue(double value){
	 this.value = value;  
  }
  
  public double getMin(){
	  return min;
  }

  public double getMax(){
	  return max;
  }
  
  public double getValue(){
	  return value;
  }  
  
  public double getScale(){
	  return scale;
  } 
  
  public void setSlider(double value, double min, double max, double scale){
	  this.value = value;
	  this.min = min;
	  this.max = max;
	  this.scale = scale;
  }
  
  public int getSeriesCount(){
	  return series.size();
  }
  
  public GraphViewSeries getSeries(int idx){
	  return series.get(idx);
  }
  
  @Override 
  public String toString() {
 	if (series.size() > 0) return "graphView"; else
	  return text; 
  }
  
  public void setIsUpdating(boolean flag){
	  isUpdating = flag;
  }
  
  public boolean isUpdating(){
	  return isUpdating;
  }
  
  
  public double getMinX(){
	  return this.minX;
  }
  
  public double getMinY(){
	  return this.minY;
  }
  
  public double getMaxX(){
	  return this.maxX;
  }
  
  public double getMaxY(){
	  return this.maxY;
  }
  
  public void setMinX(double minX){
	  this.minX = minX;
	  this.useMinX = true;
  }
  
  public void setMaxX(double maxX){
	  this.maxX = maxX;
	  this.useMaxX = true;
  }

  public void setMinY(double minY){
	  this.minY = minY;
	  this.useMinY = true;
  }
  
  public void setMaxY(double maxY){
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
  
  
}

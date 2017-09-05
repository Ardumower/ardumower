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
import java.util.List;

import com.jjoe64.graphview.CustomLabelFormatter;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.GraphViewStyle;
import com.jjoe64.graphview.GraphViewStyle.GridStyle;
import com.jjoe64.graphview.LineGraphView;

import de.grauonline.arduremote.R;
import android.app.Activity;
import android.app.ListActivity;
import android.content.Context;
import android.database.DataSetObserver;
import android.graphics.Color;
import android.graphics.Paint.Align;
import android.graphics.Typeface;
import android.util.DisplayMetrics;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.AbsListView.LayoutParams;
import android.widget.ListView;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListAdapter;
import android.widget.SeekBar;
import android.widget.TextView;

public class ListViewAdapter extends BaseAdapter{
	
private ArrayList<ListViewItem> items;
private Context context;
private float textSize = 10;


public ListViewAdapter(Context context, ArrayList<ListViewItem>items) {    	
	super();
	this.context = context;
	this.items = items;		
	textSize = new Button(context).getTextSize();
}

@Override
public View getView(int position, View convertView, ViewGroup parent) {
	
	final ListView listView = (ListView)parent;
    final int pos = position;
	final View rowView = convertView;	
    final ListViewItem item = items.get(position);    
    
    if (item.getSeriesCount() > 0){
       LineGraphView graphView = new LineGraphView(context , "");       
       //graphView.setDrawDataPoints(true);
       graphView.setDataPointsRadius(context.getResources().getDimension(R.dimen.point_radius));
       for (int i=0; i < item.getSeriesCount(); i++) 
    	  graphView.addSeries(item.getSeries(i)); // data
       if (item.useMinY()) graphView.setManualYMinBound(item.getMinY());
       if (item.useMaxY()) graphView.setManualYMaxBound(item.getMaxY());
       if ( (item.useMinX()) || (item.useMaxX()) ){
         graphView.setViewPort( item.getMinX(), item.getMaxX() );
       }
       graphView.getGraphViewStyle().setTextSize(context.getResources().getDimension(R.dimen.label_height));
       graphView.setShowLegend(true);
       //graphView.setShowVerticalLabels(true);
       if (position == items.size()-1) {
    	   graphView.setShowHorizontalLabels(true);
    	   graphView.setPadding(-30, -0, 0, 0);
    	   graphView.setMinimumHeight((int)(context.getResources().getDimension(R.dimen.graph_height) * item.getHeight()) + 38);
       } else {
    	   graphView.setShowHorizontalLabels(false);
    	   graphView.setPadding(-30, -14, 0, -24); 
    	   graphView.setMinimumHeight((int)(context.getResources().getDimension(R.dimen.graph_height) * item.getHeight()));
       }             
       graphView.setTitle(item.getText());       
       graphView.getGraphViewStyle().setGridStyle(GridStyle.BOTH);
       graphView.getGraphViewStyle().setNumVerticalLabels(3);
       graphView.getGraphViewStyle().setNumHorizontalLabels(3);
       graphView.getGraphViewStyle().setGridColor(Color.LTGRAY);
       graphView.getGraphViewStyle().setHorizontalLabelsColor(Color.RED);
       graphView.getGraphViewStyle().setVerticalLabelsWidth(100);
       graphView.getGraphViewStyle().setVerticalLabelsColor(Color.RED);
       graphView.getGraphViewStyle().setVerticalLabelsAlign(Align.RIGHT);
       graphView.setCustomLabelFormatter(new CustomLabelFormatter() {
    	   @Override
    	   public String formatLabel(double value, boolean isValueX) {
    	     if (!isValueX) {
    	       return String.format("%.1f", value);    	    	
    	     }
    	     return null; 
    	   }
    	 });
       graphView.setLayoutParams(new AbsListView.LayoutParams(LayoutParams.MATCH_PARENT, 
                 LayoutParams.MATCH_PARENT));       
       return graphView;
  	}     
    else if (item.getScale() > 0){
	    final LinearLayout linear=new LinearLayout(context); 
	    linear.setOrientation(LinearLayout.VERTICAL);
	    final TextView tv = new TextView(context);
	  	//tv.setText(item.getText());	    
	  	tv.setText(String.format("%s  %.2f", item.getText(), item.getValue() * item.getScale() ));
	  	tv.setMinimumHeight((int)(context.getResources().getDimension(R.dimen.item_height) * item.getHeight()));
	  	tv.setTextSize(TypedValue.COMPLEX_UNIT_PX, context.getResources().getDimension(R.dimen.text_height));
		tv.setGravity(Gravity.CENTER);			
		tv.setLayoutParams(new AbsListView.LayoutParams(LayoutParams.MATCH_PARENT, 
	                  LayoutParams.MATCH_PARENT));	    	    
	    final SeekBar seek=new SeekBar(context);
	    seek.setPadding(10, 10, 10, 10);
	    // example:   progress    value  (min=-0.2, max=+0.2, step=0.2)
	    //            0           -0.2
	    //            1           0
	    //            2           +0.2
	    seek.setMax((int)((item.getMax()-item.getMin())));	    
	    seek.setProgress((int)((item.getValue()-item.getMin())));
	    seek.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
			
			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
				//ListActivity activity = ((ListActivity)ListViewAdapter.this.context);				
				//int pos = ListViewAdapter.this.position;
				//lv.performClick();
				//tv.setText("blub");				
				listView.performItemClick(listView.getAdapter().getView(pos, null, null), pos, pos);
				item.setIsUpdating(false);
			}
			
			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
				item.setIsUpdating(true);
				//listView.performItemClick(listView.getAdapter().getView(pos, null, null), pos, pos);
			}
			
			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				//Log.d("test", "changed ");		
				tv.setText(String.format("%s  %.2f", item.getText(), (progress + item.getMin()) * item.getScale() ));				
				item.setValue(progress + item.getMin());
				//listView.performItemClick(listView.getAdapter().getView(pos, null, null), pos, pos);
			}
	    });	  	  	   	  
	    linear.addView(tv);
	    linear.addView(seek);
	    return linear;
  	} 
    else {
  	   TextView tv = new TextView(context);
  	   tv.setText(item.getText());
  	   if ((position == 0) && (item.getText().startsWith("|"))) tv.setTypeface(null, Typeface.BOLD);
  	   tv.setMinimumHeight((int)(context.getResources().getDimension(R.dimen.item_height) * item.getHeight()));
  	   tv.setTextSize(TypedValue.COMPLEX_UNIT_PX, context.getResources().getDimension(R.dimen.text_height));
	   tv.setGravity(Gravity.CENTER);			
	   tv.setLayoutParams(new AbsListView.LayoutParams(LayoutParams.MATCH_PARENT, 
                  LayoutParams.MATCH_PARENT));  	   
  	   return tv;       
    }	    
}

@Override
public int getCount() {	
	return items.size();
}

@Override
public Object getItem(int position) {	
	return items.get(position);
}

@Override
public long getItemId(int position) {
	return System.identityHashCode(items.get(position));
}

}

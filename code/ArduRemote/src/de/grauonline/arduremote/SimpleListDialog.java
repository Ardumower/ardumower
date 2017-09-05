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

import de.grauonline.arduremote.SimpleFileDialog.SimpleFileDialogListener;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.widget.ArrayAdapter;

public class SimpleListDialog {
	
 	public Context context;
 	public String[] items;
 	public String title; 	
 	private SimpleListDialogListener listener = null;	

	public interface SimpleListDialogListener 
	{
		public void onChosenItem(int choosenItem);
	}

 	
 	SimpleListDialog(Context context, String title, String[] items, SimpleListDialogListener listener){
 		this.context = context;
 		this.items = items;
 		this.title = title;
 		this.listener = listener;
 	}
 	
 	
	void run(){
		 final AlertDialog.Builder menuAleart = new  AlertDialog.Builder(context);
		 menuAleart.setTitle(title);
		 menuAleart.setItems(items,new DialogInterface.OnClickListener() {
		  public void onClick(DialogInterface dialog, int item) {
		     listener.onChosenItem(item); 			 
		  }
		 });
		 AlertDialog menuDrop = menuAleart.create();
		 menuDrop.show();
	}    
}



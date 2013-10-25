package com.example.ftcscout;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.content.Intent;
import android.widget.EditText; 
import android.widget.NumberPicker;
import android.view.MenuInflater;
import android.content.Context;


public class MainActivity extends Activity {
	public final static String EXTRA_MESSAGE = "com.example.myfirstapp.MESSAGE";
	
	private static Context context;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		NumberPicker np = (NumberPicker) findViewById(R.id.NumberPicker01);
		np.setMaxValue(100);
		np.setMinValue(0);
		NumberPicker np2 = (NumberPicker) findViewById(R.id.NumberPicker02);
		np2.setMaxValue(1001);
		np2.setMinValue(0);
		MainActivity.context = getApplicationContext();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
	    MenuInflater inflater = getMenuInflater();
		// Inflate the menu; this adds items to the action bar if it is present.
	    //inflater.inflate(R.menu.main, menu);
	    
	    // Inflate the menu items for use in the action bar
	    inflater.inflate(R.menu.main_activity_actions, menu);
	    return super.onCreateOptionsMenu(menu);
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
	    // Handle presses on the action bar items
	    switch (item.getItemId()) {
	        case R.id.action_search:
	            //openSearch();
	            return true;
	        case R.id.action_settings:
	            //openSettings();
	            return true;
	        default:
	            return super.onOptionsItemSelected(item);
	    }
	}
	
	/** Called when the user clicks the Send button */
	public void sendMessage(View view) {
		Intent intent = new Intent(this, DisplayMessageActivity.class);
		EditText editText = (EditText) findViewById(R.id.edit_message);
		String message = editText.getText().toString();
		NumberPicker np = (NumberPicker) findViewById(R.id.NumberPicker01);
		int x = np.getValue();
		intent.putExtra(EXTRA_MESSAGE, message);
		intent.putExtra("NumberPickerValue", x);
		startActivity(intent);
	}
}

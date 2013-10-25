package com.example.ftcscout;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.MenuItem;
import android.support.v4.app.NavUtils;
import android.content.Intent;
import android.widget.TextView;
import android.content.pm.PackageManager;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.Context;
import android.util.Log;
import java.io.File;
import java.io.OutputStreamWriter;
import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class DisplayMessageActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		Context ctx = getApplicationContext();
		
		//setContentView(R.layout.activity_display_message);
		// Show the Up button in the action bar.
		setupActionBar();
		
		// Get the message from the intent
	    Intent intent = getIntent();
	    String message = intent.getStringExtra(MainActivity.EXTRA_MESSAGE);
	    int x = intent.getIntExtra ("NumberPickerValue", -1);

	    // Create the text view
	    TextView textView = new TextView(this);
	    textView.setTextSize(40);
	    textView.setText(message + " " + Integer.toString(x) + " points");

	    // Set the text view as the activity layout
	    setContentView(textView);
	    
	    // Write our file
	    writeFile(ctx);
	}

	/**
	 * Set up the {@link android.app.ActionBar}.
	 */
	private void setupActionBar() {
		getActionBar().setDisplayHomeAsUpEnabled(true);
	}

	/*
	 * Create and write data to a file
	 */
	private void writeFile(Context ctx) {
		PackageManager m = getPackageManager();
		String s = getPackageName();
		try {
		    PackageInfo p = m.getPackageInfo(s, 0);
		    s = p.applicationInfo.dataDir;
		} catch (NameNotFoundException e) {
		    Log.w("yourtag", "Error Package name not found ", e);
		}
		
		// Create File and write data
		String filePath = s + File.separator + "test.txt";
		String data = "Hello!";
		 try {
			    FileOutputStream os = ctx.openFileOutput(filePath, Context.MODE_PRIVATE);
		        OutputStreamWriter outputStreamWriter = new OutputStreamWriter(os);
		        outputStreamWriter.write(data);
		        outputStreamWriter.close();
		    }
		    catch (IOException e) {
		    	 Log.e("MYAPP", "exception", e);

		    } 
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.display_message, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case android.R.id.home:
			// This ID represents the Home or Up button. In the case of this
			// activity, the Up button is shown. Use NavUtils to allow users
			// to navigate up one level in the application structure. For
			// more details, see the Navigation pattern on Android Design:
			//
			// http://developer.android.com/design/patterns/navigation.html#up-vs-back
			//
			NavUtils.navigateUpFromSameTask(this);
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

}

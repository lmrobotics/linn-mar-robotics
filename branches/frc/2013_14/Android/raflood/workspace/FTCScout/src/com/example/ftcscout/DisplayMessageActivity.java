package com.example.ftcscout;

import android.net.Uri;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.MenuItem;
import android.support.v4.app.NavUtils;
import android.content.ComponentName;
import android.content.Intent;
import android.widget.TextView;
import android.content.pm.PackageManager;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.Context;
import android.util.Log;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import android.bluetooth.BluetoothAdapter;

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
	    message = message + " " + Integer.toString(x) + " points";

	    // Create the text view
	    TextView textView = new TextView(this);
	    textView.setTextSize(40);
	    textView.setText(message);

	    // Set the text view as the activity layout
	    setContentView(textView);
	    String fileName = "ftc_scores____.csv";
	    // Write our file
	    writeFile(ctx, fileName);
	    
		// inside method
	    // Check if bluetooth is supported
	    BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();
	    if (btAdapter == null) {
           // Device does not support Bluetooth
           message = message + "\n Blue tooth not found on this device";
   	       textView.setText(message);
        }
        else
        {
            try {
           	 InputStream inputStream = openFileInput(fileName);
           	 InputStreamReader inputStreamReader = new InputStreamReader(inputStream);
           	 BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
           	 message = message + "\n" + bufferedReader.readLine();
     	     textView.setText(message);
           }
           catch  (Exception e) {  
           }        

            // send file via blue tooth
            message = message + "\n Sending data via Blue tooth";
    	    textView.setText(message);
    	    File file = new File(ctx.getFilesDir().getPath(), fileName);
    	    if (file.exists())
    	    {
                message = message + "\n Transmitting!";
        	    textView.setText(message);
        	    Intent bti = new Intent();
        	    bti.setAction(Intent.ACTION_SEND);
        	    //bti.setComponent(new ComponentName(
        	    //        "com.android.bluetooth",
        	    //        "com.android.bluetooth.opp.BluetoothOppLauncherActivity"));
        	    bti.setType("*/*");
        	    //bti.setComponent(new ComponentName("com.android.bluetooth", "com.android.bluetooth.opp.BluetoothOppLauncherActivity"));
      	        bti.putExtra(Intent.EXTRA_STREAM, Uri.fromFile(file) );
      	        try
      	        {
        	       startActivity(bti);
      	        }
    		    catch (Exception e) {
                    message = message + "\n" + e;
            	    textView.setText(message);
   		    	     Log.e("MYAPP", "file write failed", e);

   		        } 
    	    }
    	    else
    	    {
                message = message + "\n File does not exist";
        	    textView.setText(message);
    	    	
    	    }

        }
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
	private void writeFile(Context ctx, String fileName) {
		PackageManager m = getPackageManager();
		String s = getPackageName();
		try {
		    PackageInfo p = m.getPackageInfo(s, 0);
		    s = p.applicationInfo.dataDir;
		} catch (NameNotFoundException e) {
		    Log.w("MYAPP", "Error Package name not found ", e);
		}
		
        // Create File and write data
		String data = "Hello There!!!!";
        try {
        	    //File file = new File(ctx.getFilesDir(), fileName);
        	    //file.mkdirs();
        	    //file.createNewFile();
                FileOutputStream os = ctx.openFileOutput(fileName, Context.MODE_PRIVATE);
		        OutputStreamWriter outputStreamWriter = new OutputStreamWriter(os);
		        outputStreamWriter.write(data);
		        outputStreamWriter.close();
		    }
		    catch (Exception e) {
		    	 Log.e("MYAPP", "file write failed", e);

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

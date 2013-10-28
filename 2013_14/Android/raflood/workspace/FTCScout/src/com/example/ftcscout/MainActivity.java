package com.example.ftcscout;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.content.ComponentName;
import android.content.Intent;
import android.widget.EditText; 
import android.widget.NumberPicker;
import android.view.MenuInflater;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;


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
        String fileName = "ftc_score.csv";
        Context ctx = getApplicationContext();
        writeFile(ctx, fileName);

        sendFileViaBluetooth(fileName);
        
        EditText editText = (EditText) findViewById(R.id.edit_message);
        String message = editText.getText().toString();
        NumberPicker np = (NumberPicker) findViewById(R.id.NumberPicker01);
        int x = np.getValue();
        intent.putExtra(EXTRA_MESSAGE, message);
        intent.putExtra("NumberPickerValue", x);
        startActivity(intent);
    }

    /*
     * Sends file from android device over blue tooth
     */
    private void sendFileViaBluetooth(String fileName)
    {
        File file = new File(Environment.getExternalStorageDirectory().toString() + "/Pictures/Family", fileName);
        
        if (file.exists())
        {
            Intent bti = new Intent();
            bti.setAction(Intent.ACTION_SEND);
            bti.setType("text/plain");
            bti.putExtra(Intent.EXTRA_STREAM, Uri.fromFile(file) );
            try
            {
               startActivity(bti);
            }
            catch (Exception e) {
             Log.e("MYAPP", "file write failed", e);
            } 
        }
                    
    } // sendFileViaBluetooth
    
    /*
     * Create and write data to a file
     */
    private void writeFile(Context ctx, String fileName) {
        // Example data that will get populated from screen info.
        String data = "Super Ninjas, 104, -9, 55, 17, \n";
        try 
        {
            String path = Environment.getExternalStorageDirectory().toString() + "/Pictures/Family";
            File file1 = new File(path, fileName);
            file1.createNewFile();
            FileOutputStream os = new FileOutputStream(file1);
            OutputStreamWriter outputStreamWriter = new OutputStreamWriter(os);
            outputStreamWriter.write(data);
            outputStreamWriter.write(data);
            outputStreamWriter.write(data);
            outputStreamWriter.write(data);
            outputStreamWriter.write(data);
            outputStreamWriter.write(data); 
            outputStreamWriter.write(data);
            outputStreamWriter.write(data);
            outputStreamWriter.write(data);
            outputStreamWriter.close();
        }
        catch (Exception e) {
             Log.e("MYAPP", "file write failed", e);

        }         
                        
    } // writeFile

}

package com.example.ftcscout;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.NumberPicker;
import android.widget.RadioButton;

public class MainActivity extends Activity {
    public final static String EXTRA_MESSAGE = "com.example.myfirstapp.MESSAGE";
    
    private static Context context;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        NumberPicker np = (NumberPicker) findViewById(R.id.Driver1pt);
        np.setMaxValue(100);
        np.setMinValue(0);
        NumberPicker np2 = (NumberPicker) findViewById(R.id.Driver2pt);
        np2.setMaxValue(100);
        np2.setMinValue(0);
        NumberPicker np3 = (NumberPicker) findViewById(R.id.Driver3pt);
        np3.setMaxValue(100);
        np3.setMinValue(0);
        MainActivity.context = getApplicationContext();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu items for use in the action bar
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.main_activity_actions, menu);
        return super.onCreateOptionsMenu(menu);
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle presses on the action bar items
        switch (item.getItemId()) 
        {
            case R.id.action_send:
                sendFileViaBluetooth("ftc_score.csv");
                return true;
            case R.id.action_save:
                String fileName = "ftc_score.csv";
                Context ctx = getApplicationContext();
                writeFile(ctx, fileName);
                return true;
            case R.id.action_settings:
            	//sendFileViaBluetooth("ftc_score.csv");
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
        
        //EditText editText = (EditText) findViewById(R.id.teamName);
        //String message = editText.getText().toString();
        //NumberPicker np = (NumberPicker) findViewById(R.id.Driver1pt);
        //int x = np.getValue();
        //intent.putExtra(EXTRA_MESSAGE, message);
        //intent.putExtra("NumberPickerValue", x);
        //startActivity(intent);
    }

    /*
     * Sends file from android device over blue tooth
     */
    private void sendFileViaBluetooth(String fileName)
    {
        File file = new File(Environment.getExternalStorageDirectory().toString() + "/ScoutApp/scores", fileName);
        
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
        EditText teamName = (EditText) findViewById(R.id.teamName);
        String teamNameS = teamName.getText().toString();
        EditText teamNumber = (EditText) findViewById(R.id.teamNumber);
        String teamNumberS = teamNumber.getText().toString();
        EditText matchNumber = (EditText) findViewById(R.id.matchNumber);
        String matchNumberS = teamNumber.getText().toString();
        EditText competitionName = (EditText) findViewById(R.id.competitionName);
        String competitionNameS = teamNumber.getText().toString();
        
        RadioButton rbfivept= (RadioButton) findViewById(R.id.fivept);
        RadioButton rbtwentypt= (RadioButton) findViewById(R.id.twentypt);
        RadioButton rbfourtypt= (RadioButton) findViewById(R.id.fourtypt);
        String autonomousScore="";
        if(rbfivept.isChecked())
        {
        	autonomousScore = "5, ";
        }	
        else if(rbtwentypt.isChecked())
        {
        	autonomousScore = "20, ";
        }
        else if(rbfourtypt.isChecked())
        {
        	autonomousScore = "40, ";
        }
        RadioButton rbFullBridge= (RadioButton) findViewById(R.id.FullBridge);
        RadioButton rbPartialBridge= (RadioButton) findViewById(R.id.PartialBridge);
        RadioButton rbNoBridge= (RadioButton) findViewById(R.id.NoBridge);
        String AutoBridge="";
        if(rbFullBridge.isChecked())
        {
        	AutoBridge = "20, ";
        }	
        else if(rbPartialBridge.isChecked())
        {
        	AutoBridge = "10, ";
        }
        else if(rbNoBridge.isChecked())
        {
        	AutoBridge = "0, ";
        }
        CheckBox checkBox = (CheckBox) findViewById(R.id.hangingBridge);
        String hangingBridge;
        if(checkBox.isChecked())
        {
        	hangingBridge = "50, ";
        }	
        else
        {
        	hangingBridge = "0, ";
        }
        NumberPicker np = (NumberPicker) findViewById(R.id.Driver1pt);
        int a = np.getValue();

        NumberPicker np2 = (NumberPicker) findViewById(R.id.Driver2pt);
        int b = np2.getValue();
        
        NumberPicker np3 = (NumberPicker) findViewById(R.id.Driver3pt);
        int c = np3.getValue();
        RadioButton rbflagHigh= (RadioButton) findViewById(R.id.flagHigh);
        RadioButton rbflagLow= (RadioButton) findViewById(R.id.flagLow);
        RadioButton rbnoFLag= (RadioButton) findViewById(R.id.noFLag);
        String flagHeight="";
        if(rbflagHigh.isChecked())
        {
        	flagHeight = "35, ";
        }	
        else if(rbflagLow.isChecked())
        {
        	flagHeight = "20, ";
        }
        else if(rbnoFLag.isChecked())
        {
        	flagHeight = "0, ";
        }
        RadioButton rbminorYes= (RadioButton) findViewById(R.id.minorYes);
        RadioButton rbminorNo= (RadioButton) findViewById(R.id.minorNo);
        String minorPenaltiesbutton="";
        if(rbminorYes.isChecked())
        {
        	minorPenaltiesbutton = "yes, ";
        }	
        else if(rbminorNo.isChecked())
        {
        	minorPenaltiesbutton = "no, ";
        }
        RadioButton rbmajorYes= (RadioButton) findViewById(R.id.majorYes);
        RadioButton rbmajorNo= (RadioButton) findViewById(R.id.majorNo);
        String majorPenaltiesbutton="";
        if(rbmajorYes.isChecked())
        {
        	majorPenaltiesbutton = "yes, ";
        }	
        else if(rbmajorNo.isChecked())
        {
        	majorPenaltiesbutton = "no, ";
        }
        String header = "Team Name, Team Number, Match Number, Competition Name, Autonomous Block, Autonomous Bridge, 1 pt block, 2pt Block, 3pt Block, Hanging Over Bridge, Flag Score, Major Penalties, Minor Penalties \n";
    	String data = teamNameS + ", " + teamNumberS + ", " + matchNumberS + ", " + competitionNameS + ", " + autonomousScore + AutoBridge + Integer.toString(a) + 
    			", " + Integer.toString(b) + ", " + Integer.toString(c) + ", " + hangingBridge + flagHeight + majorPenaltiesbutton + minorPenaltiesbutton + "\n";
        try 
        {
            String path = Environment.getExternalStorageDirectory().toString() + "/ScoutApp";
            File file = new File(path, "scores");
            if (!file.exists())
            {
                file.mkdirs();
            }
            String path1 = Environment.getExternalStorageDirectory().toString() + "/ScoutApp/scores";
            File file1 = new File(path1, fileName);
            FileOutputStream os;
            OutputStreamWriter outputStreamWriter;
            if (!file1.exists())
            {
                 file1.createNewFile();
                 os = new FileOutputStream(file1, false);
                 outputStreamWriter = new OutputStreamWriter(os);
                 outputStreamWriter.write(header);
            }
            else
            {
                os = new FileOutputStream(file1, true);
                outputStreamWriter = new OutputStreamWriter(os);
            }
            outputStreamWriter.write(data);
            outputStreamWriter.close();
        }
        catch (Exception e) {
             Log.e("MYAPP", "file write failed", e);

        }         
                        
    } // writeFile

}

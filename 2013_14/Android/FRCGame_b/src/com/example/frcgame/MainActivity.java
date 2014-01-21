package com.example.frcgame;

import java.io.File;

import com.example.frcgame.DisplayMessageActivity;
import com.example.frcgame.R;

import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.Menu;
//import android.view.MenuItem;
import android.view.View;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.NumberPicker;
//import android.widget.RadioButton;


public class MainActivity extends Activity {

	private static Context context; 

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		 //  Number Picker Initialization
		  NumberPicker nplg = (NumberPicker) findViewById(R.id.Low_Goal);
		        nplg.setMaxValue(100);
		        nplg.setMinValue(0);
		        NumberPicker nphg = (NumberPicker) findViewById(R.id.High_Goal);
		        nphg.setMaxValue(100);
		        nphg.setMinValue(0);
		        NumberPicker npc = (NumberPicker) findViewById(R.id.Catches);
		        npc.setMaxValue(100);
		        npc.setMinValue(0);
		        MainActivity.context = getApplicationContext();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	/*  @Override
	    public boolean onOptionsItemSelected(MenuItem item) {
	        // Handle presses on the action bar items
	        switch (item.getItemId()) 
	        {
	            case R.id.action_send:
	                sendFileViaBluetooth("frc_score.csv");
	                return true;
	            case R.id.action_save:
	               String fileName = "frc_score.csv";
	                Context ctx = getApplicationContext();
	                writeFile(ctx, fileName);
	                return true;
	            case R.id.action_settings:
	            	sendFileViaBluetooth("frc_score.csv");
	                return true;
	            default:
	                return super.onOptionsItemSelected(item);
	        }
	  } */
    /* Sends file from android device over blue tooth
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
   
	  
	    private void writeFile(Context ctx, String fileName) {
	        // Example data that will get populated from screen info.
	        EditText teamName = (EditText) findViewById(R.id.Edit_Team_Name);
	        String teamNameS = teamName.getText().toString();
	        EditText teamNumber = (EditText) findViewById(R.id.Edit_Team_NUMBER);
	        String teamNumberS = teamNumber.getText().toString();
	        EditText matchNumber = (EditText) findViewById(R.id.Edit_Match_NUMBER);
	        String matchNumberS = teamNumber.getText().toString();
	        EditText competitionName = (EditText) findViewById(R.id.Edit_Competition);
	        String competitionNameS = teamNumber.getText().toString();
	        
	        CheckBox checkBox1 = (CheckBox) findViewById(R.id.Truss);
	        String Truss;
	        if(checkBox1.isChecked())
	        {
	        	Truss = "Yes, ";
	        }	
	        else
	        {
	        	Truss = "No, ";
	        }
	        
	        CheckBox checkBox2 = (CheckBox) findViewById(R.id.two_assist);
	        String two_assist;
	        if(checkBox2.isChecked())
	        {
	        	two_assist = "Yes, ";
	        }	
	        else
	        {
	        	two_assist = "No, ";
	        }
	        CheckBox checkBox3 = (CheckBox) findViewById(R.id.three_assist);
	        String three_assist;
	        if(checkBox3.isChecked())
	        {
	        	three_assist = "Yes, ";
	        }	
	        else
	        {
	        	three_assist = "No, ";
	        }
	        CheckBox checkBox4 = (CheckBox) findViewById(R.id.Mobility_Bonus);
	        String Mobility_Bonus;
	        if(checkBox4.isChecked())
	        {
	        	Mobility_Bonus = "Yes, ";
	        }	
	        else
	        {
	        	Mobility_Bonus = "No, ";
	        }
	        CheckBox checkBox5 = (CheckBox) findViewById(R.id.Hot_Goals);
	        String Hot_Goals;
	        if(checkBox5.isChecked())
	        {
	        	Hot_Goals = "Yes, ";
	        }	
	        else
	        {
	        	Hot_Goals = "No, ";
	        }
	        CheckBox checkBox6 = (CheckBox) findViewById(R.id.Auto_Bonus);
	        String Auto_Bonus;
	        if(checkBox6.isChecked())
	        {
	        	Auto_Bonus = "Yes, ";
	        }	
	        else
	        {
	        	Auto_Bonus = "No, ";
	        }
	        CheckBox checkBox7 = (CheckBox) findViewById(R.id.Foul);
	        String Foul;
	        if(checkBox7.isChecked())
	        {
	        	Foul = "Yes, ";
	        }	
	        else
	        {
	        	Foul = "No, ";
	        }
	        CheckBox checkBox8 = (CheckBox) findViewById(R.id.Tech_Foul);
	        String Tech_Foul;
	        if(checkBox8.isChecked())
	        {
	        	Tech_Foul = "Yes, ";
	        }	
	        else
	        {
	        	Tech_Foul = "No, ";
	        }
	        CheckBox checkBox9 = (CheckBox) findViewById(R.id.Mechanical_Problems);
	        String Mechanical_Problems;
	        if(checkBox9.isChecked())
	        {
	        	Mechanical_Problems = "Yes, ";
	        }	
	        else
	        {
	        	Mechanical_Problems = "No, ";
	        }
	        CheckBox checkBox10 = (CheckBox) findViewById(R.id.Blocked_Shots);
	        String Blocked_Shots;
	        if(checkBox10.isChecked())
	        {
	        	Blocked_Shots = "Yes, ";
	        }	
	        else
	        {
	        	Blocked_Shots = "No, ";
	        }
	        CheckBox checkBox11 = (CheckBox) findViewById(R.id.Truss_T);
	        String Truss_T;
	        if(checkBox11.isChecked())
	        {
	        	Truss_T = "Yes, ";
	        }	
	        else
	        {
	        	Truss_T = "No, ";
	        }

	        CheckBox checkBox12 = (CheckBox) findViewById(R.id.two_assist_T);
	        String two_assist_T;
	        if(checkBox12.isChecked())
	        {
	        	two_assist_T = "Yes, ";
	        }	
	        else
	        {
	        	two_assist_T = "No, ";
	        }
	        CheckBox checkBox13 = (CheckBox) findViewById(R.id.three_assist_T);
	        String three_assist_T;
	        if(checkBox13.isChecked())
	        {
	        	three_assist_T = "Yes, ";
	        }	
	        else
	        {
	        	three_assist_T = "No, ";
	        }
	        CheckBox checkBox14 = (CheckBox) findViewById(R.id.Mobility_Bonus_T);
	        String Mobility_Bonus_T;
	        if(checkBox14.isChecked())
	        {
	        	Mobility_Bonus_T = "Yes, ";
	        }	
	        else
	        {
	        	Mobility_Bonus_T = "No, ";
	        }
	        CheckBox checkBox15 = (CheckBox) findViewById(R.id.Hot_Goals_T);
	        String Hot_Goals_T;
	        if(checkBox15.isChecked())
	        {
	        	Hot_Goals_T = "Yes, ";
	        }	
	        else
	        {
	        	Hot_Goals_T = "No, ";
	        }
	        CheckBox checkBox16 = (CheckBox) findViewById(R.id.Auto_Bonus_T);
	        String Auto_Bonus_T;
	        if(checkBox16.isChecked())
	        {
	        	Auto_Bonus_T = "Yes, ";
	        }	
	        else
	        {
	        	Auto_Bonus_T = "No, ";
	        }
	        CheckBox checkBox17 = (CheckBox) findViewById(R.id.Foul_T);
	        String Foul_T;
	        if(checkBox17.isChecked())
	        {
	        	Foul_T = "Yes, ";
	        }	
	        else
	        {
	        	Foul_T = "No, ";
	        }
	        CheckBox checkBox18 = (CheckBox) findViewById(R.id.Tech_Foul_T);
	        String Tech_Foul_T;
	        if(checkBox18.isChecked())
	        {
	        	Tech_Foul_T = "Yes, ";
	        }	
	        else
	        {
	        	Tech_Foul_T = "No, ";
	        }
	        CheckBox checkBox19 = (CheckBox) findViewById(R.id.Mechanical_Problems_T);
	        String Mechanical_Problems_T;
	        if(checkBox19.isChecked())
	        {
	        	Mechanical_Problems_T = "Yes, ";
	        }	
	        else
	        {
	        	Mechanical_Problems_T = "No, ";
	        }
	        CheckBox checkBox20 = (CheckBox) findViewById(R.id.Blocked_Shots_T);
	        String Blocked_Shots_T;
	        if(checkBox20.isChecked())
	        {
	        	Blocked_Shots_T = "Yes, ";
	        }	
	        else
	        {
	        	Blocked_Shots_T = "No, ";
	        }
	        NumberPicker np = (NumberPicker) findViewById(R.id.Low_Goal);
	        int a = np.getValue();

	        NumberPicker np2 = (NumberPicker) findViewById(R.id.High_Goal);
	        int b = np2.getValue();
	        
	        NumberPicker np3 = (NumberPicker) findViewById(R.id.Catches);
	        int c = np3.getValue();

	        String header = "Team Name, Team Number, Match Number, Competition Name, checkBox1, checkBox2, checkBox3, checkBox4, checkbox5, checkBox6, checkBox7, checkBox8, checkbox9, checkbox10, checkbox11, checkbox12, checkBox13, checkBox14, checkBox15, checkBox16, checkBox17, checkBox18, checkBox19, checkBox20, \n";
	    	String data = teamNameS + ", " + teamNumberS + ", " + matchNumberS + ", " + competitionNameS + ", " + Truss + ", " + two_assist + ", " + three_assist + ", " + Mobility_Bonus + ", " + Hot_Goals + ", " + Auto_Bonus + ", " + Foul + ", " + Tech_Foul + ", " + Mechanical_Problems + ", " + Blocked_Shots + ", " + Truss_T + ", " + two_assist_T + ", " + three_assist_T + ", " + Mobility_Bonus_T + ", " + Hot_Goals_T + ", " + Auto_Bonus_T + ", " + Foul_T + ", " + Tech_Foul_T + ", " + Mechanical_Problems_T + ", " + Blocked_Shots_T + Integer.toString(a) + 
	    			", " + Integer.toString(b) + ", " + Integer.toString(c) +"\n";
	    }
	    public void sendMessage(View view) {
			Intent intent = new Intent(this, DisplayMessageActivity.class);
			String fileName = "frc_score.csv";
			Context ctx = getApplicationContext();
			writeFile(ctx, fileName);

			sendFileViaBluetooth(fileName);
		}	

		public void startTime(View view) {
			long startTime = System.nanoTime();
		}

		public void stopTime(View view) {
			long endTime = System.nanoTime();
			//	long timeDifference = endTime - startTime;
		}
}
	        

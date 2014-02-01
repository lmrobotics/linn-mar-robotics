package com.example.frcgame;



import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.*;
//ColorChangeButtons as per http://stackoverflow.com/questions/1521640/standard-android-button-with-a-different-color?
// TODO import android.graphics.PorterDuff;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
				// {{ CheckBoxes
				final CheckBox doubleauto = (CheckBox) findViewById(R.id.dAuto);
				final CheckBox automobonus = (CheckBox) findViewById(R.id.Mobility_Bonus);
				final CheckBox telemobonus = (CheckBox) findViewById(R.id.Mobility_Bonus_T);
				final CheckBox hotGoal = (CheckBox) findViewById(R.id.Hot_Goals);
				final CheckBox autoBonus = (CheckBox) findViewById(R.id.Auto_Bonus);
				final CheckBox autofoul = (CheckBox) findViewById(R.id.Foul);
				final CheckBox telefoul = (CheckBox) findViewById(R.id.Foul_T);
				final CheckBox teletechfoul = (CheckBox) findViewById(R.id.Tech_Foul_T);
				final CheckBox truss = (CheckBox) findViewById(R.id.Truss);
				final CheckBox twoassist = (CheckBox) findViewById(R.id.two_assist);
				final CheckBox threeassist = (CheckBox) findViewById(R.id.three_assist);
				final CheckBox autotechfoul = (CheckBox) findViewById(R.id.Tech_Foul);
				final CheckBox autoshotblock = (CheckBox) findViewById(R.id.Blocked_Shots);
				final CheckBox teleshotblock = (CheckBox) findViewById(R.id.Blocked_Shots_T);
				final CheckBox automechprob = (CheckBox) findViewById(R.id.Mechanical_Problems);
				final CheckBox telemechprob = (CheckBox) findViewById(R.id.Mechanical_Problems);
				// }} CheckBoxes
		 		// {{ Number Picker
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
		        // }} Number Picker
		        //MainActivity.context = getApplicationContext();
		        // {{ Comments
		        //Comments on Tele
		        final EditText telecomm = (EditText) findViewById(R.id.Comments_Tele);
		        //Comments on Auto
				final EditText autocomm = (EditText) findViewById(R.id.Comments_Auto);
		        //These are objects that can be used to get and set text ie. autocomm.setText("Hello")
		        // }} Comments

		      	// {{ Button Init
		        final Button reca1 = (Button) findViewById(R.id.RecA1);
		        reca1.setOnClickListener(new View.OnClickListener(){
		        	public void onClick(View v)	{
		        		//TODO Action 
		        	}
		        });
		        final Button reca2 = (Button) findViewById(R.id.RecA2);
		        reca2.setOnClickListener(new View.OnClickListener(){
		        	public void onClick(View v)	{
		        		//TODO Action 
		        	}
		        });
		        final Button reca3 = (Button) findViewById(R.id.RecA3);
		        reca3.setOnClickListener(new View.OnClickListener(){
		        	public void onClick(View v)	{
		        		//TODO Action 
		        	}
		        });
		        final Button senta1 = (Button) findViewById(R.id.SentA1);
		        senta1.setOnClickListener(new View.OnClickListener(){
		        	public void onClick(View v)	{
		        		//TODO Action 
		        	}
		        });
		        final Button senta2 = (Button) findViewById(R.id.SentA2);
		        senta2.setOnClickListener(new View.OnClickListener(){
		        	public void onClick(View v)	{
		        		//TODO Action 
		        	}
		        });
		        final Button senta3 = (Button) findViewById(R.id.SentA3);
		        senta3.setOnClickListener(new View.OnClickListener(){
		        	public void onClick(View v)	{
		        		//TODO Action 
		        	}
		        });
		        // }} Button Init
		        //Send Data Button initialization
		        final Button datasend = (Button) findViewById(R.id.senddata);
		        datasend.setOnClickListener(new View.OnClickListener() {
					@Override
					public void onClick(View v) {
						// TODO Auto-generated method stub
						//Enter Send Data Code Here
						
					}
				});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}

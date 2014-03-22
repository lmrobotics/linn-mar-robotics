package com.lmrobotics.frcgamescoutfinal.app;

import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.NumberPicker;

/**
 * Created by TV Family on 3/17/14.
 */


public class ObjStor {
    public static NumberPicker autoLGMade;
    public static NumberPicker autoLGMissed;
    public static NumberPicker autoHGMade;
    public static NumberPicker autoHGMissed;
    public static NumberPicker autoHGHot;
    public static CheckBox autoMobBonus;
    public static CheckBox autoHotGoal;
    public static EditText MatchID;
    public static EditText TeamNo;
    public static CheckBox isMatchReplay;
    public static NumberPicker teleLGMade;
    public static NumberPicker teleLGMissed;
    public static NumberPicker teleHGMade;
    public static NumberPicker teleHGMissed;
    public static NumberPicker teleTrussMade;
    public static NumberPicker teleTrussMissed;
    public static NumberPicker telePossesions;
    public static StringBuffer txtpass;
    public static CheckBox teleMobBonus;
    public static NumberPicker telePossessions;
    public static NumberPicker teleADrops;
    public static NumberPicker teleIDrops;

    public static String getTxtpass(){
        //txtpass.ensureCapacity(1000);
        //txtpass.delete(0,txtpass.length());
        txtpass=new StringBuffer();
        txtpass.append(getTeamNo()+","+getMatchId()+","+
                getVal(autoMobBonus)+","+autoHGMade.getValue()+","+autoHGHot.getValue()+","+autoHGMissed.getValue()+","+autoLGMade.getValue()+","+autoLGMissed.getValue()+","+
                teleLGMade.getValue()+","+teleLGMissed.getValue()+","+teleHGMade.getValue()+","+teleHGMissed.getValue()+","+teleTrussMade.getValue()+","+teleTrussMissed.getValue()+","+telePossesions.getValue()+","+teleADrops.getValue()+","+teleIDrops.getValue()+","+
                "3"+","+"An Average Team"+","+"0"+"\n");
        return txtpass.toString();
    }
    public static String getTeamNo(){
        if(TeamNo!=null) {
            return TeamNo.getText().toString();
        }
        else{
            return "";
        }
    }
    public static String getMatchId(){
        if(MatchID!=null) {
            if (!isMatchReplay.isChecked()) {
                return MatchID.getText().toString();
            }
            else{
                return MatchID.getText().toString().concat("R");
            }
        }
        else{
            return "";
        }
    }
    public static int getVal(CheckBox x){
        if(x.isChecked()){
            return 1;
        }
        else{
            return 0;
        }
    }
}

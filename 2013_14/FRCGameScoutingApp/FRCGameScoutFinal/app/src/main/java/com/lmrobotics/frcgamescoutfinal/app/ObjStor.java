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
    public static NumberPicker telePossessions;
    public static NumberPicker teleADrops;
    public static NumberPicker teleIDrops;
    public static EditText supercomments;
    public static NumberPicker fouls;
    public static CheckBox incapacitated;

    public static String getTxtpass(){
        //txtpass.ensureCapacity(1000);
        //txtpass.delete(0,txtpass.length());
        txtpass=new StringBuffer();
        txtpass.append(getTeamNo()+","+getMatchId()+","+
                getVal(autoMobBonus)+","+autoHGHot.getValue()+","+autoHGMade.getValue()+","+autoHGMissed.getValue()+","+autoLGMade.getValue()+","+autoLGMissed.getValue()+","+
                teleHGMade.getValue()+","+teleHGMissed.getValue()+","+teleLGMade.getValue()+","+teleLGMissed.getValue()+","+teleTrussMade.getValue()+","+teleTrussMissed.getValue()+","+telePossesions.getValue()+","+teleADrops.getValue()+","+teleIDrops.getValue()+","+
                fouls.getValue()+","+supercomments.getText()+","+getVal(incapacitated)+"\n");
        return txtpass.toString();
    }
    public static String getComments(EditText x){
        if(x!=null&&x.getText()!=null){
            return x.getText().toString();
        }
        else{
            return " ";
        }
    }
    public static String getTeamNo(){
        if(TeamNo!=null&&TeamNo.getText()!=null) {
            return TeamNo.getText().toString();
        }
        else{
            return "";
        }
    }
    public static String getMatchId(){
        if(MatchID!=null&&MatchID.getText()!=null) {
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
        if(x!=null){
        if(x.isChecked()){
            return 1;
        }
        else{
            return 0;
        }
        }
        else{
            return 0;
        }
    }
}

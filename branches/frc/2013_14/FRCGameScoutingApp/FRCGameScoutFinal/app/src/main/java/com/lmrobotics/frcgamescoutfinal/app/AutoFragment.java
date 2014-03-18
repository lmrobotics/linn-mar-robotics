package com.lmrobotics.frcgamescoutfinal.app;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.NumberPicker;


/**
 * Created by TV Family on 3/16/14.
 */
public class AutoFragment extends Fragment{

    public AutoFragment() {
    }

    public View mView;
    public NumberPicker autoLGMade;
    public NumberPicker autoLGMissed;
    public NumberPicker autoHGMade;
    public NumberPicker autoHGMissed;
    public CheckBox autoMobBonus;
    public CheckBox autoHotGoal;

    public static AutoFragment newInstance() {
        return new AutoFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_auto, container, false);
        this.mView=rootView;
        //AddActivityTextHere
        final NumberPicker autoLGMade = (NumberPicker) rootView.findViewById(R.id.autoLGMade);
        autoLGMade.setMaxValue(3);
        autoLGMade.setMinValue(0);
        autoLGMade.setValue(0);
        this.autoLGMade=autoLGMade;
        final NumberPicker autoLGMissed = (NumberPicker) rootView.findViewById(R.id.autoLGMissed);
        autoLGMissed.setMaxValue(3);
        autoLGMissed.setMinValue(0);
        autoLGMissed.setValue(0);
        this.autoLGMissed=autoLGMissed;
        final NumberPicker autoHGMade = (NumberPicker) rootView.findViewById(R.id.autoHGMade);
        autoHGMade.setMaxValue(3);
        autoHGMade.setMinValue(0);
        autoHGMade.setValue(0);
        this.autoHGMade=autoHGMade;
        final NumberPicker autoHGMissed = (NumberPicker) rootView.findViewById(R.id.autoHGMissed);
        autoHGMissed.setMaxValue(3);
        autoHGMissed.setMinValue(0);
        autoHGMissed.setValue(0);
        this.autoHGMissed=autoHGMissed;
        final CheckBox autoHotGoal = (CheckBox) rootView.findViewById(R.id.hotGoal);
        this.autoHotGoal=autoHotGoal;
        final CheckBox autoMobBonus = (CheckBox) rootView.findViewById(R.id.mobBonus);
        this.autoMobBonus=autoMobBonus;
        return rootView;
    }

    /*@Override
    public void onDetach(){
        ObjStor.MatchID=Integer.parseInt(this.MatchID.getText().toString());
        ObjStor.TeamNo=Integer.parseInt(this.TeamNo.getText().toString());
        ObjStor.matchReplay=this.isMatchReplay.isChecked();
        //Toast.makeText(MyApplication.getAppContext(), "Data Saved to ObjStor", 100).show();
    }*/
}

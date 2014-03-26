package com.lmrobotics.frcgamescoutfinal.app;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.NumberPicker;
import android.widget.Toast;


/**
 * Created by TV Family on 3/16/14.
 */
public class TeleFragment extends Fragment{


    public NumberPicker telePossessions;
    public NumberPicker teleADrops;
    public NumberPicker teleIDrops;
    public CheckBox incapacitated;

    public TeleFragment() {
    }

    public View mView;
    public NumberPicker teleLGMade;
    public NumberPicker teleLGMissed;
    public NumberPicker teleHGMade;
    public NumberPicker teleHGMissed;
    public CheckBox teleMobBonus;
    public NumberPicker teleTrussMade;
    public NumberPicker teleTrussMissed;

    public static TeleFragment newInstance() {
        return new TeleFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_tele, container, false);
        this.mView=rootView;
        //AddActivityTextHere
        final NumberPicker teleLGMade = (NumberPicker) rootView.findViewById(R.id.teleLGMade);
        teleLGMade.setMaxValue(25);
        teleLGMade.setMinValue(0);
        teleLGMade.setValue(0);
        this.teleLGMade=teleLGMade;
        ObjStor.teleLGMade=teleLGMade;
        final NumberPicker teleLGMissed = (NumberPicker) rootView.findViewById(R.id.teleLGMissed);
        teleLGMissed.setMaxValue(25);
        teleLGMissed.setMinValue(0);
        teleLGMissed.setValue(0);
        this.teleLGMissed=teleLGMissed;
        ObjStor.teleLGMissed=teleLGMissed;
        final NumberPicker teleHGMade = (NumberPicker) rootView.findViewById(R.id.teleHGMade);
        teleHGMade.setMaxValue(25);
        teleHGMade.setMinValue(0);
        teleHGMade.setValue(0);
        this.teleHGMade=teleHGMade;
        ObjStor.teleHGMade=teleHGMade;
        final NumberPicker teleHGMissed = (NumberPicker) rootView.findViewById(R.id.teleHGMissed);
        teleHGMissed.setMaxValue(25);
        teleHGMissed.setMinValue(0);
        teleHGMissed.setValue(0);
        this.teleHGMissed=teleHGMissed;
        ObjStor.teleHGMissed=teleHGMissed;
        final NumberPicker teleTrussMade = (NumberPicker) rootView.findViewById(R.id.teleTrussMade);
        teleTrussMade.setMaxValue(25);
        teleTrussMade.setMinValue(0);
        teleTrussMade.setValue(0);
        this.teleTrussMade=teleTrussMade;
        ObjStor.teleTrussMade=teleTrussMade;
        final NumberPicker teleTrussMissed = (NumberPicker) rootView.findViewById(R.id.teleTrussMissed);
        teleTrussMissed.setMaxValue(25);
        teleTrussMissed.setMinValue(0);
        teleTrussMissed.setValue(0);
        this.teleTrussMissed=teleTrussMissed;
        ObjStor.teleTrussMissed=teleTrussMissed;
        final NumberPicker telePossessions = (NumberPicker) rootView.findViewById(R.id.telePossessions);
        telePossessions.setMaxValue(50);
        telePossessions.setMinValue(0);
        telePossessions.setValue(0);
        this.telePossessions=telePossessions;
        ObjStor.telePossesions=telePossessions;
        final NumberPicker teleADrops = (NumberPicker) rootView.findViewById(R.id.teleADrops);
        teleADrops.setMaxValue(50);
        teleADrops.setMinValue(0);
        teleADrops.setValue(0);
        this.teleADrops=teleADrops;
        ObjStor.teleADrops=teleADrops;
        final NumberPicker teleIDrops = (NumberPicker) rootView.findViewById(R.id.teleIDrops);
        teleIDrops.setMaxValue(50);
        teleIDrops.setMinValue(0);
        teleIDrops.setValue(0);
        this.teleIDrops=teleIDrops;
        ObjStor.teleIDrops=teleIDrops;
        final CheckBox incapacitated = (CheckBox) rootView.findViewById(R.id.incapacitated);
        this.incapacitated=incapacitated;
        ObjStor.incapacitated=incapacitated;
        return rootView;
    }

    @Override
    public void onDetach(){
        View v = mView;
        Toast.makeText(v.getContext(), "Pane 2 Detatched", 100).show();
    }
}

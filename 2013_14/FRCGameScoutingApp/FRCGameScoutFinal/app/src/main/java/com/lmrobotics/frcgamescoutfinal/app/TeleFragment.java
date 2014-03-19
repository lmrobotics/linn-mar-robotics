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

    public TeleFragment() {
    }

    public View mView;
    public NumberPicker teleLGMade;
    public NumberPicker teleLGMissed;
    public NumberPicker teleHGMade;
    public NumberPicker teleHGMissed;
    public CheckBox teleMobBonus;
    public CheckBox teleHotGoal;

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
        teleLGMade.setMaxValue(3);
        teleLGMade.setMinValue(0);
        teleLGMade.setValue(0);
        this.teleLGMade=teleLGMade;
        ObjStor.teleLGMade=teleLGMade;
        final NumberPicker teleLGMissed = (NumberPicker) rootView.findViewById(R.id.teleLGMissed);
        teleLGMissed.setMaxValue(3);
        teleLGMissed.setMinValue(0);
        teleLGMissed.setValue(0);
        this.teleLGMissed=teleLGMissed;
        ObjStor.teleLGMissed=teleLGMissed;
        final NumberPicker teleHGMade = (NumberPicker) rootView.findViewById(R.id.teleHGMade);
        teleHGMade.setMaxValue(3);
        teleHGMade.setMinValue(0);
        teleHGMade.setValue(0);
        this.teleHGMade=teleHGMade;
        ObjStor.teleHGMade=teleHGMade;
        final NumberPicker teleHGMissed = (NumberPicker) rootView.findViewById(R.id.teleHGMissed);
        teleHGMissed.setMaxValue(3);
        teleHGMissed.setMinValue(0);
        teleHGMissed.setValue(0);
        this.teleHGMissed=teleHGMissed;
        ObjStor.teleHGMissed=teleHGMissed;
        final CheckBox teleHotGoal = (CheckBox) rootView.findViewById(R.id.hotGoal);
        this.teleHotGoal=teleHotGoal;
        final CheckBox teleMobBonus = (CheckBox) rootView.findViewById(R.id.mobBonus);
        this.teleMobBonus=teleMobBonus;
        this.teleMobBonus=teleMobBonus;
        //Toast.makeText(rootView.getContext(),"OnViewCreated called",Toast.LENGTH_SHORT).show();
        return rootView;
    }

    @Override
    public void onDetach(){
        View v = mView;
        Toast.makeText(v.getContext(), "Pane 2 Detatched", 100).show();
    }
}

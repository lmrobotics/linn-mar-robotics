package com.lmrobotics.frcgamescoutfinal.app;

import android.app.Fragment;
import android.app.FragmentManager;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

/**
 * Created by TV Family on 3/16/14.
 */
public class SetupFragment extends Fragment{

    public SetupFragment() {
    }

    public View mView;
    public EditText MatchID;
    public EditText TeamNo;
    public CheckBox isMatchReplay;

    public static SetupFragment newInstance() {
        return new SetupFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_setup, container, false);
        this.mView=rootView;
        //AddActivityTextHere
        final EditText MatchID=(EditText) rootView.findViewById(R.id.matchID);
        this.MatchID=MatchID;
        ObjStor.MatchID=MatchID;
        final EditText TeamNo = (EditText) rootView.findViewById(R.id.teamNo);
        this.TeamNo=TeamNo;
        ObjStor.TeamNo=TeamNo;
        final CheckBox isMatchReplay = (CheckBox) rootView.findViewById(R.id.matchReplay);
        isMatchReplay.setChecked(false);
        this.isMatchReplay=isMatchReplay;
        ObjStor.isMatchReplay=isMatchReplay;
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

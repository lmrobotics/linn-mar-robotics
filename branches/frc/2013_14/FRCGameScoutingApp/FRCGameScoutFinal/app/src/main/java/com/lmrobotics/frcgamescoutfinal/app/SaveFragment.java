package com.lmrobotics.frcgamescoutfinal.app;

        import android.app.Fragment;
        import android.app.FragmentManager;
        import android.os.Bundle;
        import android.util.AndroidRuntimeException;
        import android.view.LayoutInflater;
        import android.view.View;
        import android.view.ViewGroup;
        import android.widget.Button;
        import android.widget.Toast;

/**
 * Created by TV Family on 3/16/14.
 */
public class SaveFragment extends Fragment {

    public SaveFragment() {
    }

    public View mView;

    public static SaveFragment newInstance() {
        return new SaveFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View rootView = inflater.inflate(R.layout.fragment_save, container, false);
        this.mView=rootView;
        //AddActivityTextHere
        Button save = (Button) rootView.findViewById(R.id.finSave);
        save.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //POC TODO REAL CODE
                Toast.makeText(rootView.getContext(), ((ObjStor.MatchID.getText().toString() + ObjStor.TeamNo.getText().toString() + ObjStor.autoHGMade.getValue())),Toast.LENGTH_LONG).show();
            }
        });
        Button send = (Button) rootView.findViewById(R.id.finSend);
        send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO
            }
        });
        Button reset = (Button) rootView.findViewById(R.id.finReset);
        reset.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO ProofOfConcept NEEDED
                System.gc();

            }
        });
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

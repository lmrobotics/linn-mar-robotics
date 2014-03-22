package com.lmrobotics.frcgamescoutfinal.app;

        import android.app.Fragment;
        import android.app.FragmentManager;
        import android.content.Intent;
        import android.net.Uri;
        import android.os.Bundle;
        import android.os.Environment;
        import android.util.AndroidRuntimeException;
        import android.view.LayoutInflater;
        import android.view.View;
        import android.view.ViewGroup;
        import android.widget.Button;
        import android.widget.Toast;

        import java.io.File;
        import java.io.FileOutputStream;
        import java.io.OutputStreamWriter;

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
                Toast.makeText(rootView.getContext(),"Data Saving."+ObjStor.getTxtpass(),Toast.LENGTH_SHORT).show();
                FileOutputStream outputStream;
                OutputStreamWriter outputStreamWriter;
                try {
                    String externaldirectorypath = Environment.getExternalStorageDirectory().toString() + "/FRCGameData";
                    String internaldirectorypath = Environment.getExternalStorageDirectory().toString() + "/FRCGameData/Version2";
                    File internaldirectoryfile = new File(externaldirectorypath, "Version2");
                    if (!internaldirectoryfile.exists()) {
                        internaldirectoryfile.mkdirs();
                    }
                    File realfilepass = new File(internaldirectorypath, "frc_score_" + ObjStor.getTeamNo() + "_" + ObjStor.getMatchId() + ".csv");
                    if (!realfilepass.exists()) {
                        outputStream = new FileOutputStream(realfilepass, false);
                        outputStreamWriter = new OutputStreamWriter(outputStream);
                    } else {
                        outputStream = new FileOutputStream(realfilepass, true);
                        outputStreamWriter = new OutputStreamWriter(outputStream);
                    }
                    outputStreamWriter.write(ObjStor.getTxtpass());
                    outputStream.write(String.valueOf(ObjStor.getTxtpass()).getBytes());
                }
                catch(Exception e){
                    //I should record the exception, but I won't
                }
            }
        });
        Button send = (Button) rootView.findViewById(R.id.finSend);
        send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(rootView.getContext(),"DataSending",Toast.LENGTH_SHORT).show();
                File file = new File(Environment.getExternalStorageDirectory().toString() + "/FRCGameData/Version2", "frc_score_"+ObjStor.getTeamNo()+"_"+ObjStor.getMatchId()+".csv");

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
                       //No Exception handling
                    }
                }
            }
        });
        Button reset = (Button) rootView.findViewById(R.id.finReset);
        reset.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO ProofOfConcept NEEDED
                System.gc();
                Toast.makeText(rootView.getContext(),"This button doesn't do anything but show this message as of now.",Toast.LENGTH_LONG).show();
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

package com.example.frcpitscout;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import android.os.Environment;
import android.content.Intent;
import android.provider.MediaStore;
import android.net.Uri;


public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	String mCurrentPhotoPath;

	private File createImageFile() throws IOException {
	    // Create an image file name
	   // String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
	    String imageFileName = "JPEG_" +  "_";
	    File storageDir = Environment.getExternalStoragePublicDirectory(
	            Environment.DIRECTORY_PICTURES);
	    File image = File.createTempFile(
	        imageFileName,  /* prefix */
	        ".jpg",         /* suffix */
	        storageDir      /* directory */
	    );

	    // Save a file: path for use with ACTION_VIEW intents
	    mCurrentPhotoPath = "file:" + image.getAbsolutePath();
	    return image;
	}
	static final int REQUEST_TAKE_PHOTO = 1;

	private void dispatchTakePictureIntent() {
	    Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
	    // Ensure that there's a camera activity to handle the intent
	    if (takePictureIntent.resolveActivity(getPackageManager()) != null) {
	        // Create the File where the photo should go
	        File photoFile = null;
	        try {
	            photoFile = createImageFile();
	        } catch (IOException ex) {
	            // Error occurred while creating the File
	        }
	        // Continue only if the File was successfully created
	        if (photoFile != null) {
	            takePictureIntent.putExtra(MediaStore.EXTRA_OUTPUT,
	                    Uri.fromFile(photoFile));
	          //  startActivityForResult(takePictureIntent, REQUEST_TAKE_PHOTO);
	        }
	    }
	}
}

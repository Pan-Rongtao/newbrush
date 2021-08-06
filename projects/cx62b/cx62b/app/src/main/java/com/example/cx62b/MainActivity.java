package com.example.cx62b;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.os.Environment;
import android.view.ViewGroup;
import android.widget.Toast;

import nb.jni.NBSurfaceView;

public class MainActivity extends AppCompatActivity {

    static private MainActivity s_instance;
    public NBSurfaceView mModelView;

    public static MainActivity getInstance() { return s_instance; }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        s_instance = this;

        if (hasStoragePermission(this)) {
            initUI();
        }
    }

    private void initUI() {
        mModelView = new NBSurfaceView(this, "nb_jni_cx62b");
        //mModelView.getHolder().setFormat(PixelFormat.TRANSLUCENT);
        //mModelView.setZOrderOnTop(true);
        this.addContentView(mModelView, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
    }

    private static Boolean hasStoragePermission(Activity activity)
    {
        Boolean b = ActivityCompat.checkSelfPermission(activity,"android.permission.WRITE_EXTERNAL_STORAGE") == PackageManager.PERMISSION_GRANTED;
        if(!b) {
            ActivityCompat.requestPermissions(activity, new String[]{ "android.permission.READ_EXTERNAL_STORAGE", "android.permission.WRITE_EXTERNAL_STORAGE" }, 1);
        }
        return b;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        if(grantResults[0] == PackageManager.PERMISSION_DENIED)
            System.exit(0);

        if (requestCode == 1) {
            initUI();
        }
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

}
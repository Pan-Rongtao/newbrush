package com.example.modelDIY;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.content.res.Resources;
import android.graphics.drawable.Drawable;

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
        mModelView = new NBSurfaceView(this, "nb_jni_modelDIY");
        mModelView.getHolder().setFormat(PixelFormat.TRANSLUCENT);
        mModelView.setZOrderOnTop(true);
        this.addContentView(mModelView, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));

        //隐藏标题栏, 隐藏系统状态栏, 隐藏导航栏
        if (getSupportActionBar()!=null)    getSupportActionBar().hide();
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        int uiOptions = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY | View.SYSTEM_UI_FLAG_FULLSCREEN;
        getWindow().getDecorView().setSystemUiVisibility(uiOptions);
        //this.getWindow().setBackgroundDrawable(getResources().getDrawable(R.drawable.bkcolor));
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
package com.example.cdx706;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.RelativeLayout;

import nb.jni.NBSurfaceView;

public class MainActivity extends AppCompatActivity {

    static private MainActivity s_instance;
    static private int mode = 1;
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
        mModelView = new NBSurfaceView(this, "nb_jni_cdx706", "/storage/emulated/0/resource/");
        mModelView.getHolder().setFormat(PixelFormat.TRANSLUCENT);
        mModelView.setZOrderOnTop(true);
        mModelView.setLayoutParams(new ViewGroup.LayoutParams(756, 756));
        mModelView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_DOWN) {
                    //mModelView.responseTouch(v, event);
                    if (mode == 3) {
                        mode = 1;
                        //mModelView.setBackgroundResource(R.drawable.eco_bg);
                        mModelView.setDataInt("mode", 1);
                    } else if (mode == 1) {
                        mode = 2;
                        //mModelView.setBackgroundResource(R.drawable.normal_bg);
                        mModelView.setDataInt("mode", 2);
                    } else if (mode == 2) {
                        mode = 3;
                        //mModelView.setBackgroundResource(R.drawable.sport_bg);
                        mModelView.setDataInt("mode", 3);
                    }
                }
                return true;
            }
        });
        this.addContentView(mModelView, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        //setContentView(mModelView);
        //隐藏标题栏, 隐藏系统状态栏, 隐藏导航栏
        if (getSupportActionBar()!=null)    getSupportActionBar().hide();
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        int uiOptions = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY | View.SYSTEM_UI_FLAG_FULLSCREEN;
        getWindow().getDecorView().setSystemUiVisibility(uiOptions);
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
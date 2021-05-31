package com.example.app;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;

import nb.jni.NBSurfaceView;

public class MainActivity extends AppCompatActivity {

    static private MainActivity s_instance;
    public NBSurfaceView mModelView;

    public static MainActivity getInstance() { return s_instance; }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mModelView = new NBSurfaceView(this, "nb_jni_modelDIY");
        s_instance = this;
        this.addContentView(mModelView, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));

        //隐藏标题栏：
        if (getSupportActionBar()!=null){
            getSupportActionBar().hide();
        }

        //隐藏系统状态栏
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

        //隐藏导航栏
        int uiOptions = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY | View.SYSTEM_UI_FLAG_FULLSCREEN;
        getWindow().getDecorView().setSystemUiVisibility(uiOptions);
    }

}
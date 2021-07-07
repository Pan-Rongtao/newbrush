package com.example.app;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.ViewGroup;

import nb.jni.NBSurfaceView;

public class MainActivity extends AppCompatActivity {

    static private MainActivity s_instance;
    public NBSurfaceView mModelView;

    public static MainActivity getInstance() { return s_instance; }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mModelView = new NBSurfaceView(this, "nb_jni_radarACM");
        s_instance = this;
        this.addContentView(mModelView, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
    }

}
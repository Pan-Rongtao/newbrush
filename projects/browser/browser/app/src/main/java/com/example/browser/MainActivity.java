package com.example.browser;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.Toast;

import com.leon.lfilepickerlibrary.LFilePicker;
import com.leon.lfilepickerlibrary.utils.Constant;

import java.util.List;

import nb.jni.NBSurfaceView;

public class MainActivity extends AppCompatActivity {

    static private MainActivity s_instance;
    public NBSurfaceView mModelView;
    public ControlView mControlView;

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
        mModelView = new NBSurfaceView(this, "nb_jni_browser", "/storage/emulated/0/resource/");
        mModelView.getHolder().setFormat(PixelFormat.TRANSLUCENT);
        mModelView.setZOrderOnTop(true);
        mControlView = new ControlView(this);
        //mControlView.mRoot.setVisibility(View.INVISIBLE);
        final CheckBox cbShowController = new CheckBox(this);
        cbShowController.setChecked(true);
        //cbShowController.setText("隐藏面板");
        cbShowController.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //cbShowController.setText( cbShowController.isChecked() ? "显示面板" : "隐藏面板");
                mControlView.mRoot.setVisibility(cbShowController.isChecked() ? View.VISIBLE : View.INVISIBLE);
            }
        });
        this.addContentView(mModelView, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        this.addContentView(mControlView.mRoot, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        this.addContentView(cbShowController, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
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

    public void openFilePicker()
    {
        new LFilePicker()
                .withActivity(this)
                .withRequestCode(1000)
                .withStartPath("/storage/emulated/0/resource")//指定初始显示路径
                .withFileFilter(new String[]{".fbx", ".obj"})
                .withMutilyMode(false)
                .start();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode == RESULT_OK) {
            if (requestCode == 1000) {
                List<String> list = data.getStringArrayListExtra(Constant.RESULT_INFO);
                Toast.makeText(getApplicationContext(), "正在打开" + list.get(0), Toast.LENGTH_SHORT).show();

                mModelView.setDataString("NewPath", list.get(0));
            }
        }
    }
}
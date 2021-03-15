package com.example.app;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.Toast;

import com.leon.lfilepickerlibrary.LFilePicker;
import com.leon.lfilepickerlibrary.utils.Constant;

import java.util.List;

import nb.jni.NBSurfaceView;

public class MainActivity extends AppCompatActivity {

    static private MainActivity s_instance;
    public NBSurfaceView mModelView;
    public ControlView mControlView;

    private Button mBtnShowController;

    public static MainActivity getInstance() { return s_instance; }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        verifyStoragePermissions(this);

        mModelView = new NBSurfaceView(this, "nb_jni_browser");
        mControlView = new ControlView(this);
        mBtnShowController = new Button(this);
        mBtnShowController.setText("显示面板");
        mBtnShowController.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(mControlView.mRoot.getVisibility() == View.VISIBLE)
                {
                    mControlView.mRoot.setVisibility(View.INVISIBLE);
                    mBtnShowController.setText("显示面板");
                }
                else
                {
                    mControlView.mRoot.setVisibility(View.VISIBLE);
                    mBtnShowController.setText("隐藏面板");
                }
            }
        });
        s_instance = this;
        this.addContentView(mModelView, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        this.addContentView(mControlView.mRoot, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        this.addContentView(mBtnShowController, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
    }

    private static void verifyStoragePermissions(Activity activity) {
        try {
            //检测是否有写的权限，没有则申请，会弹出对话框
            int permission = ActivityCompat.checkSelfPermission(activity,"android.permission.WRITE_EXTERNAL_STORAGE");
            if (permission != PackageManager.PERMISSION_GRANTED) {
                String[] permissions = { "android.permission.READ_EXTERNAL_STORAGE", "android.permission.WRITE_EXTERNAL_STORAGE" };
                ActivityCompat.requestPermissions(activity, permissions, 1);
            }
        } catch (Exception e) { e.printStackTrace(); }
    }

    private static int REQUESTCODE_FROM_ACTIVITY = 1000;
    public void openFilePicker()
    {
        new LFilePicker()
                .withActivity(this)
                .withRequestCode(REQUESTCODE_FROM_ACTIVITY)
                .withStartPath("/storage/emulated/0/resource")//指定初始显示路径
                .withFileFilter(new String[]{".fbx", ".obj"})
                .withMutilyMode(false)
                .start();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode == RESULT_OK) {
            if (requestCode == REQUESTCODE_FROM_ACTIVITY) {
                List<String> list = data.getStringArrayListExtra(Constant.RESULT_INFO);
                Toast.makeText(getApplicationContext(), "正在打开" + list.get(0), Toast.LENGTH_SHORT).show();

                mModelView.setDataString("NewPath", list.get(0));
            }
        }
    }
}
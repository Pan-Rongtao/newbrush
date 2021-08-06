package com.example.cdx706;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.RelativeLayout;

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
        mModelView = new NBSurfaceView(this, "nb_jni_cdx706");
        //this.addContentView(mModelView, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        /*ViewGroup viewGroup = (ViewGroup) getLayoutInflater().from(this).inflate(R.layout.activity_main, null);
        viewGroup.addView(mModelView);*/
        RelativeLayout rly = new RelativeLayout(this);
        RelativeLayout.LayoutParams lp2 = new RelativeLayout.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        lp2.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
        Button btnOne = new Button(this);
        btnOne.setText("按钮1");
        // 为按钮1设置一个id值
        btnOne.setId(123);
        // 设置按钮1的位置,在父容器中居中
        RelativeLayout.LayoutParams rlp1 = new RelativeLayout.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        rlp1.addRule(RelativeLayout.CENTER_IN_PARENT);
        // 设置按钮2的位置,在按钮1的下方,并且对齐父容器右面
        RelativeLayout.LayoutParams rlp2 = new RelativeLayout.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        rlp2.width = 756;
        rlp2.height = 756;
        rlp2.addRule(RelativeLayout.BELOW, 123);
        rlp2.addRule(RelativeLayout.CENTER_IN_PARENT);
        // 将组件添加到外部容器中
        rly.addView(mModelView, rlp2);
        //rly.addView(btnOne, rlp1);
        //rly.addView(mModelView);
        setContentView(rly);
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
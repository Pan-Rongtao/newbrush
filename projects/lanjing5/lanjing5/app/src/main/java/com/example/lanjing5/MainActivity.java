package com.example.lanjing5;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.FrameLayout;

import nb.jni.NBSurfaceView;

public class MainActivity extends AppCompatActivity {

    static private MainActivity s_instance;
    public NBSurfaceView mModelView;
    private Button mBtnAnim0;
    private Button mBtnAnim1;
    private Button mBtnAnim2;
    private Button mBtnAnim3;

    public static MainActivity getInstance() { return s_instance; }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        s_instance = this;
        if (hasStoragePermission(this)) {
            initUI();
        }
    }

    float touchDownX = 0.0f;
    float touchDownY = 0.0f;
    private void initUI() {
        mModelView = new NBSurfaceView(this, "nb_jni_lanjing5");
        mModelView.getHolder().setFormat(PixelFormat.TRANSLUCENT);
        mModelView.setZOrderOnTop(true);
        mModelView.setLayoutParams(new ViewGroup.LayoutParams(500, 500));
        mModelView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {

                if(event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    touchDownX = event.getX();
                    touchDownY = event.getY();
                //    Log.v("xxx", "down=" + touchDownX + "," + touchDownY);
                }

                float x = mModelView.getTranslationX();
                float y = mModelView.getTranslationY();

                mModelView.setTranslationX(x + event.getX() - touchDownX);
                mModelView.setTranslationY(y + event.getY() - touchDownY);
                return true;
            }
        });
        mModelView.setOnEventListener(new NBSurfaceView.OnEventListener() {
            @Override
            public void onEvent(String eventName, String args){
                Log.i("onEvent", "mModelView.onEvent:eventName=" + eventName + ", args=" + args);
                if(eventName.equals("AnimationStateChangedEvent"))
                {
                    String [] strs = args.split(",");
                    int animationIndex = Integer.parseInt(strs[0]);
                    int animationState = Integer.parseInt(strs[1]);
                    if(animationIndex == 2 && animationState == 1)  //动画2完成后播放动画0
                    {
                        mModelView.setDataInt("AnimationType", 0);
                    }
                }
                else
                {
                    Log.i("onEvent", "unknown event");
                }
            }
        } );
        //this.addContentView(mModelView, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        setContentView(mModelView);
        //隐藏标题栏, 隐藏系统状态栏, 隐藏导航栏
        if (getSupportActionBar()!=null)    getSupportActionBar().hide();
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        int uiOptions = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY | View.SYSTEM_UI_FLAG_FULLSCREEN;
        getWindow().getDecorView().setSystemUiVisibility(uiOptions);
        //this.getWindow().setBackgroundDrawable(getResources().getDrawable(R.drawable.bkcolor));

        mBtnAnim0 = new Button(this);
        mBtnAnim0.setText("动画0");
        mBtnAnim1 = new Button(this);
        mBtnAnim1.setText("动画1");
        mBtnAnim1.setTranslationX(100);
        mBtnAnim2 = new Button(this);
        mBtnAnim2.setText("动画2");
        mBtnAnim2.setTranslationX(200);
        mBtnAnim3 = new Button(this);
        mBtnAnim3.setText("动画3");
        mBtnAnim3.setTranslationX(300);
        mBtnAnim0.setOnClickListener(clickListener);
        mBtnAnim1.setOnClickListener(clickListener);
        mBtnAnim2.setOnClickListener(clickListener);
        mBtnAnim3.setOnClickListener(clickListener);
        this.addContentView(mBtnAnim0, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        this.addContentView(mBtnAnim1, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        this.addContentView(mBtnAnim2, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        this.addContentView(mBtnAnim3, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
    }

    private Button.OnClickListener clickListener = new Button.OnClickListener(){
        @Override
        public void onClick(View v) {
            if(v == mBtnAnim0) {
                mModelView.setDataInt("AnimationType", 0);
            }
            else if(v == mBtnAnim1) {
                mModelView.setDataInt("AnimationType", 1);
            }
            else if(v == mBtnAnim2) {
                mModelView.setDataInt("AnimationType", 0x10000000 | 2);
            }
            else if(v == mBtnAnim3) {
                mModelView.setDataInt("AnimationType", 3);
            }
        }
    };

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
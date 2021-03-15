package com.example.app;
import android.app.Activity;
import android.content.Context;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.GridLayout;
import android.widget.GridView;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.TextView;

import com.leon.lfilepickerlibrary.LFilePicker;

import org.w3c.dom.Text;

public class ControlView extends Activity {

    private SeekBar[] mSbAmbient = new SeekBar[3];
    private SeekBar[] mSbDiffuse = new SeekBar[3];
    private SeekBar[] mSbSpecular = new SeekBar[3];
    private SeekBar[] mSbLightPosition = new SeekBar[3];

    private SeekBar[] mSbTranslate = new SeekBar[3];
    private SeekBar[] mSbRotate = new SeekBar[3];
    private SeekBar mSbScale;
    Button mBtnOpen;

    Button mBtnDoor1;
    Button mBtnDoor2;
    Button mBtnDoor3;
    Button mBtnDoor4;
    Button mBtnDoor5;
    Button mBtnDoor6;
    Button mBtnAnimation;
    boolean mDoor1On = false;
    boolean mDoor2On = false;
    boolean mDoor3On = false;
    boolean mDoor4On = false;
    boolean mDoor5On = false;
    boolean mDoor6On = false;
    boolean mAnimationOn = false;

    LinearLayout mRoot;


    public ControlView(Context context) {

        mRoot = new LinearLayout(context);
        mRoot.setOrientation(LinearLayout.HORIZONTAL);
        mRoot.setTranslationX(100);
        mRoot.setTranslationY(50);
        //mRoot.setLayoutParams(new ViewGroup.LayoutParams(1920, 80));


        LinearLayout layout0 = new LinearLayout(context);
        layout0.setOrientation(LinearLayout.VERTICAL);
        LinearLayout ambientGroup = makeColorGroup(context, "环境光", mSbAmbient, 0, 255, new int[]{125,125,125});
        LinearLayout diffuseGroup = makeColorGroup(context, "漫反射", mSbDiffuse, 0, 255, new int[]{255,255,255});
        LinearLayout specularGroup = makeColorGroup(context, "高光", mSbSpecular, 0, 255, new int[]{0,125,125});
        LinearLayout lightPositionGroup = makeColorGroup(context, "光源位置", mSbLightPosition, -100, 100, new int[]{50,10,50});
        layout0.addView(ambientGroup);
        layout0.addView(diffuseGroup);
        layout0.addView(specularGroup);
        layout0.addView(lightPositionGroup);

        LinearLayout layout1 = new LinearLayout(context);
        layout1.setOrientation(LinearLayout.VERTICAL);
        LinearLayout positionGroup = makeColorGroup(context, "平移", mSbTranslate, -100, 100, new int[]{0,-10,0});
        LinearLayout rotateGroup = makeColorGroup(context, "旋转", mSbRotate, 0, 360, new int[]{0,0,0});
        //LinearLayout scaleGroup = makeColorGroup(context, "缩放", mSbScale, 1, 100, new int[]{15,15,15});
        TextView txtTitle = new TextView(context);
        txtTitle.setText("缩放");
        mSbScale = makeSeekBar(context, 0, 100, 15);
        mSbScale.setOnSeekBarChangeListener(changeListerer);
        mBtnOpen = new Button(context);
        mBtnOpen.setText("打开");
        mBtnOpen.setOnClickListener(clickListener);
        layout1.addView(positionGroup);
        layout1.addView(rotateGroup);
        layout1.addView(txtTitle);
        layout1.addView(mSbScale);
        layout1.addView(mBtnOpen);

        LinearLayout layout2 = new LinearLayout(context);
        layout2.setOrientation(LinearLayout.VERTICAL);
        mBtnDoor1 = new Button(context);
        mBtnDoor1.setText("门1");
        mBtnDoor2 = new Button(context);
        mBtnDoor2.setText("门2");
        mBtnDoor3 = new Button(context);
        mBtnDoor3.setText("门3");
        mBtnDoor4 = new Button(context);
        mBtnDoor4.setText("门4");
        mBtnDoor5 = new Button(context);
        mBtnDoor5.setText("引擎盖");
        mBtnDoor6 = new Button(context);
        mBtnDoor6.setText("后备箱");
        mBtnAnimation = new Button(context);
        mBtnAnimation.setText("动画");
        //mBtnAnimation.setLayoutParams(new ViewGroup.LayoutParams(300, 60));
        mBtnDoor1.setOnClickListener(clickListener);
        mBtnDoor2.setOnClickListener(clickListener);
        mBtnDoor3.setOnClickListener(clickListener);
        mBtnDoor4.setOnClickListener(clickListener);
        mBtnDoor5.setOnClickListener(clickListener);
        mBtnDoor6.setOnClickListener(clickListener);
        mBtnAnimation.setOnClickListener(clickListener);
        layout2.addView(mBtnDoor1);
        layout2.addView(mBtnDoor2);
        layout2.addView(mBtnDoor3);
        layout2.addView(mBtnDoor4);
        layout2.addView(mBtnDoor5);
        layout2.addView(mBtnDoor6);
        layout2.addView(mBtnAnimation);

        mRoot.addView(layout0);
        mRoot.addView(layout1);
        mRoot.addView(layout2);
    }

    private SeekBar.OnSeekBarChangeListener changeListerer = new SeekBar.OnSeekBarChangeListener(){
        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            MainActivity.getInstance().mModelView.setDataColor("Ambient", mSbAmbient[0].getProgress(), mSbAmbient[1].getProgress(), mSbAmbient[2].getProgress(), 255);
            MainActivity.getInstance().mModelView.setDataColor("Diffuse", mSbDiffuse[0].getProgress(), mSbDiffuse[1].getProgress(), mSbDiffuse[2].getProgress(), 255);
            MainActivity.getInstance().mModelView.setDataColor("Specular", mSbSpecular[0].getProgress(), mSbSpecular[1].getProgress(), mSbSpecular[2].getProgress(), 255);
            MainActivity.getInstance().mModelView.setDataVec3("LightPosition", mSbLightPosition[0].getProgress() * 0.1f, mSbLightPosition[1].getProgress() * 0.1f, mSbLightPosition[2].getProgress() * 0.1f);
            MainActivity.getInstance().mModelView.setDataVec3("Translate", mSbTranslate[0].getProgress() * 0.1f, mSbTranslate[1].getProgress() * 0.1f, mSbTranslate[2].getProgress() * 0.1f);
            MainActivity.getInstance().mModelView.setDataVec3("Rotate", mSbRotate[0].getProgress() * (float)(Math.PI/180), mSbRotate[1].getProgress() * (float)(Math.PI/180), mSbRotate[2].getProgress() * (float)(Math.PI/180));
            if(seekBar == mSbScale)
                MainActivity.getInstance().mModelView.setDataVec3("Scale", mSbScale.getProgress() * 0.005f, mSbScale.getProgress() * 0.005f, mSbScale.getProgress() * 0.005f);
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar) { }

        @Override
        public void onStopTrackingTouch(SeekBar seekBar) { }
    };

    private Button.OnClickListener clickListener = new Button.OnClickListener(){
        @Override
        public void onClick(View v) {
            if(v == mBtnDoor1)
            {
                mDoor1On = !mDoor1On;
                MainActivity.getInstance().mModelView.setDataBool("Door1Switch", mDoor1On);
            }
            else if(v == mBtnDoor2)
            {
                mDoor2On = !mDoor2On;
                MainActivity.getInstance().mModelView.setDataBool("Door2Switch", mDoor2On);
            }
            else if(v == mBtnDoor3)
            {
                mDoor3On = !mDoor3On;
                MainActivity.getInstance().mModelView.setDataBool("Door3Switch", mDoor3On);
            }
            else if(v == mBtnDoor4)
            {
                mDoor4On = !mDoor4On;
                MainActivity.getInstance().mModelView.setDataBool("Door4Switch", mDoor4On);
            }
            else if(v == mBtnDoor5)
            {
                mDoor5On = !mDoor5On;
                MainActivity.getInstance().mModelView.setDataBool("Door5Switch", mDoor5On);
            }
            else if(v == mBtnDoor6)
            {
                mDoor6On = !mDoor6On;
                MainActivity.getInstance().mModelView.setDataBool("Door6Switch", mDoor6On);
            }
            else if(v == mBtnAnimation)
            {
                mAnimationOn = !mAnimationOn;
                MainActivity.getInstance().mModelView.setDataBool("AllSwitch", mAnimationOn);
            }
            else if(v == mBtnOpen)
            {
                openFilePicker();
            }
        }
    };

    private SeekBar makeSeekBar(Context context, int min, int max, int value) {
        SeekBar sb = new SeekBar(context);
        sb.setMin(min);
        sb.setMax(max);
        sb.setLayoutParams(new ViewGroup.LayoutParams(300, 60));
        sb.setProgress(value);
        return sb;
    }

    private LinearLayout makeColorGroup(Context context, String title, SeekBar[] sbs, int min, int max, int[] value){

        LinearLayout group = new LinearLayout(context);
        group.setOrientation(LinearLayout.VERTICAL);
        TextView txtTitle = new TextView(context);
        txtTitle.setText(title);
        sbs[0] = makeSeekBar(context, min, max, value[0]);
        sbs[1] = makeSeekBar(context, min, max, value[1]);
        sbs[2] = makeSeekBar(context, min, max, value[2]);

        sbs[0].setOnSeekBarChangeListener(changeListerer);
        sbs[1].setOnSeekBarChangeListener(changeListerer);
        sbs[2].setOnSeekBarChangeListener(changeListerer);

        sbs[0].setProgress(value[0]);
        sbs[1].setProgress(value[1]);
        sbs[2].setProgress(value[2]);

        group.addView(txtTitle);
        group.addView(sbs[0]);
        group.addView(sbs[1]);
        group.addView(sbs[2]);

        return group;
    }

    public void openFilePicker()
    {
        MainActivity.getInstance().openFilePicker();
    }

}

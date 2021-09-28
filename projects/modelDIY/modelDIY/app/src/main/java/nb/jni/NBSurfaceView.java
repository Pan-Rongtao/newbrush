package nb.jni;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

public class NBSurfaceView extends GLSurfaceView {

    private NBRenderer mRenderer;
    private static OnEventListener mOnEventListener;

    public NBSurfaceView(Context context, String pluginName) {
        super(context);

        setEGLContextClientVersion(2);
        //setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        setEGLConfigChooser(new NBConfigChooser());
        mRenderer = new NBRenderer(pluginName);
        setRenderer(mRenderer);
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);

        setOnTouchListener(new OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) { mRenderer.getPlugin().touch(event.getAction(), event.getX(), event.getY()); return true; }
        });
    }

    public void setDataBool(String path, boolean value)                         { mRenderer.getPlugin().setData(path, String.valueOf(value)); }
    public void setDataInt(String path, int value)                              { mRenderer.getPlugin().setData(path, String.valueOf(value)); }
    public void setDataFloat(String path, float value)                          { mRenderer.getPlugin().setData(path, String.valueOf(value)); }
    public void setDataString(String path, String value)                        { mRenderer.getPlugin().setData(path, value); }
    public void setDataColor(String path, int r, int g, int b, int a)           { mRenderer.getPlugin().setData(path, String.format("%d,%d,%d,%d", a, r, g, b)); }
    public void setDataVec2(String path, float x, float y)                      { mRenderer.getPlugin().setData(path, String.format("%f,%f", x, y)); }
    public void setDataVec3(String path, float x, float y, float z)             { mRenderer.getPlugin().setData(path, String.format("%f,%f,%f", x, y, z)); }
    public void setDataVec4(String path, float x, float y, float z, float w)    { mRenderer.getPlugin().setData(path, String.format("%f,%f,%f,%f", x, y, z, w)); }

    public interface OnEventListener                                            { public void onEvent(String eventName, String args); }
    public void setOnEventListener(OnEventListener l)                           { mOnEventListener = l; }
    public static void onNBEvent(String eventName, String args)                 { if(mOnEventListener != null) mOnEventListener.onEvent(eventName, args); }
}

class NBConfigChooser implements GLSurfaceView.EGLConfigChooser{
    @Override
    public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {

        int attribs[] = {
                EGL10.EGL_LEVEL, 0,
                EGL10.EGL_RENDERABLE_TYPE, 4,  // EGL_OPENGL_ES2_BIT
                EGL10.EGL_COLOR_BUFFER_TYPE, EGL10.EGL_RGB_BUFFER,
                EGL10.EGL_RED_SIZE, 8,
                EGL10.EGL_GREEN_SIZE, 8,
                EGL10.EGL_BLUE_SIZE, 8,
                EGL10.EGL_ALPHA_SIZE, 8,
                EGL10.EGL_DEPTH_SIZE, 16,
                EGL10.EGL_SAMPLE_BUFFERS, 1,
                EGL10.EGL_SAMPLES, 4,  // 在这里修改MSAA的倍数，4就是4xMSAA，再往上开程序可能会崩
                EGL10.EGL_NONE
        };
        EGLConfig[] configs = new EGLConfig[1];
        int[] configCounts = new int[1];
        egl.eglChooseConfig(display, attribs, configs, 1, configCounts);

        return configCounts[0] == 0 ? null : configs[0];
    }
}

class NBRenderer implements GLSurfaceView.Renderer
{
    static String LogTAG = "[ModelRenderer]";
    private Newbrush mNB;

    public NBRenderer(String pluginName)                                     { Log.i(LogTAG, "ModelRenderer create "); mNB = new Newbrush(pluginName); }
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config)                     { Log.i(LogTAG, "onSurfaceCreated"); mNB.init(); }
    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height)                { Log.i(LogTAG, "onSurfaceChanged"); mNB.resize(width, height); }
    @Override
    public void onDrawFrame(GL10 gl)                                            { /*Log.i(LogTAG, "onDrawFrame");*/ mNB.render(); }
    Newbrush getPlugin()                                                        { return mNB; }
}

class Newbrush {

    public Newbrush(String soPath) {
        Log.i("[Newbrush]", "load so");
        System.loadLibrary(soPath);
    }

    public native void init();
    public native void resize(int width, int height);
    public native void render();
    public native void touch(int action, float x, float y);
    public native void setData(String path, String v);
}
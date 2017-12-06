package com.example.javierchapa.myapplication;

import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    private GLSurfaceView glSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        AssetManager assetManager = getAssets();
        String pathToInternalDir = getFilesDir().getAbsolutePath();
        JNIWrapper.assign_asset_manager(assetManager, pathToInternalDir);

        glSurfaceView = new GLSurfaceView(this);
        glSurfaceView.setEGLContextClientVersion(2);
        glSurfaceView.setRenderer(new RendererWrapper());
        setContentView(glSurfaceView);
    }

    @Override
    protected void onPause() {
        super.onPause();
        glSurfaceView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        glSurfaceView.onResume();
    }
}

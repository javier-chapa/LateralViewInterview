package com.example.javierchapa.myapplication;

import android.content.res.AssetManager;

public class JNIWrapper {

    static {
        System.loadLibrary("native-lib");
    }

    public static native void on_surface_created();

    public static native void on_surface_changed(int width, int height);

    public static native void on_draw_frame();

    public static native void assign_asset_manager(AssetManager assetManager, String pathToInternalDir);
}

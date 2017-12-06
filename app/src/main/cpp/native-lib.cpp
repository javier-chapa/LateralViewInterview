#include <jni.h>
#include <android/asset_manager_jni.h>
#include <renderer.h>
#include <Utilities/asset.h>

using namespace std;

extern "C"
{
    Renderer *renderer;
    Asset *asset;

    JNIEXPORT void JNICALL Java_com_example_javierchapa_myapplication_JNIWrapper_on_1surface_1created(JNIEnv *env, jclass clazz) {
        renderer = new Renderer();
        renderer->Init();
    }

    JNIEXPORT void JNICALL Java_com_example_javierchapa_myapplication_JNIWrapper_on_1surface_1changed(JNIEnv *env, jclass clazz, jint width, jint height) {
        renderer->Resize(width, height);
    }

    JNIEXPORT void JNICALL Java_com_example_javierchapa_myapplication_JNIWrapper_on_1draw_1frame(JNIEnv *env, jclass clazz) {
        renderer->Draw();
    }

    JNIEXPORT void JNICALL Java_com_example_javierchapa_myapplication_JNIWrapper_assign_1asset_1manager(JNIEnv *env, jclass clazz, jobject assetManager, jstring pathToInternalDir) {
        asset = new Asset(env, clazz, assetManager, pathToInternalDir);
    }
};
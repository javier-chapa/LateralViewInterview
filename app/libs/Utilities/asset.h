#pragma once

#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <pthread.h>
#include <string>

using namespace std;

class Asset
{
private:
    AAssetManager *apkAssetManager;
    string apkInternalPath;
    mutable pthread_mutex_t threadMutex;
    string GetFileName(string fileName);

public:
    Asset(JNIEnv *env, jobject obj, jobject assetManager, jstring pathToInternalDir);
    bool ExtractAssetReturnFilename(string, string &, bool = false);
};

extern "C"
{
    extern Asset *asset;
};
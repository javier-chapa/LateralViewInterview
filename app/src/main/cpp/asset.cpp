#include <Utilities/asset.h>

Asset::Asset(JNIEnv *env, jobject obj, jobject assetManager, jstring pathToInternalDir) {
    apkAssetManager = AAssetManager_fromJava(env, assetManager);
    const char *cPathToInternalDir;
    cPathToInternalDir = env->GetStringUTFChars(pathToInternalDir, NULL ) ;
    apkInternalPath = string(cPathToInternalDir);
    env->ReleaseStringUTFChars(pathToInternalDir, cPathToInternalDir);
    pthread_mutex_init(&threadMutex, NULL );
}

string Asset::GetFileName(string fileName) {
    string::size_type slashIndex = fileName.find_last_of("/");

    string onlyName;
    if (slashIndex == string::npos) {
        onlyName = fileName.substr(0, string::npos);
    } else {
        onlyName = fileName.substr(slashIndex + 1, string::npos);
    }

    return onlyName;
}

bool Asset::ExtractAssetReturnFilename(string assetName, string &filename, bool checkIfFileIsAvailable) {
    filename = apkInternalPath + "/" + GetFileName(assetName);

    FILE* file = fopen(filename.c_str(), "rb");
    if (file && checkIfFileIsAvailable) {

        fclose(file);
        pthread_mutex_unlock( &threadMutex);
        return true;

    }

    bool result = false;

    pthread_mutex_lock( &threadMutex);

    AAsset* asset = AAssetManager_open(apkAssetManager, assetName.c_str(), AASSET_MODE_STREAMING);

    char buf[BUFSIZ];
    int nb_read = 0;
    if (asset != NULL)
    {
        FILE* out = fopen(filename.c_str(), "w");
        while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0)
        {
            fwrite(buf, nb_read, 1, out);
        }
        fclose(out);
        AAsset_close(asset);
        result = true;
    }

    pthread_mutex_unlock( &threadMutex);
    return result;
}

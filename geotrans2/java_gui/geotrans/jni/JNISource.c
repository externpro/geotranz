#include <jni.h>
#include "string.h"
#include "source.h"
#include "ThrowException.h"



JNIEXPORT jlong JNICALL Java_geotrans_jni_JNISource_JNISourceCount(JNIEnv *env, jobject obj)
{
    long count = 0;

    Source_Count(&count);

    return count;
}


JNIEXPORT jlong JNICALL Java_geotrans_jni_JNISource_JNISourceIndex(JNIEnv *env, jobject obj, jstring name)
{
    long index = 0;
    const char *sourceName;

    sourceName = (*env)->GetStringUTFChars(env, name, NULL);
    if (sourceName == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return index;
    }

    if (Source_Index(sourceName, &index))
        throwException(env, "geotrans/jni/GeotransError", "Error getting source index.");

    (*env)->ReleaseStringUTFChars(env, name, sourceName);

    return index;
}


JNIEXPORT jstring JNICALL Java_geotrans_jni_JNISource_JNISourceName(JNIEnv *env, jobject obj, jlong index)
{
    char sourceName[50];
    jstring jStr = NULL;

    if (Source_Name((long)index, sourceName))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting source name.");
        return jStr;
    }

    jStr = (*env)->NewStringUTF(env, sourceName);
    if (jStr == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");

    return jStr;
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNISource_JNISourceAccuracy(JNIEnv *env, jobject obj, jlong index)
{

    double ce90, le90, se90;
    long errorCode = 0;
    jclass cls;
    jmethodID cid;
    
    if(Source_Accuracy((long)index, &ce90, &le90, &se90))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting source accuracy");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/gui/Accuracy");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Accuracy class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Accuracy method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, ce90, le90, se90);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Accuracy object could not be created.");

    return obj;
}


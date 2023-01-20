#include <jni.h>
#include "strtoval.h"
#include "ThrowException.h"


JNIEXPORT jstring JNICALL Java_geotrans_jni_JNIStrtoval_JNIErrorPrefix(JNIEnv *env, jobject obj, jint direction, jint system)
{
    char str[60];
    jstring jStr = NULL;

    Error_Prefix(direction, system, "", str);
    jStr = ((*env)->NewStringUTF(env, str));
    if (jStr == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");

    return jStr;
}


JNIEXPORT jstring JNICALL Java_geotrans_jni_JNIStrtoval_JNILatitudeToString(JNIEnv *env, jobject obj, jdouble latitude, jboolean use_NSEW, jboolean use_Minutes, jboolean use_Seconds)
{
    char str[15];
    jstring jStr = NULL;

    if (Latitude_to_String(latitude, str, use_NSEW, use_Minutes, use_Seconds))
    {
        throwException(env, "geotrans/jni/GeotransError", "Invalid latitude.");
        return jStr;
    }

    jStr = ((*env)->NewStringUTF(env, str));
    if (jStr == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");

    return jStr;
}


JNIEXPORT jstring JNICALL Java_geotrans_jni_JNIStrtoval_JNILongitudeToString(JNIEnv *env, jobject obj, jdouble longitude, jboolean use_NSEW, jboolean use_Minutes, jboolean use_Seconds)
{
    char str[15];
    jstring jStr = NULL;

    if (Longitude_to_String(longitude, str, use_NSEW, use_Minutes, use_Seconds))
    {
        throwException(env, "geotrans/jni/GeotransError", "Invalid longitude.");
        return jStr;
    }

    jStr = ((*env)->NewStringUTF(env, str));
    if (jStr == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");

    return jStr;
}


JNIEXPORT jstring JNICALL Java_geotrans_jni_JNIStrtoval_JNIMeterToString(JNIEnv *env, jobject obj, jdouble meters)
{
    char str[15];
    jstring jStr = NULL;

    if (Meter_to_String(meters, str))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error converting meters to string.");
        return jStr;
    }

    jStr = ((*env)->NewStringUTF(env, str));
    if (jStr == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");

    return jStr;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIStrtoval_JNISetSeparator(JNIEnv *env, jobject obj, jchar separator)
{
    Set_Separator((char)separator);
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIStrtoval_JNISetLongRange(JNIEnv *env, jobject obj, jint range)
{
    Set_Long_Range(range);
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIStrtoval_JNISetLatLongPrecision(JNIEnv *env, jobject obj, jlong precis)
{
    Set_Lat_Long_Precision((long)precis);
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIStrtoval_JNIShowLeadingZeros(JNIEnv *env, jobject obj, jboolean lz)
{
    Show_Leading_Zeros(lz);
}


JNIEXPORT jdouble JNICALL Java_geotrans_jni_JNIStrtoval_JNIStringToDouble(JNIEnv *env, jobject obj, jstring jStr)
{
    long errorCode = 0;
    double num = 0;
    const char *cStr;

    cStr = (*env)->GetStringUTFChars(env, jStr, NULL);
    if (cStr == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return num;
    }

    if (String_to_Double(cStr, &num))
        throwException(env, "geotrans/jni/GeotransError", "Error converting string to double.");

    (*env)->ReleaseStringUTFChars(env, jStr, cStr);

    return num;
}


JNIEXPORT jdouble JNICALL Java_geotrans_jni_JNIStrtoval_JNIStringToLatitude(JNIEnv *env, jobject obj, jstring jStr)
{
    double lat = 0;
    const char *cStr;

    cStr = (*env)->GetStringUTFChars(env, jStr, NULL);
    if (cStr == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return lat;
    }

    if (String_to_Latitude(cStr, &lat))
        throwException(env, "geotrans/jni/GeotransError", "Invalid latitude string.");

    (*env)->ReleaseStringUTFChars(env, jStr, cStr);

    return lat;
}


JNIEXPORT jlong JNICALL Java_geotrans_jni_JNIStrtoval_JNIStringToLong(JNIEnv *env, jobject obj, jstring jStr)
{
    long num = 0;
    const char *cStr;

    cStr = (*env)->GetStringUTFChars(env, jStr, NULL);
    if (cStr == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return num;
    }

    if (String_to_Long(cStr, &num))
        throwException(env, "geotrans/jni/GeotransError", "Error converting string to long.");

    (*env)->ReleaseStringUTFChars(env, jStr, cStr);

    return num;
}


JNIEXPORT jdouble JNICALL Java_geotrans_jni_JNIStrtoval_JNIStringToLongitude(JNIEnv *env, jobject obj, jstring jStr)
{
    double lon = 0;
    const char *cStr;

    cStr = (*env)->GetStringUTFChars(env, jStr, NULL);
    if (cStr == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return lon;
    }

    if (String_to_Longitude(cStr, &lon))
        throwException(env, "geotrans/jni/GeotransError", "Invalid longitude string.");

    (*env)->ReleaseStringUTFChars(env, jStr, cStr);

    return lon;
}



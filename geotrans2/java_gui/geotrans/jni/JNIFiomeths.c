#include <jni.h>
#include "fiomeths.h"
#include "ThrowException.h"



long numErrors = 0;
long numProcessed = 0;
long numWarnings = 0;

JNIEXPORT void JNICALL Java_geotrans_jni_JNIFiomeths_JNIWriteExampleCoord(JNIEnv *env, jobject obj)
{
    long errorCode = 0;

    errorCode = Write_Example_Coord();
    if (errorCode)
        throwException(env, "geotrans/jni/GeotransError", "Error creating header file");
}

JNIEXPORT void JNICALL Java_geotrans_jni_JNIFiomeths_JNICloseInputFile(JNIEnv *env, jobject obj)
{
    Close_Input_File();
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIFiomeths_JNICloseOutputFile(JNIEnv *env, jobject obj)
{
    Close_Output_File();
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIFiomeths_JNIConvertFile(JNIEnv *env, jobject obj)
{
    if (Convert_File(&numErrors, &numProcessed, &numWarnings))
        throwException(env, "geotrans/jni/GeotransError", "Error parsing input file.");
}


JNIEXPORT jstring JNICALL Java_geotrans_jni_JNIFiomeths_JNIGetFileErrorString(JNIEnv *env, jobject obj, jlong error)
{
    char str[128];
    jstring jStr = NULL;

    Get_File_Error_String((long)error, str);
    jStr = ((*env)->NewStringUTF(env, str));
    if (jStr == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");

    return jStr;
}


JNIEXPORT jlong JNICALL Java_geotrans_jni_JNIFiomeths_JNIGetNumErrors(JNIEnv *env, jobject obj)
{
    return numErrors;
}


JNIEXPORT jlong JNICALL Java_geotrans_jni_JNIFiomeths_JNIGetNumProcessed(JNIEnv *env, jobject obj)
{
    return numProcessed;
}

JNIEXPORT jlong JNICALL Java_geotrans_jni_JNIFiomeths_JNIGetNumWarnings(JNIEnv *env, jobject obj)
{
    return numWarnings;
}

JNIEXPORT void JNICALL Java_geotrans_jni_JNIFiomeths_JNISetInputFilename(JNIEnv *env, jobject obj, jstring name)
{
    long errorCode = 0;
    char str[128];
    const char *fileName;

    fileName = (*env)->GetStringUTFChars(env, name, NULL);
    if(fileName == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }
    errorCode = Set_Input_Filename(fileName);
    if (errorCode)
    {
        Get_File_Error_String(errorCode, str);
        throwException(env, "geotrans/jni/GeotransError", str);
    }

    (*env)->ReleaseStringUTFChars(env, name, fileName);
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIFiomeths_JNISetOutputFilename(JNIEnv *env, jobject obj, jstring name)
{
    const char *filename;

    filename = (*env)->GetStringUTFChars(env, name, NULL);
    if(filename == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }

    if (Set_Output_Filename(filename))
        throwException(env, "geotrans/jni/GeotransError", "Error opening output file.");

    (*env)->ReleaseStringUTFChars(env, name, filename);
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIFiomeths_JNIUseNSEW(JNIEnv *env, jobject obj, jboolean useNSEW)
{
    Use_NSEW(useNSEW);
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIFiomeths_JNIUseMinutes(JNIEnv *env, jobject obj, jboolean useMinutes)
{
    Use_Minutes(useMinutes);
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIFiomeths_JNIUseSeconds(JNIEnv *env, jobject obj, jboolean useSeconds)
{
    Use_Seconds(useSeconds);
}


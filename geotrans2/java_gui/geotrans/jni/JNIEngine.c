#include <jni.h>
#include "string.h"
#include "engine.h"
#include "ThrowException.h"


JNIEXPORT jint JNICALL Java_geotrans_jni_JNIEngine_JNICheckValidConversion(JNIEnv *env, jobject obj, jint input_system, jint output_system, jint input_datum, jint output_datum)
{
  return Valid_Conversion(input_system, output_system, input_datum, output_datum);
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNIConvert(JNIEnv *env, jobject obj, jint state)
{
    long errorCode = 0;
    char errStr[256];

    errorCode = Convert(state);
    if (errorCode & ENGINE_INPUT_ERROR)
    {
        Get_Conversion_Status_String(Interactive,Input,"\n",errStr);
        throwException(env, "geotrans/jni/GeotransError", errStr);
    }
    else if (errorCode & ENGINE_INPUT_WARNING)
    {
        Get_Conversion_Status_String(Interactive,Input,"\n",errStr);
        throwException(env, "geotrans/jni/GeotransWarning", errStr);

    }
    if (errorCode & ENGINE_OUTPUT_ERROR)
    {
        Get_Conversion_Status_String(Interactive,Output,"\n",errStr);
        throwException(env, "geotrans/jni/GeotransError", errStr);
    }
    else if (errorCode & ENGINE_OUTPUT_WARNING)
    {
        Get_Conversion_Status_String(Interactive,Output,"\n",errStr);
        throwException(env, "geotrans/jni/GeotransWarning", errStr);
    }
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNIDefine3ParamDatum(JNIEnv *env, jobject obj, 
                                                                        jstring datCode, 
                                                                        jstring datName, 
                                                                        jstring ellipCode, 
                                                                        jdouble deltaX, 
                                                                        jdouble deltaY, 
                                                                        jdouble deltaZ, 
                                                                        jdouble sigmaX, 
                                                                        jdouble sigmaY, 
                                                                        jdouble sigmaZ, 
                                                                        jdouble southLat, 
                                                                        jdouble northLat, 
                                                                        jdouble westLon, 
                                                                        jdouble eastLon)
{
    long errorCode = 0;
    char errStr[256];
    const char *datumCode;
    const char *datumName;
    const char *ellipsoidCode;

    datumCode = (*env)->GetStringUTFChars(env, datCode, NULL);
    if (datumCode == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }

    datumName = (*env)->GetStringUTFChars(env, datName, NULL);
    if (datumName == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }

    ellipsoidCode = (*env)->GetStringUTFChars(env, ellipCode, NULL);
    if (ellipsoidCode == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }

    errorCode = Define_Datum(Three_Param_Datum_Type, datumCode, datumName, ellipsoidCode, deltaX, deltaY, deltaZ,
                    sigmaX, sigmaY, sigmaZ, southLat, northLat, westLon, eastLon, 0, 0, 0, 0);
    if (errorCode)
    {
        Get_Return_Code_String(errorCode, "\n", errStr);
        throwException(env, "geotrans/jni/GeotransError", errStr);
    }

    (*env)->ReleaseStringUTFChars(env, datCode, datumCode);
    (*env)->ReleaseStringUTFChars(env, datName, datumName);
    (*env)->ReleaseStringUTFChars(env, ellipCode, ellipsoidCode);
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNIDefine7ParamDatum(JNIEnv *env, jobject obj, 
                                                                        jstring datCode, 
                                                                        jstring datName, 
                                                                        jstring ellipCode, 
                                                                        jdouble deltaX, 
                                                                        jdouble deltaY, 
                                                                        jdouble deltaZ, 
                                                                        jdouble rotationX, 
                                                                        jdouble rotationY, 
                                                                        jdouble rotationZ, 
                                                                        jdouble scaleFactor)
{
    long errorCode = 0;
    char errStr[256];
    const char *datumCode;
    const char *datumName;
    const char *ellipsoidCode;

    datumCode = (*env)->GetStringUTFChars(env, datCode, NULL);
    if (datumCode == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }

    datumName = (*env)->GetStringUTFChars(env, datName, NULL);
    if (datumName == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }

    ellipsoidCode = (*env)->GetStringUTFChars(env, ellipCode, NULL);
    if (ellipsoidCode == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }

    errorCode = Define_Datum(Seven_Param_Datum_Type, datumCode, datumName, ellipsoidCode, deltaX, deltaY, deltaZ,
                    -1, -1, -1, -90, 90, -180, 180, rotationX, rotationY, rotationZ, scaleFactor);
    if (errorCode)
    {
        Get_Return_Code_String(errorCode, "\n", errStr);
        throwException(env, "geotrans/jni/GeotransError", errStr);
    }

    (*env)->ReleaseStringUTFChars(env, datCode, datumCode);
    (*env)->ReleaseStringUTFChars(env, datName, datumName);
    (*env)->ReleaseStringUTFChars(env, ellipCode, ellipsoidCode);
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNIDefineEllipsoid(JNIEnv *env, jobject obj, 
                                                                  jstring ellipCode, 
                                                                  jstring ellipName, 
                                                                  jdouble a, 
                                                                  jdouble f)
{
    long errorCode = 0;
    char errStr[256];
    const char *ellipsoidCode;
    const char *ellipsoidName;

    ellipsoidCode = (*env)->GetStringUTFChars(env, ellipCode, NULL);
    if (ellipsoidCode == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }

    ellipsoidName = (*env)->GetStringUTFChars(env, ellipName, NULL);
    if (ellipsoidName == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }

    errorCode = Define_Ellipsoid(ellipsoidCode, ellipsoidName, a, f);
    if (errorCode)
    {
        Get_Return_Code_String(errorCode, "\n", errStr);
        throwException(env, "geotrans/jni/GeotransError", errStr);
    }

    (*env)->ReleaseStringUTFChars(env, ellipCode, ellipsoidCode);
    (*env)->ReleaseStringUTFChars(env, ellipName, ellipsoidName);
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNIRemoveDatum(JNIEnv *env, jobject obj, jstring datCode)
{
    long errorCode = 0;
    char errStr[256];
    const char *datumCode;

    datumCode = (*env)->GetStringUTFChars(env, datCode, NULL);
    if (datumCode == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }
    
    errorCode = Remove_Datum(datumCode);
    if (errorCode)
    {
        Get_Return_Code_String(errorCode, "\n", errStr);
        throwException(env, "geotrans/jni/GeotransError", errStr);
    }

    (*env)->ReleaseStringUTFChars(env, datCode, datumCode);
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNIRemoveEllipsoid(JNIEnv *env, jobject obj, jstring ellipCode)
{
    long errorCode = 0;
    char errStr[256];
    const char *ellipsoidCode;

    ellipsoidCode = (*env)->GetStringUTFChars(env, ellipCode, NULL);
    if (ellipsoidCode == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }
    
    errorCode = Remove_Ellipsoid(ellipsoidCode);
    if (errorCode)
    {
        Get_Return_Code_String(errorCode, "\n", errStr);
        throwException(env, "geotrans/jni/GeotransError", errStr);
    }

    (*env)->ReleaseStringUTFChars(env, ellipCode, ellipsoidCode);
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNIInitializeEngine(JNIEnv *env, jobject obj)
{
  char error_str[256] = "Error initializing GEOTRANS engine:";
  long error_code = Initialize_Engine();   

  // Check for ellipsoid file errors
  if (error_code  & ENGINE_ELLIPSOID_ERROR)
    strcat(error_str, "\n    Unable to locate ellipsoid data file: ellips.dat");

  if (error_code  & ENGINE_ELLIPSOID_OVERFLOW)
    strcat(error_str, "\n    Ellipsoid table is full");

  if (error_code  & ENGINE_INVALID_CODE_ERROR)
    strcat(error_str, "\n    Invalid ellipsoid code");

  // Check for datum file errors
  if (error_code  & ENGINE_DATUM_ERROR)
    strcat(error_str, "\n    Unable to locate datum data files: 3_param.dat, 7_param.dat");
  if (error_code  & ENGINE_DATUM_OVERFLOW)
    strcat(error_str, "\n    Datum table is full");

  if (error_code  & ENGINE_DATUM_FILE_PARSE_ERROR)
    strcat(error_str, "\n    Unable to read datum file");

  // Check for geoid file errors
  if (error_code  & ENGINE_GEOID_ERROR)
    strcat(error_str, "\n    Unable to locate geoid data files: egm84.grd, egm96.grd");

  if (error_code  & ENGINE_GEOID_FILE_PARSE_ERROR)
    strcat(error_str, "\n    Unable to read geoid file");

  if(error_code)
  {
    strcat(error_str, "!");
    throwException(env, "geotrans/jni/GeotransError", error_str);
  }
} 


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetConversionErrors(JNIEnv *env, jobject obj, jint state)
{
    double ce90, le90, se90;
    long errorCode = 0;
    jclass cls;
    jmethodID cid;
    
    if(Get_Conversion_Errors(state, &ce90, &le90, &se90))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting conversion errors");
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


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetConversionErrors(JNIEnv *env, jobject obj, jint state, jdouble ce90, jdouble le90, jdouble se90)
{
    if (Set_Conversion_Errors(state, ce90, le90, se90))
        throwException(env, "geotrans/jni/GeotransError", "Error setting conversion errors.");
}


JNIEXPORT jstring JNICALL Java_geotrans_jni_JNIEngine_JNIGetCoordinateSystemCode(JNIEnv *env, jobject obj, jint coordSystem)
{
    char coordSystemCode[10];
    jstring jStr = NULL;

    if (Get_Coordinate_System_Code((long)coordSystem, coordSystemCode))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting coordinate system code.");
        return jStr;
    }

    jStr = (*env)->NewStringUTF(env, coordSystemCode);
    if (jStr == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");

    return jStr;
}


JNIEXPORT jint JNICALL Java_geotrans_jni_JNIEngine_JNIGetCoordinateSystem(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Coordinate_Type coordSystem = 0;

    if (Get_Coordinate_System(state, direction, &coordSystem))
        throwException(env, "geotrans/jni/GeotransError", "Error getting coordinate system.");

    return coordSystem;
     
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetCoordinateSystem(JNIEnv *env, jobject obj, jint state, jint direction, jint coordSystem)
{

    if (Set_Coordinate_System(state, direction, coordSystem))
        throwException(env, "geotrans/jni/GeotransError", "Error setting coordinate system.");
}



JNIEXPORT jlong JNICALL Java_geotrans_jni_JNIEngine_JNIGetDatum(JNIEnv *env, jobject obj, jint state, jint direction)
{
    long index = 0;

    if (Get_Datum(state, direction, &index))
        throwException(env, "geotrans/jni/GeotransError", "Error getting datum.");

    return index;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetDatum(JNIEnv *env, jobject obj, jint state, jint direction, jlong index)
{
    if(Set_Datum(state, direction, (long)index+1))
        throwException(env, "geotrans/jni/GeotransError", "Error setting datum.");
}


JNIEXPORT jstring JNICALL Java_geotrans_jni_JNIEngine_JNIGetDatumCode(JNIEnv *env, jobject obj, jlong index)
{
    char datumCode[10];
    jstring jStr = NULL;

    if (Get_Datum_Code((long)index, datumCode))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting datum code.");
        return jStr;
    }

    jStr = (*env)->NewStringUTF(env, datumCode);
    if (jStr == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");

    return jStr;
}


JNIEXPORT jlong JNICALL Java_geotrans_jni_JNIEngine_JNIGetDatumCount(JNIEnv *env, jobject obj)
{
    long count = 0;

    if (Get_Datum_Count(&count))
        throwException(env, "geotrans/jni/GeotransError", "Error getting datum count.");

    return count;
}


JNIEXPORT jlong JNICALL Java_geotrans_jni_JNIEngine_JNIGetDatumIndex(JNIEnv *env, jobject obj, jstring datCode)
{
    long index = 0;
    const char *datumCode;

    datumCode = (*env)->GetStringUTFChars(env, datCode, NULL);
    if (datumCode == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return index;
    }

    if (Get_Datum_Index(datumCode, &index))
        throwException(env, "geotrans/jni/GeotransError", "Error getting datum index.");

    (*env)->ReleaseStringUTFChars(env, datCode, datumCode);

    return index;
}


JNIEXPORT jstring JNICALL Java_geotrans_jni_JNIEngine_JNIGetDatumName(JNIEnv *env, jobject obj, jlong index)
{
    char datumName[40];
    jstring jStr = NULL;

    if (Get_Datum_Name((long)index, datumName))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting datum name.");
        return jStr;
    }

    jStr = (*env)->NewStringUTF(env, datumName);
    if (jStr == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");

    return jStr;
}


JNIEXPORT jstring JNICALL Java_geotrans_jni_JNIEngine_JNIGetDatumEllipsoidCode(JNIEnv *env, jobject obj, jlong index)
{
    char datumEllipsoidCode[10];
    jstring jStr = NULL;

    if (Get_Datum_Ellipsoid_Code((long)index, datumEllipsoidCode))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting datum ellipsoid code.");
        return jStr;
    }

    jStr = (*env)->NewStringUTF(env, datumEllipsoidCode);
    if (jStr == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");

    return jStr;
}


JNIEXPORT jstring JNICALL Java_geotrans_jni_JNIEngine_JNIGetEllipsoidCode(JNIEnv *env, jobject obj, jlong index)
{
    char ellipsoidCode[10];
    jstring jStr = NULL;

    if (Get_Ellipsoid_Code((long)index, ellipsoidCode))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting ellipsoid code.");
        return jStr;
    }

    jStr = (*env)->NewStringUTF(env, ellipsoidCode);
    if (jStr == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");

    return jStr;
}


JNIEXPORT jlong JNICALL Java_geotrans_jni_JNIEngine_JNIGetEllipsoidCount(JNIEnv *env, jobject obj)
{
    long count = 0;

    if (Get_Ellipsoid_Count(&count))
        throwException(env, "geotrans/jni/GeotransError", "Error getting ellipsoid count.");

    return count;
}


JNIEXPORT jlong JNICALL Java_geotrans_jni_JNIEngine_JNIGetEllipsoidIndex(JNIEnv *env, jobject obj, jstring code)
{
    long index = 0;
    const char *ellipsoidCode;

    ellipsoidCode = (*env)->GetStringUTFChars(env, code, NULL);
    if (ellipsoidCode == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return index;
    }

    if (Get_Ellipsoid_Index(ellipsoidCode, &index))
        throwException(env, "geotrans/jni/GeotransError", "Error getting ellipsoid index.");

    (*env)->ReleaseStringUTFChars(env, code, ellipsoidCode);

    return index;
}


JNIEXPORT jstring JNICALL Java_geotrans_jni_JNIEngine_JNIGetEllipsoidName(JNIEnv *env, jobject obj, jlong index)
{
    char ellipsoidName[40];
    jstring jStr = NULL;

    if (Get_Ellipsoid_Name((long)index, ellipsoidName))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting ellipsoid name.");
        return jStr;
    }

    jStr = (*env)->NewStringUTF(env, ellipsoidName);
    if (jStr == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");

    return jStr;
}


JNIEXPORT jint JNICALL Java_geotrans_jni_JNIEngine_JNIGetPrecision(JNIEnv *env, jobject obj)
{
  Precision precis;

  Get_Precision(&precis);
  return precis;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetPrecision(JNIEnv *env, jobject obj, jint precis)
{
    Set_Precision(precis);
}


// Get/Set Albers Equal Area Conic Coordinates/Parameters
JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetAlbersEqualAreaConicParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Albers_Equal_Area_Conic_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Albers_Equal_Area_Conic_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Albers Equal Area Conic parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/AlbersEqualAreaConic");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: AlbersEqualAreaConic class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: AlbersEqualAreaConic method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.central_meridian, params.std_parallel_1, params.std_parallel_2, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: AlbersEqualAreaConic object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetAlbersEqualAreaConicParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Albers_Equal_Area_Conic_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "std_parallel_1", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Std parallel 1 field ID error.");
        return;
    }
    params.std_parallel_1 = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "std_parallel_2", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Std parallel 2 field ID error.");
        return;
    }
    params.std_parallel_2 = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Albers_Equal_Area_Conic_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Albers Equal Area Conic parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetAlbersEqualAreaConicCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Albers_Equal_Area_Conic_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Albers_Equal_Area_Conic_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Albers Equal Area Conic coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/AlbersEqualAreaConic");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: AlbersEqualAreaConic class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: AlbersEqualAreaConic method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: AlbersEqualAreaConic object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetAlbersEqualAreaConicCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Albers_Equal_Area_Conic_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Albers_Equal_Area_Conic_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Albers Equal Area Conic coordinates could not be set");
}

// Get/Set Azimuthal Equidistant Coordinates/Parameters
JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetAzimuthalEquidistantParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Azimuthal_Equidistant_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Azimuthal_Equidistant_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Azimuthal Equidistant parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/AzimuthalEquidistant");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: AzimuthalEquidistant class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: AzimuthalEquidistant method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.central_meridian, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: AzimuthalEquidistant object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetAzimuthalEquidistantParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Azimuthal_Equidistant_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Azimuthal_Equidistant_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Azimuthal Equidistant parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetAzimuthalEquidistantCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Azimuthal_Equidistant_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Azimuthal_Equidistant_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Azimuthal Equidistant coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/AzimuthalEquidistant");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: AzimuthalEquidistant class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: AzimuthalEquidistant method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: AzimuthalEquidistant object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetAzimuthalEquidistantCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Azimuthal_Equidistant_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Azimuthal_Equidistant_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Azimuthal Equidistant coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetBonneParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Bonne_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Bonne_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Bonne parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/projections/Bonne");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Bonne class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Bonne method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.central_meridian, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Bonne object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetBonneParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Bonne_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Bonne_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Bonne parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetBonneCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Bonne_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Bonne_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Bonne coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Bonne");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Bonne class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Bonne method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Bonne object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetBonneCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Bonne_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Bonne_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Bonne coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetBNGCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    BNG_Tuple coords;
    jclass cls;
    jmethodID cid;
    jstring jStr;


    if (Get_BNG_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting British National Grid coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/BNG");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: BNG class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(Ljava/lang/String;)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: BNG method id not found.");
        return obj;
    }

    jStr = (*env)->NewStringUTF(env, coords.string);
    obj = (*env)->NewObject(env, cls, cid, jStr);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: BNG object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetBNGCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    BNG_Tuple coords;
    jclass cls;
    jfieldID fid;
    jstring jStr;
    const char *str;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "coordinateString", "Ljava/lang/String;");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Coordinate string field ID error.");
        return;
    }
    jStr = (*env)->GetObjectField(env, jCoords, fid);
    str = (*env)->GetStringUTFChars(env, jStr, NULL);
    if (str == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }

    strcpy(coords.string, str);
    if (Set_BNG_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "BNG coordinates could not be set");

    (*env)->ReleaseStringUTFChars(env, jStr, str);
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetCassiniParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Cassini_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Cassini_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Cassini parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Cassini");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Cassini class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Cassini method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.central_meridian, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Cassini object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetCassiniParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Cassini_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Cassini_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Cassini parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetCassiniCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Cassini_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Cassini_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Cassini coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Cassini");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Cassini class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Cassini method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Cassini object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetCassiniCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Cassini_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Cassini_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Cassini coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetCylindricalEqualAreaParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Cylindrical_Equal_Area_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Cylindrical_Equal_Area_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Cylindrical Equal Area parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/CylindricalEqualArea");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: CylindricalEqualArea class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: CylindricalEqualArea method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.central_meridian, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: CylindricalEqualArea object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetCylindricalEqualAreaParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Cylindrical_Equal_Area_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Cylindrical_Equal_Area_Params(state, direction, params))
        throwException(env, "geotrans/jni/jni/GeotransError", "Cylindrical Equal Area parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetCylindricalEqualAreaCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Cylindrical_Equal_Area_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Cylindrical_Equal_Area_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/jni/GeotransError", "Error getting Cylindrical Equal Area coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/CylindricalEqualArea");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: CylindricalEqualArea class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: CylindricalEqualArea method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: CylindricalEqualArea object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetCylindricalEqualAreaCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Cylindrical_Equal_Area_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Cylindrical_Equal_Area_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/jni/GeotransError", "CylindricalEqualArea coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetEckert4Params(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Eckert4_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Eckert4_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/jni/GeotransError", "Error getting Eckert4 parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Eckert4");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Eckert4 class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Eckert4 method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.central_meridian, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Eckert4 object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetEckert4Params(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Eckert4_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Eckert4_Params(state, direction, params))
        throwException(env, "geotrans/jni/jni/GeotransError", "Cylindrical Equal Area parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetEckert4Coordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Eckert4_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Eckert4_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Eckert4 coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Eckert4");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Eckert4 class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Eckert4 method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Eckert4 object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetEckert4Coordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Eckert4_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Eckert4_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Eckert4 coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetEckert6Params(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Eckert6_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Eckert6_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Eckert6 parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Eckert6");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Eckert6 class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Eckert6 method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.central_meridian, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Eckert6 object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetEckert6Params(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Eckert6_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Eckert6_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Eckert6 parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetEckert6Coordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Eckert6_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Eckert6_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Eckert6 coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Eckert6");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Eckert6 class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Eckert6 method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Eckert6 object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetEckert6Coordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Eckert6_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Eckert6_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Eckert6 coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetEquidistantCylindricalParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Equidistant_Cylindrical_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Equidistant_Cylindrical_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Equidistant Cylindrical parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/EquidistantCylindrical");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: EquidistantCylindrical class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: EquidistantCylindrical method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.std_parallel, params.central_meridian, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: EquidistantCylindrical object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetEquidistantCylindricalParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Equidistant_Cylindrical_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "std_parallel", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Std parallel field ID error.");
        return;
    }
    params.std_parallel = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Equidistant_Cylindrical_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Equidistant Cylindrical parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetEquidistantCylindricalCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Equidistant_Cylindrical_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Equidistant_Cylindrical_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Equidistant Cylindrical coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/EquidistantCylindrical");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: EquidistantCylindrical class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: EquidistantCylindrical method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: EquidistantCylindrical object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetEquidistantCylindricalCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Equidistant_Cylindrical_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Equidistant_Cylindrical_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "EquidistantCylindrical coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetGARSCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    GARS_Tuple coords;
    jclass cls;
    jmethodID cid;
    jstring jStr;


    if (Get_GARS_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting GARS coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/GARS");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: GARS class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(Ljava/lang/String;)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: GARS method id not found.");
        return obj;
    }

    jStr = (*env)->NewStringUTF(env, coords.string);
    obj = (*env)->NewObject(env, cls, cid, jStr);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: GARS object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetGARSCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    GARS_Tuple coords;
    jclass cls;
    jfieldID fid;
    jstring jStr;
    const char *str;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "coordinateString", "Ljava/lang/String;");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Coordinate string field ID error.");
        return;
    }
    jStr = (*env)->GetObjectField(env, jCoords, fid);
    str = (*env)->GetStringUTFChars(env, jStr, NULL);
    if (str == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }

    strcpy(coords.string, str);

    if (Set_GARS_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "GARS coordinates could not be set");

    (*env)->ReleaseStringUTFChars(env, jStr, str);
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetGeocentricCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Geocentric_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Geocentric_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Geocentric coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Geocentric");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Geocentric class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Geocentric method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.x, coords.y, coords.z);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Geocentric object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetGeocentricCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Geocentric_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "x", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: X field ID error.");
        return;
    }
    coords.x = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "y", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Y field ID error.");
        return;
    }
    coords.y = (*env)->GetDoubleField(env, jCoords, fid);
   
    fid = (*env)->GetFieldID(env, cls, "z", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Z field ID error.");
        return;
    }
    coords.z = (*env)->GetDoubleField(env, jCoords, fid);

    if (Set_Geocentric_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Geocentric coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetGeodeticParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Geodetic_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Geodetic_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Geodetic parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Geodetic");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Geodetic class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(I)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Geodetic method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.height_type);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Geodetic object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetGeodeticParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Geodetic_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "heightType", "I");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Height Type field ID error.");
        return;
    }
    params.height_type = (*env)->GetIntField(env, jParams, fid);

    if (Set_Geodetic_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Equidistant Cylindrical parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetGeodeticCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Geodetic_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Geodetic_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Geodetic coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Geodetic");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Geodetic class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Geodetic method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.longitude, coords.latitude, coords.height);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Geodetic object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetGeodeticCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Geodetic_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "longitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Longitude field ID error.");
        return;
    }
    coords.longitude = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Latitude field ID error.");
        return;
    }
    coords.latitude = (*env)->GetDoubleField(env, jCoords, fid);
   
    fid = (*env)->GetFieldID(env, cls, "height", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Height field ID error.");
        return;
    }
    coords.height = (*env)->GetDoubleField(env, jCoords, fid);

    if (Set_Geodetic_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Geodetic coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetGEOREFCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    GEOREF_Tuple coords;
    jclass cls;
    jmethodID cid;
    jstring jStr;


    if (Get_GEOREF_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting GEOREF coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/GEOREF");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: GEOREF class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(Ljava/lang/String;)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: GEOREF method id not found.");
        return obj;
    }

    jStr = (*env)->NewStringUTF(env, coords.string);
    obj = (*env)->NewObject(env, cls, cid, jStr);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: GEOREF object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetGEOREFCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    GEOREF_Tuple coords;
    jclass cls;
    jfieldID fid;
    jstring jStr;
    const char *str;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "coordinateString", "Ljava/lang/String;");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Coordinate string field ID error.");
        return;
    }
    jStr = (*env)->GetObjectField(env, jCoords, fid);
    str = (*env)->GetStringUTFChars(env, jStr, NULL);
    if (str == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }

    strcpy(coords.string, str);

    if (Set_GEOREF_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "GEOREF coordinates could not be set");

    (*env)->ReleaseStringUTFChars(env, jStr, str);
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetGnomonicParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Gnomonic_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Gnomonic_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Gnomonic parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Gnomonic");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Gnomonic class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Gnomonic method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.central_meridian, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Gnomonic object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetGnomonicParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Gnomonic_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Gnomonic_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Gnomonic parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetGnomonicCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Gnomonic_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Gnomonic_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Gnomonic coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Gnomonic");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Gnomonic class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Gnomonic method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Gnomonic object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetGnomonicCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Gnomonic_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Gnomonic_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Gnomonic coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetLambertConformalConic1Params(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Lambert_Conformal_Conic_1_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Lambert_Conformal_Conic_1_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Lambert Conformal Conic 1 parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/LambertConformalConic1");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LambertConformalConic1 class not found.");
        return NULL;
    }
    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LambertConformalConic1 method id not found.");
        return NULL;
    }
    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.central_meridian, params.false_easting, params.false_northing, params.scale_factor);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LambertConformalConic1 object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetLambertConformalConic1Params(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Lambert_Conformal_Conic_1_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
      
    fid = (*env)->GetFieldID(env, cls, "scale_factor", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Scale factor field ID error.");
        return;
    }
    params.scale_factor = (*env)->GetDoubleField(env, jParams, fid);

    if (Set_Lambert_Conformal_Conic_1_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Lambert Conformal Conic 1 parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetLambertConformalConic1Coordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Lambert_Conformal_Conic_1_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Lambert_Conformal_Conic_1_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Lambert Conformal Conic 1 coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/LambertConformalConic1");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LambertConformalConic1 class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LambertConformalConic1 method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LambertConformalConic1 object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetLambertConformalConic1Coordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Lambert_Conformal_Conic_1_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Lambert_Conformal_Conic_1_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "LambertConformalConic1 coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetLambertConformalConic2Params(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Lambert_Conformal_Conic_2_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Lambert_Conformal_Conic_2_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Lambert Conformal Conic 2 parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/LambertConformalConic2");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LambertConformalConic2 class not found.");
        return NULL;
    }
    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LambertConformalConic2 method id not found.");
        return NULL;
    }
    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.central_meridian, params.std_parallel_1, params.std_parallel_2, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LambertConformalConic2 object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetLambertConformalConic2Params(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Lambert_Conformal_Conic_2_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "std_parallel_1", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Std parallel 1 field ID error.");
        return;
    }
    params.std_parallel_1 = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "std_parallel_2", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Std parallel 2 field ID error.");
        return;
    }
    params.std_parallel_2 = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
      
    if (Set_Lambert_Conformal_Conic_2_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Lambert Conformal Conic 2 parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetLambertConformalConic2Coordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Lambert_Conformal_Conic_2_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Lambert_Conformal_Conic_2_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Lambert Conformal Conic 2 coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/LambertConformalConic2");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LambertConformalConic2 class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LambertConformalConic2 method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LambertConformalConic2 object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetLambertConformalConic2Coordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Lambert_Conformal_Conic_2_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Lambert_Conformal_Conic_2_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "LambertConformalConic2 coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetLocalCartesianParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Local_Cartesian_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Local_Cartesian_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Local Cartesian parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/LocalCartesian");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LocalCartesian class not found.");
        return NULL;
    }
    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LocalCartesian method id not found.");
        return NULL;
    }
    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.origin_longitude, params.origin_height, params.orientation);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LocalCartesian object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetLocalCartesianParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Local_Cartesian_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "origin_longitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin longitude field ID error.");
        return;
    }
    params.origin_longitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "origin_height", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin height field ID error.");
        return;
    }
    params.origin_height = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "orientation", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Orientation field ID error.");
        return;
    }
    params.orientation = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Local_Cartesian_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Local Cartesian parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetLocalCartesianCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Local_Cartesian_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Local_Cartesian_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Local Cartesian coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/LocalCartesian");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LocalCartesian class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LocalCartesian method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.x, coords.y, coords.z);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: LocalCartesian object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetLocalCartesianCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Local_Cartesian_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "x", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: X field ID error.");
        return;
    }
    coords.x = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "y", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Y field ID error.");
        return;
    }
    coords.y = (*env)->GetDoubleField(env, jCoords, fid);
   
    fid = (*env)->GetFieldID(env, cls, "z", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Z field ID error.");
        return;
    }
    coords.z = (*env)->GetDoubleField(env, jCoords, fid);

    if (Set_Local_Cartesian_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "LocalCartesian coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetMercatorParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Mercator_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Mercator_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Mercator parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Mercator");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Mercator class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Mercator method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.latitude_of_true_scale, params.central_meridian, params.scale_factor, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Mercator object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetMercatorParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Mercator_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "latitude_of_true_scale", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Latitude_of_true_scale field ID error.");
        return;
    }
    params.latitude_of_true_scale = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "scale_factor", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Scale factor field ID error.");
        return;
    }
    params.scale_factor = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Mercator_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Mercator parameters could not be set");

}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetMercatorCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Mercator_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Mercator_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Mercator coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Mercator");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Mercator class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Mercator method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Mercator object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetMercatorCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Mercator_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Mercator_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Mercator coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetMGRSCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    MGRS_Tuple coords;
    jclass cls;
    jmethodID cid;
    jstring jStr;


    if (Get_MGRS_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting MGRS coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/MGRS");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: MGRS class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(Ljava/lang/String;)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: MGRS method id not found.");
        return obj;
    }

    jStr = (*env)->NewStringUTF(env, coords.string);
    obj = (*env)->NewObject(env, cls, cid, jStr);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: MGRS object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetMGRSCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    MGRS_Tuple coords;
    jclass cls;
    jfieldID fid;
    jstring jStr;
    const char *str;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "coordinateString", "Ljava/lang/String;");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Coordinate string field ID error.");
        return;
    }
    jStr = (*env)->GetObjectField(env, jCoords, fid);
    str = (*env)->GetStringUTFChars(env, jStr, NULL);
    if (str == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }

    strcpy(coords.string, str);

    if (Set_MGRS_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "MGRS coordinates could not be set");

    (*env)->ReleaseStringUTFChars(env, jStr, str);
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetMillerCylindricalParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Miller_Cylindrical_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Miller_Cylindrical_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Miller Cylindrical parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/MillerCylindrical");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: MillerCylindrical class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: MillerCylindrical method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.central_meridian, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: MillerCylindrical object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetMillerCylindricalParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Miller_Cylindrical_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Miller_Cylindrical_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Miller Cylindrical parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetMillerCylindricalCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Miller_Cylindrical_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Miller_Cylindrical_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Miller Cylindrical coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/MillerCylindrical");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: MillerCylindrical class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: MillerCylindrical method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: MillerCylindrical object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetMillerCylindricalCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Miller_Cylindrical_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Miller_Cylindrical_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "MillerCylindrical coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetMollweideParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Mollweide_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Mollweide_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Mollweide parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Mollweide");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Mollweide class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Mollweide method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.central_meridian, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Mollweide object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetMollweideParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Mollweide_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Mollweide_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Mollweide parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetMollweideCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Mollweide_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Mollweide_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Mollweide coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Mollweide");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Mollweide class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Mollweide method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Mollweide object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetMollweideCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Mollweide_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Mollweide_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Mollweide coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetNeysParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Neys_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Neys_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Neys parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Neys");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Neys class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Neys method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.central_meridian, params.std_parallel_1, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Neys object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetNeysParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Neys_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "std_parallel_1", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Std parallel 1 field ID error.");
        return;
    }
    params.std_parallel_1 = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Neys_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Neys parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetNeysCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Neys_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Neys_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Neys coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Neys");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Neys class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Neys method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Neys object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetNeysCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Neys_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Neys_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Neys coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetNZMGCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    NZMG_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_NZMG_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting New Zealand Map Grid coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/NZMG");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: NZMG class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: NZMG method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: NZMG object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetNZMGCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    NZMG_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_NZMG_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "NZMG coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetObliqueMercatorParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Oblique_Mercator_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Oblique_Mercator_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Oblique Mercator parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/ObliqueMercator");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: ObliqueMercator class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDDDDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: ObliqueMercator method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.latitude_1, params.longitude_1, params.latitude_2, params.longitude_2, params.scale_factor, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: ObliqueMercator object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetObliqueMercatorParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Oblique_Mercator_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "latitude_1", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Latitude 1 field ID error.");
        return;
    }
    params.latitude_1 = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "longitude_1", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Longitude 1 field ID error.");
        return;
    }
    params.longitude_1 = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "latitude_2", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Latitude 2 field ID error.");
        return;
    }
    params.latitude_2 = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "longitude_2", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Longitude 2 field ID error.");
        return;
    }
    params.longitude_2 = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "scale_factor", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Scale factor field ID error.");
        return;
    }
    params.scale_factor = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Oblique_Mercator_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Oblique Mercator parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetObliqueMercatorCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Oblique_Mercator_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Oblique_Mercator_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Oblique Mercator coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/ObliqueMercator");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: ObliqueMercator class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: ObliqueMercator method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: ObliqueMercator object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetObliqueMercatorCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Oblique_Mercator_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Oblique_Mercator_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "ObliqueMercator coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetOrthographicParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Orthographic_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Orthographic_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Orthographic parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Orthographic");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Orthographic class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Orthographic method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.central_meridian, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Orthographic object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetOrthographicParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Orthographic_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Orthographic_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Oblique Mercator parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetOrthographicCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Orthographic_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Orthographic_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Orthographic coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Orthographic");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Orthographic class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Orthographic method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Orthographic object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetOrthographicCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Orthographic_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Orthographic_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Orthographic coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetPolarStereographicParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Polar_Stereo_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Polar_Stereo_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Polar Stereographic parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/PolarStereographic");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: PolarStereographic class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: PolarStereographic method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.latitude_of_true_scale, params.longitude_down_from_pole, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: PolarStereographic object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetPolarStereographicParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Polar_Stereo_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "latitude_of_true_scale", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Latitude of true scale field ID error.");
        return;
    }
    params.latitude_of_true_scale = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "longitude_down_from_pole", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Longitude down from pole field ID error.");
        return;
    }
    params.longitude_down_from_pole = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Polar_Stereo_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Oblique Mercator parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetPolarStereographicCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Polar_Stereo_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Polar_Stereo_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Polar Stereographic coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/PolarStereographic");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: PolarStereographic class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: PolarStereographic method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: PolarStereographic object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetPolarStereographicCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Polar_Stereo_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Polar_Stereo_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "PolarStereographic coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetPolyconicParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Polyconic_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Polyconic_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Polyconic parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Polyconic");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Polyconic class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Polyconic method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.central_meridian, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Polyconic object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetPolyconicParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Polyconic_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Polyconic_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Polyconic parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetPolyconicCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Polyconic_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Polyconic_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Polyconic coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Polyconic");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Polyconic class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Polyconic method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Polyconic object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetPolyconicCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Polyconic_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Polyconic_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Polyconic coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetSinusoidalParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Sinusoidal_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Sinusoidal_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Sinusoidal parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Sinusoidal");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Sinusoidal class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Sinusoidal method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.central_meridian, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Sinusoidal object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetSinusoidalParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Sinusoidal_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Sinusoidal_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Sinusoidal parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetSinusoidalCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Sinusoidal_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Sinusoidal_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Sinusoidal coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Sinusoidal");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Sinusoidal class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Sinusoidal method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Sinusoidal object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetSinusoidalCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Sinusoidal_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Sinusoidal_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Sinusoidal coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetStereographicParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Stereographic_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Stereographic_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Stereographic parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Stereographic");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Stereographic class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Stereographic method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.central_meridian, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Stereographic object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetStereographicParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Stereographic_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Stereographic_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Sinusoidal parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetStereographicCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Stereographic_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Stereographic_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Stereographic coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/Stereographic");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Stereographic class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Stereographic method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Stereographic object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetStereographicCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Stereographic_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Stereographic_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "Stereographic coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetTransverseCylindricalEqualAreaParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Transverse_Cylindrical_Equal_Area_Parameters params;
    jclass cls;
    jmethodID cid;

    if (Get_Transverse_Cylindrical_Equal_Area_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting TransverseCylindricalEqualArea parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/TransverseCylindricalEqualArea");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Transverse Cylindrical Equal Area class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: TransverseCylindricalEqualArea method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.central_meridian, params.scale_factor, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: TransverseCylindricalEqualArea object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetTransverseCylindricalEqualAreaParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Transverse_Cylindrical_Equal_Area_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "scale_factor", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Scale factor field ID error.");
        return;
    }
    params.scale_factor = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Transverse_Cylindrical_Equal_Area_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Transverse Cylindrical Equal Area parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetTransverseCylindricalEqualAreaCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Transverse_Cylindrical_Equal_Area_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Transverse_Cylindrical_Equal_Area_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Transverse Cylindrical Equal Area coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/TransverseCylindricalEqualArea");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: TransverseCylindricalEqualArea class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: TransverseCylindricalEqualArea method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: TransverseCylindricalEqualArea object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetTransverseCylindricalEqualAreaCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Transverse_Cylindrical_Equal_Area_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Transverse_Cylindrical_Equal_Area_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "TransverseCylindricalEqualArea coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetTransverseMercatorParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Transverse_Mercator_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Transverse_Mercator_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Transverse Mercator parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/TransverseMercator");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: TransverseMercator class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDDDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: TransverseMercator method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.origin_latitude, params.central_meridian, params.scale_factor, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: TransverseMercator object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetTransverseMercatorParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Transverse_Mercator_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "origin_latitude", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Origin latitude field ID error.");
        return;
    }
    params.origin_latitude = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "scale_factor", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Scale factor field ID error.");
        return;
    }
    params.scale_factor = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Transverse_Mercator_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Transverse Mercator parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetTransverseMercatorCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Transverse_Mercator_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Transverse_Mercator_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Transverse Mercator coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/TransverseMercator");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: TransverseMercator class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: TransverseMercator method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: TransverseMercator object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetTransverseMercatorCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Transverse_Mercator_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Transverse_Mercator_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "TransverseMercator coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetUPSCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    UPS_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_UPS_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting UPS coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/UPS");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: UPS class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDC)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: UPS method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing, coords.hemisphere);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: UPS object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetUPSCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    UPS_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    fid = (*env)->GetFieldID(env, cls, "hemisphere", "C");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Hemisphere field ID error.");
        return;
    }
    coords.hemisphere = (char)(*env)->GetCharField(env, jCoords, fid);

    if (Set_UPS_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "UPS coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetUSNGCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    USNG_Tuple coords;
    jclass cls;
    jmethodID cid;
    jstring jStr;


    if (Get_USNG_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting USNG coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/USNG");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: USNG class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(Ljava/lang/String;)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: USNG method id not found.");
        return obj;
    }

    jStr = (*env)->NewStringUTF(env, coords.string);
    obj = (*env)->NewObject(env, cls, cid, jStr);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: USNG object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetUSNGCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    USNG_Tuple coords;
    jclass cls;
    jfieldID fid;
    jstring jStr;
    const char *str;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "coordinateString", "Ljava/lang/String;");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Coordinate string field ID error.");
        return;
    }
    jStr = (*env)->GetObjectField(env, jCoords, fid);
    str = (*env)->GetStringUTFChars(env, jStr, NULL);
    if (str == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Out of memory.");
        return;
    }

    strcpy(coords.string, str);

    if (Set_USNG_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "USNG coordinates could not be set");

    (*env)->ReleaseStringUTFChars(env, jStr, str);
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetUTMParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    UTM_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "zone", "J");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Zone field ID error.");
        return;
    }
    params.zone = (long)(*env)->GetLongField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "override", "J");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Override field ID error.");
        return;
    }
    params.override = (long)(*env)->GetLongField(env, jParams, fid);

    if (Set_UTM_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "UTM parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetUTMCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    UTM_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_UTM_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting UTM coordinates");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/UTM");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: UTM class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDIC)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: UTM method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing, coords.zone, coords.hemisphere);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: UTM object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetUTMCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    UTM_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    fid = (*env)->GetFieldID(env, cls, "zoneCoord", "I");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Zone field ID error.");
        return;
    }
    coords.zone = (long)(*env)->GetIntField(env, jCoords, fid);
   
    fid = (*env)->GetFieldID(env, cls, "hemisphere", "C");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Hemisphere field ID error.");
        return;
    }
    coords.hemisphere = (char)(*env)->GetCharField(env, jCoords, fid);

    if (Set_UTM_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "UTM coordinates could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetVanDerGrintenParams(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Van_der_Grinten_Parameters params;
    jclass cls;
    jmethodID cid;


    if (Get_Van_der_Grinten_Params(state, direction, &params))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Van der Grinten parameters");
        return NULL;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/VanDerGrinten");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: VanDerGrinten class not found.");
        return NULL;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DDD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: VanDerGrinten method id not found.");
        return NULL;
    }

    obj = (*env)->NewObject(env, cls, cid, params.central_meridian, params.false_easting, params.false_northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: VanDerGrinten object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetVanDerGrintenParams(JNIEnv *env, jobject obj, jint state, jint direction, jobject jParams)
{
    Van_der_Grinten_Parameters params;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jParams);

    fid = (*env)->GetFieldID(env, cls, "central_meridian", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Central meridian field ID error.");
        return;
    }
    params.central_meridian = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False easting field ID error.");
        return;
    }
    params.false_easting = (*env)->GetDoubleField(env, jParams, fid);

    fid = (*env)->GetFieldID(env, cls, "false_northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: False northing field ID error.");
        return;
    }
    params.false_northing = (*env)->GetDoubleField(env, jParams, fid);
   
    if (Set_Van_der_Grinten_Params(state, direction, params))
        throwException(env, "geotrans/jni/GeotransError", "Van der Grinten parameters could not be set");
}


JNIEXPORT jobject JNICALL Java_geotrans_jni_JNIEngine_JNIGetVanDerGrintenCoordinates(JNIEnv *env, jobject obj, jint state, jint direction)
{
    Van_der_Grinten_Tuple coords;
    jclass cls;
    jmethodID cid;


    if (Get_Van_der_Grinten_Coordinates(state, direction, &coords))
    {
        throwException(env, "geotrans/jni/GeotransError", "Error getting Van der Grinten coordinates");
        return obj;
    }

    cls = (*env)->FindClass(env, "geotrans/projections/VanDerGrinten");
    if(cls == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: VanDerGrinten class not found.");
        return obj;
    }

    cid = (*env)->GetMethodID(env, cls, "<init>", "(DD)V");
    if(cid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: VanDerGrinten method id not found.");
        return obj;
    }

    obj = (*env)->NewObject(env, cls, cid, coords.easting, coords.northing);
    if (obj == NULL)
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: VanDerGrinten object could not be created.");

    return obj;
}


JNIEXPORT void JNICALL Java_geotrans_jni_JNIEngine_JNISetVanDerGrintenCoordinates(JNIEnv *env, jobject obj, jint state, jint direction, jobject jCoords)
{
    Van_der_Grinten_Tuple coords;
    jclass cls;
    jfieldID fid;

    cls = (*env)->GetObjectClass(env, jCoords);

    fid = (*env)->GetFieldID(env, cls, "easting", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Easting field ID error.");
        return;
    }
    coords.easting = (*env)->GetDoubleField(env, jCoords, fid);

    fid = (*env)->GetFieldID(env, cls, "northing", "D");
    if (fid == NULL)
    {
        throwException(env, "geotrans/jni/JNIException", "JNI Exception: Northing field ID error.");
        return;
    }
    coords.northing = (*env)->GetDoubleField(env, jCoords, fid);
   
    if (Set_Van_der_Grinten_Coordinates(state, direction, coords))
        throwException(env, "geotrans/jni/GeotransError", "VanDerGrinten coordinates could not be set");
}


